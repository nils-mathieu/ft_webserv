/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantRead.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:12:32 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 15:14:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CantRead.hpp"

namespace ws
{
    namespace parse
    {
        CantRead::CantRead(const char* message) :
            message(message)
        {}

        void CantRead::write(std::ostream& s) const
        {
            s << "read error: " << this->message;
        }
    }
}
