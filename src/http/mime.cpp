/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mime.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:44:28 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/30 20:35:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mime.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

#include <vector>

namespace ws
{
    namespace mime
    {
        static std::vector< std::pair< const char*, const char* > >   map;

        void        initialize()
        {
            map.reserve(2500);

            #include "mime_types"

            ft::log::trace()
                << ft::log::Color::Dim
                << "loaded " << map.size() << " MIME types"
                << ft::log::Color::Reset
                << std::endl;
        }

        const char* get(const char* ext)
        {
            std::vector< std::pair<const char*, const char*> >::const_iterator iter = map.begin();

            while (iter != map.end())
            {
                if (strcmp(iter->first, ext) == 0)
                    return iter->second;
                iter++;
            }
            return 0;
        }
    }
}
