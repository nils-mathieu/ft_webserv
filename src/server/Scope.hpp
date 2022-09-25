/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:41:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 08:00:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Methods.hpp"
#include "http/StatusCode.hpp"
#include "Outcome.hpp"
#include "Catcher.hpp"
#include "Response.hpp"
#include "RequestHeader.hpp"
#include "Responding.hpp"

#include <vector>

namespace ws
{
    /// @brief A server scope, serving requests.
    class Scope
    {
    public:
        /// @brief Whether the location should be matched exactly.
        bool                    exact_location;
        /// @brief The location of this scope.
        ft::Str                 location;
        /// @brief The methods allowed in that scope.
        Methods                 added_methods;
        /// @brief The methods disallowed in that scope.
        Methods                 removed_methods;
        /// @brief Child scopes to be traversed before this one.
        std::vector<Scope>      children;
        /// @brief The outcomes of this scope. The first matching outcome is
        /// used.
        std::vector<Outcome>    outcomes;
        /// @brief The catchers defined for this scope.
        std::vector<Catcher>    catchers;
        /// @brief Whether an index should be generated when accessing a
        /// directory.
        bool                    generate_index;

    public:
        Scope();

        /// @brief Tries to process the provided request.
        ///
        /// @param request The request we are responding to.
        ///
        /// @param responding A state that's kept around while processing the
        /// request.
        ///
        /// @param response The response that we are generating.
        ///
        /// @returns Whether the request could be processed and responded to.
        bool try_respond(
            const RequestHeader& request,
            Responding& responding,
            Response& response
        ) const;
    };
}
