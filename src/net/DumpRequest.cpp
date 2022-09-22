/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:52:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 22:37:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DumpRequest.hpp"

#include <iostream>

namespace ws
{
    DumpRequest::DumpRequest(int raw_fd) :
        Connection(raw_fd),
        _got_one_byte(false)
    {}

    bool DumpRequest::can_read_more()
    {
        uint8_t buf[256];

        size_t count = read_some(buf, sizeof(buf));

        std::cout.write((char *)buf, count);

        this->_got_one_byte = true;

        return (false);
    }

    bool DumpRequest::can_send_more()
    {
        if (!this->_got_one_byte)
            return (false);

        this->send_some((const uint8_t*)"HTTP/1.1 200 OK\r\n\r\nHello, World!\r\n", 34);

        return (true);
    }
}
