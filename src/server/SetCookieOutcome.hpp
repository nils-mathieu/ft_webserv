/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetCookieOutcome.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:29:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 11:34:22 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class SetCookieOutcome : public Outcome
    {
        ft::Str _name;
        ft::Str _value;

    public:
        SetCookieOutcome(ft::Str name, ft::Str value);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
