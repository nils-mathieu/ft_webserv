/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:48:35 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 12:30:14 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    namespace log
    {
        enum LogLevel
        {
            Error,
            Warn,
            Info,
            Trace,
            Details,
        };
    }
}
