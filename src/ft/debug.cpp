/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:48:46 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 23:50:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.hpp"

#include <stdlib.h>
#include <iostream>

namespace ft
{
#ifdef DEBUG
    void assert(bool condition, const char* message)
    {
        if (condition)
            return;

        std::cerr << "assertion failed: " << message << std::endl;
        abort();
    }
#endif
}
