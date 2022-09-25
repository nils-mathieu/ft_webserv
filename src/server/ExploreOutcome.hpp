/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExploreOutcome.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:24:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:43:08 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Outcome.hpp"

namespace ws
{
    class ExploreOutcome : public Outcome
    {
    public:
        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
