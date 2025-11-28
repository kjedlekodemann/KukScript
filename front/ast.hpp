#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

struct Expression {
    virtual int evaluate(std::unordered_map<std::string,int>& vars) = 0;
    virtual ~Expression() {}
};

struct ASTNode {
    virtual ~ASTNode() {}
};

struct VarDecl : ASTNode {
    std::string name;
    std::string type;
    std::string value;
    Expression* expr = nullptr;

    ~VarDecl() {delete expr;}
};

struct Output : ASTNode {
    std::string value;
};

struct Number : Expression {
    int value;
    Number(int v) : value(v) {}
    int evaluate(std::unordered_map<std::string,int>& vars) override {return value; }
};

struct Variable : Expression {
    std::string name;
    Variable(const std::string& n) : name(n) {}
    int evaluate(std::unordered_map<std::string,int>& vars) override {
        if (vars.find(name) == vars.end()) {std::cerr << "Undefine variable: " << name << "\n";}
        return vars[name];
    }
};

struct BinaryOp : Expression {
    char op;
    Expression* left;
    Expression* right;
    BinaryOp(char o, Expression* l, Expression* r) : op(o), left(l), right(r) {}
    int evaluate(std::unordered_map<std::string,int>& vars) override {
        int l = left->evaluate(vars);
        int r = right->evaluate(vars);
        switch(op){
            case '+': return l+r;
            case '-': return l-r;
            case '*': return l*r;
            case '/': if (r!=0) {return l/r;} else {std::cerr << "Error: Division by Zero\n";}
        }
        return 0;
    }
    ~BinaryOp() { delete left; delete right; }
};
struct Assignment : ASTNode {
    std::string name;
    Expression* expr;
    Assignment(const std::string& n, Expression* e) : name(n), expr(e) {}
    ~Assignment() {delete expr;}
};