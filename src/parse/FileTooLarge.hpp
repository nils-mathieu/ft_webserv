/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTooLarge.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:11:34 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 13:12:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Exception.hpp"

namespace ws
{
    namespace parse
    {
        class FileTooLarge : public ft::Exception
        {
        public:
            size_t      size_in_bytes;

            FileTooLarge(size_t size_in_bytes);

            void write_human_size(std::ostream& s) const;

            void write(std::ostream& s) const;
        };
    }
}
