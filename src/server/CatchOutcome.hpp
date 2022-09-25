/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CatchOutcome.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:28:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:43:52 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class CatchOutcome : public Outcome
    {
        StatusCode  _caught;
        ft::Str     _page;
        StatusCode  _returned;

    public:
        CatchOutcome(StatusCode caught, ft::Str page, StatusCode returned = UINT32_MAX);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
