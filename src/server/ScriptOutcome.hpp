/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScriptOutcome.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:42:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 16:38:40 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Outcome.hpp"

#include <string>

namespace ws
{
    class ScriptOutcome : public Outcome
    {
        std::string _exec;
        ft::Str     _file;

    public:
        ScriptOutcome(ft::Str exec, ft::Str file);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
