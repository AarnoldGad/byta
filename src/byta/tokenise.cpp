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
        return (preceding_token_type == byta::token_type::OPERAND ||
                preceding_token_type == byta::token_type::CLOSE_PARENTHESIS) &&
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
                (preceding_token_type & byta::token_type::PARENTHESIS) ||
                (preceding_token_type & byta::token_type::OPERATOR)) &&
               token == "-"sv;
    }

    std::string::const_iterator seek_next_token(byta::expression_t const& expr, std::string::const_iterator const it)
    {
        NAIL_DEBUG_ASSERT(it < expr->end(), "Past-the-end input iterator!");
        for (size_t offset = 0; (it + offset) != expr->end(); ++offset)
        {
            char c = *(it + offset);
            if (is_operator_char(c) || is_parentheses(c))
                return it + (offset ? offset : 1);
        }

        return expr->end();
    }

    byta::token_type detect_token_type(std::string_view const token, byta::token_type const preceding_token_type)
    {
        using std::operator""sv;

        if (is_unary_op(token, preceding_token_type))
            return byta::token_type::UNARY_OPERATOR;
        else if (is_binary_op(token, preceding_token_type))
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

        for (char c : expr)
        {
            // TODO: Parse from defined variables
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                buffer_length++;
            }
            else if (c == '.')
            {
                if (!real_number && buffer_length > 0)
                    real_number = true;
                else
                    throw std::runtime_error("Unexpected symbol");

                buffer_length++;
            }
            else if (std::isalpha(static_cast<unsigned char>(c)))
            {
                // If was already parsing a number
                if (buffer_length > 0)
                {
                    std::string_view str(&(*(expr.begin() + offset)), buffer_length);

                    if (str.back() == '.')
                        throw std::runtime_error("Period followed by no digits!");

                    developed.push_back({
                        .type = byta::token_type::OPERAND,
                        .str = str
                    });

                    offset += buffer_length;
                    buffer_length = 0;
                    real_number = false;
                }

                developed.push_back({
                    .type = byta::token_type::OPERAND,
                    .str = {&(*(expr.begin() + offset)), 1}
                });

                offset++;
            }
            else
            {
                throw std::runtime_error(fmt::format("Unexpected symbol: {}", c));
            }
        }

        if (buffer_length > 0)
        {
            developed.push_back({
                .type = byta::token_type::OPERAND,
                .str = {&(*(expr.begin() + offset)), buffer_length}
            });
        }

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

