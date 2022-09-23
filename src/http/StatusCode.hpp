/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:32:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 13:57:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

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
        };

    private:
        Variant     _raw;

    public:
        StatusCode(Variant raw = Ok);

        /// @brief Computes the name of this status code.
        const char* name() const;

        operator Variant() const;
    };
}
