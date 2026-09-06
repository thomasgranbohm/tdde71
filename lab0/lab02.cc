#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm> // for std::sort

// What do you have to change if you omit "using namespace std;" ?

struct Time
{
    int hours;
    int minutes;
    int seconds;

public: // Set a default time to
    Time() : hours{0}, minutes{0}, seconds{0} {}

    int getTotalSeconds() const
    {
        return hours * 60 * 60 + minutes * 60 + seconds;
    }

    std::string toString() const
    {
        std::stringstream ss;

        // String building
        ss << std::left
           << std::setfill('0')
           << hours
           << ':'
           << std::right
           << std::setw(2)
           << minutes
           << ':'
           << std::setw(2)
           << seconds;

        std::string s{};
        std::getline(ss, s);
        return s;
    }
};

struct Runner
{
    std::string name;
    Time time;

public:
    Runner(const std::string &str) : name{"John Doe"}, time{}
    {
        // Init runner from full line
        std::stringstream strstream{str};
        strstream >> name;
        strstream >> time.hours;
        strstream >> time.minutes;
        strstream >> time.seconds;
    }

    std::string toString() const
    {
        std::string s;
        std::stringstream ss;

        // String building again
        ss << std::right
           << std::setw(9)
           << name
           << " | "
           << time.toString();

        std::getline(ss, s);
        return s;
    }
};

std::ifstream open_file()
{
    // Get filename
    std::cout << "Ange filnamn: " << std::flush;
    std::string filename;
    std::cin >> filename;

    // Open file
    std::ifstream input_file(filename);

    // Print error message if file didn't open and restart function.
    if (input_file.is_open() == false)
    {
        std::cerr << "FEL: Filen gick inte att öppna!" << std::endl;
        return open_file(); // Recussion maxxing
    }

    return input_file;
}

int get_n_rows(int max)
{
    // Clear input buffer
    std::cin.clear();
    std::cin.ignore(1024, '\n');

    std::cout << "Ange antal rader: " << std::flush;
    int n_rows{};

    if (std::cin >> n_rows)
    {
        if (n_rows <= 0 || n_rows > max)
        {
            std::cerr << "FEL: Det finns inte " << n_rows << " rader i filen." << std::endl;
            return get_n_rows(max);
        }
    }
    else
    {
        std::cerr << "FEL: Inmatningen måste vara ett heltal!" << std::endl;
        return get_n_rows(max);
    }

    return n_rows;
}

int main()
{
    std::vector<Runner> runners;

    std::ifstream input_file = open_file();
    std::string line;

    while (getline(input_file, line))
    {
        runners.push_back(Runner{line});
    }

    int n_rows = get_n_rows(runners.size());

    // Sort runners
    std::sort(runners.begin(), runners.end(),
              [](Runner a, Runner b)
              {
                  return a.time.getTotalSeconds() < b.time.getTotalSeconds();
              });

    std::cout << "   Namn   |   Tid   \n"
              << "====================" << std::endl;
    for (int i = 0; i < n_rows; i++)
    {
        std::cout << runners.at(i).toString() << std::endl;
    }

    return 0;
}
