// traits.hpp
// 16 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#ifndef BYTA_TRAITS_HPP
#define BYTA_TRAITS_HPP

#include <cstdint>
#include <string_view>

namespace byta
{
    enum token_type : uint8_t;

    bool is_alpha(char c) noexcept;
    bool is_digit(char c) noexcept;

    bool is_operator(char c) noexcept;
    bool is_parenthesis(char c) noexcept;
    bool is_square_bracket(char c) noexcept;
    bool is_curly_bracket(char c) noexcept;

    bool is_binary_op(std::string_view token, byta::token_type preceding_token_type);
    bool is_unary_op(std::string_view token, byta::token_type preceding_token_type);
}

#endif // BYTA_TRAITS_HPP
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

