/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:56:39 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 19:38:16 by nmathieu         ###   ########.fr       */
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
        _responding(address),
        _sent_header_fields(0)
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

        this->_responding.set_response(new StringResponse(page::default_error(StatusCode::BadRequest)));
        this->_responding.status = StatusCode::BadRequest;
    }

    Connection::Flow ServerConnection::parsed_method(Method method)
    {
        this->_header.method = method;
        return Connection::Continue;
    }

    Connection::Flow ServerConnection::parsed_uri(ft::Str uri)
    {
        ft::Str path;
        ft::Str query;

        // Find an eventual '?' character.
        if (uri.split_once(path, query, '?'))
        {
            this->_header.uri = std::string((char*)path.data(), path.size());
            this->_header.query = std::string((char*)query.data() + 1, query.size() - 1);
        }
        else
        {
            this->_header.uri = std::string((char*)uri.data(), uri.size());
        }
        return Connection::Continue;
    }

    Connection::Flow ServerConnection::parsed_http_version(ft::Str http_version)
    {
        if (http_version != "HTTP/1.1")
        {
            ft::log::info()
                << "   💣 "
                << ft::log::Color::Red
                << "HTTP version is '"
                << http_version
                << "'"
                << ft::log::Color::Reset
                << std::endl;
            this->_responding.set_response(new StringResponse(page::default_error(StatusCode::BadRequest)));
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
        ft::log::details()
            << ft::log::Color::Dim
            << key
            << ": "
            << value
            << std::endl;
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
        else if (key == "Cookie")
        {
            ft::Str name;
            ft::Str val;

            size_t begin = 0;
            for (size_t i = 0; i < value.size(); i++)
            {
                if (value[i] == '=')
                {
                    name = value.slice(begin, i);
                    begin = i + 1;
                }
                else if (value[i] == ';')
                {
                    val = value.slice(begin, i);
                    begin = i + 1;
                    this->_header.cookies[std::string((char*)name.data(), name.size())] = std::string((char*)val.data(), val.size());
                }
            }
            val = value.slice(begin, value.size());
            this->_header.cookies[std::string((char*)name.data(), name.size())] = std::string((char*)val.data(), val.size());
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
            << this->_header.uri;
        if (!this->_header.query.empty())
        {
            ft::log::info()
               << ft::log::Color::Dim
                << "?" << this->_header.query;
        }
        ft::log::info()
            << ft::log::Color::Reset
            << " for "
            << ft::log::Color::Dim
            << this->_header.host
            << ft::log::Color::Reset
            << std::endl;

        {
            std::map<std::string, std::string>::const_iterator it = this->_header.cookies.begin();
            while (it != this->_header.cookies.end())
            {
                ft::log::trace()
                    << ft::log::Color::Blue
                    << ft::log::Color::Dim
                    << "        cookie " << it->first << "=" << it->second
                    << ft::log::Color::Reset
                    << std::endl;
                it++;
            }
        }

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

        if (!this->_responding.get_response())
        {
            ft::log::trace()
                << "      response body empty: generating default page"
                << std::endl;

            std::string contents = page::default_error(this->_responding.status);
            this->_responding.set_response(new StringResponse(contents));
        }

        if (this->_header.length == 0)
            return (Connection::Close);
        else
            return (Connection::Continue);
    }

    Connection::Flow ServerConnection::recieved_more_body(ft::Str body_part)
    {
        return (this->_responding.get_response()->recieve_body(body_part, this->_header));
    }

    StatusCode ServerConnection::send_status_code()
    {
        ft::log::info()
            << "   📡 "
            << ft::log::Color::Green
            << ft::log::Color::Bold
            << this->_responding.status.code
            << " "
            << ft::log::Color::Reset
            << ft::log::Color::Green
            << ft::log::Color::Dim
            << "("
            << this->_responding.status.name()
            << ")"
            << ft::log::Color::Reset
            << std::endl;

        return (this->_responding.get_response()->catch_status_code(this->_responding.status));
    }

    bool ServerConnection::send_next_header(std::string& key, std::string& value)
    {
        if (this->_sent_header_fields < this->_responding.header_fields.size())
        {
            key = this->_responding.header_fields[this->_sent_header_fields].first;
            value = this->_responding.header_fields[this->_sent_header_fields].second;
            this->_sent_header_fields++;
            return (true);
        }
        else
        {
            return this->_responding.get_response()->next_header_field(key, value);
        }
    }

    Connection::Flow ServerConnection::send_more_body()
    {
        if (this->_responding.get_response()->send_more_body_through(*this) == Connection::Continue)
            return (Connection::Continue);

        ft::log::trace()
            << "      upload done!"
            << std::endl << std::endl;
        return (Connection::Close);
    }
}
