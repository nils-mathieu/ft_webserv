/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:19:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 12:43:36 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Exception.hpp"
#include "ft/Slice.hpp"
#include "ServerBlock.hpp"
#include "net/SocketAddress.hpp"

#include <ostream>
#include <vector>

namespace ws
{
    /// @brief The main server is responsible for actually serving requests
    /// using sub-servers ( @c ServerBlock ).
    class Config
    {
    public:
        /// @brief The server blocks defined for this server.
        std::vector<ServerBlock*>   blocks;

    public:
        ~Config();

        // =================
        //  Utility Methods
        // =================

        const ServerBlock* get_server_block(
            const SocketAddress& address,
            ft::Str host
        ) const;
    };
}
