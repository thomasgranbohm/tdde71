#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stack>
#include <string>

#include "node.hpp"

class Expression
{
public:
    Expression();
    Expression(std::string postfix);

    std::string to_postfix() const;
    std::string to_prefix() const;
    std::string to_infix() const;
    double evaluate() const;

    std::string to_string() const;

private:
    std::stack<Node *> stack{};

    void check_empty() const;
};

#endif