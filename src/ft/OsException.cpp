/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsException.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:07:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 17:26:37 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OsException.hpp"

#ifdef DEBUG
# include <errno.h>
# include <string.h>
#endif

namespace ft
{
    OsException::OsException(const char* context) :
        _error_code(errno),
        _context(context)
    {}

    void OsException::write(std::ostream& s) const
    {
#ifdef DEBUG
        s << this->_context << ": '" << strerror(this->_error_code) << "'";
#else
        s << this->_context;
#endif
    }
}
