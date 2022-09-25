/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringBody.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:25:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 11:58:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringBody.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"

namespace ws
{
    StringBody::StringBody(const std::string& s) :
        _page(s),
        _sent(0)
    {}

    size_t StringBody::get_content_length() const
    {
        return this->_page.size();
    }

    bool StringBody::send_through(Connection& connection)
    {
        this->_sent += connection.send_some(ft::Str((uint8_t*)this->_page.data() + this->_sent, this->_page.size() - this->_sent));
        return (this->_sent != this->_page.size());
    }
}
