#include <iostream>
#include "expression.hpp"

using namespace std;

int main()
{

    // Expression *e = new Expression("1 + 2 - 3 * 4 / 5 ^ 6");

    // cout
    //     << e->evaluate() << endl
    //     << e->to_string() << endl
    //     << e->to_postfix() << endl
    //     << e->to_prefix() << endl
    //     << e->to_infix() << endl;

    // delete e;

    string line;
    Expression *e{};
    while (getline(cin, line))
    {
        if (line.at(0) == ':')
        {
            if (e == nullptr)
            {
                cerr << "No expression in memory!" << endl;
                continue;
            }

            line.erase(0, 1);

            if (line == "calc")
            {
                cout << e->evaluate() << endl;
            }
            else if (line == "postfix")
            {
                cout << e->to_postfix() << endl;
            }
            else if (line == "prefix")
            {
                cout << e->to_prefix() << endl;
            }
            else if (line == "infix")
            {
                cout << e->to_infix() << endl;
            }
            else if (line == "quit" || line == "exit")
            {
                break;
            }
        }
        else
        {
            try
            {
                e = std::move(new Expression(line));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    // tycker inte att det här borde behövas
    // går inte e "out of scope" när main returnerar?
    delete e;

    return 0;
}
