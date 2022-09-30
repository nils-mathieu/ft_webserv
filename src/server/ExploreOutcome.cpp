/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExploreOutcome.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:25:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 22:17:01 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "FileResponse.hpp"
#include "CgiResponse.hpp"
#include "ExploreOutcome.hpp"

#include <sys/stat.h>

namespace ws
{
    static bool regular_file_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    static bool has_extention(const char* s, ft::Str ext)
    {
        const char* t = strrchr(s, '/');
        if (t)
            s = t + 1;
        size_t len = strlen(s);
        if (len <= ext.size())
            return (false);
        len -= ext.size();

        size_t i = 0;
        while (i < ext.size())
        {
            if (s[len + i] != ext[i])
                return (false);
            i++;
        }
        return (true);
    }

    bool ExploreOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "explore"
            << ft::log::Color::Reset
            << "`: ";

        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append(request.uri.c_str() + responding.location.size());

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
            return (false);
        }

        ft::log::trace()
            << "`"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "` found!"
            << std::endl;

        // Check if a CGI has been registed for this request.
        size_t i = responding.cgis.size();
        while (i-- != 0)
        {
            ft::Str extension = responding.cgis[i].first;
            ft::Str script = responding.cgis[i].second;

            if (has_extention(root.c_str(), extension))
            {
                ft::log::trace()
                    << ft::log::Color::Dim
                    << "          using CGI `"
                    << ft::log::Color::Yellow
                    << script
                    << ft::log::Color::Reset << ft::log::Color::Dim
                    << "`"
                    << ft::log::Color::Reset
                    << std::endl;

                std::string script_path((char*)script.data(), script.size());

                responding.status = StatusCode::Ok;
                responding.set_response(new CgiResponse(script_path.c_str(), root.c_str(), responding, request));
                return (true);
            }
        }

        responding.status = StatusCode::Ok;
        responding.set_response(new FileResponse(root.c_str()));
        return (true);
    }
}
