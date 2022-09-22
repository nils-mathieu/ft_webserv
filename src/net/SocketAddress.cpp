/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketAddress.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:31 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 19:07:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketAddress.hpp"

#include <string.h>

namespace ws
{
    SocketAddress::SocketAddress(
        uint8_t a0,
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint16_t port
    ) :
        port(port)
    {
        this->address[0] = a0;
        this->address[1] = a1;
        this->address[2] = a2;
        this->address[3] = a3;
    }

    struct sockaddr_in SocketAddress::sockaddr_in() const
    {
        struct sockaddr_in  ret;

        ret.sin_family = AF_INET;
        ret.sin_port = (in_port_t)htons(this->port);

        // The `address` field is already in network byte order. There is no
        // convertion to perform. We can't simply cast that array into an
        // `uint32_t` because that can potentially create a misaligned
        // pointer.
        memcpy(&ret.sin_addr, this->address, 4);

        return (ret);
    }
}
