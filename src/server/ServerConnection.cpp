/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:56:39 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 00:09:37 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "ServerConnection.hpp"

namespace ws
{
    ServerConnection::ServerConnection(
        int raw_fd,
        const Config& config,
        SocketAddress address
    ) :
        HttpConnection(raw_fd),
        _config(config),
        _address(address),
        _header()
    {
        ft::log::info() << " 📦 packet recieved at " << address << std::endl;
        (void)_config;
    }

    void ServerConnection::parsed_invalid_http()
    {
        ft::log::info()
            << "    💣 "
            << ft::log::Color::Red
            << "packet is not valid HTTP"
            << ft::log::Color::Reset
            << std::endl;
    }

    Connection::Flow ServerConnection::parsed_method(Method method)
    {
        this->_header.method = method;
        return Connection::Continue;
    }

    Connection::Flow ServerConnection::parsed_uri(ft::Str uri)
    {
        this->_header.uri = std::string((char*)uri.data(), uri.size());
        return Connection::Continue;
    }

    Connection::Flow ServerConnection::parsed_http_version(ft::Str http_version)
    {
        if (http_version != "HTTP/1.1")
        {
            ft::log::info()
                << "    💣 "
                << ft::log::Color::Red
                << "HTTP version is '"
                << http_version
                << "'"
                << ft::log::Color::Reset
                << std::endl;
            return Connection::Close;
        }
        else
        {
            return Connection::Continue;
        }
    }

    Connection::Flow ServerConnection::parsed_header_field(ft::Str key, ft::Str value)
    {
        if (key == "Host")
            this->_header.host = std::string((char*)value.data(), value.size());

        return (Connection::Continue);
    }

    Connection::Flow ServerConnection::parsed_header()
    {
        ft::log::info()
            << "      "
            << ft::log::Color::Green
            << this->_header.method << " "
            << ft::log::Color::BrightYellow
            << this->_header.uri
            << ft::log::Color::Reset
            << " for "
            << ft::log::Color::Dim
            << this->_header.host
            << ft::log::Color::Reset
            << std::endl;

        const ServerBlock* server_block = this->_config.get_server_block(this->_address, ft::make_str(this->_header.host.data(), this->_header.host.size()));

        if (!server_block)
        {
            ft::log::info()
                << "   💣 "
                << ft::log::Color::Red
                << "no server for this request"
                << ft::log::Color::Reset
                << std::endl;
            return (Connection::Close);
        }

        ft::log::trace()
            << "      selected server "
            << ft::log::Color::Yellow
            << server_block->label
            << ft::log::Color::Reset
            << " to serve this request"
            << std::endl;

        return (Connection::Close);
    }

    Connection::Flow ServerConnection::recieved_more_body(ft::Str body_part)
    {
        (void)body_part;
        return (Connection::Close);
    }

    StatusCode ServerConnection::send_status_code()
    {
        return (StatusCode::Ok);
    }

    bool ServerConnection::send_next_header(ft::Str& key, ft::Str& value)
    {
        (void)key;
        (void)value;
        return (false);
    }

    Connection::Flow ServerConnection::send_more_body()
    {
        return (Connection::Close);
    }
}
