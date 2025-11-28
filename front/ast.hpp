#pragma once
#include <string>
#include <vector>

struct ASTNode {
    virtual ~ASTNode() {}
};

struct VarDecl : ASTNode {
    std::string name;
    std::string type;
    std::string value;
};

struct Output : ASTNode {
    std::string value;
};