/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:46:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 16:38:29 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "net/SocketAddress.hpp"
#include "Scope.hpp"

#include <vector>
#include <map>

namespace ws
{
    /// A server, listening on a specific port.
    class ServerBlock : public Scope
    {
    public:
        /// @brief A label for this server block.
        ft::Str                     label;
        /// @brief The address that this server block is listening for.
        SocketAddress               address;
        /// @brief The hosts allowed for this server.
        std::vector<ft::Str>        hosts;
        /// @brief The registered CGIs.
        std::map<ft::Str, ft::Str>  cgis;

    public:
        // ==============
        //  Constructors
        // ==============

        ServerBlock();

        // =================
        //  Utility Methods
        // =================

        /// @brief Determines whether this @c ServerBlock matches the provided
        /// host name.
        bool    has_host(ft::Str host_name) const;
    };
}
