#include "expression.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <stack>
#include <memory>

#include "node.hpp"
#include "operator.hpp"
#include "operand.hpp"
#include "postfix.hpp"

Expression::Expression(const std::string &infix)
    : root{nullptr}
{
    from_infix(infix);
}

Expression::~Expression()
{
    delete root;
}

Expression::Expression(Expression &&other)
    : root{nullptr}
{
    root = other.root;
    other.root = nullptr;
}

Expression &Expression::operator=(Expression &&other)
{
    if (this == &other)
        return *this;

    delete root;

    root = other.root;
    other.root = nullptr;

    return *this;

    // Alternatively, you can swap the two roots and let 'other' take care of it
    // in its destructor
}

void Expression::from_postfix(const std::string &postfix)
{
    // Commented out code is from before the smart pointer bonus assignment

    std::istringstream iss{postfix};
    std::string current{};
    // std::stack<Node *> stack{};
    std::stack<std::unique_ptr<Node>> stack{};

    delete root; // Delete old tree
    root = nullptr;

    while (iss >> current)
    {
        if (std::all_of(begin(current), end(current), ::isdigit))
        {
            // Integer
            int a{std::stoi(current)};

            // stack.push(new Integer{a});
            stack.push(std::make_unique<Integer>(a));
        }
        else if (isdigit(current.at(0)))
        {
            // Float
            double a{std::stod(current)};

            // stack.push(new Real{a});
            stack.push(std::make_unique<Real>(a));
        }
        else
        {
            // Operator
            if (stack.size() < 2)
                throw std::logic_error("Missing operands for operator");

            // Operator *a{};
            std::unique_ptr<Operator> a{};

            // Node *r{stack.top()};
            std::unique_ptr<Node> r{std::move(stack.top())};
            stack.pop();

            // Node *l{stack.top()};
            std::unique_ptr<Node> l{std::move(stack.top())};
            stack.pop();

            const op_sign::sign sign {op_sign::char_to_sign(current.at(0))};
            switch (sign)
            {
                case op_sign::sign::addition:
                    a = std::make_unique<Addition>(l.release(), r.release());
                    break;
                case op_sign::sign::subtraction:
                    a = std::make_unique<Subtraction>(l.release(), r.release());
                    break;
                case op_sign::sign::multiplication:
                    a = std::make_unique<Multiplication>(l.release(), r.release());
                    break;
                case op_sign::sign::division:
                    a = std::make_unique<Division>(l.release(), r.release());
                    break;
                case op_sign::sign::power:
                    a = std::make_unique<Power>(l.release(), r.release());
                    break;
                case op_sign::sign::modulo:
                    a = std::make_unique<Modulo>(l.release(), r.release());
                    break;
                case op_sign::sign::condition:
                    a = std::make_unique<Condition>(l.release(), r.release());
                    break;
                default:
                    throw std::logic_error("In expression::from_postfix: "
                                           "No operator matches the provided character.");
            }

            stack.push(std::move(a));
        }
    }
    if (stack.size() != 1)
        throw std::logic_error("Stack has 0 or more than 1 element "
                               "at end of Expression constructor");

    root = stack.top().release(); // If we don't release the top element, 'stack' will delete it ('stack' goes out of scope)
}

void Expression::from_infix(const std::string &infix)
{
    Postfix postfix{infix};
    from_postfix(postfix.to_string());
}

std::string Expression::to_postfix() const
{
    if (root == nullptr)
        throw std::logic_error("Expression is empty");
    return root->postfix();
}

std::string Expression::to_prefix() const
{
    if (root == nullptr)
        throw std::logic_error("Expression is empty");
    return root->prefix();
}

std::string Expression::to_infix() const
{
    if (root == nullptr)
        throw std::logic_error("Expression is empty");
    return root->infix();
}

double Expression::evaluate() const
{
    if (root == nullptr)
        throw std::logic_error("Expression is empty");
    return root->evaluate();
}