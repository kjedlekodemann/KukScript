#include <iostream>
#include <fstream>
#include <sstream>
#include "front/interpreter.hpp"
#include "front/ast.hpp"
#include "front/lexer.hpp"
#include "front/parser.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) { 
        std::cout << "Usage: " << argv[0] << " <script.kuk>\n";
        return 1; 
    }

    std::ifstream file(argv[1]);
    if (!file) { 
        std::cerr << "Error: Could not open file " << argv[1] << "\n"; 
        return 1; 
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();

    auto tokens = tokenize(code);

    std::cout << "Tokens:\n";
    for (auto &t : tokens) {
        std::cout << "Token: " << t.val << " Type: " << (int)t.type << "\n";
    }
    std::cout << "----------------------\n";
    auto ast = parse(tokens);

    std::cout << "Parsed AST nodes: " << ast.size() << "\n";
    for (auto node : ast) {
        if (auto v = dynamic_cast<VarDecl*>(node)) {
            std::cout << "VarDecl: " << v->name
                      << " Type:" << v->type
                      << " Value:" << v->value << "\n";
        }

        if (auto e = dynamic_cast<Output*>(node)) {
            std::cout << "Output: " << e->value << "\n";
        }
    }
    std::cout << "=== Running Kuk Script ===\n";
    run(ast);
    
    for (auto node : ast) {
        delete node;
    }




    return 0;
}