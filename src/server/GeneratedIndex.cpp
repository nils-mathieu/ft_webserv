/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeneratedIndex.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:25:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 09:33:59 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GeneratedIndex.hpp"
#include "ft/GenericException.hpp"
#include "ft/Color.hpp"

#include <dirent.h>
#include <sstream>

namespace ws
{
    static const char* get_class_for_type(unsigned char ty)
    {
        switch (ty)
        {
        case DT_DIR: return "directory";
        case DT_REG: return "regular-file";
        case DT_LNK: return "symbolic-link";
        default: return "unknown";
        }
    }

    GeneratedIndex::GeneratedIndex(const char* dir_path, const char* uri) :
        _page(),
        _sent(0)
    {
        DIR*            dir;
        struct dirent*  ent;

        dir = opendir(dir_path);
        if (!dir)
        {
            std::stringstream s;
            s
                << "failed to open `"
                << ft::log::Color::Yellow
                << dir_path
                << ft::log::Color::Reset
                << "`";
            throw ft::GenericException(s.str());
        }

        std::stringstream   s;
        s <<
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"   <head>\n"
"       <meta charset=\"UTF-8\">\n"
"       <title>" << uri << "</title>\n"
"   </head>\n"
"   <style>\n"
"       @import url('https://fonts.googleapis.com/css2?family=Noto+Sans&display=swap');\n"
"\n"
"       body {\n"
"           margin: 20px;\n"
"           font-family: 'Noto Sans', sans-serif;\n"
"       }\n"
"\n"
"       #container {\n"
"           display: flex;\n"
"           flex-wrap: wrap;\n"
"           justify-content: center;\n"
"           gap: 5px;\n"
"           margin-top: 50px;\n"
"       }\n"
"\n"
"       a {\n"
"           color: black;\n"
"           padding: 0.3em 1em;\n"
"           text-decoration: none;\n"
"           border-radius: 0.5em;\n"
"           user-select: none;\n"
"           cursor: pointer;\n"
"\n"
"           transition: 0.2s;\n"
"       }\n"
"\n"
"       a:hover {\n"
"           background: rgba(0, 0, 0, 0.05);\n"
"       }\n"
"\n"
"       a:active {\n"
"           background: rgba(0, 0, 0, 0.1);\n"
"       }\n"
"\n"
"       .directory::before {\n"
"           content: \"📁\";\n"
"           margin-right: 5px;\n"
"       }\n"
"\n"
"       .regular-file::before {\n"
"           content: \"📄\";\n"
"           margin-right: 5px;\n"
"       }\n"
"\n"
"       .symbolic-link::before {\n"
"           content: \"🔗\";\n"
"           margin-right: 5px;\n"
"       }\n"
"\n"
"       .unknown::before {\n"
"           content: \"❓\";\n"
"           margin-right: 5px;\n"
"       }\n"
"   </style>\n"
"   <body>\n"
"       <div id=\"container\">\n";

        while ((ent = readdir(dir)) != 0)
        {
            s <<
"            <a class=\"" << get_class_for_type(ent->d_type) << "\" href=\"\">" << ent->d_name << "</a>\n";
        }

        s <<
"       </div>"
"   </body>"
"</html>";

        this->_page = s.str();
        closedir(dir);
    }

    size_t GeneratedIndex::get_content_length() const
    {
        return this->_page.size();
    }

    bool GeneratedIndex::send_through(Connection& connection)
    {
        this->_sent += connection.send_some(ft::Str((uint8_t*)this->_page.data() + this->_sent, this->_page.size() - this->_sent));
        return (this->_sent != this->_page.size());
    }
}
