/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:47:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 14:50:29 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseException.hpp"

namespace ws
{
    namespace parse
    {
        ParseException::ParseException(
            size_t line_no,
            ft::Str line,
            size_t start,
            size_t end,
            const char* message
        ) :
            line_no(line_no),
            line(line),
            start(start),
            end(end),
            message(message)
        {}

        void ParseException::write(std::ostream& stream) const
        {
            stream << "line " << this->line_no << ": " << this->message;
        }
    }
}
