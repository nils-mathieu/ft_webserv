/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:41:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 17:38:21 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Methods.hpp"
#include "http/StatusCode.hpp"
#include "Outcome.hpp"
#include "Catcher.hpp"

#include <vector>

namespace ws
{
    /// @brief A server scope, serving requests.
    class Scope
    {
    public:
        /// @brief The location of this scope.
        ft::Str                 location;
        /// @brief The methods allowed in that scope.
        Methods                 methods;
        /// @brief The status code that should be returned in case of success.
        StatusCode              status;
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
    };
}
