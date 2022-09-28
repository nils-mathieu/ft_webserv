/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetPayloadLengthOutcome.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:06:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:19:36 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SetPayloadLengthOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

namespace ws
{
    SetPayloadLengthOutcome::SetPayloadLengthOutcome(size_t max_length) :
        _max_length(max_length)
    {}

    bool SetPayloadLengthOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "max-payload-length "
            << ft::log::Color::Dim
            << this->_max_length
            << ft::log::Color::Reset
            << "`: ";

        if (request.length >= this->_max_length)
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "payload is too large (" << request.length << ")"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::PayloadTooLarge;
            return (true);
        }
        else
        {
            ft::log::trace()
                << "passed"
                << ft::log::Color::Dim
                << " (" << request.length << ")"
                << ft::log::Color::Reset
                << "!"
                << std::endl;
            return (false);
        }
    }
}
