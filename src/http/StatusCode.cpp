/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 04:12:25 by nmathieu         ###   ########.fr       */
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
        case StatusCode::Continue: return "Continue";
        case StatusCode::Ok: return "OK";
        case StatusCode::NotFound: return "Not Found";
        default: return "<Invalid>";
        }
    }

    StatusCode::operator uint32_t() const
    {
        return (this->_raw);
    }
}
