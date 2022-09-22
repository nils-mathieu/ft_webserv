/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollTypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:34:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 18:35:54 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <sys/epoll.h>

namespace ws
{
    struct PollTypes
    {
        enum Variants
        {
            /// @brief There is data to read.
            In = EPOLLIN,
            /// @brief There is data to write.
            Out = EPOLLOUT,
            /// @brief The other end hanged up.
            HangedUp = EPOLLHUP,
            /// @brief An exceptional state arised.
            Exceptional = EPOLLPRI,
            /// @brief An error occured.
            Error = EPOLLERR,
        };

    private:
        uint32_t    _raw;

    public:
        /// @brief Creates a new @c PollType instance.
        /// @param raw The raw value.
        PollTypes(uint32_t raw);

        operator uint32_t();
    };
}
