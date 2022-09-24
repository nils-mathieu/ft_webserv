/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:41:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 18:29:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/read_to_string.hpp"
#include "parse/CantRead.hpp"
#include "parse/CantOpen.hpp"
#include "parse/ParseException.hpp"
#include "parse/parse_into_config.hpp"
#include "ft/log.hpp"
#include "ft/sigint.hpp"
#include "ft/Color.hpp"
#include "async/AsyncExecutor.hpp"
#include "net/Socket.hpp"
#include "server/RespondWithServer.hpp"

#include <iomanip>
#include <iostream>

/// @brief Opens enough socket to cover the address requested by the provided
/// configuration.
void append_sockets(ws::Config& config, ws::AsyncExecutor& executor, std::vector<ws::RespondWithServer>& responders)
{
    std::vector<ws::ServerBlock>::const_iterator begin = config.blocks.begin();
    std::vector<ws::ServerBlock>::const_iterator end = config.blocks.end();
    std::vector<ws::ServerBlock>::const_iterator it1 = begin;
    std::vector<ws::ServerBlock>::const_iterator it2;

    while (it1 != end)
    {
        bool    found = false;

        it2 = begin;
        while (it2 != it1)
        {
            if (it2->address == it1->address)
            {
                found = true;
                break;
            }
            it2++;
        }

        if (!found)
        {
            responders.push_back(ws::RespondWithServer(executor, config, it1->address));
            executor.append(new ws::Socket(it1->address, responders.back()));
        }

        it1++;
    }
}

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
    catch(const ws::parse::CantRead& e)
    {
        ft::log::error()
            << ft::log::Color::Red
            << "error"
            << ft::log::Color::Reset
            << ": failed to read `"
            << ft::log::Color::Yellow
            << config_path
            << ft::log::Color::Reset
            << "`: "
            << e.message
            << std::endl;
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

    ws::Config              config;

    try
    {
        ws::parse::parse_into_config(config, ft::Str((uint8_t*)config_file.data(), config_file.size()));
    }
    catch (const ws::parse::ParseException& e)
    {
        ft::log::error()
            << ft::log::Color::Red
            << "error"
            << ft::log::Color::Reset
            << ": failed to parse `"
            << ft::log::Color::Yellow
            << config_path
            << ft::log::Color::Reset
            << "`" << std::endl
            << ft::log::Color::Dim
            << std::setw(5) << e.line_no
            << " | "
            << ft::log::Color::Reset
            << e.line.slice(0, e.start)
            << ft::log::Color::Underline
            << ((e.start == e.end) ? ft::make_str(" ") : e.line.slice(e.start, e.end))
            << ft::log::Color::Reset
            << e.line.slice(e.end, e.line.size())
            << std::endl;
        for (size_t i = 0; i < 8 + e.start; i++)
            ft::log::error() << ' ';
        ft::log::error()
            << ft::log::Color::Dim
            << "^ "
            << ft::log::Color::Reset
            << ft::log::Color::Yellow
            << e.message
            << ft::log::Color::Reset
            << std::endl;
        return (3);
    }

    // ==========================
    //  Start The Async Executor
    // ==========================

    ws::AsyncExecutor executor;
    std::vector<ws::RespondWithServer> responders;
    responders.reserve(config.blocks.size());

    append_sockets(config, executor, responders);

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
