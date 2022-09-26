/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_into_config.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:25:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 10:01:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_into_config.hpp"
#include "ParseException.hpp"
#include "LineParser.hpp"
#include "server/FileOutcome.hpp"
#include "server/CatchOutcome.hpp"
#include "server/ExploreOutcome.hpp"
#include "server/IndexOutcome.hpp"
#include "server/RedirectOutcome.hpp"
#include "server/DownloadOutcome.hpp"
#include "server/DeleteOutcome.hpp"

#include <iostream>
#include <ctype.h>

namespace ws
{
    namespace parse
    {
        static void throw_invalid_socket_address(LineParser& parser)
        {
            parser.throw_parsing_error("invalid socket address");
        }

        static void throw_missing_brace(size_t line_no)
        {
            throw ParseException(line_no, ft::Str(), 0, 0, "missing closing `}`");
        }

        static SocketAddress get_address(LineParser& parser)
        {
            ft::Str word;

            parser.next_word(word);

            ft::Str a0 = word.next_split('.');
            ft::Str a1 = word.next_split('.');
            ft::Str a2 = word.next_split('.');
            ft::Str a3 = word.next_split(':');

            if (a0.empty() || a1.empty() || a2.empty() || a3.empty())
                throw_invalid_socket_address(parser);

            SocketAddress   ret(127, 0, 0, 1, 80);

            if (
                !ft::parse_str(a0, ret.address[0])
                || !ft::parse_str(a1, ret.address[1])
                || !ft::parse_str(a2, ret.address[2])
                || !ft::parse_str(a3, ret.address[3])
            )
                throw_invalid_socket_address(parser);

            if (!word.empty())
            {
                if (!ft::parse_str(word, ret.port))
                    throw_invalid_socket_address(parser);
            }

            return ret;
        }

        static bool parse_scope_directive(Scope& scope, ft::Str& directive, LineParser& parser);

        static void parse_into_scope(Scope& scope, LineParser& parser)
        {
            while (parser.advance_line())
            {
                ft::Str directive;

                parser.next_word(directive);
                if (directive == "}")
                {
                    parser.assert_line_empty();
                    return;
                }
                else if (!parse_scope_directive(scope, directive, parser))
                    parser.throw_parsing_error("unknown scope directive");
            }
            parser.throw_parsing_error("expected `}`");
        }

        static bool parse_scope_directive(Scope& scope, ft::Str& directive, LineParser& parser)
        {
            if (directive == "method")
            {
                bool add = false;
                if (parser.get_char('-'))
                    add = false;
                else if (parser.get_char('+'))
                    add = true;
                else
                    parser.throw_parsing_error("expected `+` or `-`");

                ft::Str method_str;
                Methods methods;
                parser.next_word(method_str);
                if (method_str == "GET")
                    methods = Methods::Get;
                else if (method_str == "HEAD")
                    methods = Methods::Head;
                else if (method_str == "POST")
                    methods = Methods::Post;
                else if (method_str == "PUT")
                    methods = Methods::Put;
                else if (method_str == "DELETE")
                    methods = Methods::Delete;
                else if (method_str == "CONNECT")
                    methods = Methods::Connect;
                else if (method_str == "OPTIONS")
                    methods = Methods::Options;
                else if (method_str == "TRACE")
                    methods = Methods::Trace;
                else if (method_str == "*")
                    methods = Methods::All;
                else
                    parser.throw_parsing_error("unknown HTTP method");

                if (add)
                {
                    scope.added_methods |= methods;
                    scope.removed_methods &= ~methods;
                }
                else
                {
                    scope.added_methods &= ~methods;
                    scope.removed_methods |= methods;
                }
            }
            else if (directive == "catch")
            {
                ft::Str     word;
                uint32_t    code = 0;

                if (parser.get_char('*'))
                    code = UINT32_MAX;
                else
                {
                    parser.next_word(word);
                    if (word.empty())
                        parser.throw_parsing_error("expected a status code");
                    else if (!ft::parse_str(word, code))
                        parser.throw_parsing_error("invalid status code");
                }

                ft::Str page;
                if (!parser.next_string(page))
                    parser.throw_parsing_error("expected a string");

                uint32_t    new_code;

                parser.next_word(word);
                if (word.empty())
                    new_code = UINT32_MAX;
                else if (!ft::parse_str(word, new_code))
                    parser.throw_parsing_error("invalid status code");

                scope.outcomes.push_back(new CatchOutcome(code, page, new_code));
            }
            else if (directive == "root")
            {
                if (!parser.next_string(scope.root))
                    parser.throw_parsing_error("expected a string");
                else if (scope.root.last() != '/')
                    parser.throw_parsing_error("scope roots must end with `/`");
            }
            else if (directive == "explore")
            {
                scope.outcomes.push_back(new ExploreOutcome());
            }
            else if (directive == "index")
            {
                scope.outcomes.push_back(new IndexOutcome());
            }
            else if (directive == "file")
            {
                ft::Str path;

                if (!parser.next_string(path))
                    parser.throw_parsing_error("expected a string");

                scope.outcomes.push_back(new FileOutcome(path));
            }
            else if (directive == "redirect")
            {
                ft::Str url;

                if (!parser.next_string(url))
                    parser.throw_parsing_error("expected a string");

                scope.outcomes.push_back(new RedirectOutcome(url));
            }
            else if (directive == "download")
            {
                scope.outcomes.push_back(new DownloadOutcome());
            }
            else if (directive == "delete")
            {
                scope.outcomes.push_back(new DeleteOutcome());
            }
            else if (directive == "scope")
            {
                if (!scope.location.empty() && scope.location.last() != '/')
                    parser.throw_parsing_error("a file-scope cannot have children");
                scope.children.push_back(new Scope());
                if (parser.get_char('='))
                    scope.children.back()->exact_location = true;
                if (!parser.next_string(scope.children.back()->location))
                    scope.children.back()->location = ft::Str();
                else if (scope.children.back()->location.first() == '/')
                    parser.throw_parsing_error("scope can't start with `/`");
                if (!parser.get_char('{'))
                    parser.throw_parsing_error("expected `{`");
                parser.assert_line_empty();

                parse_into_scope(*scope.children.back(), parser);
            }
            else
                return (false);

            parser.assert_line_empty();
            return (true);
        }

        static void parse_into_server_block(ServerBlock& server_block, LineParser& parser)
        {
            while (parser.advance_line())
            {
                ft::Str directive;

                parser.next_word(directive);
                if (directive == "address")
                {
                    server_block.address = get_address(parser);
                    parser.assert_line_empty();
                }
                else if (directive == "host")
                {
                    server_block.hosts.push_back(ft::Str());
                    if (!parser.next_string(server_block.hosts.back()))
                        parser.throw_parsing_error("expected a string");
                    parser.assert_line_empty();
                }
                else if (directive == "}")
                {
                    parser.assert_line_empty();
                    return;
                }
                else if (!parse_scope_directive(server_block, directive, parser))
                    parser.throw_parsing_error("unknown server directive");
            }
            throw_missing_brace(parser.line_no() + 1);
        }

        void parse_into_config(Config& config, ft::Str input)
        {
            LineParser  parser(input);

            while (parser.advance_line())
            {
                if (!parser.get_keyword("server"))
                    parser.throw_parsing_error("expected `server`");

                config.blocks.push_back(new ServerBlock());
                parser.next_string(config.blocks.back()->label);
                if (!parser.get_char('{'))
                    parser.throw_parsing_error("expected `{`");
                parser.assert_line_empty();

                parse_into_server_block(*config.blocks.back(), parser);
            }
        }
    }
}
