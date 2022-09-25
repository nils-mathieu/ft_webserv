/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_into_config.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:25:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 06:21:21 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_into_config.hpp"
#include "ParseException.hpp"
#include "LineParser.hpp"

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
                bool add;
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
                    scope.added_methods |= methods;
                else
                    scope.removed_methods |= methods;
            }
            else if (directive == "catch")
            {
                ft::Str     word;
                bool        all;
                uint32_t    code;

                parser.next_word(word);
                if (word == "*")
                    all = true;
                else if (word.empty())
                    parser.throw_parsing_error("expected a status code");
                else
                {
                    all = false;
                    if (!ft::parse_str(word, code))
                        parser.throw_parsing_error("invalid status code");
                }

                ft::Str page;
                if (!parser.next_string(page))
                    parser.throw_parsing_error("expected a string");

                bool        has_new_code;
                uint32_t    new_code;

                parser.next_word(word);
                if (word.empty())
                    has_new_code = false;
                else
                {
                    has_new_code = true;
                    if (!ft::parse_str(word, new_code))
                        parser.throw_parsing_error("invalid status code");
                }

                if (all && has_new_code)
                    scope.catchers.push_back(Catcher(page, new_code));
                else if (all && !has_new_code)
                    scope.catchers.push_back(Catcher(page));
                else if (!all && !has_new_code)
                    scope.catchers.push_back(Catcher(code, page));
                else if (!all && has_new_code)
                    scope.catchers.push_back(Catcher(code, page, new_code));
            }
            else if (directive == "root")
            {
                ft::Str directory;

                if (!parser.next_string(directory))
                    parser.throw_parsing_error("expected a string");
                scope.outcomes.push_back(Outcome());
                scope.outcomes.back().set_root(directory);
            }
            else if (directive == "index")
            {
                ft::Str word;

                parser.next_word(word);
                if (word == "on")
                    scope.generate_index = true;
                else if (word == "off")
                    scope.generate_index = false;
                else
                    parser.throw_parsing_error("expected `on` or `off`");
            }
            else if (directive == "file")
            {
                ft::Str path;

                if (!parser.next_string(path))
                    parser.throw_parsing_error("expected a string");

                scope.outcomes.push_back(Outcome());
                scope.outcomes.back().set_file(path);
            }
            else if (directive == "throw")
            {
                ft::Str     code_str;
                uint32_t    code;

                parser.next_word(code_str);
                if (code_str.empty())
                    parser.throw_parsing_error("expected a status code");
                if (!ft::parse_str(code_str, code))
                    parser.throw_parsing_error("invalid status code");

                scope.outcomes.push_back(Outcome());
                scope.outcomes.back().set_throw(StatusCode(code));
            }
            else if (directive == "scope")
            {
                scope.children.push_back(Scope());
                if (!parser.next_string(scope.children.back().location))
                    scope.children.back().location = ft::Str();
                if (!parser.get_char('{'))
                    parser.throw_parsing_error("expected `{`");
                parser.assert_line_empty();

                parse_into_scope(scope.children.back(), parser);
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

                config.blocks.push_back(ServerBlock());
                parser.next_string(config.blocks.back().label);
                if (!parser.get_char('{'))
                    parser.throw_parsing_error("expected `{`");
                parser.assert_line_empty();

                parse_into_server_block(config.blocks.back(), parser);
            }
        }
    }
}
