#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm> // for std::sort

struct Time
{
    int hours;
    int minutes;
    int seconds;

public: // Set a default time to
    Time() : hours{0}, minutes{0}, seconds{0} {}

    int GetTotalSeconds() const
    {
        return hours * 60 * 60 + minutes * 60 + seconds;
    }

    std::string ToString() const
    {
        std::stringstream ss;

        // String building
        ss << std::setfill('0')
           << hours
           << ':'
           << std::right
           << std::setw(2)
           << minutes
           << ':'
           << std::setw(2)
           << seconds;

        return ss.str();
    }
};

struct Runner
{
    std::string name;
    Time time;

public:
    Runner(const std::string &line) : name{"John Doe"}, time{}
    {
        // Init runner from full line
        std::stringstream ss{line};
        ss >> name;
        ss >> time.hours;
        ss >> time.minutes;
        ss >> time.seconds;
    }

    std::string ToString() const
    {
        std::string s;
        std::stringstream ss;

        // String building again
        ss << std::right
           << std::setw(9)
           << name
           << " | "
           << time.ToString();

        std::getline(ss, s);
        return s;
    }
};

// std::ifstream open_file()
// {
//     // Get filename
//     std::cout << "Ange filnamn: " << std::flush;
//     std::string filename;
//     std::cin >> filename;

//     // Open file
//     std::ifstream input_file{filename};

//     // Print error message if file didn't open and restart function.
//     if (input_file.is_open() == false)
//     {
//         std::cerr << "FEL: Filen gick inte att öppna!" << std::endl;
//         return open_file(); // Recussion maxxing
//     }

//     return input_file;
// }

// int get_n_rows(int max)
// {
//     // Clear input buffer
//     std::cin.clear();
//     std::cin.ignore(1024, '\n');

//     std::cout << "Ange antal rader: " << std::flush;
//     int n_rows{};

//     if (std::cin >> n_rows)
//     {
//         if (n_rows <= 0 || n_rows > max)
//         {
//             std::cerr << "FEL: Det finns inte " << n_rows << " rader i filen." << std::endl;
//             return get_n_rows(max);
//         }
//     }
//     else
//     {
//         std::cerr << "FEL: Inmatningen måste vara ett heltal!" << std::endl;
//         return get_n_rows(max);
//     }

//     return n_rows;
// }

std::ifstream open_file()
{
    while (true)
    {
        // Get filename
        std::cout << "Ange filnamn: ";
        std::string filename;
        std::cin >> filename;
    
        // Open file
        std::ifstream input_file{filename};
    
        // Print error message if file didn't open, otherwise return filestream
        if (input_file.is_open())
        {
            return input_file;
        }
        std::cout << "FEL: Filen gick inte att öppna!" << std::endl;
    }
}

int get_n_rows(int max)
{
    while(true)
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');

        int n_rows{};

        std::cout << "Ange antal rader: ";

        if (!(std::cin >> n_rows))
        {
            std::cout << "FEL: Inmatningen måste vara ett heltal!" << std::endl;
            continue;
        }

        if (n_rows < 1 || n_rows > max)
        {
            std::cout << "FEL: Det finns inte " << n_rows
                      << " rader i filen." << std::endl;
            continue;
        }

        return n_rows;
    }
}

int main()
{
    std::vector<Runner> runners; // List of runners to be sorted and printed

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
                  // If true, put a before b
                  return a.time.GetTotalSeconds() < b.time.GetTotalSeconds();
              });

    std::cout << "   Namn   |   Tid   \n"
              << "====================" << std::endl;
    for (int i = 0; i < n_rows; i++)
    {
        std::cout << runners.at(i).ToString() << std::endl;
    }

    return 0;
}
