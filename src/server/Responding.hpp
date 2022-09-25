/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:57:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 10:02:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Methods.hpp"
#include "ft/Slice.hpp"

#include <string>

namespace ws
{
    class Responding
    {
    public:
        /// @brief The current aggregated location.
        std::string location;
        /// @brief Allowed methods.
        Methods     methods;
        /// @brief The current root.
        ft::Str     root;

    public:
        Responding();
    };
}
