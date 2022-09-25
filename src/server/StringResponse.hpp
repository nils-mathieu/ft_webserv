/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:23:45 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:04:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "Response.hpp"

namespace ws
{
    class StringResponse : public Response
    {
        std::string     _page;
        size_t          _sent;
        bool            _sent_content_length;

    public:
        StringResponse(const std::string& string);

        bool        next_header_field(std::string& key, std::string& value);
        bool        send_more_body_through(Connection& conn);
    };
}
