/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:37:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:41:31 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/OsException.hpp"
#include "Connection.hpp"

#include <unistd.h>
#include <iostream>

namespace ws
{
    struct read_data
    {
        int     fd;
        bool    is_done;
    };

    static size_t data_read_fn(void* d, uint8_t* buf, size_t size)
    {
        read_data* data = (read_data*)d;

        ssize_t count = read(data->fd, buf, size);

        if (count <= -1)
            throw ft::OsException("failed to read data from socket");

        data->is_done = (count == 0);

        return (count);
    }

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
            | PollTypes::HangedUp
            | PollTypes::Exceptional
            | PollTypes::Error;
    }

    bool Connection::poll(PollTypes types)
    {
        if ((types & PollTypes::In) == 0)
            return false;

        read_data   data;
        data.fd = this->_fd;

        this->read_more(&data, data_read_fn);

        return data.is_done;
    }
}
