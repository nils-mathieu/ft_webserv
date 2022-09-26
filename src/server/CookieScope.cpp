/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CookieScope.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:03:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 11:52:52 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CookieScope.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

namespace ws
{
    CookieScope::CookieScope(ft::Str name, ft::Str value) :
        Scope(),
        _name((char*)name.data(), name.size()),
        _value((char*)value.data(), value.size())
    {}

    bool CookieScope::try_respond(const RequestHeader& request, Responding& responding) const
    {
        ft::log::trace()
            << "      cookie scope: ";

        std::map<std::string, std::string>::const_iterator it = request.cookies.find(this->_name);
        if (it == request.cookies.end())
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "`"
                << this->_name
                << "`"
                << " not present"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::Unauthorized;
            return (false);
        }

        if (it->second != this->_value)
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "`"
                << this->_name
                << "`"
                << " = "
                << "`"
                << it->second
                << "`"
                << ft::log::Color::Dim
                << " (expected `"
                << this->_value
                << "`)"
                << ft::log::Color::Reset
                << std::endl;
            responding.status = StatusCode::Unauthorized;
            return (false);
        }

        ft::log::trace()
            << "success!"
            << std::endl;

        return (this->Scope::try_respond(request, responding));
    }
}
