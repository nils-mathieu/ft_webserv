/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_string.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:00:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 03:15:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <istream>

namespace ws
{
    namespace parse
    {
        /// @brief Reads the content of a stream into a string. `s` is replaced.
        void    read_to_string(std::istream& stream, std::string& s);

        /// @brief Reads the content of a file into a string. `s` is replaced.
        void    read_file_to_string(const char* path, std::string& s);
    }
}
