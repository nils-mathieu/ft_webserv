/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:13:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 19:17:41 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "http/Method.hpp"

#include <map>
#include <vector>

namespace ws
{
    /// @brief Extracts the information about an HTTP request that we care
    /// about.
    struct RequestHeader
    {
        /// @brief The HTTP method used for the request.
        Method                              method;
        /// @brief The request URI.
        std::string                         uri;
        /// @brief The query string.
        std::string                         query;
        /// @brief The value of the `Host` header. An empty value is used when
        /// that key is not present.
        std::string                         host;
        /// @brief The length, if any, of the request body.
        size_t                              length;
        /// @brief The cookies.
        std::map<std::string, std::string>  cookies;

        std::vector< std::pair<std::string, std::string> > header_fields;

        RequestHeader();
    };
}
