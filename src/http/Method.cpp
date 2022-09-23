/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:45:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 00:58:20 by nmathieu         ###   ########.fr       */
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

    std::ostream& operator<<(std::ostream& s, Method method)
    {
        if (method == Method::Get)
            return s << "GET";
        if (method == Method::Head)
            return s << "HEAD";
        if (method == Method::Post)
            return s << "POST";
        if (method == Method::Put)
            return s << "PUT";
        if (method == Method::Delete)
            return s << "DELETE";
        if (method == Method::Connect)
            return s << "CONNECT";
        if (method == Method::Options)
            return s << "OPTIONS";
        if (method == Method::Trace)
            return s << "TRACE";
        return s << "<INVALID>";
    }
}
