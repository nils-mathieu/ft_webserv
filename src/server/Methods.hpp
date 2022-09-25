/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:44:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 07:11:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "http/Method.hpp"

#include <stdint.h>

namespace ws
{
    /// @brief A collection of allowed methods.
    class Methods
    {
    public:
        enum Variants
        {
            None = 0,
            Get = 1 << 0,
            Head = 1 << 1,
            Post = 1 << 2,
            Put = 1 << 3,
            Delete = 1 << 4,
            Connect = 1 << 5,
            Options = 1 << 6,
            Trace = 1 << 7,
            All = Get | Head | Post | Put | Delete | Connect | Options | Trace,
        };

    private:
        Variants    _raw;

    public:
        Methods(Variants raw = None);
        explicit Methods(Method method);

        operator Variants() const;

        Methods     operator&(Methods other) const;
        void        operator&=(Methods other);
        Methods     operator|(Methods other) const;
        void        operator|=(Methods other);
        Methods     operator~() const;
    };

    std::ostream& operator<<(std::ostream& stream, const Methods& methods);
}
