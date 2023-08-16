// traits.cpp
// 16 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#include "byta/traits.hpp"

#include "byta/token.hpp"

bool byta::is_alpha(char const c) noexcept
{
    return std::isalpha(static_cast<unsigned char>(c));
};

bool byta::is_digit(char const c) noexcept
{
    return std::isdigit(static_cast<unsigned char>(c));
};

bool byta::is_operator(char const c) noexcept
{
    return (c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^');
}

bool byta::is_parenthesis(char const c) noexcept
{
    return (c == '(' || c == ')');
}

bool byta::is_square_bracket(char const c) noexcept
{
    return (c == '[' || c == ']');
}

bool byta::is_curly_bracket(char const c) noexcept
{
    return (c == '{' || c == '}');
}

bool byta::is_binary_op(std::string_view const token, byta::token_type const preceding_token_type)
{
    using std::operator""sv;
    return (preceding_token_type == byta::token_type::OPERAND ||
            preceding_token_type == byta::token_type::CLOSE_PARENTHESIS) &&
           (token == "+"sv ||
            token == "-"sv ||
            token == "*"sv ||
            token == "/"sv ||
            token == "^"sv);
}

bool byta::is_unary_op(std::string_view const token, byta::token_type const preceding_token_type)
{
    using std::operator""sv;
    return (preceding_token_type == byta::token_type::BEGIN ||
            (preceding_token_type & byta::token_type::PARENTHESIS) ||
            (preceding_token_type & byta::token_type::OPERATOR)) &&
           token == "-"sv;
}

/**
 * Copyright (C) 2023 Gaétan Jalin
 *
 * This file is part of B.Y.T.A.
 *
 * B.Y.T.A. is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * B.Y.T.A. is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with B.Y.T.A.
 * If not, see <https://www.gnu.org/licenses/>.
 **/

