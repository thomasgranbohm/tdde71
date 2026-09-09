#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm> // for std::sort


class Runner
{
    
public:
    Runner(const std::string &line) : m_Hours{13}, m_Minutes{37}, m_Seconds{0}, m_Name{"John Doe"}
    {
        // Init runner from full line
        std::stringstream ss{line};
        ss >> m_Name;
        ss >> m_Hours;
        ss >> m_Minutes;
        ss >> m_Seconds;
    }
    
    unsigned int GetHours() const { return m_Hours; };
    unsigned int GetMinutes() const { return m_Minutes; };
    unsigned int GetSeconds() const { return m_Seconds; };
    std::string GetName() const { return m_Name; }
    
    void SetHours(unsigned int hours) { m_Hours = hours; };
    void SetMinutes(unsigned int minutes) { m_Minutes = minutes; };
    void SetSeconds(unsigned int seconds) { m_Seconds = seconds; };
    void SetName(const std::string& name) {m_Name = name; }
    
    std::string ToString() const
    {
        std::string s;
        std::stringstream ss;
        
        // String building again
        ss << std::right
        << std::setw(9)
        << m_Name
        << " | "
        << std::setfill('0')
        << m_Hours
        << ':'
        << std::right
        << std::setw(2)
        << m_Minutes
        << ':'
        << std::setw(2)
        << m_Seconds;
        
        std::getline(ss, s);
        return s;
    }
    
    unsigned int GetTotalSeconds() const
    {
        return m_Hours * 60 * 60 + m_Minutes * 60 + m_Seconds;
    }
    
private:
    unsigned int m_Hours;
    unsigned int m_Minutes;
    unsigned int m_Seconds;
    std::string m_Name;
};


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
                  return a.GetTotalSeconds() < b.GetTotalSeconds();
              });

    std::cout << "   Namn   |   Tid   \n"
              << "====================" << std::endl;
    for (int i = 0; i < n_rows; i++)
    {
        std::cout << runners.at(i).ToString() << std::endl;
    }

    return 0;
}
