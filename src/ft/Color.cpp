/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:28:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 21:51:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Color.hpp"

namespace ft
{
    namespace log
    {
        Color::Color(Color::Variant variant) :
            _variant(variant)
        {}

        Color::operator Color::Variant() const
        {
            return this->_variant;
        }

        std::ostream& operator<<(std::ostream& s, const Color& color)
        {
            switch ((Color::Variant)color)
            {
            case Color::Reset: return s << "\e(B\e[m";
            case Color::Black: return s << "\e[30m";
            case Color::Red: return s << "\e[31m";
            case Color::Green: return s << "\e[32m";
            case Color::Yellow: return s << "\e[33m";
            case Color::Blue: return s << "\e[34m";
            case Color::Magenta: return s << "\e[35m";
            case Color::Cyan: return s << "\e[36m";
            case Color::White: return s << "\e[37m";
            case Color::BrightBlack: return s << "\e[90m";
            case Color::BrightRed: return s << "\e[91m";
            case Color::BrightGreen: return s << "\e[92m";
            case Color::BrightYellow: return s << "\e[93m";
            case Color::BrightBlue: return s << "\e[94m";
            case Color::BrightMagenta: return s << "\e[95m";
            case Color::BrightCyan: return s << "\e[96m";
            case Color::BrightWhite: return s << "\e[97m";
            case Color::Bold: return s << "\e[1m";
            case Color::Dim: return s << "\e[2m";
            case Color::Italics: return s << "\e[3m";
            case Color::Underline: return s << "\e[4m";
            case Color::Reverse: return s << "\e[7m";
            default: return s;
            }
        }

        std::ostream& operator<<(std::ostream& s, const Color::Variant& color)
        {
            return s << (Color(color));
        }
    }
}
