/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsException.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:06:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 17:29:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Exception.hpp"

namespace ft
{
    class OsException : public Exception
    {
    private:
#ifdef DEBUG
        int         _error_code;
#endif

        const char* _context;

    public:
        OsException(const char* context);

        virtual void write(std::ostream& s) const;
    };
}
