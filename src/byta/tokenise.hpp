// tokenise.hpp
// 24 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#ifndef BYTA_TOKENISE_HPP
#define BYTA_TOKENISE_HPP

#include <vector>
#include <string>
#include <nail/nail.hpp>

namespace byta
{
    using expression_t = nail::NamedType<std::string, struct ExpressionTag>;
    struct token_t;

    [[nodiscard]]
    std::vector<byta::token_t> tokenise(byta::expression_t const& expr);
}

#endif // BYTA_TOKENISE_HPP
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

