/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:47:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 17:10:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

namespace ws
{
    Methods::Methods(Methods::Variants raw) :
        _raw(raw)
    {}

    Methods::operator Methods::Variants() const
    {
        return (this->_raw);
    }

    Methods Methods::operator&(Methods other) const
    {
        return (Methods::Variants)(this->_raw & other._raw);
    }

    void Methods::operator&=(Methods other)
    {
        *this = *this & other;
    }

    Methods Methods::operator|(Methods other) const
    {
        return (Methods::Variants)(this->_raw | other._raw);
    }

    void Methods::operator|=(Methods other)
    {
        *this = *this | other;
    }

    Methods Methods::operator~() const
    {
        return (Methods::Variants)~this->_raw;
    }
}
