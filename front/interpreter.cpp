#include "interpreter.hpp"
#include <iostream>

void run(const std::vector<ASTNode*>& ast) {
    std::unordered_map<std::string, std::string> variables;

    for (auto node : ast) {
        if (auto v = dynamic_cast<VarDecl*>(node)) {
            variables[v->name] = v->value;
        }

        else if (auto o = dynamic_cast<Output*>(node)) {
            if (variables.find(o->value) != variables.end()) {
                std::cout << variables[o->value] << "\n";
            } else {
                std::cout << o->value << "\n";
            }
        }
        else {
            std::cerr << "Unknown AST node encountered.\n";
        }
    }
}