/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantRead.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:11:34 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 12:57:02 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Exception.hpp"

namespace ws
{
    namespace parse
    {
        class CantRead : public ft::Exception
        {
        public:
            void write(std::ostream& s) const;
        };
    }
}
