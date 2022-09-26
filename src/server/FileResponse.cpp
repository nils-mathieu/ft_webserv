/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:10:55 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 09:40:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileResponse.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"
#include "ft/Slice.hpp"

#include <sstream>

namespace ws
{
    FileResponse::FileResponse(const char* path) :
        _length(0),
        _stream(),
        _sent(0),
        _init(0),
        _buf(),
        _sent_content_length(false)
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
    }

    bool FileResponse::next_header_field(std::string& key, std::string& value)
    {
        if (this->_length == 0 || this->_sent_content_length)
            return (false);
        this->_sent_content_length = true;
        key = "Content-Length";
        uint8_t buf[32];
        value = std::string((char*)buf, ft::write_int(this->_length, buf));
        return (true);
    }

    bool FileResponse::send_more_body_through(Connection& connection)
    {
        if (this->_sent == this->_init)
        {
            this->_sent = 0;
            this->_init = this->_stream.readsome((char*)this->_buf, 4096);

            if (this->_stream.eof() || this->_init == 0)
                return (false);
        }

        this->_sent += connection.send_some(ft::Str(this->_buf + this->_sent, this->_init - this->_sent));

        return (true);
    }
}
