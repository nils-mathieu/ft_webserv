/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteOutcome.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:10:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:15:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class DeleteOutcome : public Outcome
    {
    public:
        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
