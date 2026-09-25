#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

class Node
{

public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0; // FIXME: double aswell
    virtual std::string postfix() const = 0;
    virtual std::string prefix() const = 0;
    virtual std::string infix() const = 0;
    Node(const Node &other) = delete;
    Node &operator=(const Node &other) = delete;
};

class Operand : public Node
{
};

class Real : public Operand
{
public:
    Real(const double _value) : value{_value} {}

    double evaluate() const override
    {
        return value;
    }

    std::string postfix() const override
    {
        std::ostringstream oss;
        oss << std::setprecision(3) << std::fixed << value;
        return oss.str();
    }
    std::string prefix() const override { return postfix(); }
    std::string infix() const override { return postfix(); }

protected:
    const double value;
};

class Integer : public Operand
{
public:
    Integer(const int _value) : value{_value} {}

    double evaluate() const override
    {
        return value;
    }

    std::string postfix() const override
    {
        std::ostringstream oss;
        oss << std::setprecision(3) << std::fixed << value;
        return oss.str();
    }
    std::string prefix() const override { return postfix(); }
    std::string infix() const override { return postfix(); }

protected:
    const int value;
};

class Operator : public Node
{
public:
    std::string postfix() const override
    {
        return child_left->postfix() + " " + child_right->postfix() + " " + sign;
    }
    std::string prefix() const override
    {
        // return sign + " " + child_left->prefix() + " " + child_right->prefix(); This be bugging
        return std::string{sign} + " " + child_left->prefix() + " " + child_right->prefix();
    }
    std::string infix() const override
    {
        return "( " + child_left->infix() + " " + sign + " " + child_right->infix() + " )";
    }

    Operator(const Operator &other) : sign{other.sign}, child_left{other.child_left}, child_right{other.child_right} {}

    Operator &operator=(const Operator &other)
    {
        if (this == &other)
            return *this;

        child_left = other.child_left;
        child_right = other.child_right;
        sign = other.sign;

        return *this;
    }

protected:
    Operator(
        const char _sign,
        Node *_child_left,
        Node *_child_right) : sign{_sign}, child_left{_child_left}, child_right{_child_right} {}

    char sign;
    Node *child_left;
    Node *child_right;
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
class Division : public Operator
{
public:
    Division(Node *_child_left, Node *_child_right) : Operator{'/', _child_left, _child_right} {}

    double evaluate() const override
    {
        double right_side = child_right->evaluate();

        if (right_side)
        {
            throw std::logic_error("division by zero not allowed");
        }

        return child_left->evaluate() / child_right->evaluate();
    }
};
class Power : public Operator
{
public:
    Power(Node *_child_left, Node *_child_right) : Operator{'^', _child_left, _child_right} {}

    double evaluate() const override
    {
        double left_side = child_left->evaluate();
        double right_side = child_right->evaluate();

        Real *casted_right = dynamic_cast<Real *>(child_right);

        if (left_side < 0 && casted_right != nullptr)
        {
            throw std::logic_error("negative base with floating point exponent not allowed");
        }
        else if (left_side == 0 && right_side < 0)
        {
            throw std::logic_error("zero as base with negative exponent not allowed");
        }

        return pow(left_side, right_side);
    }
};

#endif