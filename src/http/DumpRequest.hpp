/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:50:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 04:45:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "HttpConnection.hpp"

namespace ws
{
    class DumpRequest : public HttpConnection
    {
        size_t  _size;

    public:
        DumpRequest(int raw_fd);

        // ===================================================
        //  Implementation of the `HttpConnection` interaface
        // ===================================================

        Connection::Flow    parsed_invalid_http();
        Connection::Flow    parsed_method(Method method);
        Connection::Flow    parsed_uri(ft::Str uri);
        Connection::Flow    parsed_http_version(ft::Str http_version);
        Connection::Flow    parsed_header_field(ft::Str key, ft::Str value);
        Connection::Flow    parsed_header();
        Connection::Flow    recieved_more_body(ft::Str body_part);
        StatusCode          send_status_code();
        bool                send_next_header(ft::Str& key, ft::Str& value);
        Connection::Flow    send_more_body();
    };
}
