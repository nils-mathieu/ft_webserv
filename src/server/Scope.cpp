/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 17:39:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"

namespace ws
{
    Scope::Scope() :
        location(ft::make_str("/")),
        methods(),
        status(StatusCode::Ok),
        children(),
        outcomes(),
        catchers(),
        generate_index(false)
    {}
}
