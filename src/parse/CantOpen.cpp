/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantOpen.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:12:32 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 12:50:29 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CantOpen.hpp"

namespace ws
{
    namespace parse
    {
        CantOpen::CantOpen(const char* filename) :
            filename(filename)
        {}

        void CantOpen::write(std::ostream& s) const
        {
            s << "failed to open `" << this->filename << "`";
        }
    }
}
