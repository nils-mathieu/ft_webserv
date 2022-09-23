/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:23:56 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 21:37:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ostream>

namespace ft
{
    namespace log
    {
        class Color
        {
        public:
            enum Variant
            {
                Reset,

                Black,
                Red,
                Green,
                Yellow,
                Blue,
                Magenta,
                Cyan,
                White,
                BrightBlack,
                BrightRed,
                BrightGreen,
                BrightYellow,
                BrightBlue,
                BrightMagenta,
                BrightCyan,
                BrightWhite,

                Bold,
                Dim,
                Italics,
                Reverse,
                Underline,
            };

        private:
            Variant _variant;

        public:
            Color(Variant variant = Reset);

            operator Variant() const;
        };

        std::ostream&   operator<<(std::ostream& s, const Color& color);
        std::ostream&   operator<<(std::ostream& s, const Color::Variant& color);
    }
}
