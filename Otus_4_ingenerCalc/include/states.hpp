#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
public:
    Add(ASTNode* lhs, ASTNode* rhs)
        : ASTNode("+", lhs, rhs)
    {}

};

class Sub : public ASTNode {
public:
    Sub(ASTNode* lhs, ASTNode* rhs)
        : ASTNode("-", lhs, rhs)
    {}

};

class Mult : public ASTNode {
public:
    Mult(ASTNode* lhs, ASTNode* rhs)
        : ASTNode("*", lhs, rhs)
    {}

};

class Div : public ASTNode {
public:
    Div(ASTNode* lhs, ASTNode* rhs)
        : ASTNode("/", lhs, rhs)
    {}

};

class Number : public ASTNode {
 public:
     Number(int val)
         : ASTNode(std::to_string(val))
     {}
};

class Variable : public ASTNode {
public:
    Variable(const std::string& val)
        : ASTNode(val)
    {}
};
