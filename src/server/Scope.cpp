/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:09:22 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"
#include "FileResponse.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "page.hpp"
#include "StringResponse.hpp"

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
        outcomes()
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
        const char* uri,
        Responding& responding
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

            std::string root = std::string((char*)responding.root.data(), responding.root.size());
            root.append((char*)outcome.get_file().data(), outcome.get_file().size());

            if (!regular_file_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "`"
                    << root
                    << "` not found"
                    << ft::log::Color::Reset
                    << std::endl;

                responding.status = StatusCode::NotFound;
                responding.set_response(0);
                return (false);
            }

            ft::log::trace()
                << "`"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "` found!"
                << std::endl;

            responding.status = StatusCode::Ok;
            responding.set_response(new FileResponse(root.c_str()));
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Explore)
        {
            ft::log::trace()
                << "explore"
                << ft::log::Color::Reset
                << "`: ";

            std::string root = std::string((char*)responding.root.data(), responding.root.size());
            root.append(uri + responding.location.size());

            if (!regular_file_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "`"
                    << root
                    << "` not found"
                    << ft::log::Color::Reset
                    << std::endl;

                responding.status = StatusCode::NotFound;
                responding.set_response(0);
                return (false);
            }

            ft::log::trace()
                << "`"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "` found!"
                << std::endl;

            responding.status = StatusCode::Ok;
            responding.set_response(new FileResponse(root.c_str()));
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Index)
        {
            ft::log::trace()
                << "index"
                << ft::log::Color::Reset
                << "`: ";

            std::string root = std::string((char*)responding.root.data(), responding.root.size());
            root.append(uri + responding.location.size());

            if (*root.rend() == '/')
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "not a directory"
                    << ft::log::Color::Reset
                    << std::endl;
                return (false);
            }

            if (!directory_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "`"
                    << root
                    << "` not found"
                    << ft::log::Color::Reset
                    << std::endl;
                responding.status = StatusCode::NotFound;
                responding.set_response(0);
                return (false);
            }

            ft::log::trace()
                << "generating index for `"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "`"
                << std::endl;

            std::string generated_index = page::generated_index(root.c_str(), uri);

            responding.status = StatusCode::Ok;
            responding.set_response(new StringResponse(generated_index));
            return (true);
        }
        else if (outcome.get_variant() == Outcome::Catch)
        {
            ft::log::trace()
                << "catch "
                << ft::log::Color::Dim
                << outcome.get_catch_code().code
                << ft::log::Color::Reset
                << "`: ";


            if (outcome.get_catch_code().code != responding.status.code)
            {
                ft::log::trace()
                    << "not right status ("
                    << responding.status.code
                    << ")"
                    << std::endl;
                return (false);
            }

            // CAUGHT IN 4K!!
            std::string root = std::string((char*)responding.root.data(), responding.root.size());
            root.append((char*)outcome.get_catch_page().data(), outcome.get_catch_page().size());

            if (!regular_file_exists(root.c_str()))
            {
                ft::log::trace()
                    << ft::log::Color::Red
                    << "`"
                    << root
                    << "` not found"
                    << ft::log::Color::Reset
                    << std::endl;

                responding.status = StatusCode::NotFound;
                responding.set_response(0);
                return (false);
            }

            ft::log::trace()
                << "`"
                << ft::log::Color::Yellow
                << root
                << ft::log::Color::Reset
                << "` found"
                << std::endl;

            responding.set_response(new FileResponse(root.c_str()));
            StatusCode code = outcome.get_catch_new_code();
            if (code.code != UINT32_MAX)
                responding.status = code;
            return (true);
        }
        else
        {
            responding.status = StatusCode::InternalServerError;
            responding.set_response(0);
            return (false);
        }
    }

    bool Scope::try_respond(
        const RequestHeader& request,
        Responding& responding
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
                if (it->try_respond(request, responding))
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
            std::vector<Outcome>::const_iterator it = this->outcomes.begin();
            while (it != this->outcomes.end())
            {
                if (
                    try_respond_with_outcome(
                        *it,
                        request.uri.c_str(),
                        responding
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
