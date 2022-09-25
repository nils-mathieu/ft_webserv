/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 18:45:07 by nmathieu         ###   ########.fr       */
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
        case StatusCode::MovedPermanently: return "Moved Permanently";
        case StatusCode::Found: return "Found";
        case StatusCode::TemporaryRedirect: return "Temporary Redirect";
        case StatusCode::BadRequest: return "Bad Request";
        case StatusCode::NotFound: return "Not Found";
        case StatusCode::MethodNotAllowed: return "Method Not Allowed";
        case StatusCode::Conflict: return "Conflict";
        case StatusCode::LengthRequired: return "Length Required";
        case StatusCode::InternalServerError: return "Internal Server Error";
        default: return (0);
        }
    }

    bool StatusCode::is_known_code() const
    {
        return (fallible_name((StatusCode::Variant)this->code) != 0);
    }

    const char* StatusCode::name() const
    {
        const char* ret = fallible_name((StatusCode::Variant)this->code);
        if (ret)
            return (ret);
        else
            return ("Unknown");
    }

    StatusCode::operator uint32_t() const
    {
        return (this->code);
    }
}
