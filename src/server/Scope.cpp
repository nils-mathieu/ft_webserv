/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 08:51:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"
#include "FileBody.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "GeneratedIndex.hpp"

#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

namespace ws
{
    Scope::Scope() :
        exact_location(false),
        location(),
        added_methods(),
        removed_methods(),
        children(),
        outcomes(),
        catchers(),
        generate_index(false)
    {}

    static bool starts_with(const char* a, const char* b)
    {
        while (*a && *b && *a == *b)
        {
            a++;
            b++;
        }
        return (*b == '\0');
    }


    static bool can_open_file(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    static bool try_respond_with_outcome(
        const Outcome& outcome,
        const char* uri,
        const char* location,
        Response& response
    )
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow;
        if (outcome.get_variant() == Outcome::File)
            ft::log::trace()
                << "file "
                << ft::log::Color::Dim
                << outcome.get_file();
        else if (outcome.get_variant() == Outcome::Root)
            ft::log::trace()
                << "root "
                << ft::log::Color::Dim
                << outcome.get_root();
        else if (outcome.get_variant() == Outcome::Throw)
            ft::log::trace()
                << "throw "
                << ft::log::Color::Dim
                << outcome.get_throw().code;
        ft::log::trace()
            << ft::log::Color::Reset
            << "`: ";

        if (outcome.get_variant() == Outcome::File)
        {
            std::string s((char*)outcome.get_file().data(), outcome.get_file().size());

            if (!can_open_file(s.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "file not found"
                    << ft::log::Color::Reset
                    << std::endl;

                response.set_status(StatusCode::NotFound);
                return (false);
            }

            ft::log::trace() << "found!" << std::endl;

            response.set_status(StatusCode::Ok);
            response.set_body(new FileBody(s.c_str()));
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Root)
        {
            std::string s((char*)outcome.get_root().data(), outcome.get_root().size());
            if (*s.rbegin() != '/')
                s.push_back('/');
            s.append(uri + strlen(location));

            ft::log::trace()
                << ft::log::Color::Yellow
                << s
                << ft::log::Color::Reset
                << ": ";

            if (!can_open_file(s.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "file not found"
                    << ft::log::Color::Reset
                    << std::endl;

                response.set_status(StatusCode::NotFound);
                return (false);
            }

            ft::log::trace() << "found!" << std::endl;

            response.set_status(StatusCode::Ok);
            response.set_body(new FileBody(s.c_str()));
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Throw)
        {
            ft::log::trace() << "done!" << std::endl;

            response.set_body(0);
            response.set_status(outcome.get_throw());
            return (true);
        }
        else
        {
            return (false);
        }
    }

    bool Scope::try_respond(
        const RequestHeader& request,
        Responding& responding,
        Response& response
    ) const
    {
        // This is kept around to truncate the aggregated location later.
        size_t original_location_size = responding.location.size();
        Methods original_methods = responding.methods;

        responding.location.append((char*)this->location.data(), this->location.size());
        responding.methods |= this->added_methods;
        responding.methods &= ~this->removed_methods;

        // ==========================================
        //  Check If One Of The Children Can Respond
        // ==========================================

        {
            std::vector<Scope>::const_iterator  it = this->children.begin();
            while (it != this->children.end())
            {
                if (it->try_respond(request, responding, response))
                {
                    responding.location.resize(original_location_size);
                    responding.methods = original_methods;
                    return (true);
                }

                it++;
            }
        }

        // ========================
        //  Try To Respond Ourself
        // ========================

        // ... if we are allowed to!
        if (!starts_with(request.uri.c_str(), responding.location.c_str()))
        {
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            return (false);
        }

        if (
            this->exact_location
            && responding.location.size() != request.uri.size()
        )
        {
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            return (false);
        }

        ft::log::trace()
            << "      scope `"
            << ft::log::Color::Yellow
            << responding.location
            << ft::log::Color::Reset
            << "` may respond"
            << std::endl;

        // Check if the method is allowed for this scope.
        if ((responding.methods & (Methods)request.method) == 0)
        {
            ft::log::trace()
                << "        method `"
                << ft::log::Color::Red
                << request.method
                << ft::log::Color::Reset
                << "` not allowed" << std::endl
                << "        "
                << ft::log::Color::Dim
                << "allowed methods:"
                << ft::log::Color::Green
                << responding.methods
                << ft::log::Color::Reset
                << std::endl;

            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            return (false);
        }

        // Check if we have a defined outcome for this request.
        {
            std::vector<Outcome>::const_iterator it = this->outcomes.begin();
            while (it != this->outcomes.end())
            {
                if (
                    try_respond_with_outcome(
                        *it,
                        request.uri.c_str(),
                        responding.location.c_str(),
                        response
                    )
                )
                {
                    responding.methods = original_methods;
                    responding.location.resize(original_location_size);
                    return (true);
                }

                it++;
            }
        }

        // If there was no outcome, we can still generate an index.
        if (
            *request.uri.rbegin() == '/'
            && this->generate_index
        )
        {
            ft::log::trace()
                << "        can generate an index";

            response.set_status(StatusCode::Ok);
            response.set_body(new GeneratedIndex(".", request.uri.c_str()));
            return (true);
        }

        // =============================
        //  We Were Not Able To Respond
        // =============================

        responding.methods = original_methods;
        responding.location.resize(original_location_size);
        return (false);
    }
}
