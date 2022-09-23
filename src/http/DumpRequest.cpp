/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:52:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 04:46:46 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DumpRequest.hpp"

#include <iostream>

namespace ws
{
    DumpRequest::DumpRequest(int raw_fd) :
        HttpConnection(raw_fd),
        _size(0)
    {}

    Connection::Flow DumpRequest::parsed_invalid_http()
    {
        std::cout << "found invalid HTTP in the request" << std::endl;
        return (Connection::Close);
    }

    Connection::Flow DumpRequest::parsed_method(Method method)
    {
        std::cout << "Method: " << method << std::endl;
        return (Connection::Continue);
    }

    Connection::Flow DumpRequest::parsed_uri(ft::Str uri)
    {
        std::cout << "URI: " << uri << std::endl;
        return (Connection::Continue);
    }

    Connection::Flow DumpRequest::parsed_http_version(ft::Str http_version)
    {
        std::cout << "HTTP Version: " << http_version << std::endl;

        if (http_version != "HTTP/1.1")
        {
            std::cout << "unsupported HTTP version, aborting...";
            return (Connection::Close);
        }

        return (Connection::Continue);
    }

    Connection::Flow DumpRequest::parsed_header_field(ft::Str key, ft::Str value)
    {
        std::cout << "| " << key << ": " << value << std::endl;

        if (key == "Content-Length")
        {
            const uint8_t* s = ft::parse_str(value, this->_size);

            if (s == 0 || s != value.end())
                this->_size = 0;
        }

        return (Connection::Continue);
    }

    Connection::Flow DumpRequest::parsed_header()
    {
        if (this->_size == 0)
        {
            std::cout << "No Body" << std::endl;
            return (Connection::Close);
        }
        else
        {
            std::cout << std::endl;
            return (Connection::Continue);
        }
    }

    Connection::Flow DumpRequest::recieved_more_body(ft::Str body_part)
    {
        if (body_part.size() >= this->_size)
            body_part = body_part.slice(0, this->_size);
        this->_size -= body_part.size();
        std::cout << body_part << std::endl;
        if (this->_size == 0)
            return (Connection::Close);
        else
            return (Connection::Continue);
    }

    StatusCode DumpRequest::send_status_code()
    {
        return StatusCode::Ok;
    }

    bool DumpRequest::send_next_header(ft::Str& key, ft::Str& value)
    {
        (void)key;
        (void)value;
        return false;
    }

    Connection::Flow DumpRequest::send_more_body()
    {
        return Connection::Close;
    }
}
