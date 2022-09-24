/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_string.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:03:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/24 13:15:31 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_to_string.hpp"
#include "CantOpen.hpp"
#include "CantRead.hpp"
#include "FileTooLarge.hpp"

#include <fstream>
#include <iostream>

namespace ws
{
    namespace parse
    {
        void read_to_string(std::istream& stream, std::string& s)
        {
            while (true)
            {
                char c;
                stream.get(c);

                if (stream.eof())
                    break;

                if (stream.fail() || stream.bad())
                    throw CantRead();

                s.push_back(c);

                if (s.size() >= 2000000)
                    throw FileTooLarge(s.size());
            }
        }

        void read_file_to_string(const char* path, std::string& s)
        {
            std::fstream    stream(path);

            if (!stream)
                throw CantOpen(path);

            read_to_string(stream, s);
        }
    }
}
