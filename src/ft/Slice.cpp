/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slice.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:54:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 11:06:50 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Slice.hpp"

namespace ft
{
    Str make_str(const char* s, size_t max)
    {
        return Str((uint8_t*)s, strnlen(s, max));
    }

    bool operator==(Str a, const char* str)
    {
        uint8_t* it = a.begin();
        uint8_t* end = a.end();

        while (it != end && *str && *it == *str)
        {
            it++;
            str++;
        }
        return (*str == '\0' && it == end);
    }

    bool operator!=(Str a, const char* str)
    {
        return !(a == str);
    }

    bool operator==(Str a, const std::string& str)
    {
        return (a == str.c_str());
    }

    bool operator!=(Str a, const std::string& str)
    {
        return !(a == str);
    }

    std::ostream& operator<<(std::ostream& s, Str other)
    {
        return s.write((const char*)other.data(), other.size());
    }
}
