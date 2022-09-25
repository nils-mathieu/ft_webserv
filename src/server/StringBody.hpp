/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringBody.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:23:45 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 11:58:45 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "Response.hpp"

namespace ws
{
    class StringBody : public ResponseBody
    {
        std::string     _page;
        size_t          _sent;

    public:
        StringBody(const std::string& string);

        size_t  get_content_length() const;
        bool    send_through(Connection& connection);
    };
}
