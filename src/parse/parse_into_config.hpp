/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_into_config.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:20:46 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 13:39:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "server/Config.hpp"

namespace ws
{
    namespace parse
    {
        /// @brief Parses the provided input into a @c Config instance.
        void    parse_into_config(Config& config, ft::Str input);
    }
}
