/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyReciever.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:56:31 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 18:11:03 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RequestHeader.hpp"
#include "ft/Slice.hpp"
#include "net/Connection.hpp"

namespace ws
{
    class BodyReciever
    {
    public:
        virtual ~BodyReciever();

        virtual Connection::Flow recieve_body(ft::Str body_part, const RequestHeader& header) = 0;
    };
}
