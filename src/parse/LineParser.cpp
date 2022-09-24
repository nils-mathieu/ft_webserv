/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LineParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:38:53 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 18:12:08 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LineParser.hpp"
#include "ParseException.hpp"
#include "ft/Slice.hpp"

namespace ws
{
    namespace parse
    {
        LineParser::LineParser(ft::Str input) :
            _remainder(input),
            _line_no(0),
            _last_start(0),
            _last_end(0),
            _initial(0),
            _line()
        {}

        static bool is_any_kind_of_space(const uint8_t& c)
        {
            return (isspace(c));
        }

        static ft::Str trim_comments(ft::Str input)
        {
            ft::Str not_a_comment;
            ft::Str a_comment;

            if (input.split_once(not_a_comment, a_comment, '#'))
                return (not_a_comment);
            else
                return (input);
        }

        bool LineParser::advance_line()
        {
            do
            {
                if (this->_remainder.empty())
                    return (false);

                this->_line = this->_remainder.next_split('\n');
                this->_line = trim_comments(this->_line);
                this->_line = this->_line.trim(is_any_kind_of_space);
                this->_initial = this->_line.data();
                this->_line_no++;
            }
            while (this->_line.empty());

            return (true);
        }

        void LineParser::throw_parsing_error(const char* message)
        {
            ft::Str og_line((uint8_t*)this->_initial, this->_line.end());
            throw ParseException(this->_line_no, og_line, this->_last_start, this->_last_end, message);
        }

        void LineParser::assert_line_empty()
        {
            if (this->_line.empty())
                return;
            this->_last_start = this->consumed();
            this->_line = ft::Str(this->_line.end(), this->_line.end());
            this->_last_end = this->consumed();
            this->throw_parsing_error("expected end-of-line");
        }

        size_t LineParser::consumed() const
        {
            return (this->_line.data() - this->_initial);
        }

        size_t LineParser::line_no() const
        {
            return this->_line_no;
        }

        void LineParser::next_word(ft::Str& word)
        {
            ft::Str second;

            this->_last_start = this->consumed();
            if (this->_line.split_once(word, second, ' '))
                this->_line = second;
            else
            {
                word = this->_line;
                this->_line = ft::Str(word.end(), word.end());
            }
            this->_last_end = this->consumed();
            this->_line = this->_line.trim_left(is_any_kind_of_space);
        }

        bool LineParser::get_keyword(const char* s)
        {
            ft::Str first;
            ft::Str second;

            this->_last_start = this->consumed();
            if (!this->_line.split_once(first, second, ' '))
            {
                first = this->_line;
                second = ft::Str(this->_line.end(), this->_line.end());
            }
            if (first == s)
            {
                this->_line = second;
                this->_last_end = this->consumed();
                this->_line = this->_line.trim_left(is_any_kind_of_space);
                return (true);
            }
            else
            {
                this->_last_end = this->consumed();
                this->_line = this->_line.trim_left(is_any_kind_of_space);
                return (false);
            }
        }

        bool LineParser::get_char(uint8_t c)
        {
            this->_last_start = this->consumed();
            this->_last_end = this->consumed();
            if (this->_line.empty())
                return (false);
            if (this->_line[0] == c)
            {
                this->_last_start = this->consumed();
                this->_line = ft::Str(this->_line.begin() + 1, this->_line.end());
                this->_last_end = this->consumed();
                this->_line = this->_line.trim_left(is_any_kind_of_space);
                return (true);
            }
            else
            {
                this->_last_end = this->consumed() + 1;
                return (false);
            }
        }

        bool LineParser::next_string(ft::Str& contents)
        {
            this->_last_start = this->consumed();
            this->_last_end = this->consumed();
            if (this->_line.empty())
                return (false);
            if (this->_line[0] == '\"')
            {
                const uint8_t* it = this->_line.begin() + 1;
                while (it != this->_line.end())
                {
                    if (*it == '\"')
                    {
                        contents = ft::Str(this->_line.begin() + 1, (uint8_t*)it);
                        this->_line = ft::Str((uint8_t*)it + 1, this->_line.end());
                        this->_last_end = this->consumed();
                        this->_line = this->_line.trim_left(is_any_kind_of_space);
                        return (true);
                    }
                    it++;
                }
            }
            return (false);
        }
    }
}
