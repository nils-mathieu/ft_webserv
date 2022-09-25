/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:51:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 14:59:51 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "page.hpp"

#include "ft/Color.hpp"
#include "ft/GenericException.hpp"
#include "ft/Slice.hpp"

#include <dirent.h>
#include <sstream>
#include <string.h>

namespace ws
{
    namespace page
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

        std::string generated_index(const char* dir_path, const char* uri)
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

            std::string new_uri = uri;
            while ((ent = readdir(dir)) != 0)
            {
                size_t original_size = new_uri.size();
                ft::Str new_uri_ref;

                if (strcmp(ent->d_name, ".") == 0)
                    new_uri_ref = ft::Str((uint8_t*)new_uri.data(), new_uri.size());
                else if (strcmp(ent->d_name, "..") == 0)
                {
                    for (int i = (int)new_uri.size() - 2; i >= 0; i--)
                    {
                    if (new_uri[i] == '/')
                        {
                            new_uri_ref = ft::Str((uint8_t*)new_uri.data(), i + 1);
                            break;
                        }
                    }
                }
                else
                {
                    new_uri.append(ent->d_name);
                    new_uri_ref = ft::Str((uint8_t*)new_uri.data(), new_uri.size());
                }

                    s <<
"            <a class=\"" << get_class_for_type(ent->d_type) << "\" href=\"" << new_uri_ref << "\">" << ent->d_name << "</a>\n";

                new_uri.resize(original_size);
            }

            s <<
"       </div>"
"   </body>"
"</html>";
            closedir(dir);

            return (s.str());
        }

        std::string default_error(StatusCode code)
        {
            std::stringstream s;

            s <<
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"   <head>\n"
"       <meta charset=\"UTF-8\">\n"
"       <title>" << code.name() << "</title>\n"
"   </head>\n"
"   <style>\n"
"       @import url('https://fonts.googleapis.com/css2?family=Noto+Sans&display=swap');\n"
"\n"
"       body {\n"
"           margin: 20px;\n"
"           font-family: 'Noto Sans', sans-serif;\n"
"       }\n"
"\n"
"       div {\n"
"           position: absolute;\n"
"           top: 50%;\n"
"           left: 50%;\n"
"           transform: translate(-50%, -50%);\n"
"       }\n"
"\n"
"       h1 {\n"
"           text-transform: uppercase;\n"
"       }\n"
"   </style>\n"
"   <body>\n"
"       <div id=\"container\">\n"
"           <h1>" << code.name() << " (" << code.code << ")" << "</h1>\n"
"       </div>\n"
"   </body>\n"
"</html>\n";

            return s.str();
        }
    }
}
