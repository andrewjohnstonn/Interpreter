#include <catch2/catch_test_macros.hpp>

#include "Lexer.h"

#include <cstdint>
#include <string>
#include <vector>

SCENARIO("single line is tokenised")
{
    WHEN("the lexer receives the line of andrew code: \
            - int i = 5 + 5")
    {
        std::string input { "int i = 5 + 5" };
        Lexer lexer{ "int i = 5 + 5" };

        THEN("the line is tokenised into the following: \
            - { INT, IDENTIFIER, ASSIGNMENT, NUMBER, PLUS, NUMBER }")
            {
                const auto& tokens = lexer.tokenise();
                CHECK(tokens.size() == 6);
                CHECK(tokens[0].type == TokenType::INT);
                CHECK(tokens[1].type == TokenType::IDENTIFIER);
                CHECK(tokens[2].type == TokenType::ASSIGNMENT);
                CHECK(tokens[3].type == TokenType::NUMBER);
                CHECK(tokens[4].type == TokenType::PLUS);
                CHECK(tokens[5].type == TokenType::NUMBER);
            }
    }
}