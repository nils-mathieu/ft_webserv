/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CatchOutcome.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:29:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 21:17:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "CatchOutcome.hpp"
#include "FileResponse.hpp"

#include <sys/stat.h>

namespace ws
{
    CatchOutcome::CatchOutcome(StatusCode caught, ft::Str page, StatusCode returned) :
        _caught(caught),
        _page(page),
        _returned(returned)
    {}

    static bool regular_file_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    bool CatchOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        (void)request;

        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "catch "
            << ft::log::Color::Dim
            << this->_caught.code
            << ft::log::Color::Reset
            << "`: ";


        if (this->_caught.code != responding.status.code)
        {
            ft::log::trace()
                << "not right status ("
                << responding.status.code
                << ")"
                << std::endl;
            return (false);
        }

        // CAUGHT IN 4K!!
        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append((char*)this->_page.data(), this->_page.size());

        if (!regular_file_exists(root.c_str()))
        {
            ft::log::trace()
                << ft::log::Color::Red
                << "`"
                << root
                << "` not found"
                << ft::log::Color::Reset
                << std::endl;

            responding.status = StatusCode::NotFound;
            return (false);
        }

        ft::log::trace()
            << "`"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "` found"
            << std::endl;

        responding.set_response(new FileResponse(root.c_str()));
        if (this->_returned.code != UINT32_MAX)
            responding.status = this->_returned;
        return (true);
    }
}
