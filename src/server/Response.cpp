/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:42:20 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 21:02:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/debug.hpp"
#include "Response.hpp"

namespace ws
{
    ResponseBody::~ResponseBody() {}

    Response::Response() :
        _body(0),
        _status(StatusCode::Ok)
    {}

    Response::~Response()
    {
        if (this->_body)
            delete this->_body;
    }

    StatusCode Response::get_status() const
    {
        return (this->_status);
    }

    size_t Response::get_body_length() const
    {
        if (this->_body)
            return (this->_body->get_content_length());
        else
            return (0);
    }

    void Response::set_body(ResponseBody* body)
    {
        if (this->_body)
            delete this->_body;
        this->_body = body;
    }

    void Response::set_status(StatusCode status)
    {
        this->_status = status;
    }

    bool Response::send_body_through(Connection& connection)
    {
        if (this->_body)
            return (this->_body->send_through(connection));
        else
            return (false);
    }
}
