/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 13:42:25 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"

namespace ws
{
    Scope::Scope() :
        methods(),
        status(StatusCode::Ok),
        children(),
        outcomes()
    {}
}
