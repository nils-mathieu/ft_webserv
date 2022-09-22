/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:47:09 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 19:41:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/OsException.hpp"
#include "async/Pollable.hpp"
#include "SocketAddress.hpp"
#include "Responder.hpp"

namespace ws
{
    /// @brief An open socket connection.
    class Socket : public Pollable
    {
        /// @brief The file descriptor that refers to the open connection.
        int         _descriptor;
        /// @brief The `Responser` responsible for handling incoming
        /// connections.
        Responder&  _responder;

    public:
        // ==============
        //  Constructors
        // ==============

        /// @brief Opens a new socket connection.
        Socket(const SocketAddress& addr, Responder& responder);

        /// @brief Closes the socket connection.
        ~Socket();

        // ==============================================
        //  Implementation of the `Pollable` interaface.
        // ==============================================

        int             file_descriptor() const;
        PollTypes       interest() const;
        bool            poll(PollTypes types);
    };
}
