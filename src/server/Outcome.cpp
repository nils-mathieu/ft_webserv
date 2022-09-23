/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Outcome.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:00:56 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 13:57:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Outcome.hpp"

namespace ws
{
    Outcome::Outcome() :
        _variant(Outcome::Dummy)
    {}

    void Outcome::set_throw(StatusCode code)
    {
        this->_variant = Outcome::Throw;
        this->_repr._throw = code;
    }

    void Outcome::set_file(ft::Str file_path)
    {
        this->_variant = Outcome::File;
        this->_repr._file[0] = file_path.begin();
        this->_repr._file[1] = file_path.end();
    }

    void Outcome::set_root(ft::Str root_path)
    {
        this->_variant = Outcome::Root;
        this->_repr._root[0] = root_path.begin();
        this->_repr._root[1] = root_path.end();
    }

    Outcome::Variant Outcome::get_variant() const
    {
        return (this->_variant);
    }

    StatusCode Outcome::get_throw() const
    {
        return (StatusCode(this->_repr._throw));
    }

    ft::Str Outcome::get_file() const
    {
        return (ft::Str(this->_repr._file[0], this->_repr._file[1]));
    }

    ft::Str Outcome::get_root() const
    {
        return (ft::Str(this->_repr._root[0], this->_repr._root[1]));
    }
}
