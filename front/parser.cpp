#include "parser.hpp"
#include <iostream>

std::vector<ASTNode*> parse(const std::vector<Tokn>& tokns) {
    std::vector<ASTNode*> ast;
    size_t i=0;


    while (i < tokns.size()) {
        Tokn t = tokns[i];

        if (t.type == TokenType::DEF) {
            VarDecl* node = new VarDecl();

            i++;

            if (i >= tokns.size() || tokns[i].type != TokenType::ID) {
                std::cerr << "Expected variable name after def\n";
                break;
            }
            node->name = tokns[i].val;
            i++;

            if (i >= tokns.size() || tokns[i].type != TokenType::COLON) {
                std::cerr << "Expected ':' after variable name\n";
                break;
            }
            i++;

            if (i >= tokns.size() || tokns[i].type != TokenType::TYPE) {
                std::cerr << "Expected type after ':'\n";
                break;
            }
            node->type = tokns[i].val;
            i++;
        
            if (i >= tokns.size() || tokns[i].type != TokenType::OPERATOR) {
                std::cerr << "Expected '=' after type\n";
                break;
            }
            i++;

            if (i >= tokns.size() || 
            (tokns[i].type != TokenType::NUMBER && tokns[i].type != TokenType::STRING)) {
                std::cerr << "Expected literal value after '='\n";
                break;
            }
            node->value = tokns[i].val;
            i++;
            if (i >= tokns.size() || tokns[i].type != TokenType::SEMICOLON) {
                std::cerr << "Expected ';' after value\n";
                break;
            }
            i++;

            ast.push_back(node);
        }  
    else if (t.type == TokenType::OUTPUT) {
        Output* node = new Output();

        i++;
        if (i >= tokns.size() || tokns[i].type != TokenType::COLON) {
            std::cerr << "Expected ':' after output\n";
            break;
        }
        i++;

        if (i >= tokns.size() ||
        (tokns[i].type != TokenType::ID && tokns[i].type != TokenType::STRING)) {
            std::cerr << "Expected variable or string after output:\n";
            break;
        }
        node->value = tokns[i].val;
        i++;

        if (i >= tokns.size() || tokns[i].type != TokenType::SEMICOLON) {
            std::cerr << "Expected ';' after output value\n";
            break;
        }
        i++;

        ast.push_back(node);
    }
    else {
        std::cerr << "Unknown token: " << t.val << "\n";
        i++;
    }
    }
    return ast;
}
