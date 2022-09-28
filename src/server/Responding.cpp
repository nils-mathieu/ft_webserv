/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:58:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:11:51 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responding.hpp"

namespace ws
{
    Responding::Responding() :
        _response(0),
        _reciever(0),
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
        if (this->_reciever)
            delete this->_reciever;
    }

    void Responding::set_response(Response* response)
    {
        if (this->_response)
            delete this->_response;
        this->_response = response;
    }

    void Responding::set_reciever(BodyReciever* reciever)
    {
        if (this->_reciever)
            delete this->_reciever;
        this->_reciever = reciever;
    }

    Response* Responding::get_response()
    {
        return this->_response;
    }

    BodyReciever* Responding::get_reciever()
    {
        return this->_reciever;
    }
}
