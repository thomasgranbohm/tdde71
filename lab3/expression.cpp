#include <algorithm>
#include <cctype>
#include <sstream>

#include "expression.hpp"
#include "node.hpp"
#include "operator.hpp"
#include "operand.hpp"
#include "postfix.hpp"

Expression::Expression(std::string str)
{
    Postfix p{str};

    std::istringstream iss{p.to_string()};
    std::string current{};
    while (iss >> current)
    {
        if (std::all_of(begin(current), end(current), ::isdigit))
        {
            // Vi har hittat ett heltal
            int a = std::stoi(current);
            stack.push(new Integer{a});
        }
        else if (isdigit(current.at(0)))
        {
            // Vi hoppas ordet är ett flyttal
            double a = std::stod(current);
            stack.push(new Real{a});
        }
        else
        {
            // Vi hoppas ordet är en operator
            if (stack.size() < 2)
            {
                throw std::logic_error("malformatted expression");
            }

            Operator *a{};

            Node *r{stack.top()};
            stack.pop();

            // Vi vill fortfarande faktiskt ha kvar alla noder på stacken
            Node *l{stack.top()};
            stack.push(r);

            switch (current.at(0))
            {
            case Operator::signs::addition:
                a = new Addition{l, r};
                break;
            case Operator::signs::subtraction:
                a = new Subtraction{l, r};
                break;
            case Operator::signs::multiplication:
                a = new Multiplication{l, r};
                break;
            case Operator::signs::division:
                a = new Division{l, r};
                break;
            case Operator::signs::power:
                a = new Power{l, r};
                break;
            case Operator::signs::modulo:
                a = new Modulo{l, r};
                break;
            case Operator::signs::condition:
                a = new Condition{l, r};
                break;
            default:
                throw std::logic_error("undefined operator");
            }

            stack.push(a);
        }
    }
}

void Expression::check_empty() const
{
    if (stack.empty())
    {
        throw std::logic_error("stack is empty");
    }
}

double Expression::evaluate() const
{
    check_empty();

    return stack.top()
        ->evaluate();
}

std::string Expression::to_infix() const
{
    return to_string();
}

std::string Expression::to_postfix() const
{
    check_empty();

    return stack.top()
        ->postfix();
}

std::string Expression::to_prefix() const
{
    check_empty();

    return stack.top()
        ->prefix();
}

std::string Expression::to_string() const
{
    check_empty();

    return stack.top()
        ->infix();
}

Expression::Expression(Expression &&other)
{
    stack.swap(other.stack);
}

Expression &Expression::operator=(Expression &&other)
{
    if (this != &other)
    {
        stack.swap(other.stack);
    }

    return *this;
}

void Expression::empty_stack()
{
    while (!stack.empty())
    {
        delete stack.top();

        stack.pop();
    }
}