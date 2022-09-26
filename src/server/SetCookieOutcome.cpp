/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetCookieOutcome.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:34:30 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 12:04:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SetCookieOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

#include <utility>

namespace ws
{
    SetCookieOutcome::SetCookieOutcome(ft::Str name, ft::Str value) :
        _name(name),
        _value(value)
    {}

    bool SetCookieOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        (void)request;
        std::string s;
        s.append((char*)this->_name.data(), this->_name.size());
        s.push_back('=');
        s.append((char*)this->_value.data(), this->_value.size());
        responding.header_fields.push_back(std::make_pair("Set-Cookie", s));

        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "set-cookie "
            << ft::log::Color::Dim
            << this->_name
            << "="
            << this->_value
            << ft::log::Color::Reset
            << ": success!"
            << std::endl;

        return (false);
    }
}
