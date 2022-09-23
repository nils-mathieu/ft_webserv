/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RespondWithServer.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:22:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:03:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "net/Responder.hpp"
#include "net/SocketAddress.hpp"
#include "Config.hpp"
#include "async/AsyncExecutor.hpp"

namespace ws
{
    class RespondWithServer : public Responder
    {
        AsyncExecutor&      _executor;
        const Config&       _config;
        SocketAddress       _address;

    public:
        RespondWithServer(
            AsyncExecutor& executor,
            const Config& config,
            SocketAddress address
        );

        // =====================
        //  Responder Interface
        // =====================

        void accept(int conn);
    };
}
