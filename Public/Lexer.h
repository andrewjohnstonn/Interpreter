#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType
{
    INT,
    STRING,
    NUMBER,
    IDENTIFIER,
    PLUS,
    MINUS,
    PRINT,
    SEMICOLON,
    ASSIGNMENT,
    EQUALS,
    LEFT_PARENTHESES,
    RIGHT_PARENTHESES
};

struct Token
{
    TokenType type;
    std::string value;
    int line;

    Token(TokenType t_, std::string v_, int l_) : type{ t_ }, value{ v_ }, line{ l_ } {}
};

class Lexer
{
    public:
        explicit Lexer(std::string const& input);

        const std::vector<Token> tokenise();

    private:
        std::string mInput;
        std::size_t mPosition;
        int mLine;
        std::unordered_map<std::string, TokenType> mKeywords;

        void initialiseKeywords() noexcept;
        bool endOfFile() const { return mPosition >= mInput.size(); }
        const char next() {  return mInput[mPosition++]; }
        const char peek() const { return endOfFile() ? '\0' : mInput[mPosition]; }
        bool nextChar(char const c);

        const Token readNumber(char c);
        const Token readIdentifier(char c);
        const Token readString(char c) const;
 
        const bool isAlphabetical(char const c) const;
        const bool isAlphanumeric(char const c) const;
        const bool isNumeric(char const c) const;
        const bool isWhitespace(char const c) const;
};