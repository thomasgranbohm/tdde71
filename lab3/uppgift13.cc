#include <iostream>

using namespace std;

int main()
{
  string line;
  while ( getline(cin, line) )
  {
    Expression e{line};
    cout << e.to_string() << endl
         << e.evaluate() << endl;
  }
  return 0;
}
