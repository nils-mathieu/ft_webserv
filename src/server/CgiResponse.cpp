/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:52:35 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 19:38:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/CleanlyTerminate.hpp"
#include "CgiResponse.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "ft/OsException.hpp"
#include "ft/GenericException.hpp"

#include <iostream>
#include <string.h>
#include <unistd.h>

#define READ_BUF_SIZE 8192

namespace ws
{
    static bool is_a_space(const uint8_t& c) {
        return (c == ' ');
    }

    static std::string get_directory(const char* s)
    {
        std::string ret;
        const char* last_slash = strrchr(s, '/');
        if (last_slash)
            ret.append(s, last_slash - s + 1);
        else
            ret.append(s);
        return ret;
    }

    static void fork_content(
        int input_pipe[2],
        int output_pipe[2],
        const char* script,
        const char* file,
        const Responding& responding,
        const RequestHeader& request
    )
    {
        (void)responding;

        // Setup the pipe.
        close(output_pipe[0]); // The read-end of the pipe won't be needed here.
        close(input_pipe[1]); // The write-end of the pipe won't be needed here.

        if (dup2(output_pipe[1], STDOUT_FILENO) == -1)
            throw ft::OsException("failed to dup the output pipe");
        close(output_pipe[1]);
        if (dup2(input_pipe[0], STDIN_FILENO) == -1)
            throw ft::OsException("failed to dup the input pipe");
        close(input_pipe[0]);

        char* filename = (char*)basename(file);
        std::string dir = get_directory(file);

        if (chdir(dir.c_str()) != 0)
            throw ft::OsException("failed to change directory");

        char *const argv[] = {
            (char*)script,
            filename,
            0
        };

        uint8_t buf[32];

        std::string content_length;
        content_length.append("CONTENT_LENGTH=");
        content_length.append((char*)buf, ft::write_int(request.length, buf));
        std::string path_info;
        path_info.append("PATH_INFO=");
        path_info.append(filename);
        std::string path_translated;
        path_translated.append("PATH_TRANSLATED=");
        path_translated.append(filename);
        std::string script_name;
        script_name.append("SCRIPT_NAME=");
        script_name.append(file);
        std::string query_string;
        query_string.append("QUERY_STRING=");
        query_string.append(request.query.c_str());
        std::string request_method;
        request_method.append("REQUEST_METHOD=");
        request_method.append(request.method.name());
        std::string server_name;
        server_name.append("SERVER_NAME=");
        server_name.append((char*)request.host.c_str());
        std::string server_port;
        server_port.append("SERVER_PORT=");
        server_port.append((char*)buf, ft::write_int(responding.server_address.port, buf));

        std::vector<char*> envp;
        envp.push_back((char*)"AUTH_TYPE="); // Left Unspecified
        envp.push_back((char*)content_length.c_str());
        envp.push_back((char*)"CONTENT_TYPE="); // Left Unspecified
        envp.push_back((char*)"GATEWAY_INTERFACE=CGI/1.1");
        envp.push_back((char*)"SERVER_SOFTWARE=webserv/0.1");
        envp.push_back((char*)path_info.c_str());
        envp.push_back((char*)path_translated.c_str());
        envp.push_back((char*)query_string.c_str());
        envp.push_back((char*)"REMOTE_ADDR="); // TODO (Left Unspecified For Now)
        envp.push_back((char*)"REMOTE_HOST="); // Left Unspecified
        envp.push_back((char*)"REMOTE_IDENT="); // Left Unspecified
        envp.push_back((char*)"REMOTE_USER="); // Left Unspecified
        envp.push_back((char*)request_method.c_str());
        envp.push_back((char*)script_name.c_str());
        envp.push_back((char*)server_name.c_str());
        envp.push_back((char*)server_port.c_str());
        envp.push_back((char*)"SERVER_PROTOCOL=HTTP/1.1");
        envp.push_back((char*)"SERVER_SOFTWARE=WebServ/0.1");
        envp.push_back((char*)"REDIRECT_STATUS=200");
        // envp.push_back((char*)"COMSPEC="); // TODO
        // envp.push_back((char*)"DOCUMENT_ROOT="); // TODO
        // envp.push_back((char*)"REQUEST_URI="); // TODO
        // envp.push_back((char*)"SERVER_SIGNATURE="); // TODO

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

        execve(script, argv, envp.data());

        throw ft::OsException("failed to execute the CGI script");
    }

