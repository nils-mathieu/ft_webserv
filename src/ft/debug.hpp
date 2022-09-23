/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:47:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 23:50:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
#ifdef DEBUG
    /// @brief Checks whether `condition` is `true`. Otherwise aborts with a
    /// message.
    void    assert(bool condition, const char* msg);
#else
    inline void assert(bool, const char*) {}
#endif
}
