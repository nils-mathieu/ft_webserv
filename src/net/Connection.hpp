/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:36:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 22:33:41 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "async/Pollable.hpp"

namespace ws
{
    /// @brief An open connection.
    class Connection : public Pollable
    {
        int     _fd;

    public:
        // ==============
        //  Constructors
        // ==============

        /// @brief Creates a new @c Connection instance.
        /// @param raw_fd The raw FD of the connection.
        Connection(int raw_fd);

        ~Connection();

        // ==============================================
        //  Implementation of the `Pollable` interaface.
        // ==============================================

        int             file_descriptor() const;
        PollTypes       interest() const;
        bool            poll(PollTypes types);

    protected:
        // ============================
        //  sending and recieving data
        // ============================

        /// @brief Sends some bytes.
        ///
        /// @details This function should only be called within the
        /// `call_send_more` callback function.
        ///
        /// @param data A pointer to the bytes that are to be sent.
        /// @param count The number of bytes to send.
        ///
        /// @return The number of bytes that were sent.
        size_t          send_some(const uint8_t* data, size_t count);

        /// @brief Reads some bytes
        ///
        /// @param buf The buffer that is to store available data.
        /// @param count The size of the buffer.
        ///
        /// @return The number of bytes that were read.
        size_t          read_some(uint8_t* buf, size_t count);

    protected:
        // ======================
        //  virtual pure methods
        // ======================

        /// @brief Indicates that more data is available for reading.
        ///
        /// @returns Whether the connection can be closed.
        virtual bool    can_read_more() = 0;

        /// @brief Indicates that data can be sent through this connection.
        ///
        /// @return Whether the connection can be closed.
        virtual bool    can_send_more() = 0;
    };
}
