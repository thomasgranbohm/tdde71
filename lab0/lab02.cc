#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

struct Runner
{
    std::string name;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
};

std::string to_string(Runner const &runner)
{
    std::string s;
    std::stringstream ss;

    // String building again
    ss << std::right
       << std::setw(9)
       << runner.name
       << " | "
       << std::setfill('0')
       << runner.hours
       << ':'
       << std::setw(2)
       << runner.minutes
       << ':'
       << std::setw(2)
       << runner.seconds;

    return ss.str();
}

unsigned int get_total_seconds(Runner const &runner)
{
    return runner.hours * 60 * 60 + runner.minutes * 60 + runner.seconds;
}

void open_file(std::ifstream &input_file)
{
    do
    {
        // Get filename
        std::cout << "Ange filnamn: ";
        std::string filename;
        std::cin >> filename;

        // Open file
        input_file.open(filename);

        // Print error message if file didn't open, otherwise return filestream
        if (!input_file.is_open())
        {
            std::cout << "FEL: Filen gick inte att öppna!" << std::endl;
        }
    } while (!input_file.is_open());
}

int get_n_rows(int max)
{
    while (true)
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

void sort(std::vector<Runner> &runners)
{
    // Bubble sort
    for (unsigned int i{0}; i < runners.size() - 1; ++i)
    {
        for (unsigned int j{0}; j < runners.size() - i - 1; ++j)
        {
            if (get_total_seconds(runners.at(j)) > get_total_seconds(runners.at(j + 1)))
            {
                Runner temp = runners.at(j);
                runners.at(j) = runners.at(j + 1);
                runners.at(j + 1) = temp;
            }
        }
    }
}

int main()
{
    std::vector<Runner> runners; // List of runners to be sorted and printed
    std::ifstream input_file{};
    std::stringstream ss{};
    std::string name;
    unsigned int hours, minutes, seconds;

    open_file(input_file);
    ss << input_file.rdbuf();

    while (ss >> name >> hours >> minutes >> seconds)
    {
        runners.push_back(Runner{name, hours, minutes, seconds});
    }

    int n_rows{get_n_rows(runners.size())};
    sort(runners);

    std::cout << "   Namn   |   Tid   \n"
              << "====================" << std::endl;
    for (int i{0}; i < n_rows; i++)
    {
        std::cout << to_string(runners.at(i)) << std::endl;
    }

    return 0;
}
