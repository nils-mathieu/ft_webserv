/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CleanlyTerminate.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:57:16 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 14:58:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    class CleanlyTerminate
    {
    public:
        int exit_code;

        CleanlyTerminate(int exit_code);
    };
}
