/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 03:53:38 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusCode.hpp"

namespace ws
{
    StatusCode::StatusCode(StatusCode::Variant raw) :
        _raw(raw)
    {}

    const char* StatusCode::name() const
    {
        switch (this->_raw)
        {
        case StatusCode::Ok: return "OK";
        default: return "<Invalid>";
        }
    }

    StatusCode::operator uint32_t() const
    {
        return (this->_raw);
    }
}
