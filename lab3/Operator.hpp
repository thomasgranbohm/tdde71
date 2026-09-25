#ifndef OPERATOR_H
#define OPERATOR_H

#include "Node.hpp"
#include "Operand.hpp"

class Operator : public Node
{
public:
    std::string postfix() const override;
    std::string prefix() const override;
    std::string infix() const override;

protected:
    Operator(
        const char _sign,
        Node *_child_left,
        Node *_child_right) : sign{_sign}, child_left{_child_left}, child_right{_child_right} {}

    char sign;
    Node *child_left;
    Node *child_right;
};

class Addition : public Operator
{
public:
    Addition(Node *_child_left, Node *_child_right) : Operator{'+', _child_left, _child_right} {}

    double evaluate() const override
    {
        return child_left->evaluate() + child_right->evaluate();
    }
};

class Multiplication : public Operator
{
public:
    Multiplication(Node *_child_left, Node *_child_right) : Operator{'*', _child_left, _child_right} {}

    double evaluate() const override
    {
        return child_left->evaluate() * child_right->evaluate();
    }
};

class Subtraction : public Operator
{
public:
    Subtraction(Node *_child_left, Node *_child_right) : Operator{'-', _child_left, _child_right} {}

    double evaluate() const override
    {
        return child_left->evaluate() - child_right->evaluate();
    }
};

class Division : public Operator
{
public:
    Division(Node *_child_left, Node *_child_right) : Operator{'/', _child_left, _child_right} {}

    double evaluate() const override;
};

class Power : public Operator
{
public:
    Power(Node *_child_left, Node *_child_right) : Operator{'^', _child_left, _child_right} {}

    double evaluate() const override;
};

#endif