/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:25:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 14:25:54 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringResponse.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"
#include "ft/Slice.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

namespace ws
{
    StringResponse::StringResponse(const std::string& s) :
        _page(s),
        _sent(0),
        _sent_content_length(false)
    {}

    bool StringResponse::next_header_field(std::string& key, std::string& value)
    {
        if (this->_page.size() == 0 || this->_sent_content_length)
            return (false);
        this->_sent_content_length = true;
        key = "Content-Length";
        uint8_t buf[32];
        value = std::string((char*)buf, ft::write_int(this->_page.size(), buf));
        return (true);
    }

    Connection::Flow StringResponse::send_more_body_through(Connection& connection)
    {
        this->_sent += connection.send_some(ft::Str((uint8_t*)this->_page.data() + this->_sent, this->_page.size() - this->_sent));

        ft::log::details()
            << ft::log::Color::Dim
            << "sending string: "
            << this->_sent << "/" << this->_page.size() << " bytes (" << (100.0 * (double)this->_sent / (double)this->_page.size()) << "%)"
            << ft::log::Color::Reset
            << std::endl;

        if (this->_sent != this->_page.size())
            return (Connection::Continue);
        else
            return (Connection::Close);
    }
}
