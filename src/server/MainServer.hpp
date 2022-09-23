/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:19:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 21:46:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ServerBlock.hpp"

#include <vector>

namespace ws
{
    /// @brief The main server is responsible for actually serving requests
    /// using sub-servers ( @c ServerBlock ).
    class MainServer
    {
    public:
        /// @brief The server blocks defined for this server.
        std::vector<ServerBlock>    blocks;
    };
}
