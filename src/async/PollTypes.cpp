/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollTypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:38:27 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 18:37:38 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollTypes.hpp"

namespace ws
{
    PollTypes::PollTypes(uint32_t raw) :
        _raw(raw)
    {}

    PollTypes::operator uint32_t()
    {
        return this->_raw;
    }
}
