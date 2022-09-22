/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:52:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 21:43:59 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DumpRequest.hpp"

#include <iostream>

namespace ws
{
    DumpRequest::DumpRequest(int raw_fd) :
        Connection(raw_fd)
    {}

    bool DumpRequest::read_more(void* data, Connection::ReadFn read_fn)
    {
        uint8_t buf[128];
        size_t count = read_fn(data, buf, sizeof(buf));

        if (count == 0)
            return (true);

        std::cout.write((char *)buf, count);

        return (false);
    }
}
