/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileOutcome.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:20:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/29 13:10:32 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileOutcome.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"
#include "CgiResponse.hpp"
#include "FileResponse.hpp"

#include <sys/stat.h>

namespace ws
{
    FileOutcome::FileOutcome(ft::Str file, ft::Str script) :
        _file(file),
        _script((char*)script.data(), script.size())
    {}

    static bool regular_file_exists(const char* s)
    {
        struct stat st;
        if (stat(s, &st) != 0)
            return (false);
        return (st.st_mode & S_IFREG);
    }

    bool FileOutcome::try_respond(Responding& responding, const RequestHeader& request) const
    {
        (void)request;

        ft::log::trace()
            << "        outcome `"
            << ft::log::Color::Yellow
            << "file "
            << ft::log::Color::Dim
            << this->_file
            << ft::log::Color::Reset
            << "`: ";

        // =====================
        //  Some Initial Checks
        // =====================

        std::string root = std::string((char*)responding.root.data(), responding.root.size());
        root.append((char*)this->_file.data(), this->_file.size());

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

        if (!this->_script.empty())
        {
            ft::log::trace()
                << std::endl
                << ft::log::Color::Dim
                << "          using CGI: "
                << this->_script
                << ft::log::Color::Reset
                << std::endl;

            responding.set_response(new CgiResponse(this->_script.c_str(), root.c_str(), responding, request));
            return (true);
        }

        ft::log::trace()
            << "`"
            << ft::log::Color::Yellow
            << root
            << ft::log::Color::Reset
            << "` found!"
            << std::endl;

        responding.status = StatusCode::Ok;
        responding.set_response(new FileResponse(root.c_str()));
        return (true);
    }
}
