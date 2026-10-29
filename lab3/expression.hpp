#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <stack>
#include "node.hpp"

class Expression
{
public:
    Expression()
        : root{nullptr} {}

    Expression(const std::string &infix);

    ~Expression();

    Expression(const Expression &) = delete;
    Expression &operator=(const Expression &) = delete;

    Expression(Expression &&other);
    Expression &operator=(Expression &&other);

    std::string to_postfix() const;

    std::string to_prefix() const;

    std::string to_infix() const;
    
    double evaluate() const;

private:
    void from_postfix(const std::string &postfix);

    void from_infix(const std::string &infix);

    Node *root;
};

#endif