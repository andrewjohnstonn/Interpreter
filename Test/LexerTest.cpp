#include <catch2/catch_test_macros.hpp>

#include "Lexer.h"

#include <cstdint>
#include <string>
#include <vector>

SCENARIO("single line is tokenised")
{
    WHEN("the lexer receives the line of source code: \
            - int i = 5 + 5;")
    {
        std::string input { "int i = 5 + 5;\n" };
        Lexer lexer{ input };

        THEN("the line is tokenised into the following: \
            - { INT, IDENTIFIER, ASSIGNMENT, NUMBER, PLUS, NUMBER }")
            {
                const auto& tokens = lexer.tokenise();
                CHECK(tokens.size() == 7);
                CHECK(tokens[0].type == TokenType::INT);
                CHECK(tokens[1].type == TokenType::IDENTIFIER);
                CHECK(tokens[2].type == TokenType::ASSIGNMENT);
                CHECK(tokens[3].type == TokenType::NUMBER);
                CHECK(tokens[4].type == TokenType::PLUS);
                CHECK(tokens[5].type == TokenType::NUMBER);
                CHECK(tokens[6].type == TokenType::SEMICOLON);
            }
    }
}

SCENARIO("multiple lines tokenised")
{
    WHEN("the lexer receives the following lines of source code: \
            - int i = 5 + 5; \
            - print(i);")
    {
        std::string input { "int i = 5 + 5;\n print(i);\n" };
        Lexer lexer { input };

        THEN("the source is tokenised into the following: \
                - { INT, IDENTIFIER, ASSIGNMENT, NUMBER, PLUS, NUMBER, SEMICOLON, PRINT, LEFT_PARENTHESES, IDENTIFIER, RIGHT_PARENTHESES, SEMICOLON }")
                {
                    const auto& tokens = lexer.tokenise();
                    CHECK(tokens.size() == 12);
                    CHECK(tokens[0].type == TokenType::INT);
                    CHECK(tokens[1].type == TokenType::IDENTIFIER);
                    CHECK(tokens[2].type == TokenType::ASSIGNMENT);
                    CHECK(tokens[3].type == TokenType::NUMBER);
                    CHECK(tokens[4].type == TokenType::PLUS);
                    CHECK(tokens[5].type == TokenType::NUMBER);
                    CHECK(tokens[6].type == TokenType::SEMICOLON);
                    CHECK(tokens[7].type == TokenType::PRINT);
                    CHECK(tokens[8].type == TokenType::LEFT_PARENTHESES);
                    CHECK(tokens[9].type == TokenType::IDENTIFIER);
                    CHECK(tokens[10].type == TokenType::RIGHT_PARENTHESES);
                    CHECK(tokens[11].type == TokenType::SEMICOLON);
                }
    }
}

TEST_CASE("double character tokens")
{
        std::string input { "= == =\n" };
        Lexer lexer{ input };
        const auto& tokens = lexer.tokenise();
        CHECK(tokens.size() == 3);
        CHECK(tokens[0].type == TokenType::ASSIGNMENT);
        CHECK(tokens[1].type == TokenType::EQUALS);
        CHECK(tokens[2].type == TokenType::ASSIGNMENT);
}

TEST_CASE("multiple digit numbers")
{
    std::string input { "1 12 123 1234\n" };
    Lexer lexer { input };
    const auto& tokens = lexer.tokenise();
    CHECK(tokens.size() == 4);
    CHECK(tokens[0].value == "1");
    CHECK(tokens[1].value == "12");
    CHECK(tokens[2].value == "123");
    CHECK(tokens[3].value == "1234");

    for(auto token : tokens){
        CHECK(token.type == TokenType::NUMBER);
    }
}

TEST_CASE("correct identifiers")
{
    std::string input { "hello int hi print\n" };
    Lexer lexer { input };
    const auto& tokens = lexer.tokenise();
    CHECK(tokens.size() == 4);
    CHECK(tokens[0].type == TokenType::IDENTIFIER);
    CHECK(tokens[1].type == TokenType::INT);
    CHECK(tokens[2].type == TokenType::IDENTIFIER);
    CHECK(tokens[3].type == TokenType::PRINT);
}