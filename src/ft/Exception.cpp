/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:55:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:26:34 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

namespace ft
{
    Exception::~Exception() {}

    void Exception::write(std::ostream& s) const
    {
        s << "no further information";
    }
}
