/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexOutcome.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:26:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:21:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IndexOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "StringResponse.hpp"
#include "page.hpp"

#include <sys/stat.h>

namespace ws
{
    static bool directory_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFDIR);
    }

    bool IndexOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "index"
            << ft::log::Color::Reset
            << "`: ";

        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append(request.uri.c_str() + responding.location.size());

        if (*root.rbegin() != '/')
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
            return (false);
        }

        ft::log::trace()
            << "generating index for `"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "`"
            << std::endl;

        std::string generated_index = page::generated_index(root.c_str(), request.uri.c_str());

        responding.status = StatusCode::Ok;
        responding.set_response(new StringResponse(generated_index));
        return (true);
    }
}
