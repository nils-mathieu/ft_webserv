/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketAddress.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:27:27 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:46:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <netinet/in.h>
#include <ostream>

namespace ws
{
    /// @brief Represents a IP/v4 socket address.
    struct SocketAddress
    {
        /// @brief The port number of the address.
        uint16_t    port;
        /// @brief The four components of the address.
        uint8_t     address[4];

        /// @brief Creates a new @c SocketAddress .
        /// @param a0 The first component of the address.
        /// @param a1 The second component of the address.
        /// @param a2 The thrid component of the address.
        /// @param a3 The fourth component of the address.
        /// @param port The port number of the address.
        SocketAddress(
            uint8_t a0,
            uint8_t a1,
            uint8_t a2,
            uint8_t a3,
            uint16_t port
        );

        /// @brief Creates an instance of `struct sockaddr_in` from this
        /// @c SocketAddress instance.
        struct sockaddr_in sockaddr_in() const;

        bool operator==(const SocketAddress& other)const ;
        bool operator!=(const SocketAddress& other)const ;
    };

    std::ostream& operator<<(std::ostream& s, const SocketAddress& address);
}
