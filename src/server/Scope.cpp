/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 10:20:17 by nmathieu         ###   ########.fr       */
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
        root(),
        added_methods(),
        removed_methods(),
        children(),
        outcomes(),
        catchers()
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


    static bool regular_file_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    static bool directory_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFDIR);
    }

    static bool try_respond_with_outcome(
        const Outcome& outcome,
        std::string& root,
        const char* uri,
        const char* location,
        Response& response
    )
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow;

        if (outcome.get_variant() == Outcome::File)
        {
            ft::log::trace()
                << "file "
                << ft::log::Color::Dim
                << outcome.get_file()
                << ft::log::Color::Reset
                << "`: ";

            size_t  original_size = root.size();
            root.append((char*)outcome.get_file().data(), outcome.get_file().size());

            if (!regular_file_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "file not found"
                    << ft::log::Color::Reset
                    << std::endl;

                root.resize(original_size);
                response.set_status(StatusCode::NotFound);
                return (false);
            }

            ft::log::trace()
                << "`"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "` found!"
                << std::endl;

            response.set_status(StatusCode::Ok);
            response.set_body(new FileBody(root.c_str()));
            root.resize(original_size);
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Explore)
        {
            ft::log::trace()
                << "explore"
                << ft::log::Color::Reset
                << "`: ";

            size_t  original_size = root.size();
            root.append(uri + strlen(location));

            if (!regular_file_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "file not found"
                    << ft::log::Color::Reset
                    << std::endl;

                root.resize(original_size);
                response.set_status(StatusCode::NotFound);
                return (false);
            }

            ft::log::trace()
                << "`"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "` found!"
                << std::endl;

            response.set_status(StatusCode::Ok);
            response.set_body(new FileBody(root.c_str()));
            root.resize(original_size);
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Throw)
        {
            ft::log::trace()
                << "throw "
                << ft::log::Color::Dim
                << outcome.get_throw().code
                << ft::log::Color::Reset
                << "`: done!"
                << std::endl;

            response.set_body(0);
            response.set_status(outcome.get_throw());
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Index)
        {
            ft::log::trace()
                << "index"
                << ft::log::Color::Reset
                << "`: ";

            size_t  original_size = root.size();
            root.append(uri + strlen(location));

            if (*root.rend() == '/')
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "not a directory"
                    << ft::log::Color::Reset
                    << std::endl;
                root.resize(original_size);
                return (false);
            }

            if (!directory_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "directory not found"
                    << ft::log::Color::Reset
                    << std::endl;
                root.resize(original_size);
                return (false);
            }

            ft::log::trace()
                << "generating index for `"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "`"
                << std::endl;

            response.set_body(new GeneratedIndex(root.c_str(), uri));
            response.set_status(StatusCode::Ok);
            root.resize(original_size);
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
        size_t  original_location_size = responding.location.size();
        Methods original_methods = responding.methods;
        ft::Str original_root = responding.root;

        responding.location.append((char*)this->location.data(), this->location.size());
        responding.methods |= this->added_methods;
        responding.methods &= ~this->removed_methods;

        if (!this->root.empty())
            responding.root = this->root;

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
                    responding.root = original_root;
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
            responding.root = original_root;
            return (false);
        }

        if (
            this->exact_location
            && responding.location.size() != request.uri.size()
        )
        {
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            responding.root = original_root;
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
            responding.root = original_root;
            return (false);
        }

        // Check if we have a defined outcome for this request.
        {
            std::string root_tmp((char*)responding.root.data(), responding.root.size());

            std::vector<Outcome>::const_iterator it = this->outcomes.begin();
            while (it != this->outcomes.end())
            {
                if (
                    try_respond_with_outcome(
                        *it,
                        root_tmp,
                        request.uri.c_str(),
                        responding.location.c_str(),
                        response
                    )
                )
                {
                    responding.methods = original_methods;
                    responding.location.resize(original_location_size);
                    responding.root = original_root;
                    return (true);
                }

                it++;
            }
        }

        // =============================
        //  We Were Not Able To Respond
        // =============================

        responding.methods = original_methods;
        responding.location.resize(original_location_size);
        responding.root = original_root;
        return (false);
    }
}
