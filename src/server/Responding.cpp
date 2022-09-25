/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:58:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 05:58:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responding.hpp"

namespace ws
{
    Responding::Responding() :
        location("/"),
        methods(ws::Methods::All)
    {}
}
