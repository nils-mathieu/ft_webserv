/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Outcome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:53:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 07:24:34 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft/Slice.hpp"
#include "http/StatusCode.hpp"
#include "Response.hpp"

namespace ws
{
    class Outcome
    {
    public:
        enum Variant
        {
            /// @brief Does nothing.
            Dummy,
            /// @brief Throw an error inconditionally.
            Throw,
            /// @brief A specific file should be sent.
            File,
            /// @brief Root the request in a specific directory.
            Root,
        };

    private:
        union Repr
        {
            uint32_t            _throw;
            uint8_t*            _file[2];
            uint8_t*            _root[2];
        };

        Repr        _repr;
        Variant     _variant;

    public:
        Outcome();

        // ===================
        //  Getters & Setters
        // ===================

        void        set_throw(StatusCode code);
        void        set_file(ft::Str file_path);
        void        set_root(ft::Str directory_path);

        Variant     get_variant() const;
        StatusCode  get_throw() const;
        ft::Str     get_file() const;
        ft::Str     get_root() const;
    };

    std::ostream& operator<<(std::ostream& stream, const Outcome& outcome);
}
