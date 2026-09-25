
#include <algorithm>
#include <cctype>
#include <sstream>

#include "expression.hpp"
#include "node.hpp"
#include "operator.hpp"
#include "operand.hpp"

Expression::Expression(std::string postfix)
{
    std::istringstream iss{postfix};
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

            Node *l{stack.top()};
            stack.pop();

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

double Expression::evaluate() const
{
    if (stack.empty())
    {
        throw std::logic_error("stack is empty");
    }

    return stack.top()->evaluate();
}

std::string Expression::to_string() const
{
    if (stack.empty())
    {
        throw std::logic_error("stack is empty");
    }

    return stack.top()->infix();
}