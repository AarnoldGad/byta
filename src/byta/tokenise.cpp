// tokenise.cpp
// 24 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license notice
#include "byta/tokenise.hpp"

#include <cctype>
#include <string_view>

#include "byta/traits.hpp"
#include "byta/token.hpp"

// TODO: implement ** and Ex (=10^x) operators
namespace
{
    std::string::const_iterator seek_next_token(byta::expression_t const& expr, std::string::const_iterator const it)
    {
        NAIL_DEBUG_ASSERT(it < expr->end(), "Past-the-end input iterator!");

        for (size_t offset = 0; (it + offset) != expr->end(); ++offset)
        {
            char c = *(it + offset);
            if (byta::is_operator(c) || byta::is_parenthesis(c))
                return it + (offset ? offset : 1);
        }

        return expr->end();
    }

    byta::token_type detect_token_type(std::string_view const token, byta::token_type const preceding_token_type)
    {
        using std::operator""sv;

        if (byta::is_unary_op(token, preceding_token_type))
            return byta::token_type::UNARY_OPERATOR;
        else if (byta::is_binary_op(token, preceding_token_type))
            return byta::token_type::BINARY_OPERATOR;
        else if (token == "("sv)
            return byta::token_type::OPEN_PARENTHESIS;
        else if (token == ")"sv)
            return byta::token_type::CLOSE_PARENTHESIS;
        else
            return byta::token_type::OPERAND;
    }

    std::vector<byta::token_t> develop_operand(std::string_view const expr)
    {
        using std::operator""sv;

        std::vector<byta::token_t> developed;
        std::size_t offset = 0;
        std::size_t buffer_length = 0;
        bool real_number = false;

        auto push_operand = [&developed](std::string_view const& token) -> void
        {
            developed.push_back({
                .type = byta::token_type::OPERAND,
                .str = token
            });
        };

        auto push_buffered_number = [&expr, &push_operand, &offset, &buffer_length]() -> void
        {
            std::string_view token(&(*(expr.begin() + offset)), buffer_length);

            if (token.back() == '.')
                throw std::runtime_error("Real number with no decimals!");

            push_operand(token);
        };

        for (char c : expr)
        {
            // TODO: Parse from defined variables
            if (byta::is_digit(c))
            {
                // Continue parsing a multidigit number
                buffer_length++;
            }
            else if (c == '.')
            {
                // If parsing a number and first period encountered
                if (!real_number && buffer_length > 0)
                    real_number = true;
                else
                    throw std::runtime_error("Unexpected symbol");

                buffer_length++;
            }
            else if (byta::is_alpha(c))
            {
                // If was already parsing a number
                if (buffer_length > 0)
                {
                    push_buffered_number();

                    offset += buffer_length;
                    buffer_length = 0;
                    real_number = false;
                }

                push_operand({&(*(expr.begin() + offset)), 1});

                offset++;
            }
            else
            {
                throw std::runtime_error(fmt::format("Unexpected symbol: {}", c));
            }
        }

        if (buffer_length > 0)
            push_buffered_number();

        return developed;
    }

    void post_process_tokens(std::vector<byta::token_t>& tokens)
    {
        using std::operator""sv;
        std::vector<byta::token_t> processed;

        for (auto it = tokens.begin(); it != tokens.end(); ++it)
        {
            auto next = std::next(it);

            if (next == tokens.end())
            {
                processed.push_back(*it);
                continue;
            }

            // Insert * between 2 consecutive operands, closing parenthesis
            // and operand or operand and opening parenthesis
            if ((it->type == byta::token_type::OPERAND &&
                 (next->type == byta::token_type::OPERAND ||
                  next->type == byta::token_type::OPEN_PARENTHESIS)) ||
                (it->type == byta::token_type::CLOSE_PARENTHESIS &&
                 next->type == byta::token_type::OPERAND)
               )
            {
                processed.push_back(*it);
                processed.push_back({
                    .type = byta::token_type::BINARY_OPERATOR,
                    .str = "*"sv
                });
            }
            else
            {
                processed.push_back(*it);
            }
        }

        tokens = processed;
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

        if (type == byta::token_type::OPERAND)
        {
            std::vector<byta::token_t> developed = develop_operand(token);
            tokens.insert(tokens.end(), developed.begin(), developed.end());
        }
        else
        {
            tokens.push_back({.type = type, .str = token});
        }


        it = next_it;
        last_token_type = type;
    }

    post_process_tokens(tokens);

    // tokens.push_back({.type = byta::token_type::END, .str = {}});

    return tokens;
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

