#pragma once
#include "lexer.hpp"
#include "ast.hpp"
#include <vector>

std::vector<ASTNode*> parse(const std::vector<Tokn>& tokns);