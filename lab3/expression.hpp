#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression
{
public:
    Expression(std::string postfix);
    std::string to_infix();
    double evaluate();

private:
    std::stack<Node *> stack{};
};

#endif