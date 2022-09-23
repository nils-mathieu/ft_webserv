/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:50:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 03:55:35 by nmathieu         ###   ########.fr       */
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

        bool        parsed_invalid_http();
        bool        parsed_method(Method method);
        bool        parsed_uri(ft::Str uri);
        bool        parsed_http_version(ft::Str http_version);
        bool        parsed_header_field(ft::Str key, ft::Str value);
        bool        parsed_header();
        bool        recieved_more_body(ft::Str body_part);
        StatusCode  send_status_code();
        bool        send_next_header(ft::Str& key, ft::Str& value);
        bool        send_more_body();
    };
}
