/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:37:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 22:39:51 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/OsException.hpp"
#include "Connection.hpp"

#include <unistd.h>
#include <iostream>

namespace ws
{
    Connection::Connection(int raw_fd) :
        _fd(raw_fd)
    {}

    Connection::~Connection()
    {
        close(this->_fd);
    }

    int Connection::file_descriptor() const
    {
        return this->_fd;
    }

    PollTypes Connection::interest() const
    {
        return
            PollTypes::In
            | PollTypes::Out
            | PollTypes::HangedUp
            | PollTypes::Exceptional
            | PollTypes::Error;
    }

    bool Connection::poll(PollTypes types)
    {
        if ((types & PollTypes::In) != 0)
        {
            // New data is available for reading!
            return this->can_read_more();
        }
        else if ((types & PollTypes::Out) != 0)
        {
            // Data can be sent!
            return this->can_send_more();
        }
        else
        {
            return (false);
        }
    }

    size_t Connection::read_some(uint8_t* buf, size_t size)
    {
        ssize_t count = read(this->_fd, buf, size);

        if (count <= -1)
            throw ft::OsException("failed to read data from socket");

        return (count);
    }

    size_t Connection::send_some(const uint8_t* data, size_t count)
    {
        ssize_t ret = write(this->_fd, data, count);

        if (ret <= -1)
            throw ft::OsException("failed to send data to socket");

        return (ret);
    }
}
