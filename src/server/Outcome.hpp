/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Outcome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:53:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 15:14:58 by nmathieu         ###   ########.fr       */
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
            /// @brief A specific file should be sent.
            File,
            /// @brief Use the current root and explore it.
            Explore,
            /// @brief An index should be generated.
            Index,
            /// @brief Catches the current status code.
            Catch,
            /// @brief Redirects the request to another location.
            Redirect,
            /// @brief Downloads the body of the request.
            Download,
        };

    private:
        union Repr
        {
            uint8_t*            _file[2];
            struct
            {
                uint32_t    _code;
                uint8_t*    _page[2];
                uint32_t    _new_code;
            }                   _catch;
            uint8_t*            _redirect[2];
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
        void        set_explore();
        void        set_index();
        void        set_catch(StatusCode code, ft::Str page, StatusCode new_code = UINT32_MAX);
        void        set_redirect(ft::Str url);
        void        set_download();

        Variant     get_variant() const;
        StatusCode  get_throw() const;
        ft::Str     get_file() const;
        StatusCode  get_catch_code() const;
        ft::Str     get_catch_page() const;
        StatusCode  get_catch_new_code() const;
        ft::Str     get_redirect() const;
    };
}
