/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:32:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 12:54:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <ostream>

namespace ws
{
    class StatusCode
    {
    public:
        enum Variant
        {
            Continue = 100,

            Ok = 200,

            MovedPermanently = 301,
            Found = 302,
            TemporaryRedirect = 307,

            BadRequest = 400,
            Unauthorized = 401,
            NotFound = 404,
            MethodNotAllowed = 405,
            Conflict = 409,
            LengthRequired = 411,
            PayloadTooLarge = 413,

            InternalServerError = 500,
        };

        uint32_t     code;

    public:
        StatusCode(Variant variant = Ok);
        StatusCode(uint32_t code);

        /// @brief Returns whether this HTTP status code is known.
        bool        is_known_code() const;

        /// @brief Computes the name of this status code.
        const char* name() const;

        operator uint32_t() const;
    };

    std::ostream& operator<<(std::ostream& stream, const StatusCode& code);
}
