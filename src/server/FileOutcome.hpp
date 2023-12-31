/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileOutcome.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 15:08:52 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "Responding.hpp"
#include "Outcome.hpp"

#include <string>

namespace ws
{
    class FileOutcome : public Outcome
    {
        ft::Str     _file;
        std::string _script;

    public:
        FileOutcome(ft::Str file, ft::Str script = ft::Str());

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
