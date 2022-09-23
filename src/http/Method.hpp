/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:44:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:06:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ostream>

namespace ws
{
    /// @brief An HTTP method.
    class Method
    {
    public:
        enum Variant
        {
            Get,
            Head,
            Post,
            Put,
            Delete,
            Connect,
            Options,
            Trace,
        };

    private:
        Variant _raw;

    public:
        Method(Variant raw);

        /// @brief Returns the name of this HTTP method.
        const char* name() const;

        bool operator==(Method other);
        bool operator!=(Method other);
    };

    std::ostream& operator<<(std::ostream& s, Method other);
}
