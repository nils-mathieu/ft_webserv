/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DumpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:50:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 22:32:59 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Connection.hpp"

namespace ws
{
    class DumpRequest : public Connection
    {
        bool    _got_one_byte;

    public:
        DumpRequest(int raw_fd);

        // ==============================================
        //  Implementation of the `Connection` interaface.
        // ==============================================

        bool    can_read_more();
        bool    can_send_more();
    };
}
