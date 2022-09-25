/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 15:40:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"
#include "net/Connection.hpp"

namespace ws
{
    class Response
    {
    public:
        virtual ~Response();

        virtual bool next_header_field(std::string& key, std::string& value) = 0;
        virtual bool send_more_body_through(Connection& conn) = 0;
    };
}
