/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpConnection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:54:59 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 02:13:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpConnection.hpp"

#include <iostream>

namespace ws
{
    HttpConnection::HttpConnection(int raw_fd) :
        Connection(raw_fd),
        _data(1024),
        _parsing_state(0),
        _size(0),
        _colon_position(0)
    {}

    static bool is_a_literal_slice(const uint8_t& c)
    {
        return (c == ' ');
    }

    bool HttpConnection::can_read_more()
    {
        // ====================================================
        //  1. try to read at least 512 bytes from the socket
        // ====================================================

        // This is the number of bytes that were available last time. We have
        // to avoid re-checking those.
        size_t  i = this->_data.available();

        this->_data.reserve(512);
        size_t count = this->read_some(
            this->_data.read_buffer(),
            this->_data.spare_capacity()
        );
        this->_data.assume_filled(count);
        this->_size += count;

        size_t available = this->_data.available();

        // ================================
        //  2. resume parsing: HTTP method
        // ================================

        while (true)
        {
            if (this->_parsing_state == 0)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] != ' ')
                        continue;

                    // A space has been found, we have parsed the method of the
                    // request.
                    ft::Str method = this->_data.slice(0, i);

                    this->_parsing_state = 1;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;

                    bool stop_requested;

                    if (method == "GET")
                        stop_requested = this->parsed_method(Method::Get);
                    else if (method == "HEAD")
                        stop_requested = this->parsed_method(Method::Head);
                    else if (method == "POST")
                        stop_requested = this->parsed_method(Method::Post);
                    else if (method == "PUT")
                        stop_requested = this->parsed_method(Method::Put);
                    else if (method == "DELETE")
                        stop_requested = this->parsed_method(Method::Delete);
                    else if (method == "CONNECT")
                        stop_requested = this->parsed_method(Method::Connect);
                    else if (method == "OPTIONS")
                        stop_requested = this->parsed_method(Method::Options);
                    else if (method == "TRACE")
                        stop_requested = this->parsed_method(Method::Trace);
                    else
                        stop_requested = this->parsed_invalid_http();

                    if (stop_requested)
                        return (false);
                    else
                        break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ====================================
            //  3. resume parsing: first separator
            // ====================================

            if (this->_parsing_state == 1)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] == ' ')
                        continue;

                    // A non-space has been found - this is the begining of the URI.
                    this->_parsing_state = 2;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;
                    break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ================================
            //  4. resume parsing: request URI
            // ================================

            if (this->_parsing_state == 2)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] != ' ')
                        continue;

                    // We got over the whole URI.
                    ft::Str uri = this->_data.slice(0, i);

                    this->_parsing_state = 3;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;

                    if (this->parsed_uri(uri))
                        return (false);
                    else
                        break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // =====================================
            //  5. resume parsing: second separator
            // =====================================

            if (this->_parsing_state == 3)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] == ' ')
                        continue;

                    this->_parsing_state = 4;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;
                    break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // =================================
            //  6. resume parsing: HTTP version
            // =================================

            if (this->_parsing_state == 4)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] != ' ' && this->_data[i] != '\r')
                        continue;

                    ft::Str http_version = this->_data.slice(0, i);

                    this->_parsing_state = 5;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;

                    if (this->parsed_http_version(http_version))
                        return (false);
                    else
                        break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ==========================================
            //  7. resume parsing: end of the first line
            // ==========================================

            if (this->_parsing_state == 5)
            {
                if (i >= available)
                    return (true);

                if (i == 0)
                {
                    if (this->_data[0] != '\r')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                if (i >= available)
                    return (true);

                if (i == 1)
                {
                    if (this->_data[1] != '\n')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                this->_parsing_state = 6;
                this->_data.consume(i);
                available -= i;
                i = 0;

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ======================================
            //  8. resume parsing: header field: key
            // ======================================

            if (this->_parsing_state == 6)
            {
                // If the first character is a `\r`, then this is probably the end
                // of the header.
                if (i >= available)
                    return (false);

                if (i == 0 && this->_data[0] == '\r')
                {
                    this->_parsing_state = 9;
                }
                else
                {
                    // Otherwise, this is probably a simple key-value pair.
                    for (; i < available; ++i)
                    {
                        if (this->_data[i] != ':')
                            continue;

                        this->_colon_position = i;
                        this->_parsing_state = 7;
                        i++;
                        break;
                    }
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ========================================
            //  9. resume parsing: header field: value
            // ========================================

            if (this->_parsing_state == 7)
            {
                for (; i < available; ++i)
                {
                    if (this->_data[i] != '\r')
                        continue;

                    ft::Str key = this->_data.slice(0, this->_colon_position).trim(is_a_literal_slice);
                    ft::Str value = this->_data.slice(this->_colon_position + 1, i).trim(is_a_literal_slice);

                    this->_parsing_state = 8;
                    this->_data.consume(i);
                    available -= i;
                    i = 0;

                    if (this->parsed_header_field(key, value))
                        return (false);
                    else
                        break;
                }

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // ========================================
            //  10. resume parsing: header field: CRLF
            // ========================================

            if (this->_parsing_state == 8)
            {
                if (i >= available)
                    return (true);

                if (i == 0)
                {
                    if (this->_data[0] != '\r')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                if (i >= available)
                    return (true);

                if (i == 1)
                {
                    if (this->_data[1] != '\n')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                this->_parsing_state = 6;
                this->_data.consume(i);
                available -= i;
                i = 0;

                if (i == available)
                    return (true);
                else
                    continue;
            }

            // =============================================
            //  11. resume parsing: header field: final CRLF
            // =============================================

            if (this->_parsing_state == 9)
            {
                if (i >= available)
                    return (true);

                if (i == 0)
                {
                    if (this->_data[0] != '\r')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                if (i >= available)
                    return (true);

                if (i == 1)
                {
                    if (this->_data[1] != '\n')
                        return (!this->parsed_invalid_http());
                    ++i;
                }

                this->_parsing_state = 10;
                this->_data.consume(i);
                available -= i;
                i = 0;

                if (this->parsed_header())
                    return (false);
                else if (i == available)
                    return (true);
                else
                    continue;
            }

            // ======================================
            //  12. resume parsing: reading the body
            // ======================================

            if (this->_parsing_state == 10)
            {
                ft::Str body_part = this->_data.slice();

                this->_data.consume(available);
                available = 0;

                return (!this->recieved_more_body(body_part));
            }
        }

        return (true);
    }

    bool HttpConnection::can_send_more()
    {
        return (false);
    }
}
