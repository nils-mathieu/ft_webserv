/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantRead.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:12:32 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 03:28:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CantRead.hpp"

namespace ws
{
    namespace parse
    {
        CantRead::CantRead(const char* filename) :
            filename(filename)
        {}

        void CantRead::write(std::ostream& s) const
        {
            s << "failed to read `" << this->filename << "`";
        }
    }
}
