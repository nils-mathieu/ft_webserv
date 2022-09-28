/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetPayloadLengthOutcome.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:04:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:19:40 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class SetPayloadLengthOutcome : public Outcome
    {
        size_t  _max_length;

    public:
        SetPayloadLengthOutcome(size_t max_length);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
