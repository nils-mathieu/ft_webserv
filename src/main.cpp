/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:41:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 13:20:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/read_to_string.hpp"
#include "parse/CantRead.hpp"
#include "parse/CantOpen.hpp"
#include "parse/FileTooLarge.hpp"
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
    const char* config_path;

    if (argc <= 0)
        return (2);
    if (argc == 1)
    {
        ft::log::warn()
            << ft::log::Color::Yellow
            << "warning"
            << ft::log::Color::Reset
            << ": using default config `"
            << ft::log::Color::Yellow
            << "webserv.conf"
            << ft::log::Color::Reset
            << "`" << std::endl;
        config_path = "webserv.conf";
    }
    else if (argc == 2)
    {
        config_path = argv[1];
    }
    else
    {
        ft::log::error()
            << ft::log::Color::Red << ft::log::Color::Bold
            << "invalid usage"
            << ft::log::Color::Reset
            << ": " << argv[0] << " [CONFIG]"
            << std::endl;
        return (2);
    }

    // ==================
    //  Parse The Config
    // ==================
    std::string config_file;

    try
    {
        ws::parse::read_file_to_string(config_path, config_file);
    }
    catch(const ws::parse::CantRead&)
    {
        ft::log::error()
            << ft::log::Color::Red
            << "error"
            << ft::log::Color::Reset
            << ": failed to read `"
            << ft::log::Color::Yellow
            << config_path
            << ft::log::Color::Reset
            << "`" << std::endl;
        return (1);
    }
    catch (const ws::parse::CantOpen&)
    {
        ft::log::error()
            << ft::log::Color::Red
            << "error"
            << ft::log::Color::Reset
            << ": can't open `"
            << ft::log::Color::Yellow
            << config_path
            << ft::log::Color::Reset
            << "` for reading" << std::endl;
        return (1);
    }
    catch (const ws::parse::FileTooLarge& e)
    {
        ft::log::error()
            << ft::log::Color::Red
            << "error"
            << ft::log::Color::Reset
            << ": config is too large ("
            << ft::log::Color::Yellow;
        e.write_human_size(ft::log::error());
        ft::log::error()
            << ft::log::Color::Reset
            << ")" << std::endl;
        return (1);
    }

    std::cout << config_file << std::endl;

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
