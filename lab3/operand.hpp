#ifndef OPERAND_H
#define OPERAND_H

#include "node.hpp"

class Operand : public Node
{
public:
    std::string prefix() const override { return get_string(); }
    std::string infix() const override { return get_string(); }
    std::string postfix() const override { return get_string(); }

protected:
    virtual std::string get_string() const = 0;
};

class Real : public Operand
{
public:
    Real(const double _value) : value{_value} {}

    double evaluate() const override
    {
        return value;
    }

    std::string get_string() const override;

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

    std::string get_string() const override;

protected:
    const int value;
};

#endif