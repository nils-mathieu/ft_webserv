/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:51:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"
#include "net/Connection.hpp"
#include "RequestHeader.hpp"

namespace ws
{
    class Response
    {
    public:
        virtual ~Response();

        virtual bool                next_header_field(std::string& key, std::string& value);
        virtual Connection::Flow    send_more_body_through(Connection& conn);
        virtual Connection::Flow    recieve_body(ft::Str body_part, const RequestHeader& header);
    };
}
