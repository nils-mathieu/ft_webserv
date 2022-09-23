/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpConnection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:40:31 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 02:13:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/ParseBuf.hpp"
#include "ft/Slice.hpp"
#include "Method.hpp"
#include "net/Connection.hpp"

namespace ws
{
    class HttpConnection : public Connection
    {
    private:
        /// @brief The vector used to read the request.
        ft::ParseBuf    _data;

        /// @brief The current state of the parsing.
        ///
        /// ====== The First Line ======
        ///
        ///  0 - parsing the method.
        ///  1 - parsing the first separator (between the HTTP method and the
        ///      URI).
        ///  2 - pasing the URI.
        ///  3 - parsing the second separator (between the URI and the HTTP
        ///      version).
        ///  4 - parsaing the HTTP version.
        ///  5 - parsing the CRLF of the first line.
        ///
        /// ====== The Header Fields ======
        ///
        ///  6 - parsing the key of a key-value pair.
        ///  7 - parsing the value of a key-value pair.
        ///  8 - parsing the final CRLF of a key-value pair.
        ///  9 - parsing the CRLF ending the header.
        ///
        /// ====== The Body ======
        ///
        /// 10 - reading the body of the request.
        int             _parsing_state;

        /// @brief The size of the request so far.
        size_t          _size;

        /// @brief The index of the ':' character in a key-value pair.
        size_t          _colon_position;

    public:
        HttpConnection(int raw_fd);

    protected:
        // ==============================================
        //  Implementation of the `Connection` interaface.
        // ==============================================

        bool    can_read_more();
        bool    can_send_more();

    protected:
        // ===========
        //  interface
        // ===========

        /// @brief Indicates that invalid HTTP was found in the request.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_invalid_http() = 0;

        /// @brief Indicates that the method of the HTTP request has been
        /// parsed.
        ///
        /// @param status The parsed method.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_method(Method method) = 0;

        /// @brief Indicates that the URI of the HTTP request has been parsed.
        ///
        /// @param uri The parsed URI.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_uri(ft::Str uri) = 0;

        /// @brief Indicates that the HTTP version of the request has been
        /// parsed.
        ///
        /// @param http_version The parsed HTTP version.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_http_version(ft::Str http_version) = 0;

        /// @brief Indicates that a new header field has been parsed.
        ///
        /// @param key The key of the key-value pair.
        /// @param value The value of the key-value pair.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_header_field(ft::Str key, ft::Str value) = 0;

        /// @brief Indicates that the header has been completely parsed.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    parsed_header() = 0;

        /// @brief More of the body has been recieved.
        ///
        /// @param body_part A slice of the body that has been parsed.
        ///
        /// @returns Whether the connection is done reading the request.
        virtual bool    recieved_more_body(ft::Str body_part) = 0;
    };
}
