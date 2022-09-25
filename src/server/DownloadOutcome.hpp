/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DownloadOutcome.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:18:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 19:00:22 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

namespace ws
{
    class DownloadOutcome : public Outcome
    {
    public:
        bool    try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
