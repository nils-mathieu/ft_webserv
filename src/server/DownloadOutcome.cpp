/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DownloadOutcome.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:18:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:52:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "DownloadOutcome.hpp"
#include "DownloadBody.hpp"

#include <unistd.h>
#include <fcntl.h>

namespace ws
{
    bool DownloadOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "download"
            << ft::log::Color::Reset
            << "`: ";

        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append(request.uri.c_str() + responding.location.size());

        if (request.length == 0)
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "can't download file of size 0"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::LengthRequired;
            return (false);
        }

        // Create the file in advance to check whether the operation is
        // actually possible.
        int fd = open(root.c_str(), O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
        if (fd == -1)
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "can't create `"
                << root
                << "`"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::Conflict;
            return (false);
        }
        close(fd);

        ft::log::trace()
            << "created `"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "`"
            << std::endl;

        responding.status = StatusCode::Ok;
        responding.set_response(new DownloadBody(root.c_str()));
        return (true);
    }
}
