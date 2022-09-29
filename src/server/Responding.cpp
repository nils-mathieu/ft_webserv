/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:58:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/29 15:26:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responding.hpp"

namespace ws
{
    Responding::Responding(SocketAddress server_address) :
        _response(0),
        server_address(server_address),
        status(StatusCode::Ok),
        location("/"),
        methods(Methods::All),
        root(ft::make_str("./")),
        header_fields()
    {}

    Responding::~Responding()
    {
        if (this->_response)
            delete this->_response;
    }

    void Responding::set_response(Response* response)
    {
        if (this->_response)
            delete this->_response;
        this->_response = response;
    }

    Response* Responding::get_response()
    {
        return this->_response;
    }
}
