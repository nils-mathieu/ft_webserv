/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Catcher.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 14:00:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"

namespace ws
{
    struct Catcher
    {
        /// @brief Wether `code` can be ignored and this catcher matches
        /// every possible error.
        bool                all;
        /// @brief The status code of this catcher.
        StatusCode          code;
        /// @brief The page.
        ft::Str             path;
        /// @brief Whether a new status code should be emitted.
        bool                has_new_status_code;
        /// @brief The new status code, in any.
        StatusCode          new_code;

        Catcher(ft::Str path);
        Catcher(ft::Str path, StatusCode new_code);
        Catcher(StatusCode code, ft::Str path);
        Catcher(StatusCode code, ft::Str path, StatusCode new_code);
    };
}
