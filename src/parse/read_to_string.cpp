/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_string.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:03:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 03:30:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_to_string.hpp"
#include "CantRead.hpp"

#include <fstream>
#include <iostream>

namespace ws
{
    namespace parse
    {
        void read_to_string(std::istream& stream, std::string& s)
        {
            char    buf[4096];

            while (stream.read(buf, sizeof(buf)))
                s.append(buf, sizeof(buf));
            s.append(buf, stream.gcount());
        }

        void read_file_to_string(const char* path, std::string& s)
        {
            std::fstream    stream(path);

            if (!stream)
                throw CantRead(path);

            read_to_string(stream, s);
        }
    }
}
