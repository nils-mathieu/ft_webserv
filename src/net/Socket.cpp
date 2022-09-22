/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:49:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:34:25 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <iostream>
namespace ws
{
    Socket::Socket(const SocketAddress& addr, Responder& responder) :
        _descriptor(-1),
        _responder(responder)
    {
        // ===============================
        //  1. open the socket connection
        // ===============================

        int fd = socket(AF_INET, SOCK_STREAM /* | SOCK_NONBLOCK */, 0);

        if (fd == -1)
            throw ft::OsException("can't open socket connection");

        this->_descriptor = fd;

        int yes = 1;
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0
            || setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int)))
            throw ft::OsException("can't setup socket connection");

        // =============================================
        //  2. bind the socket to the requested address
        // =============================================

        struct sockaddr_in ad = addr.sockaddr_in();

        if (bind(fd, (const struct sockaddr*)&ad, sizeof(struct sockaddr_in)) != 0)
            throw ft::OsException("can't bind socket connection");

        // ========================================
        //  3. start to listen for new connections
        // ========================================

        if (listen(fd, 32) != 0)
            throw ft::OsException("can't listen to socket connection");
    }

    Socket::~Socket()
    {
        close(this->_descriptor);
    }


    int Socket::file_descriptor() const
    {
        return (this->_descriptor);
    }

    PollTypes Socket::interest() const
    {
        return (
            PollTypes::In
            | PollTypes::HangedUp
            | PollTypes::Exceptional
            | PollTypes::Error);
    }

    bool Socket::poll(PollTypes types)
    {
        if ((types & PollTypes::In) == 0)
            return (false);

        int fd = accept(this->_descriptor, 0, 0);
        if (fd == -1)
            throw ft::OsException("failed to accept an incoming request");

        this->_responder.accept(fd);

        return (false);
    }
}
