#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "expression.hpp"

using namespace std;

int main()
{
    string line;
    Expression *e{};
    std::vector<Expression *> saved{};

    while (getline(cin, line))
    {
        if (line.length() == 0)
            continue;

        if (line.at(0) == ':')
        {
            line.erase(0, 1);
            istringstream oss{line};
            string command{};
            oss >> command;

            if (command == "quit" || command == "exit")
            {
                break;
            }
            else if (command == "list")
            {
                cout << "===== List of saved expressions: =====" << endl;
                for (unsigned int i{0}; i < saved.size(); i++)
                {
                    cout << setw(3) << setfill(' ') << i << ". " << saved.at(i)->to_string() << endl;
                }
            }

            // FIXME: maybe some buggy behaviour here when e is undefined

            if (e == nullptr)
            {
                cerr << "No expression in memory!" << endl;
                continue;
            }

            if (command == "calc")
            {
                cout << e->evaluate() << endl;
            }
            else if (command == "postfix")
            {
                cout << e->to_postfix() << endl;
            }
            else if (command == "prefix")
            {
                cout << e->to_prefix() << endl;
            }
            else if (command == "infix")
            {
                cout << e->to_infix() << endl;
            }
            else if (command == "save")
            {
                saved.push_back(e);
            }
            else if (command == "activate")
            {
                int n{};
                oss >> n;

                e = saved.at(n);
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
