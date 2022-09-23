/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RespondWithServer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:29:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:03:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RespondWithServer.hpp"
#include "ServerConnection.hpp"

namespace ws
{
    RespondWithServer::RespondWithServer(
        AsyncExecutor& executor,
        const Config& config,
        SocketAddress address
    ) :
        _executor(executor),
        _config(config),
        _address(address)
    {}

    void RespondWithServer::accept(int conn)
    {
        this->_executor.append(new ServerConnection(conn, this->_config, this->_address));
    }
}
