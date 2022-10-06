/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:10:55 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 20:22:47 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileResponse.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"
#include "ft/Slice.hpp"
#include "ft/log.hpp"
#include "http/mime.hpp"

#include <sstream>

namespace ws
{
    const char* get_ext(const char* s)
    {
        const char* t = s + strlen(s);

        while (t-- > s)
        {
            if (*t == '/')
                return (0);
            if (*t == '.')
                return (t);
        }
        return (0);
    }

    FileResponse::FileResponse(const char* path) :
        _length(0),
        _stream(),
        _sent(0),
        _init(0),
        _buf(),
        _sent_so_far(0),
        _sent_headers(0),
        _content_type(0)
    {
        this->_stream.open(path, std::ifstream::ate | std::ifstream::binary | std::ifstream::in);

        if (this->_stream.fail())
        {
            std::stringstream s;
            s
                << "failed to open `"
                << ft::log::Color::Yellow
                << path
                << ft::log::Color::Reset
                << "`";
            throw ft::GenericException(s.str());
        }

        this->_length = this->_stream.tellg();
        this->_stream.seekg(0, std::ifstream::beg);

        if (this->_stream.fail() || this->_stream.bad())
        {
            std::stringstream s;
            s
                << "failed to seek `"
                << ft::log::Color::Yellow
                << path
                << ft::log::Color::Reset
                << "`";
            throw ft::GenericException(s.str());
        }

        const char* ext = get_ext(path);
        if (ext)
            this->_content_type = mime::get(ext);
    }

    bool FileResponse::next_header_field(std::string& key, std::string& value)
    {
        while (true)
        {
            if (this->_sent_headers == 0)
            {
                this->_sent_headers = 1;
                if (this->_length != 0)
                {
                    key = "Content-Length";
                    uint8_t buf[32];
                    value = std::string((char*)buf, ft::write_int(this->_length, buf));
                    return (true);
                }
            }
            else if (this->_sent_headers == 1)
            {
                this->_sent_headers = 2;
                if (this->_content_type)
                {
                    key = "Content-Type";
                    value = std::string(this->_content_type);
                    return (true);
                }
            }
            else
                return (false);
        }
    }

    Connection::Flow FileResponse::send_more_body_through(Connection& connection)
    {
        if (this->_sent == this->_init)
        {
            this->_sent = 0;
            this->_init = this->_stream.readsome((char*)this->_buf, 4096);

            if (this->_stream.eof() || this->_init == 0)
                return (Connection::Close);
        }

        size_t sent = connection.send_some(ft::Str(this->_buf + this->_sent, this->_init - this->_sent));
        this->_sent += sent;
        this->_sent_so_far += sent;

        ft::log::details()
            << ft::log::Color::Dim
            << "sending file: "
            << this->_sent_so_far << "/" << this->_length << " bytes (" << (100.0 * (double)this->_sent_so_far / (double)this->_length) << "%)"
            << ft::log::Color::Reset
            << std::endl;

        return (Connection::Continue);
    }
}
