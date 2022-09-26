/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 05:57:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 11:38:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Methods.hpp"
#include "ft/Slice.hpp"
#include "Response.hpp"
#include "BodyReciever.hpp"

#include <string>
#include <utility>
#include <vector>

namespace ws
{
    class Responding
    {
        /// @brief The response that will actually be sent.
        Response*       _response;
        /// @brief The reciever responsible for using the request body.
        BodyReciever*   _reciever;

    public:
        /// @brief The current status code.
        StatusCode  status;

        /// @brief The current aggregated location.
        std::string location;
        /// @brief Allowed methods.
        Methods     methods;
        /// @brief The current root.
        ft::Str     root;

        std::vector< std::pair<std::string, std::string> >   header_fields;

    public:
        Responding();

        ~Responding();

        void            set_response(Response* response);
        Response*       get_response();

        void            set_reciever(BodyReciever* response);
        BodyReciever*   get_reciever();
    };
}
