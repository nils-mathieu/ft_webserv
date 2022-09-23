/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:44:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 13:43:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
        };

    private:
        Variants    _raw;

    public:
        Methods(Variants raw = None);

        operator uint32_t() const;
    };
}
