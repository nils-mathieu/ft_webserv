/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Outcome.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:00:56 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 15:15:01 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Outcome.hpp"

namespace ws
{
    Outcome::Outcome() :
        _variant(Outcome::Dummy)
    {}

    void Outcome::set_file(ft::Str file_path)
    {
        this->_variant = Outcome::File;
        this->_repr._file[0] = file_path.begin();
        this->_repr._file[1] = file_path.end();
    }

    void Outcome::set_explore()
    {
        this->_variant = Outcome::Explore;
    }

    void Outcome::set_index()
    {
        this->_variant = Outcome::Index;
    }

    void Outcome::set_catch(StatusCode code, ft::Str page, StatusCode new_code)
    {
        this->_variant = Outcome::Catch;
        this->_repr._catch._code = code.code;
        this->_repr._catch._page[0] = page.begin();
        this->_repr._catch._page[1] = page.end();
        this->_repr._catch._new_code = new_code.code;
    }

    void Outcome::set_redirect(ft::Str url)
    {
        this->_variant = Outcome::Redirect;
        this->_repr._redirect[0] = url.begin();
        this->_repr._redirect[1] = url.begin();
    }

    void Outcome::set_download()
    {
        this->_variant = Outcome::Download;
    }

    Outcome::Variant Outcome::get_variant() const
    {
        return (this->_variant);
    }

    ft::Str Outcome::get_file() const
    {
        return (ft::Str(this->_repr._file[0], this->_repr._file[1]));
    }

    StatusCode Outcome::get_catch_code() const
    {
        return (this->_repr._catch._code);
    }

    ft::Str Outcome::get_catch_page() const
    {
        return (ft::Str(this->_repr._catch._page[0], this->_repr._catch._page[1]));
    }

    StatusCode Outcome::get_catch_new_code() const
    {
        return (this->_repr._catch._new_code);
    }

    ft::Str Outcome::get_redirect() const
    {
        return (ft::Str(this->_repr._redirect[0], this->_repr._redirect[1]));
    }
}
