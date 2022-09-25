/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:56:39 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:36:03 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "ServerConnection.hpp"
#include "StringResponse.hpp"
#include "FileResponse.hpp"
#include "page.hpp"

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
        _header(),
        _responding()
    {
        ft::log::info() << " 📦 packet recieved at " << address << std::endl;
    }

    void ServerConnection::parsed_invalid_http()
    {
        ft::log::info()
            << "   💣 "
            << ft::log::Color::Red
            << "packet is not valid HTTP"
            << ft::log::Color::Reset
            << std::endl;

        this->_responding.status = StatusCode::BadRequest;
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
                << "   💣 "
                << ft::log::Color::Yellow
                << "HTTP version is '"
                << http_version
                << "'"
                << ft::log::Color::Reset
                << std::endl;
            this->_responding.status = StatusCode::BadRequest;
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
        else if (key == "Content-Length")
        {
            if (!ft::parse_str(value, this->_header.length))
            {
                this->_responding.status = StatusCode::BadRequest;
                return (Connection::Close);
            }
        }
        return (Connection::Continue);
    }

    Connection::Flow ServerConnection::parsed_header()
    {
        // =======================
        //  Select A Server Block
        // =======================

        ft::log::info()
            << "   📢 "
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

        const ServerBlock* server_block = this->_config.get_server_block(
            this->_address,
            ft::make_str(
                this->_header.host.data(),
                this->_header.host.size()
            )
        );

        // This should actually never happen. A socket listening for that ID
        // wouldn't have been opened if it wasn't for at least one server.
        if (!server_block)
        {
            ft::log::info()
                << "   💣 "
                << ft::log::Color::Red
                << "no server for this request"
                << ft::log::Color::Reset
                << std::endl;

            this->_responding.status = StatusCode::InternalServerError;

            return (Connection::Close);
        }

        ft::log::trace()
            << "      selected `"
            << ft::log::Color::Yellow
            << server_block->label
            << ft::log::Color::Reset
            << "` to serve this request"
            << std::endl;

        // =====================================================
        //  Use The Selected Server Block To Server The Request
        // =====================================================

        try
        {
            if (!server_block->try_respond(this->_header, this->_responding))
            {
                // The server block could not respond to the request.
                // This is an configuration error.
                ft::log::info()
                    << "   💣 "
                    << ft::log::Color::Red
                    << "server could not serve this request"
                    << ft::log::Color::Reset
                    << std::endl;
            }
        }
        catch (const ft::Exception& e)
        {
            ft::log::error()
                << "      "
                << ft::log::Color::Red
                << "error"
                << ft::log::Color::Reset
                << ": ";
            e.write(ft::log::error());
            ft::log::error() << std::endl;

            this->_responding.status = StatusCode::InternalServerError;
        }
        catch (const std::exception& e)
        {
            ft::log::error()
                << "      "
                << ft::log::Color::Red
                << "error"
                << ft::log::Color::Reset
                << ": " << e.what()
                << std::endl;

            this->_responding.status = StatusCode::InternalServerError;
        }

        if (this->_responding.get_reciever())
            return (Connection::Continue);
        else
            return (Connection::Close);
    }

    Connection::Flow ServerConnection::recieved_more_body(ft::Str body_part)
    {
        // The reciever shouldn't be null because we checked in `parsed_header`
        // that it wasn't. The connection would've been closed already if it
        // wasn't the case.
        return (this->_responding.get_reciever()->recieve_body(body_part, this->_header));
    }

    StatusCode ServerConnection::send_status_code()
    {
        if (!this->_responding.get_response())
        {
            ft::log::trace()
                << ft::log::Color::Dim
                << "      response body empty: generating error page"
                << ft::log::Color::Reset
                << std::endl;

            std::string contents = page::default_error(this->_responding.status);
            this->_responding.set_response(new StringResponse(contents));
        }

        ft::log::info()
            << "   📡 "
            << ft::log::Color::Green
            << this->_responding.status.code
            << " "
            << ft::log::Color::Dim
            << this->_responding.status.name()
            << ft::log::Color::Reset
            << std::endl;

        return (this->_responding.status);
    }

    bool ServerConnection::send_next_header(std::string& key, std::string& value)
    {
        return this->_responding.get_response()->next_header_field(key, value);
    }

    Connection::Flow ServerConnection::send_more_body()
    {
        if (this->_responding.get_response()->send_more_body_through(*this))
            return (Connection::Continue);

        ft::log::info()
            << ft::log::Color::Bold
            << ft::log::Color::Green
            << "      upload done!"
            << ft::log::Color::Reset
            << std::endl << std::endl;
        return (Connection::Close);
    }
}
