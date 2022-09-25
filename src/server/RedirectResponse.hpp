/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:33:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 17:37:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Response.hpp"

namespace ws
{
    class RedirectResponse : public Response
    {
        ft::Str     _url;
        bool        _sent_location;

    public:
        RedirectResponse(ft::Str url);

        bool next_header_field(std::string& key, std::string& value);
        bool send_more_body_through(Connection& conn);
    };
}
