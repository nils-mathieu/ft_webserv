/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:32:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 03:52:50 by nmathieu         ###   ########.fr       */
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
            Ok = 200,
        };

    private:
        Variant     _raw;

    public:
        StatusCode(Variant raw);

        /// @brief Computes the name of this status code.
        const char* name() const;

        operator uint32_t() const;
    };
}
