/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:34:59 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:32:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Connection.hpp"

namespace ws
{
    class Responder
    {
    public:
        virtual ~Responder();

        /// @brief Accepts an incoming connection. This function *takes
        /// ownership* of the provided file descriptor and will take care of
        /// closing it when the time comes.
        ///
        /// @param conn The file descriptor of the connection socket.
        virtual void accept(int conn) = 0;
    };
}
