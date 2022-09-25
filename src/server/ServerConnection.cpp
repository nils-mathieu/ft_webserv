/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:56:39 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 12:26:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "ServerConnection.hpp"
#include "StringBody.hpp"
#include "FileBody.hpp"
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
        _response(),
        _header_state(0)
    {
        ft::log::info() << " 📦 packet recieved at " << address << std::endl;
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
                << ft::log::Color::Yellow
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

            this->_response.set_status(StatusCode::InternalServerError);

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
            Responding  responding;

            if (!server_block->try_respond(this->_header, responding, this->_response))
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
            ft::log::info()
                << "      "
                << ft::log::Color::Red
                << "error"
                << ft::log::Color::Reset
                << ": ";
            e.write(ft::log::info());
            ft::log::info() << std::endl;

            this->_response.set_status(StatusCode::InternalServerError);
            this->_response.set_body(0);
        }
        catch (const std::exception& e)
        {
            ft::log::info()
                << "      "
                << ft::log::Color::Red
                << "error"
                << ft::log::Color::Reset
                << ": " << e.what()
                << std::endl;

            this->_response.set_status(StatusCode::InternalServerError);
            this->_response.set_body(0);
        }

        // If the above logic was not able to fill to body of the request,
        // provide a simple default error page.
        if (!this->_response.has_body())
        {
            ft::log::trace()
                << ft::log::Color::Dim
                << "      response body empty: generating error page"
                << ft::log::Color::Reset
                << std::endl;

            std::string contents = page::default_error(this->_response.get_status());
            this->_response.set_body(new StringBody(contents));
        }

        return (Connection::Close);
    }

    Connection::Flow ServerConnection::recieved_more_body(ft::Str body_part)
    {
        (void)body_part;
        return (Connection::Close);
    }

    StatusCode ServerConnection::send_status_code()
    {
        ft::log::info()
            << "   📡 "
            << ft::log::Color::Green
            << this->_response.get_status().code
            << " "
            << ft::log::Color::Dim
            << this->_response.get_status().name()
            << ft::log::Color::Reset
            << std::endl;
        return (this->_response.get_status());
    }

    bool ServerConnection::send_next_header(std::string& key, std::string& value)
    {
        while (true)
        {
            if (this->_header_state == 0)
            {

                this->_header_state++;
                size_t  length = this->_response.get_body_length();
                if (length)
                {
                    uint8_t buf[32];
                    key = "Content-Length";
                    value = std::string((char*)buf, ft::write_int(length, buf));
                    return (true);
                }
            }
            else
                return (false);
        }
    }

    Connection::Flow ServerConnection::send_more_body()
    {
        if (this->_response.send_body_through(*this))
            return (Connection::Continue);
        else
        {
            ft::log::info()
                << ft::log::Color::Bold
                << ft::log::Color::Green
                << "      upload done!"
                << ft::log::Color::Reset
                << std::endl << std::endl;
            return (Connection::Close);
        }
    }
}
