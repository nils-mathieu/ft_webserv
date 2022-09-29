/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:57:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/29 15:34:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Methods.hpp"
#include "ft/Slice.hpp"
#include "Response.hpp"
#include "net/SocketAddress.hpp"

#include <string>
#include <utility>
#include <vector>

namespace ws
{
    class Responding
    {
        /// @brief The response that will actually be sent.
        Response*       _response;

    public:
        // Information about the server serving the request.
        SocketAddress server_address;

        /// @brief The current status code.
        StatusCode  status;

        /// @brief The current aggregated location.
        std::string location;
        /// @brief Allowed methods.
        Methods     methods;
        /// @brief The current root.
        ft::Str     root;
        std::vector< std::pair<std::string, std::string> >   header_fields;
        /// @brief The registered CGIs so far.
        std::vector< std::pair<ft::Str, ft::Str> >  cgis;

    public:
        Responding(SocketAddress server_address);

        ~Responding();

        void            set_response(Response* response);
        Response*       get_response();
    };
}
