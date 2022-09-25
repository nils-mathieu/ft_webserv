/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileOutcome.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 16:37:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "Responding.hpp"
#include "Outcome.hpp"

namespace ws
{
    class FileOutcome : public Outcome
    {
        ft::Str     _file;

    public:
        FileOutcome(ft::Str file);

        bool try_respond(Responding& responding, const RequestHeader& request) const;
    };
}
