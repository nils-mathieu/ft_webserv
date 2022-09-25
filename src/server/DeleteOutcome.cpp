/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteOutcome.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:11:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:14:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

#include <unistd.h>

namespace ws
{
    bool DeleteOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "delete"
            << ft::log::Color::Reset
            << "`: ";

        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append(request.uri.c_str() + responding.location.size());

        // Create the file in advance to check whether the operation is
        // actually possible.
        if (unlink(root.c_str()) == -1)
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "can't delete `"
                << root
                << "`"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::Conflict;
            return (false);
        }

        ft::log::trace()
            << "deleted `"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "`"
            << std::endl;

        responding.status = StatusCode::Ok;
        return (true);
    }
}
