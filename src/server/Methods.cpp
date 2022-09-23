/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:47:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 12:48:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

namespace ws
{
    Methods::Methods(Methods::Variants raw) :
        _raw(raw)
    {}

    Methods::operator uint32_t() const
    {
        return (this->_raw);
    }
}
