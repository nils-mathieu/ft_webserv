/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Outcome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:53:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 18:57:00 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"
#include "Response.hpp"
#include "Responding.hpp"
#include "RequestHeader.hpp"

namespace ws
{
    class Outcome
    {
    public:
        virtual ~Outcome();

        virtual bool    try_respond(Responding& responding, const RequestHeader& request) const = 0;
    };
}
