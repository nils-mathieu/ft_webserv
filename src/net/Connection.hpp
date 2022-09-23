/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:36:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 03:54:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "async/Pollable.hpp"

namespace ws
{
    /// @brief An open connection.
    class Connection : public Pollable
    {
        int     _fd;

        bool    _reading_done;
        bool    _writing_done;

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
        /// @param slice The source buffer.
        ///
        /// @return The number of bytes that were sent.
        size_t          send_some(ft::Slice<uint8_t> slice);

        /// @brief Reads some bytes
        ///
        /// @param slice The destination buffer.
        ///
        /// @return The number of bytes that were read.
        size_t          read_some(ft::Slice<uint8_t> slice);

    protected:
        // ======================
        //  virtual pure methods
        // ======================

        /// @brief Indicates that more data is available for reading.
        ///
        /// @returns Whether this connection still wants to read more data.
        virtual bool    can_read_more() = 0;

        /// @brief Indicates that data can be sent through this connection.
        ///
        /// @return Whether the connection still wants to send more data.
        virtual bool    can_send_more() = 0;
    };
}
