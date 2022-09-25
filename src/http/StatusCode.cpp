/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 07:29:05 by nmathieu         ###   ########.fr       */
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

    static const char* fallible_name(StatusCode::Variant variant)
    {
        switch (variant)
        {
        case StatusCode::Continue: return "Continue";
        case StatusCode::Ok: return "OK";
        case StatusCode::NotFound: return "Not Found";
        case StatusCode::InternalServerError: return "Internal Server Error";
        default: return (0);
        }
    }

    const char* StatusCode::name() const
    {
        const char* ret = fallible_name((StatusCode::Variant)this->code);
        if (ret)
            return (ret);
        else
            return ("<Other>");
    }

    StatusCode::operator uint32_t() const
    {
        return (this->code);
    }

    std::ostream& operator<<(std::ostream& stream, const StatusCode& code)
    {
        const char* ret = fallible_name((StatusCode::Variant)code.code);
        if (ret)
            return stream << ret;
        else
            return stream << code.code;
    }
}
