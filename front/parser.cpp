#include "parser.hpp"
#include <iostream>
#include <sstream>

Expression* parseExpression(const std::vector<Tokn>& tokns, size_t& i);
Expression* parsePrimary(const std::vector<Tokn>& tokns, size_t& i) {
    Tokn t = tokns[i];
    if (t.type == TokenType::NUMBER) {
        i++;
        return new Number(std::stoi(t.val));
    } else if (t.type==TokenType::ID) {
        i++;
        return new Variable(t.val);
    } else if (t.type==TokenType::LPAREN) {
        i++;
        Expression* e = parseExpression(tokns,i);
        if (tokns[i].type != TokenType::RPAREN) {std::cerr << "Expected )\n";}
        i++;
        return e;
    }
    return nullptr;
}
Expression* parseTerm(const std::vector<Tokn>& tokns, size_t& i) {
    Expression* left = parsePrimary(tokns,i);
    while (i < tokns.size() && (tokns[i].val=="*" || tokns[i].val=="/")) {
        char op = tokns[i].val[0];
        i++;
        Expression* right = parsePrimary(tokns,i);
        left = new BinaryOp(op,left,right);
    }
    return left;
}
Expression* parseExpression(const std::vector<Tokn>& tokns, size_t& i) {
    Expression* left = parseTerm(tokns,i);
    while (i < tokns.size() && (tokns[i].val=="+" || tokns[i].val=="-")) {
        char op = tokns[i].val[0];
        i++;
        Expression* right = parseTerm(tokns,i);
        left = new BinaryOp(op,left,right);
    }
    return left;
}

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

            node->expr = parseExpression(tokns,i);

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
    else if (t.type == TokenType::ID) {
        std::string varname = t.val;
        if (i + 1 < tokns.size() && tokns[i+1].type == TokenType::OPERATOR && tokns[i+1].val == "=") {
            i+=2;

            Expression* expr = parseExpression(tokns,i);
            if (i >= tokns.size() || tokns[i].type != TokenType::SEMICOLON) {
                std::cerr << "Expected ';' after assignment\n";
                delete expr;
                break;
            }
            i++;

            Assignment* node = new Assignment(varname, expr);
            ast.push_back(node);
            continue;
        }
    }
    else {
        std::cerr << "Unknown token: " << t.val << "\n";
        i++;
    }
    }
    return ast;
}
