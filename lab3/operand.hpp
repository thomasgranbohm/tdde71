#ifndef OPERAND_H
#define OPERAND_H

#include "node.hpp"

class Operand : public Node
{
    std::string prefix() const override { return postfix(); }
    std::string infix() const override { return postfix(); }
};

class Real : public Operand
{
public:
    Real(const double _value) : value{_value} {}

    double evaluate() const override
    {
        return value;
    }

    std::string postfix() const override;

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

    std::string postfix() const override;

protected:
    const int value;
};

#endif