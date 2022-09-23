/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:41:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 21:44:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/sigint.hpp"
#include "ft/Color.hpp"
#include "http/DumpRequest.hpp"
#include "async/AsyncExecutor.hpp"
#include "net/Socket.hpp"
#include "net/SpawnConnection.hpp"

#include <iostream>

/*
# Cool Emojis:
📦
*/

/// @brief Like `main`, but can throw.
int fallible_main(void)
{
    // ==========================
    //  Start The Async Executor
    // ==========================

    ws::AsyncExecutor   executor;
    ws::SpawnConnection<ws::DumpRequest> responder(executor);
    executor.append(new ws::Socket(ws::SocketAddress(127, 0, 0, 1, 8010), responder));
    executor.append(new ws::Socket(ws::SocketAddress(127, 0, 0, 1, 8011), responder));

    while (!ft::sigint::occured())
    {
        executor.poll_some(-1);
    }
    return (0);
}

int main(void)
{
    // =========================
    //  Initialize Global State
    // =========================
    //  This state may be needed after the `fallible_main` function has
    //  returned. None of these function should ever throw exceptions.
    ft::log::initialize();
    ft::sigint::initialize();

    try
    {
        return (fallible_main());
    }
    catch (const ft::Exception& exception)
    {
        ft::log::error()
            << ft::log::Color::Red << ft::log::Color::Bold
            << "fatal error"
            << ft::log::Color::Reset
            << ": ";
        exception.write(ft::log::error());
        ft::log::error() << std::endl;

        return (1);
    }
    catch (const std::exception& exception)
    {
        ft::log::error()
            << ft::log::Color::Red << ft::log::Color::Bold
            << "fatal error"
            << ft::log::Color::Reset
            << ": "
            << exception.what()
            << std::endl;

        return (1);
    }
}
