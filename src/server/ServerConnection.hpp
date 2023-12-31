/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:51:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:12:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpConnection.hpp"
#include "http/Method.hpp"
#include "net/SocketAddress.hpp"
#include "net/Connection.hpp"
#include "RequestHeader.hpp"
#include "Response.hpp"
#include "Config.hpp"

namespace ws
{
    class ServerConnection : public HttpConnection
    {
        /// @brief The global configuration.
        const Config&   _config;
        /// @brief The socket address that this ServerConnection is listening
        /// for.
        SocketAddress   _address;

        /// @brief This header is populated whilst being created.
        RequestHeader   _header;

        /// @brief The state that's kept around when processing the request.
        Responding      _responding;

        size_t          _sent_header_fields;

    public:
        ServerConnection(
            int raw_fd,
            const Config& config,
            SocketAddress address
        );

        // ===============================
        //  Implementation of HttpRequest
        // ===============================

        void                parsed_invalid_http();
        Connection::Flow    parsed_method(Method method);
        Connection::Flow    parsed_uri(ft::Str uri);
        Connection::Flow    parsed_http_version(ft::Str http_version);
        Connection::Flow    parsed_header_field(ft::Str key, ft::Str value);
        Connection::Flow    parsed_header();
        Connection::Flow    recieved_more_body(ft::Str body_part);
        Connection::Flow    parsed_some(size_t payload_size_so_far);

        StatusCode          send_status_code();
        bool                send_next_header(std::string& key, std::string& value);
        Connection::Flow    send_more_body();
    };
}
