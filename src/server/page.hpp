/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:47:30 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 11:54:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "http/StatusCode.hpp"

#include <string>

namespace ws
{
    namespace page
    {
        std::string generated_index(const char* path, const char* title);
        std::string default_error(StatusCode code);
    }
}
