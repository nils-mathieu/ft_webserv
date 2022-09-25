/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:44:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 06:29:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <ostream>

namespace ws
{
    /// @brief An HTTP method.
    class Method
    {
    public:
        enum Variant
        {
            Get = 0,
            Head = 1,
            Post = 2,
            Put = 3,
            Delete = 4,
            Connect = 5,
            Options = 6,
            Trace = 7,
        };

    private:
        Variant _raw;

    public:
        Method(Variant raw);

        /// @brief Returns the name of this HTTP method.
        const char* name() const;

        bool operator==(Method other);
        bool operator!=(Method other);

        operator uint32_t() const;
    };

    std::ostream& operator<<(std::ostream& s, Method other);
}
