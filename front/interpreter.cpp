#include "interpreter.hpp"
#include <iostream>

void run(const std::vector<ASTNode*>& ast) {
    std::unordered_map<std::string, int> variables;

    for (auto node : ast) {
        if (auto v = dynamic_cast<VarDecl*>(node)) {
            if(v->expr) {
                variables[v->name] = v->expr->evaluate(variables);
            } else {
                variables[v->name] = std::stoi(v->value);
            }
        }

        else if (auto o = dynamic_cast<Output*>(node)) {
            if (variables.find(o->value) != variables.end()) {
                std::cout << variables[o->value] << "\n";
            } else {
                std::cout << o->value << "\n";
            }
        }
        else if (auto a = dynamic_cast<Assignment*>(node)) {
            if (!a->expr) {
                std::cerr << "Runtime Error: assignment has no expression for " << a->name << "\n";
                continue;
            }
            int result = a->expr->evaluate(variables);
            variables[a->name] = result;
        }
        else {
            std::cerr << "Unknown AST node encountered.\n";
        }
    }
}