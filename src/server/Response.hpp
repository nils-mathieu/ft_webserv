/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 21:39:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"
#include "net/Connection.hpp"

namespace ws
{
    class ResponseBody
    {
    public:
        virtual ~ResponseBody();

        /// @brief Returns the number of bytes that are expected to be sent by
        /// the `send_through` method.
        virtual size_t get_content_length() const = 0;

        /// @brief Sends part of this body through the provided connection.
        ///
        /// @returns Whether more data is available.
        virtual bool send_through(Connection& connection) = 0;
    };

    class Response
    {
        ResponseBody*   _body;
        StatusCode      _status;

    public:
        Response();

        ~Response();

        // ===================
        //  Getters & Setters
        // ===================

        StatusCode      get_status() const;
        size_t          get_body_length() const;

        void            set_body(ResponseBody* body);
        void            set_status(StatusCode status);
        bool            send_body_through(Connection& connection);
    };
}
