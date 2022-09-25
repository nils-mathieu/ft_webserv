/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:31:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 17:26:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

namespace ws
{
    Config::~Config()
    {
        while (!this->blocks.empty())
        {
            delete this->blocks.back();
            this->blocks.pop_back();
        }
    }

    const ServerBlock* Config::get_server_block(
        const SocketAddress& address,
        ft::Str host
    ) const
    {
        const ServerBlock*                          first_for_address = 0;
        std::vector<ServerBlock*>::const_iterator    it;

        it = this->blocks.begin();
        while (it != this->blocks.end())
        {
            if ((*it)->address == address)
            {
                if (!first_for_address)
                    first_for_address = *it;
                if ((*it)->has_host(host))
                    return (*it);
            }
            it++;
        }
        return (first_for_address);
    }
}
