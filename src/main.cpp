/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:41:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 03:30:18 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/read_to_string.hpp"
#include "ft/log.hpp"
#include "ft/sigint.hpp"
#include "ft/Color.hpp"
#include "async/AsyncExecutor.hpp"
#include "net/Socket.hpp"
#include "server/RespondWithServer.hpp"

#include <iostream>

/// @brief Like `main`, but can throw.
int fallible_main(int argc, char** argv)
{
    // =====================
    //  Parse The Arguments
    // =====================

    if (argc <= 0)
        return (2);
    if (argc != 2)
    {
        ft::log::error()
            << ft::log::Color::Red << ft::log::Color::Bold
            << "invalid usage"
            << ft::log::Color::Reset
            << ": " << argv[0] << " [CONFIG.conf]"
            << std::endl;
        return (2);
    }

    // ==================
    //  Parse The Config
    // ==================
    std::string                             config_file;
    ws::parse::read_file_to_string(argv[1], config_file);

    ws::Config              config;

    // ==========================
    //  Start The Async Executor
    // ==========================
    ws::SocketAddress       address(127, 0, 0, 1, 8000);
    ws::AsyncExecutor       executor;
    ws::RespondWithServer   responder(executor, config, address);
    executor.append(new ws::Socket(address, responder));

    while (!ft::sigint::occured())
    {
        try
        {
            executor.poll_some(-1);
        }
        catch (const ft::Exception& exception)
        {
            ft::log::error()
                << ft::log::Color::Red << ft::log::Color::Bold
                << "error"
                << ft::log::Color::Reset
                << ": ";
            exception.write(ft::log::error());
            ft::log::error() << std::endl;
        }
    }

    return (0);
}

int main(int argc, char** argv)
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
        return (fallible_main(argc, argv));
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
