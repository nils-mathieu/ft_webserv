/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:32:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 07:26:38 by nmathieu         ###   ########.fr       */
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

            NotFound = 404,

            InternalServerError = 500,
        };

        uint32_t     code;

    public:
        StatusCode(Variant variant = Ok);
        StatusCode(uint32_t code);

        /// @brief Computes the name of this status code.
        const char* name() const;

        operator uint32_t() const;
    };

    std::ostream& operator<<(std::ostream& stream, const StatusCode& code);
}
