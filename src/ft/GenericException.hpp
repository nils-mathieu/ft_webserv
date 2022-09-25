/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GenericException.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:23:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 05:26:52 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Exception.hpp"

namespace ft
{
    class GenericException : public Exception
    {
    public:
        std::string message;

        GenericException(const std::string& message);

        void write(std::ostream& s) const;
    };
}
