/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:06:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 20:10:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Response.hpp"

#include <fstream>

namespace ws
{
    class FileResponse : public Response
    {
        size_t          _length;
        std::ifstream   _stream;
        size_t          _sent;
        size_t          _init;
        uint8_t         _buf[4096];
        size_t          _sent_so_far;
        int             _sent_headers;
        const char*     _content_type;


    public:
        FileResponse(const char* path);

        bool                next_header_field(std::string& key, std::string& value);
        Connection::Flow    send_more_body_through(Connection& conn);
    };
}
