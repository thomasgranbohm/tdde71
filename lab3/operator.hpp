#ifndef OPERATOR_H
#define OPERATOR_H

#include "node.hpp"
#include "operand.hpp"

#include <cmath>

class Operator : public Node
{
public:
    ~Operator();

    Operator(const Operator &) = delete;
    Operator &operator=(const Operator &) = delete;

    std::string postfix() const override;
    std::string prefix() const override;
    std::string infix() const override;

    enum class sign : char
    {
        addition = '+',
        subtraction = '-',
        multiplication = '*',
        division = '/',
        power = '^',
        modulo = '%',
        condition = '?'
    };

    static char sign_to_char(Operator::sign _sign);

protected:
    Operator(Node *_child_left, Node *_child_right)
        : child_left{_child_left}, child_right{_child_right} {}

    virtual char get_sign() const = 0;
    Node *child_left;
    Node *child_right;
};

class Addition : public Operator
{
public:
    Addition(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::addition); }
};

class Subtraction : public Operator
{
public:
    Subtraction(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::subtraction); }
};

class Multiplication : public Operator
{
public:
    Multiplication(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::multiplication); }
};

class Division : public Operator
{
public:
    Division(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::division); }
};

class Power : public Operator
{
public:
    Power(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::power); }
};

class Modulo : public Operator
{
public:
    Modulo(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::modulo); }
};

class Condition : public Operator
{
public:
    Condition(Node *_child_left, Node *_child_right)
        : Operator{_child_left, _child_right} {}

    double evaluate() const override;

private:
    char get_sign() const override { return sign_to_char(sign::condition); }
};
#endif