/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:51:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/29 15:21:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Responding.hpp"
#include "Response.hpp"

namespace ws
{
    class CgiResponse : public Response
    {
        int _input_fd;
        int _output_fd;

        std::vector<uint8_t>                            _buf;
        std::vector< std::pair< ft::Str, ft::Str > >    _headers;
        StatusCode                                      _new_status;

        size_t                                          _recieved_body;
        size_t                                          _sent_header_field;
        size_t                                          _sent_data;

        void prepare_response();

    public:
        CgiResponse(
            const char* script,
            const char* file,
            Responding& responding,
            const RequestHeader& request
        );

        ~CgiResponse();

        Connection::Flow    recieve_body(ft::Str body_part, const RequestHeader& header);
        StatusCode          catch_status_code(StatusCode current);
        bool                next_header_field(std::string& key, std::string& value);
        Connection::Flow    send_more_body_through(Connection& conn);
    };
}
