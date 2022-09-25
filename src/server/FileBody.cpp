/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileBody.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:10:55 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 05:31:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileBody.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"

#include <sstream>

namespace ws
{
    FileBody::FileBody(const char* path) :
        _length(0),
        _stream(),
        _sent(0),
        _init(0),
        _buf()
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

    size_t FileBody::get_content_length() const
    {
        return (this->_length);
    }

    bool FileBody::send_through(Connection& connection)
    {
        if (this->_sent == this->_init)
        {
            this->_sent = 0;
            this->_init = this->_stream.readsome((char*)this->_buf, 4096);

            if (this->_stream.eof())
                return (false);
        }

        this->_sent += connection.send_some(ft::Str(this->_buf + this->_sent, this->_init - this->_sent));

        return (true);
    }
}
