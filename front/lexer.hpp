#pragma once
#include <string>
#include <vector>

// Yo, if you're reading here you're a nerd!

enum class TokenType {
    DEF,
    OUTPUT,
    IF,
    ELSE,
    WHILE,
    END,
    ID,
    TYPE,
    NUMBER,
    STRING,
    OPERATOR,
    COLON,
    SEMICOLON,
    UNKNOWN
};

struct Tokn {
    TokenType type;
    std::string val;
};

bool isKey(const std::string& word, TokenType &type);
std::vector<Tokn> tokenize(const std::string& code);  