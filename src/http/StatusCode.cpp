/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 17:18:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusCode.hpp"

namespace ws
{
    StatusCode::StatusCode(StatusCode::Variant variant) :
        code((uint32_t)variant)
    {}

    StatusCode::StatusCode(uint32_t code) :
        code(code)
    {}

    const char* StatusCode::name() const
    {
        switch ((StatusCode::Variant)this->code)
        {
        case StatusCode::Continue: return "Continue";
        case StatusCode::Ok: return "OK";
        case StatusCode::NotFound: return "Not Found";
        default: return "<Invalid>";
        }
    }

    StatusCode::operator uint32_t() const
    {
        return (this->code);
    }
}
