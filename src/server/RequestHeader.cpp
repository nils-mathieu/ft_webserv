/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:17:06 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 15:47:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

namespace ws
{
    RequestHeader::RequestHeader() :
        method(Method::Get),
        uri(),
        host(),
        length(0),
        cookies(),
        header_fields()
    {}
}
