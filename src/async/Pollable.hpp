/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pollable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:47:21 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 19:49:48 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "PollTypes.hpp"

namespace ws
{
    class AsyncExecutor;

    /// @brief An interface that describes the behaviour of types that own a
    /// `poll`able file descriptor.
    class Pollable
    {
    public:
        virtual             ~Pollable();

        /// @brief Returns the pollable file descriptor.
        virtual int         file_descriptor() const = 0;

        /// @brief Returns the events this type is interested in.
        virtual PollTypes    interest() const = 0;

        /// @brief When progress can be made on the given file descriptor, this
        /// function is called.
        /// @return Wether this @c Pollable can be removed from the list.
        virtual bool        poll(PollTypes types) = 0;
    };
}
