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
    Expression(Expression const &) = delete;            // Copy constructor
    Expression &operator=(Expression const &) = delete; // Copy assignment
    Expression(Expression &&other);                     // move ctor
    Expression &operator=(Expression &&other);          // move assignment
    ~Expression() { empty_stack(); };                   // dtor

    std::string to_postfix() const;
    std::string to_prefix() const;
    std::string to_infix() const;
    double evaluate() const;

    std::string to_string() const;

private:
    std::stack<Node *> stack{};

    void check_empty() const;
    void empty_stack();
};

#endif