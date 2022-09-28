/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:37:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:54:57 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectResponse.hpp"

namespace ws
{
    RedirectResponse::RedirectResponse(ft::Str url) :
        _url(url),
        _sent_location(false)
    {}

    bool RedirectResponse::next_header_field(std::string& key, std::string& value)
    {
        if (this->_sent_location)
            return (false);
        this->_sent_location = true;
        key = "Location";
        value = std::string((char*)this->_url.data(), this->_url.size());
        return (true);
    }
}
