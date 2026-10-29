#include "operator.hpp"

#include <stdexcept>

Operator::~Operator()
{
    delete child_left;
    delete child_right;
} // Node::~Node is called after this

char Operator::sign_to_char(Operator::sign _sign)
{
    return static_cast<char>(_sign);
}

std::string Operator::postfix() const
{
    return child_left->postfix() + " " + child_right->postfix() + " " + get_sign();
}

std::string Operator::prefix() const
{
    return std::string{get_sign()} + " " + child_left->prefix() + " " + child_right->prefix();
}

std::string Operator::infix() const
{
    return "( " + child_left->infix() + " " + get_sign() + " " + child_right->infix() + " )";
}

double Addition::evaluate() const
{
    return child_left->evaluate() + child_right->evaluate();
}

double Subtraction::evaluate() const
{
    return child_left->evaluate() - child_right->evaluate();
}

double Multiplication::evaluate() const
{
    return child_left->evaluate() * child_right->evaluate();
}

double Division::evaluate() const
{
    double right_side{child_right->evaluate()};

    if (right_side == 0.0)
    {
        throw std::logic_error("division by zero not allowed");
    }

    return child_left->evaluate() / right_side;
}

double Power::evaluate() const
{
    double left_side{child_left->evaluate()};
    double right_side{child_right->evaluate()};

    // Real *casted_right{dynamic_cast<Real *>(child_right)};
    bool right_has_decimals{std::fmod(right_side, 1.0) != 0.0};

    if (left_side < 0 && right_has_decimals)
    {
        throw std::logic_error("negative base with floating point exponent not allowed");
    }
    else if (left_side == 0 && right_side < 0)
    {
        throw std::logic_error("zero as base with negative exponent not allowed");
    }

    return pow(left_side, right_side);
}

double Modulo::evaluate() const
{
    return fmod(child_left->evaluate(), child_right->evaluate());
}

double Condition::evaluate() const
{
    double left_side{child_left->evaluate()};

    return left_side != 0.0 ? child_right->evaluate() : 0.0;
};