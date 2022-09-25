/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GenericException.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:24:52 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 05:27:02 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GenericException.hpp"

namespace ft
{
    GenericException::GenericException(const std::string& message) :
        message(message)
    {}

    void GenericException::write(std::ostream& stream) const
    {
        stream << this->message;
    }
}
