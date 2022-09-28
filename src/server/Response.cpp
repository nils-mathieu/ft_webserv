/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:42:20 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 14:17:46 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

namespace ws
{
    Response::~Response() {}

    bool Response::next_header_field(std::string& key, std::string& value)
    {
        (void)key;
        (void)value;
        return (false);
    }

    Connection::Flow Response::send_more_body_through(Connection& conn)
    {
        (void)conn;
        ft::log::trace()
            << "      sending an empty body"
            << std::endl;
        return (Connection::Close);
    }

    Connection::Flow Response::recieve_body(ft::Str body_part, const RequestHeader& header)
    {
        (void)body_part;
        (void)header;
        return (Connection::Close);
    }
}
