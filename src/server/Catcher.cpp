/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Catcher.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:59:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 14:01:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Catcher.hpp"

namespace ws
{
    Catcher::Catcher(ft::Str path) :
        all(true),
        code(),
        path(path),
        has_new_status_code(false),
        new_code()
    {}

    Catcher::Catcher(ft::Str path, StatusCode new_code) :
        all(true),
        code(),
        path(path),
        has_new_status_code(true),
        new_code(new_code)
    {}

    Catcher::Catcher(StatusCode code, ft::Str path) :
        all(false),
        code(code),
        path(path),
        has_new_status_code(false),
        new_code()
    {}

    Catcher::Catcher(StatusCode code, ft::Str path, StatusCode new_code) :
        all(false),
        code(code),
        path(path),
        has_new_status_code(true),
        new_code(new_code)
    {}
}
