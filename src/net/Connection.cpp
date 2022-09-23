/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:37:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 22:47:17 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/OsException.hpp"
#include "Connection.hpp"

#include <unistd.h>
#include <iostream>

namespace ws
{
    Connection::Connection(int raw_fd) :
        _fd(raw_fd),
        _reading_done(false),
        _writing_done(false)
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
        if ((types & PollTypes::In) != 0 && !this->_reading_done)
        {
            // New data is available for reading!
            if (this->can_read_more() == Connection::Close)
                this->_reading_done = true;
        }
        if ((types & PollTypes::Out) != 0 && !this->_writing_done)
        {
            // Data can be sent!
            if (this->can_send_more() == Connection::Close)
                this->_writing_done = true;
        }
        if ((types & PollTypes::HangedUp) != 0)
            return (true);

        return (this->_reading_done && this->_writing_done);
    }

    size_t Connection::read_some(ft::Slice<uint8_t> slice)
    {
        ssize_t count = read(this->_fd, slice.data(), slice.size());

        if (count <= -1)
            throw ft::OsException("failed to read data from socket");

        return (count);
    }

    size_t Connection::send_some(ft::Slice<uint8_t> slice)
    {
        ssize_t ret = write(this->_fd, slice.data(), slice.size());

        if (ret <= -1)
            throw ft::OsException("failed to send data to socket");

        return (ret);
    }
}
