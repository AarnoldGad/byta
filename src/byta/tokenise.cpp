// tokenise.cpp
// 24 Jul 2023 Gaétan "Gad" Jalin
// See end of file for complete license notice
#include "byta/tokenise.hpp"

#include <cctype>
#include <string_view>

// TODO: implement ** and Ex (=10^x) operators
namespace
{
    bool is_operator_char(char const c)
    {
        return (c == '+' ||
                c == '-' ||
                c == '*' ||
                c == '/' ||
                c == '^');
    }

    bool is_parentheses(char const c)
    {
        return (c == '(' || c == ')');
    }

    bool is_binary_op(std::string_view const token, byta::token_type const preceding_token_type)
    {
        using std::operator""sv;
        return (preceding_token_type == byta::token_type::OPERAND) &&
               (token == "+"sv ||
                token == "-"sv ||
                token == "*"sv ||
                token == "/"sv ||
                token == "^"sv);
    }

    bool is_unary_op(std::string_view const token, byta::token_type const preceding_token_type)
    {
        using std::operator""sv;
        return (preceding_token_type == byta::token_type::BEGIN ||
                (preceding_token_type & byta::token_type::PARENTHESES) ||
                (preceding_token_type & byta::token_type::OPERATOR)) &&
               token == "-"sv;
    }
}

[[nodiscard]]
std::vector<byta::token_t> byta::tokenise(byta::expression_t const& expr)
{
    std::vector<byta::token_t> tokens;

    byta::token_type last_token_type = byta::token_type::BEGIN;
    std::string::const_iterator it = expr->begin();

    // tokens.push_back({.type = byta::token_type::BEGIN, .str = {}});

    while(it != expr->end())
    {
        std::string::const_iterator next_it = seek_next_token(expr, it);
        std::string_view token(&(*it), std::distance(it, next_it));
        byta::token_type type = detect_token_type(token, last_token_type);

        tokens.push_back({.type = type, .str = token});

        it = next_it;
        last_token_type = type;
    }

    // tokens.push_back({.type = byta::token_type::END, .str = {}});

    return tokens;
}

std::string::const_iterator byta::seek_next_token(byta::expression_t const& expr, std::string::const_iterator const it)
{
    size_t offset = 0;
    while ((it + offset) != expr->end())
    {
        char c = *(it + offset);
        if (is_operator_char(c) || is_parentheses(c))
        {
            return it + (offset ? offset : 1);
        }
        else
        {
            ++offset;
        }
    }

    return expr->end();
}

byta::token_type byta::detect_token_type(std::string_view const token, byta::token_type const preceding_token_type)
{
    using std::operator""sv;

    if (is_unary_op(token, preceding_token_type))
        return byta::token_type::UNARY_OPERATOR;
    else if (is_binary_op(token, preceding_token_type))
        return byta::token_type::BINARY_OPERATOR;
    else if (token == "("sv)
        return byta::token_type::OPEN_PARENTHESES;
    else if (token == ")"sv)
        return byta::token_type::CLOSE_PARENTHESES;
    else
        return byta::token_type::OPERAND;
}
/**
 * Copyright (C) 2023 Gaétan Jalin
 *
 * This file is part of BYTA.
 *
 * BYTA is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with BYTA.
 * If not, see <https://www.gnu.org/licenses/>.
 **/

