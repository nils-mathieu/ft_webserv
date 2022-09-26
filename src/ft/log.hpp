/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:22:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 12:30:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "LogLevel.hpp"

#include <ostream>

namespace ft
{
    namespace log
    {
        /// @brief Initializes the logging system.
        void                initialize();

        /// @brief Sets the max verbosity level.
        void                set_max_level(LogLevel level);

        /// @brief Logs an incredibly verbose message.
        std::ostream&       details();
        /// @brief Logs very verbose message.
        std::ostream&       trace();
        /// @brief Logs an informational message.
        std::ostream&       info();
        /// @brief Logs a warning message.
        std::ostream&       warn();
        /// @brief Logs an error.
        std::ostream&       error();
    }
}
