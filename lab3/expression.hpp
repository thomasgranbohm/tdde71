#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stack>
#include <string>

#include "node.hpp"

class Expression
{
public:
    Expression(std::string postfix);
    std::string to_infix();
    double evaluate() const;

    std::string to_string() const;

private:
    std::stack<Node *> stack{};
};

#endif