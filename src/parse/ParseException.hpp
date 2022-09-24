/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:44:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 15:17:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Exception.hpp"
#include "ft/Slice.hpp"

namespace ws
{
    namespace parse
    {
        class ParseException : public ft::Exception
        {
        public:
            /// @brief On which line the error occured.
            size_t  line_no;

            /// @brief The line that generated the error.
            ft::Str line;

            /// @brief The first character of the line that generated the error.
            size_t  start;
            /// @brief The first character of the line that was *not* part of
            /// the error.
            size_t  end;

            /// @brief The message.
            const char* message;

            ParseException(
                size_t line_no,
                ft::Str line,
                size_t start,
                size_t end,
                const char* message
            );

            void write(std::ostream& stream) const;
        };
    }
}
