// main.cpp
// 19 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#include <fmt/format.h>
#include <nail/nail.hpp>

#include "byta/tokenise.hpp"
#include "byta/traits.hpp"
#include "byta/token.hpp"

void debug_print(std::vector<byta::token_t>& tokens)
{
    char const* type_str = nullptr;

    for (auto& token : tokens)
    {
        switch (token.type)
        {
            case byta::token_type::BEGIN:
                type_str = "BEGIN  "; break;
            case byta::token_type::UNARY_OPERATOR:
                type_str = "UNARY  "; break;
            case byta::token_type::BINARY_OPERATOR:
                type_str = "BINARY "; break;
            case byta::token_type::OPERAND:
                type_str = "OPERAND"; break;
            case byta::token_type::OPEN_PARENTHESIS:
                type_str = "OPEN   "; break;
            case byta::token_type::CLOSE_PARENTHESIS:
                type_str = "CLOSE  "; break;
            case byta::token_type::END:
                type_str = "END    "; break;
            default:
                type_str = "UNKNOWN";
        }

        fmt::println("{} : {}", type_str, token.str);
    }
}

int main(int const argc, char const* const argv[])
{
    // Parse arguments
    if (argc <= 1)
        return 0;

    byta::expression_t const expr(argv[1]);

    // Validate input
    std::vector<byta::token_t> tokens = byta::tokenise(expr);
    debug_print(tokens);

    // Interpret input

    // Simplify results

    return 0;
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

