/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LineParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:37:23 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 18:11:21 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"

namespace ws
{
    namespace parse
    {
        class LineParser
        {
            // ==============
            //  Global State
            // ==============

            ft::Str         _remainder;
            size_t          _line_no;

            // ============
            //  Line State
            // ============

            size_t          _last_start;
            size_t          _last_end;
            const uint8_t*  _initial;
            ft::Str         _line;

        public:
            LineParser(ft::Str input);

            // ========
            //  Global
            // ========

            /// @brief Get to the next line.
            bool    advance_line();

            /// @brief Throws a parsing error.
            void    throw_parsing_error(const char* message);

            /// @brief Throws if the current line is not empty.
            void    assert_line_empty();

            // =========
            //  Getters
            // =========

            /// @brief Returns the number of bytes that were consumed so far.
            size_t  consumed() const;

            /// @brief Returns the current line number.
            size_t  line_no() const;

            // =========
            //  Parsers
            // =========

            /// @brief Takes the next word.
            void    next_word(ft::Str& word);

            /// @brief Returns whether the first word is the specified keyword.
            bool    get_keyword(const char* keyword);

            /// @brief Takes the next string.
            bool    next_string(ft::Str& contents);

            /// @brief Takes the next character.
            bool    get_char(uint8_t c);
        };
    }
}
