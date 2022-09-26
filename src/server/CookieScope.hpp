/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CookieScope.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:00:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 11:20:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ft/Slice.hpp>

#include "Scope.hpp"

namespace ws
{
    class CookieScope : public Scope
    {
        std::string _name;
        std::string _value;

    public:
        CookieScope(ft::Str name, ft::Str value);

        bool try_respond(
            const RequestHeader& request,
            Responding& responding
        ) const;
    };
}
