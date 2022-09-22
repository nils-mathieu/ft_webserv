/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:53:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 15:59:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ostream>

namespace ft
{
    /// @brief A generic exception that is able to write itself to a stream.
    class Exception
    {
    public:
        /// @brief The destructor of the @c Exception type.
        virtual ~Exception();

        /// @brief Writes a short description of The error.
        /// @param s The stream in which the data will be written.
        virtual void write(std::ostream& s) const;
    };
}