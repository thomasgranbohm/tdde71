#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void clearCin()
{
    cin.clear();
    cin.ignore(1024, '\n');
}

void delA()
{
    int number{};
    float floating{};
    char c{};
    std::string s{};

    cout << "===== Del A Formaterad I/O =====" << endl
         << "Skriv in ett heltal: " << flush;

    cin >> number;
    clearCin();
    cout << "Du skrev in talet: " << number << endl
         << "Skriv in ett heltal och ett flyttal: " << flush;

    cin >> number;
    cin >> floating;
    clearCin();
    cout << "Du skrev in heltalet: " << number << endl
         << "Du skrev in flyttalet: " << floating << endl
         << "Skriv in ett flyttal och ett heltal: " << flush;

    cin >> floating;
    cin >> number;
    clearCin();
    cout
        << "Du skrev in heltalet: " << number << endl
        << "Du skrev in flyttalet: " << floating << endl
        << "Skriv in ett tecken: " << flush;

    cin >> c;
    clearCin();
    cout
        << "Du skrev in tecknet: " << c << endl
        << "Skriv in ett ord: " << flush;

    cin >> s;
    clearCin();
    cout
        << "Du skrev in ordet: " << s << endl;
}

void delB()
{
    int number{};
    std::string s{};
    char c{};

    cout << "===== Del B Escapesekvenser =====\n"
         << "Skriv in ett heltal och ett ord: " << flush;

    cin >> number >> s;
    clearCin();

    cout
        << "Du skrev in talet |" << number << "| och ordet |" << s << "|.\n"
        << "Skriv in ett tecken och ett ord: " << flush;

    cin >> c >> s;
    clearCin();

    cout << "Du skrev in ordet \"" << s << "\" och tecknet '" << c << "'." << endl;
}

void delC()
{
    float f{};
    std::string s{};

    cout << "===== Del C Inmatningsbuffer och tabellutskrift =====" << endl
         << "Skriv in en sträng och ett decimaltal fem gånger på samma rad:" << endl;

    cout.precision(3);

    for (int i = 0; i < 5; i++)
    {
        cin >> s;
        cin >> f;

        if (i == 0)
        {
            cout << "Här är talen i tabellform:" << endl
                 << setw(30) << setfill('=') << '=' << endl;
        }

        cout
            << std::left
            << s
            << std::setw(30 - s.size())
            << std::setfill('_')
            << std::fixed
            << std::right
            << f << endl;
    }
    clearCin();
}

void delD()
{
    std::string s{};
    cout << "===== Del D Oformaterad I/O =====" << endl
         << "Skriv in en rad text: " << flush;
    getline(cin, s);
    cout << endl
         << "Du skrev in: \"" << s << "\"" << endl
         << "Skriv in en till rad text: " << flush;
    getline(cin, s);
    cout << endl
         << "Du skrev in: \"" << s << "\"" << endl;
}

void delE()
{
    string s{};
    stringstream ss(s);
    cout << "===== Del E Sträng som datakälla (istf cin) =====" << endl
         << "Skriv in LiU-ID och fulständigt namn på samma rad:" << endl;
    getline(cin, s);
    cout << "Du skrev in: \"" << s << "\"" << endl;

    ss >> s;
    ss >> s;
    cout << "Förnamn: " << s << endl;
    getline(ss >> ws, s);
    cout << "Övriga namn: " << s << endl;
}

void delF()
{
    string s{};
    int n{};
    cout << "===== Del F Frivilligt =====" << endl
         << "Skriv in ett ord: ";
    cin >> s;
    n = s.size() + 1;
    clearCin();
    cout << '+' << setw(n) << setfill('-') << '+' << endl;
    cout << '|' << s << '|' << endl;
    cout << '+' << setw(n) << setfill('-') << '+' << endl;
}

int main()
{
    delA();
    delB();
    delC();
    delD();
    delE();
    delF();
    return 0;
}