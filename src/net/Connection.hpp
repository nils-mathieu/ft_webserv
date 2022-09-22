/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:36:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:02:56 by nmathieu         ###   ########.fr       */
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
        // ======================
        //  virtual pure methods
        // ======================

        /// @brief A function that may be used to read some data.
        typedef size_t      (*ReadFn)(void* data, uint8_t* buf, size_t size);

        /// @brief Indicates that more data is available for reading.
        ///
        /// @param data A pointer to some opaque data required by the `read_fn`
        /// function.
        /// @param read_fn A function that should be called *once* to get
        /// some data out of the open connection.
        ///
        /// @returns Whether the connection can be closed (even though it has
        /// not been completely exhausted).
        virtual bool    read_more(void* data, ReadFn read_fn) = 0;
    };
}
