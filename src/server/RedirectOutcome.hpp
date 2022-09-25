/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectOutcome.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:28:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 17:45:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"
#include "ft/Slice.hpp"

namespace ws
{
    class RedirectOutcome : public Outcome
    {
        ft::Str     _location;

    public:
        RedirectOutcome(ft::Str location);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
