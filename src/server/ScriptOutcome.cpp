/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScriptOutcome.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:30 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 16:10:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScriptOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "ft/OsException.hpp"
#include "ft/GenericException.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

namespace ws
{
    ScriptOutcome::ScriptOutcome(ft::Str exec, ft::Str file) :
        _exec((char*)exec.data(), exec.size()),
        _file(file)
    {}

    static bool regular_file_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    static bool file_is_executable(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG && st.st_mode & S_IXUSR);
    }

    static bool is_a_space(const uint8_t& c) {
        return (c == ' ');
    }

    bool ScriptOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "script "
            << ft::log::Color::Dim
            << this->_exec
            << " "
            << this->_file
            << ft::log::Color::Reset
            << "`:";

        std::string buf = std::string((char*)responding.root.data(), responding.root.size());
        buf.append((char*)this->_file.data(), this->_file.size());

        // =====================
        //  Some Initial Checks
        // =====================

        if (!regular_file_exists(buf.c_str()))
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "file `" << buf << "`"
                << "not found"
                << ft::log::Color::Reset
                << std::endl;

            responding.status = StatusCode::NotFound;
            return (false);
        }

        if (!file_is_executable(this->_exec.c_str()))
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "file `" << this->_exec << "`"
                << "not executable"
                << ft::log::Color::Reset
                << std::endl;

            responding.status = StatusCode::NotFound;
            return (false);
        }

        // ==============================================
        //  Spawn A Child Process And Collect The Result
        // ==============================================

        int pipe_fds[2];
        if (pipe(pipe_fds) != 0)
            throw ft::OsException("failed to create a pipe");

        pid_t pid = fork();
        if (pid == 0)
        {
            {
                // Setup the pipe.
                close(pipe_fds[0]); // The read-end of the pipe won't be needed here.
                dup2(pipe_fds[1], STDOUT_FILENO);

                std::string exec_path((char*)this->_exec.data(), this->_exec.size());

                char *const argv[] = {
                    basename((char*)buf.c_str()),
                    0
                };

                ft::Str query_str;
                for (size_t i = 0; i < request.uri.size(); i++)
                {
                    if (request.uri[i] == '?')
                    {
                        query_str = ft::Str((uint8_t*)request.uri.data() + i + 1, (uint8_t*)request.uri.data() + request.uri.size());
                        break;
                    }
                }

                std::string request_method;
                request_method.append("REQUEST_METHOD=");
                request_method.append(request.method.name());
                std::string path_info;
                path_info.append("PATH_INFO=");
                path_info.append(this->_exec);
                std::string path_translated;
                path_translated.append("PATH_TRANSLATED=");
                path_translated.append(this->_exec);
                std::string script_name;
                script_name.append("SCRIPT_NAME=");
                script_name.append((char*)this->_file.data(), this->_file.size());
                std::string query_string;
                query_string.append("QUERY_STRING=");
                query_string.append((char*)query_str.data(), query_str.size());

                std::vector<char*> envp;
                envp.push_back((char*)"SERVER_SOFTWARE=webserv/0.1");
                envp.push_back((char*)"SERVER_NAME=");
                envp.push_back((char*)"GATEWAY_INTERFACE=CGI/1.1");
                envp.push_back((char*)"SERVER_PROTOCOL=HTTP/1.1");
                envp.push_back((char*)"SERVER_PORT="); // TODO
                envp.push_back((char*)request_method.c_str());
                envp.push_back((char*)path_info.c_str());
                envp.push_back((char*)path_translated.c_str());
                envp.push_back((char*)script_name.c_str());
                envp.push_back((char*)query_string.c_str());
                envp.push_back((char*)"REMOTE_HOST="); // TODO
                envp.push_back((char*)"REMOTE_ADDR="); // TODO
                envp.push_back((char*)"AUTH_TYPE="); // TODO
                envp.push_back((char*)"REMOTE_USER="); // TODO
                envp.push_back((char*)"REMOTE_IDENT="); // TODO
                envp.push_back((char*)"CONTENT_TYPE="); // TODO
                envp.push_back((char*)"CONTENT_LENGTH="); // TODO

                std::vector<std::string>    header_store;
                for (size_t i = 0; i < request.header_fields.size(); i++)
                {
                    std::string s;
                    s.append("HTTP_");
                    for (size_t j = 0; j < request.header_fields[i].first.size(); j++)
                    {
                        if (request.header_fields[i].first[j] == '-')
                            s.push_back('_');
                        else if ('a' <= request.header_fields[i].first[j] && request.header_fields[i].first[j] <= 'z')
                            s.push_back(request.header_fields[i].first[j] - 32);
                        else
                            s.push_back(request.header_fields[i].first[j]);
                    }
                    s.push_back('=');
                    s.append(request.header_fields[i].second);
                    envp.push_back((char*)s.c_str());
                }

                envp.push_back(0);

                execve(exec_path.c_str(), argv, envp.data());
            }

            abort();
        }

        close(pipe_fds[1]); // The write-end of the pipe won't be needed here.

        buf.clear();
        char    buf2[4096]; // This is so dumb, so many copies.

        while (true)
        {
            ssize_t count = read(pipe_fds[0], buf2, 4096);
            if (count <= 1)
            {
                close(pipe_fds[0]);
                throw ft::OsException("failed to read from the pipe");
            }
            if (count == 0)
                break;
            buf.append(buf2, count);
        }

        // Close the pipe.
        // This should kill the child process.
        close(pipe_fds[0]);

        // ============================
        //  Parse The Collected String
        // ============================

        ft::Str key;
        ft::Str value;
        size_t  start = 0;
        size_t  i = 0;
        while (i < buf.size())
        {
            while (i < buf.size() && buf[i] != ':')
                i++;
            key = ft::Str((uint8_t*)buf.data() + start, (uint8_t*)buf.data() + i).trim(is_a_space);
            start = ++i;
            while (i < buf.size() && buf[i] != '\r')
                i++;
            value = ft::Str((uint8_t*)buf.data() + start, (uint8_t*)buf.data() + i).trim(is_a_space);
            if (key == "Status")
            {
                uint32_t code;
                if (!ft::parse_str(value, code))
                    throw ft::GenericException("unexpected CGI behavior");
                responding.status = StatusCode(code);
            }
            else
            {
                responding.header_fields.push_back(std::make_pair(std::string((char*)key.data(), key.size()), std::string((char*)value.data(), value.size())));
            }
            i++;
            if (i >= buf.size() || buf[i] != '\n')
                throw ft::GenericException("unexpected CGI behavior");
        }

        return (true);
    }
}
