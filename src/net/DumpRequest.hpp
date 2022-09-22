/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:50:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 20:09:25 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Connection.hpp"

namespace ws
{
    class DumpRequest : public Connection
    {
    public:
        DumpRequest(int raw_fd);

        // ==============================================
        //  Implementation of the `Connection` interaface.
        // ==============================================

        bool    read_more(void* data, Connection::ReadFn read_fn);
    };
}
