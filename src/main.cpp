/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:41:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 19:03:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/sigint.hpp"
#include "http/DumpRequest.hpp"
#include "async/AsyncExecutor.hpp"
#include "net/Socket.hpp"
#include "net/SpawnConnection.hpp"

#include <iostream>

int main(void)
{
    try
    {
        ft::log::initialize();
        ft::sigint::initialize();

        ws::AsyncExecutor   executor;
        ws::SpawnConnection<ws::DumpRequest> responder(executor);
        executor.append(new ws::Socket(ws::SocketAddress(127, 0, 0, 1, 8010), responder));
        executor.append(new ws::Socket(ws::SocketAddress(127, 0, 0, 1, 8011), responder));

        while (!ft::sigint::occured())
        {
            if (!executor.poll_some(-1))
                std::cerr << "timed out" << std::endl;
        }
    }
    catch(const ft::Exception& e)
    {
        e.write(std::cerr);
        std::cerr << std::endl;
    }

    return (0);
}
