// tokenise.hpp
// 24 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#include <vector>
#include <string>
#include <nail/nail.hpp>

namespace byta
{
    using expression_t = nail::NamedType<std::string, struct ExpressionTag>;

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

    [[nodiscard]]
    std::vector<token_t> tokenise(expression_t const& expr);
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

