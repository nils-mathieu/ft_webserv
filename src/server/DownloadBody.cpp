/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DownloadBody.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:02:38 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 19:55:46 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DownloadBody.hpp"
#include "ft/GenericException.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

#include <sstream>

namespace ws
{
    DownloadBody::DownloadBody(const char* path) :
        _written(0),
        _stream()
    {
        this->_stream.open(path, std::ofstream::binary);

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
    }

    Connection::Flow DownloadBody::recieve_body(ft::Str body_part, const RequestHeader& header)
    {
        this->_stream.write((char*)body_part.data(), body_part.size());
        this->_written += body_part.size();

        if (this->_written >= header.length)
            return (Connection::Close);
        else
            return (Connection::Continue);
    }
}
