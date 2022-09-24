/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTooLarge.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:12:32 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 13:16:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileTooLarge.hpp"

namespace ws
{
    namespace parse
    {
        FileTooLarge::FileTooLarge(size_t size_in_bytes)
            : size_in_bytes(size_in_bytes)
        {}

        void FileTooLarge::write_human_size(std::ostream& s) const
        {
            if (this->size_in_bytes <= 1000)
                s << this->size_in_bytes << "b";
            else if (this->size_in_bytes <= 1000000)
                s << (this->size_in_bytes / 1000) << "kib";
            else if (this->size_in_bytes <= 1000000000)
                s << (this->size_in_bytes / 1000000) << "Mib";
            else
                s << (this->size_in_bytes / 1000000000) << "Gib";
        }

        void FileTooLarge::write(std::ostream& s) const
        {
            s << "the file is too large (> ";
            this->write_human_size(s);
            s << ")";
        }
    }
}
