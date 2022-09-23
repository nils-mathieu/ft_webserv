/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:45:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:06:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

namespace ws
{
    Method::Method(Method::Variant raw) :
        _raw(raw)
    {}

    bool Method::operator==(Method other)
    {
        return (this->_raw == other._raw);
    }

    bool Method::operator!=(Method other)
    {
        return this->_raw != other._raw;
    }

    const char* Method::name() const
    {
        switch (this->_raw)
        {
        case Method::Get: return "GET";
        case Method::Head: return "HEAD";
        case Method::Post: return "POST";
        case Method::Put: return "PUT";
        case Method::Delete: return "DELETE";
        case Method::Connect: return "CONNECT";
        case Method::Options: return "OPTIONS";
        case Method::Trace: return "TRACE";
        default: return "<INVALID>";
        }
    }

    std::ostream& operator<<(std::ostream& s, Method method)
    {
        return s << method.name();
    }
}
