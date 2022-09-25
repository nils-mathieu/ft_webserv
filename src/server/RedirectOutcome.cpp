/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectOutcome.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:30:34 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:21:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectOutcome.hpp"
#include "ft/log.hpp"
#include "RedirectResponse.hpp"
#include "ft/Color.hpp"

namespace ws
{
    RedirectOutcome::RedirectOutcome(ft::Str location) :
        _location(location)
    {}

    bool RedirectOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        (void)request;

        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "redirect "
            << ft::log::Color::Dim
            << this->_location
            << ft::log::Color::Reset
            << "`: success!"
            << std::endl;

        responding.status = StatusCode::MovedPermanently;
        responding.set_response(new RedirectResponse(this->_location));
        return (true);
    }
}
