/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CantOpen.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:11:34 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 12:50:47 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Exception.hpp"

namespace ws
{
    namespace parse
    {
        class CantOpen : public ft::Exception
        {
        public:
            const char*     filename;

            CantOpen(const char* filename);

            void write(std::ostream& s) const;
        };
    }
}
