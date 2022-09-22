/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpawnConnection.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:10:54 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:21:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "async/AsyncExecutor.hpp"

namespace ws
{
    template< typename C >
    class SpawnConnection : public Responder
    {
        AsyncExecutor& _executor;

    public:
        SpawnConnection(AsyncExecutor& executor) :
            _executor(executor)
        {}

        void accept(int conn)
        {
            this->_executor.append(new C(conn));
        }
    };
}
