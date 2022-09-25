/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexOutcome.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:26:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:43:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class IndexOutcome : public Outcome
    {
    public:
        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
