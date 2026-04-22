#include "Lexer.h"

Lexer::Lexer(std::string const& _input) :
    mInput { _input },
    mPosition{ 0 },
    mLine { 1 },
    mKeywords{}
{
    initialiseKeywords();
}

void Lexer::initialiseKeywords() noexcept
{
    mKeywords["int"] = TokenType::INT;
    mKeywords["print"] = TokenType::PRINT;
}

const std::vector<Token> Lexer::tokenise()
{
    std::vector<Token> tokens {};
    
    while(!endOfFile())
    {
        //TODO: ignore whitespace, then check for end of file again
        char current = next();
        //single char tokens
        switch(current)
        {
            case '+': tokens.emplace_back(TokenType::PLUS, "+", mLine); continue;
            case '-': tokens.emplace_back(TokenType::MINUS, "-", mLine); continue;
            case '(': tokens.emplace_back(TokenType::LEFT_PARENTHESIS, "(", mLine); continue;
            case ')': tokens.emplace_back(TokenType::RIGHT_PARENTHESIS, ")", mLine); continue;
            case ';': tokens.emplace_back(TokenType::SEMICOLON, ";", mLine);
        }
        //two char tokens (==, !=)
        switch(current)
        {
            case '=': 
                if(nextChar('=')){
                    tokens.emplace_back(TokenType::EQUALS, "==", mLine); continue;
                }
                else{
                    tokens.emplace_back(TokenType::ASSIGNMENT, "=", mLine); continue;
                }
        }

        if(isNumeric(current)){
            tokens.emplace_back(readNumber(current));
            continue;
        }

        if(isAlphabetical(current)){
            tokens.emplace_back(readIdentifier(current));
            continue;
        }

    }

    return tokens;
}

bool Lexer::nextChar(char const c)
{
    if((endOfFile()) || (mInput[mPosition] != c)) return false;
    mPosition++;
    return true;
}

const Token Lexer::readNumber(char c) const
{
    std::string number{ c };

    return Token{TokenType::NUMBER, number, mLine};
}

const Token Lexer::readIdentifier(char c) const
{
    std::string identifier { c };

    return Token{TokenType::IDENTIFIER, identifier, mLine};
}

const Token Lexer::readString(char c) const
{
    std::string str { c };

    return Token{TokenType::STRING, str, mLine};
}

const bool Lexer::isAlphabetical(char const c) const
{
    return(
        ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) 
    );
}

const bool Lexer::isAlphanumeric(char const c) const
{
    return (isAlphabetical(c)) || (isNumeric(c));
}

const bool Lexer::isNumeric(char const c) const
{
    return(
        (c >= 0) && (c <= 9)
    );
}

const bool Lexer::isWhitespace(char const c) const
{
    return (
        (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r')
    ); 
}