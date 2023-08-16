// token.hpp
// 16 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#ifndef BYTA_TOKEN_HPP
#define BYTA_TOKEN_HPP

#include <cstdint>
#include <nail/nail.hpp>

namespace byta
{
    enum token_type : uint8_t
    {
        BEGIN             = NAIL_BIT(0),

        OPERAND           = NAIL_BIT(1),
        UNARY_OPERATOR    = NAIL_BIT(2),
        BINARY_OPERATOR   = NAIL_BIT(3),
        OPEN_PARENTHESIS  = NAIL_BIT(4),
        CLOSE_PARENTHESIS = NAIL_BIT(5),

        END               = NAIL_BIT(7),

        OPERATOR          = (BINARY_OPERATOR | UNARY_OPERATOR),
        PARENTHESIS       = (OPEN_PARENTHESIS | CLOSE_PARENTHESIS),
    };

    typedef struct token_t
    {
        token_type type;
        // str points to original Expression
        std::string_view str;
    } token_t;
}

#endif // BYTA_TOKEN_HPP
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

