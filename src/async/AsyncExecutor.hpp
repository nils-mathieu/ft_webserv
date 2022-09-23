/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsyncExecutor.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:55:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 23:02:38 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Pollable.hpp"

#include <vector>

namespace ws
{
    class AsyncExecutor
    {
        /// @brief The objects that are managed by this @c AsyncExecutor
        /// instance.
        std::vector< Pollable* >      _entities;

        /// @brief The descriptor returned by `epoll_create`.
        int                           _epoll;

    private:
        AsyncExecutor(const AsyncExecutor& other);

    public:
        // ==============
        //  Constructors
        // ==============

        /// @brief Creates an empty @c AsyncExecutor.
        AsyncExecutor();

        ~AsyncExecutor();

        // =========
        //  Methods
        // =========

        /// @brief Registers a new @c Pollable for execution. Note that the
        /// provided `pollable` pointer is took over by the function: it will
        /// be its responsability for destroying and `free`ing it.
        ///
        /// @param pollable The pollable that is to be registered.
        void    append(Pollable* pollable);

        /// @brief Waits on every registered value until one of them becomes
        /// available. If multiple of them are polled at once, all of theme
        /// are updated.
        ///
        /// @param timeout The maximum number of milliseconds that the function
        /// is allowed to wait.
        bool    poll_some(int timeout);
    };
}
