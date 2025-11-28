#include "lexer.hpp"
#include <cctype>
#include <sstream>

bool isKey(const std::string &word, TokenType &type) {
    if (word=="def") { type = TokenType::DEF; return true; }
    if (word=="output") { type = TokenType::OUTPUT; return true; }
    if (word=="if") { type = TokenType::IF; return true; }
    if (word=="else") { type = TokenType::ELSE; return true; }
    if (word=="while") { type = TokenType::WHILE; return true; }
    if (word=="end") { type = TokenType::END; return true; }
    if (word=="int" || word=="float" || word=="str") { type = TokenType::TYPE; return true; }
    return false;
}

std::vector<Tokn> tokenize(const std::string &code) {
    std::vector<Tokn> tokns;
    size_t i=0;
    while (i<code.size()) {
        if (isspace(code[i])) { i++; continue; }

        //separation like semicolons and shit
        if (code[i]==';') {tokns.push_back({TokenType::SEMICOLON, ";"}); i++; continue; }
        if (code[i]==':') {tokns.push_back({TokenType::COLON, ":"}); i++; continue; }

        //num
        if (isdigit(code[i])) {
            std::string num;
            while (i < code.size() && (isdigit(code[i]) || code[i] == '.')) {num += code[i]; i++; }
            tokns.push_back({TokenType::NUMBER, num});
            continue;
        }

        //strings
        if (code[i] == '"') {
            std::string str;
            i++;
            while (i < code.size() && code[i] != '"') {str += code[i]; i++;}
            i++;
            tokns.push_back({TokenType::STRING, str});
            continue;
        }

        //ids
        if (isalpha(code[i]) || code[i]=='_') {
            std::string word;
            while (i < code.size() && (isalnum(code[i]) || code[i]=='_')) {word += code[i]; i++; }
            TokenType type;
            if (isKey(word,type)) { tokns.push_back({type,word}); }
            else {tokns.push_back({TokenType::ID,word});}
            continue;
        }

        //operators
        std::string op;
        if (code[i] == '=' || code[i] == '/' || code[i] == '*' || code[i] == '-' || code[i] == '+' || code[i] == '>' || code[i] == '<') {
            op += code[i]; i++;
            if (i<code.size() && code[i-1]=='=' && code[i] == '=') { op += '='; i++; }
            tokns.push_back({TokenType::OPERATOR, op});
            continue;
        }

        // ????
        tokns.push_back({TokenType::UNKNOWN, std::string(1,code[i])});
        i++;
    }
    return tokns;
}