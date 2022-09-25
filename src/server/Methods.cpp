/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:47:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 07:17:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

namespace ws
{
    Methods::Methods(Methods::Variants raw) :
        _raw(raw)
    {}

    Methods::Methods(Method method) :
        _raw((Methods::Variants)(1U << (uint32_t)method))
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
        return (Methods::Variants)(~this->_raw & (int)Methods::All);
    }

    std::ostream& operator<<(std::ostream& stream, const Methods& methods)
    {
        if ((Methods::Variants)methods == Methods::None)
            stream << " NONE";
        if (methods & (Methods)Methods::Get)
            stream << " GET";
        if (methods & (Methods)Methods::Head)
            stream << " HEAD";
        if (methods & (Methods)Methods::Post)
            stream << " POST";
        if (methods & (Methods)Methods::Put)
            stream << " PUT";
        if (methods & (Methods)Methods::Delete)
            stream << " DELETE";
        if (methods & (Methods)Methods::Connect)
            stream << " CONNECT";
        if (methods & (Methods)Methods::Options)
            stream << " OPTIONS";
        if (methods & (Methods)Methods::Trace)
            stream << " TRACE";
        return stream;
    }
}
