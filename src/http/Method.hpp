/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:44:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 00:57:39 by nmathieu         ###   ########.fr       */
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

        bool operator==(Method other);
    };

    std::ostream& operator<<(std::ostream& s, Method other);
}
