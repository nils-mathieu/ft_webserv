/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:03:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 10:03:03 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerBlock.hpp"

#include <algorithm>

namespace ws
{
    ServerBlock::ServerBlock() :
        Scope(),
        address(SocketAddress(127, 0, 0, 1, 8000)),
        hosts()
    {
        this->root = ft::make_str("./");
    }

    bool ServerBlock::has_host(ft::Str host_name) const
    {
        if (this->hosts.empty())
            return (true);
        else
            return ( std::find(this->hosts.begin(), this->hosts.end(), host_name) != this->hosts.end() );
    }
}
