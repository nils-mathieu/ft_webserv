/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExploreOutcome.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:25:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 17:41:45 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "FileResponse.hpp"
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

    bool ExploreOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "      outcome `"
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
}