    CgiResponse::CgiResponse(
        const char* script,
        const char* file,
        Responding& responding,
        const RequestHeader& request
    ) :
        _input_fd(-1),
        _output_fd(-1),
        _buf(),
        _headers(),
        _new_status(UINT32_MAX),
        _recieved_body(0),
        _sent_header_field(0),
        _sent_data(0)
    {
        int input_pipe[2];
        if (pipe(input_pipe) != 0)
            throw ft::OsException("failed to create a pipe");

        int output_pipe[2];
        if (pipe(output_pipe) != 0)
            throw ft::OsException("failed to create a pipe");

        pid_t pid = fork();
        if (pid == -1)
            throw ft::OsException("failed to fork");
        else if (pid == 0)
        {
            try
            {
                fork_content(input_pipe, output_pipe, script, file, responding, request);
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

                throw ft::CleanlyTerminate(1);
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

                throw ft::CleanlyTerminate(1);
            }

            throw ft::CleanlyTerminate(0);
        }

        close(output_pipe[1]); // The write-end of the pipe won't be needed here.
        close(input_pipe[0]); // The read-end of the pipe won't be needed here.
        this->_output_fd = output_pipe[0];
        this->_input_fd = output_pipe[1];

        if (request.length == 0)
            this->prepare_response();
    }

    CgiResponse::~CgiResponse()
    {
        close(this->_output_fd);
        close(this->_input_fd);
    }

    void CgiResponse::prepare_response()
    {
        char    buf2[READ_BUF_SIZE];

        // Finish reading the output of the CGI.
        while (true)
        {
            ssize_t count = read(this->_output_fd, buf2, READ_BUF_SIZE);
            if (count < 0)
                throw ft::OsException("failed to read from the pipe");
            if (count == 0)
                break;
            this->_buf.reserve(this->_buf.size() + count);
            for (size_t i = 0; i < (size_t)count; i++)
                this->_buf.push_back(buf2[i]);
        }

        // ============================
        //  Parse The Collected String
        // ============================

        ft::Str key;
        ft::Str value;
        size_t  i = 0;
        while (i < this->_buf.size())
        {
            size_t  start = i;
            if (this->_buf[i] == '\r')
            {
                i++;
                if (i >= this->_buf.size() || this->_buf[i] != '\n')
                    throw ft::GenericException("unexpected CGI behavior");
                i++;
                break;
            }
            while (i < this->_buf.size() && this->_buf[i] != ':')
                i++;
            if (i >= this->_buf.size())
                throw ft::GenericException("unexpected CGI behavior");
            key = ft::Str(this->_buf.data() + start, this->_buf.data() + i).trim(is_a_space);
            start = ++i;
            while (i < this->_buf.size() && this->_buf[i] != '\r')
                i++;
            value = ft::Str(this->_buf.data() + start, this->_buf.data() + i).trim(is_a_space);
            if (key == "Status")
            {
                uint32_t code;
                if (!ft::parse_str(value, code))
                    throw ft::GenericException("unexpected CGI behavior: can't parse the provided status");
                this->_new_status = StatusCode(code);
            }
            else
            {
                this->_headers.push_back(std::make_pair(key, value));
            }
            if (i >= this->_buf.size())
                break;
            i++;
            if (i >= this->_buf.size() || this->_buf[i] != '\n')
                throw ft::GenericException("unexpected CGI behavior");
            i++;
        }

        this->_sent_data = i;
    }

    Connection::Flow CgiResponse::recieve_body(ft::Str body_part, const RequestHeader& header)
    {
        char    buf2[READ_BUF_SIZE]; // This is so dumb, so many copies.

        // ============================================
        //  Send The Body Part To The Executing Script
        // ============================================

        if (this->_recieved_body >= header.length)
        {
            this->prepare_response();
            return (Connection::Close);
        }

        while (!body_part.empty())
        {
            ssize_t count = write(this->_input_fd, body_part.data(), body_part.size());
            if (count <= -1)
                throw ft::OsException("failed to send data to the CGI");
            body_part = body_part.slice(count, body_part.size());
        }
        this->_recieved_body += body_part.size();

        // ====================
        //  Read The Data Back
        // ====================

        ssize_t count = read(this->_output_fd, buf2, READ_BUF_SIZE);
        if (count < 0)
            throw ft::OsException("failed to read from the pipe");

        this->_buf.reserve(this->_buf.size() + count);
        for (size_t i = 0; i < (size_t)count; i++)
            this->_buf.push_back(buf2[i]);

        if (count == 0)
        {
            this->prepare_response();
            return (Connection::Close);
        }
        else
            return (Connection::Continue);
    }

    StatusCode CgiResponse::catch_status_code(StatusCode current)
    {
        if (this->_new_status.code == UINT32_MAX)
            return current;
        else
            return this->_new_status;
    }

    bool CgiResponse::next_header_field(std::string& key, std::string& value)
    {
        if (this->_sent_header_field >= this->_headers.size())
            return (false);

        key.clear();
        key.append((char*)this->_headers[this->_sent_header_field].first.data(), this->_headers[this->_sent_header_field].first.size());
        value.clear();
        value.append((char*)this->_headers[this->_sent_header_field].second.data(), this->_headers[this->_sent_header_field].second.size());
        this->_sent_header_field++;
        return (true);
    }

    Connection::Flow CgiResponse::send_more_body_through(Connection& conn)
    {
        if (this->_sent_data >= this->_buf.size())
            return (Connection::Close);

        this->_sent_data += conn.send_some(ft::Str(this->_buf.data() + this->_sent_data, this->_buf.size() - this->_sent_data));
        return (Connection::Continue);
    }
}
