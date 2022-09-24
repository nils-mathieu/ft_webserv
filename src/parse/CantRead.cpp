/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantRead.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:12:32 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 12:57:04 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CantRead.hpp"

namespace ws
{
    namespace parse
    {
        void CantRead::write(std::ostream& s) const
        {
            s << "error whilst reading";
        }
    }
}
