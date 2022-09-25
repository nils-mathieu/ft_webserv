/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileBody.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:06:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 21:40:59 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Response.hpp"

#include <fstream>

namespace ws
{
    class FileBody : public ResponseBody
    {
        size_t          _length;
        std::ifstream   _stream;
        size_t          _sent;
        size_t          _init;
        uint8_t         _buf[4096];


    public:
        FileBody(const char* path);

        size_t  get_content_length() const;
        bool    send_through(Connection& connection);
    };
}
