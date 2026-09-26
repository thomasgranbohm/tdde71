#include <iostream>
#include "expression.hpp"

using namespace std;

int main()
{
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
                e = new Expression(line);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
    return 0;
}
