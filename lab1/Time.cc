#include "Time.hpp"
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

// Checks if time values are out of bounds/range
void Time::check_values()
{
    if (this->hour < 0 || this->hour >= 24)
    {
        throw std::out_of_range(ERROR_HOUR_RANGE);
    }
    if (this->minute < 0 || this->minute >= 60)
    {
        throw std::out_of_range(ERROR_MINUTE_RANGE);
    }
    if (this->second < 0 || this->second >= 60)
    {
        throw std::out_of_range(ERROR_SECOND_RANGE);
    }
    if (this->milliseconds < 0 || this->milliseconds >= 1000)
    {
        throw std::out_of_range(ERROR_MILLISECOND_RANGE);
    }
}

Time::Time(int _hour, int _minute, int _second, int _milliseconds) : hour{_hour}, minute{_minute}, second{_second}, milliseconds{_milliseconds}
{
    Time::check_values();
}

// Returns the next n number of integers in an istringstream
int get_next_integer(std::istringstream &iss, int n)
{
    char c{};
    std::ostringstream cs;

    for (int i = 0; i < n; i++)
    {
        iss >> c;

        // Throw if it failed to read or if the character was not an integer
        if (iss.fail())
            throw std::logic_error(ERROR_VALID_INTEGER);
        else if (c < ASCII_ZERO || c > ASCII_NINE)
            throw std::logic_error(ERROR_ILLEGAL_CHAR);

        cs << c;
    }

    return std::stoi(cs.str());
}

// Skips the desired character in an istringstream by reading it
// to a temporary variable 'c'
void skip_char(std::istringstream &iss, char desired)
{
    char c{};
    iss >> c;

    // Throw if it failed to read or if the read character was not the desired one
    if (iss.fail())
        throw std::logic_error(ERROR_VALID_INTEGER);
    else if (c != desired)
        throw std::logic_error(ERROR_ILLEGAL_CHAR);
}

Time::Time(const std::string &str) : hour{0}, minute{0}, second{0}, milliseconds{0}
{
    int n_chars = str.size();

    // Throw if the length of the string does not match an expected format.
    // The expected formats are 'HH:MM:SS.mmm' and 'HH:MM:SS'.
    if (n_chars > 12 || n_chars < 8)
    {
        throw std::out_of_range(ERROR_ABNORMAL_TIMESTAMP);
    }

    // Extract the time data from the string by using an istringstream:
    std::istringstream iss{str};

    this->hour = get_next_integer(iss, 2);
    skip_char(iss, ASCII_COLON);
    this->minute = get_next_integer(iss, 2);
    skip_char(iss, ASCII_COLON);
    this->second = get_next_integer(iss, 2);

    // Extract the millisecond data if the string has the appropriate length
    if (n_chars > 8)
    {
        skip_char(iss, ASCII_DOT);
        this->milliseconds = get_next_integer(iss, 3);
    }

    check_values();
}

bool Time::is_am() const
{
    return this->hour < 12;
}

// Converts the time data to a string with one of the following formats:
//  - HH:MM:SS - if twelve_hour == false and milliseconds == 0
//  - HH:MM:SS(am/pm) - if twelve_hour == true and milliseconds == 0
//  - HH:MM:SS.mmm - if twelve_hour == false and milliseconds != 0
//  - HH:MM:SS.mmm(am/pm) - if twelve_hour == true and milliseconds != 0
std::string Time::to_string(bool twelwe_hour) const
{
    std::ostringstream oss{};

    bool is_am = this->is_am();

    int hour{this->hour};

    if (twelwe_hour)
    {
        hour = ((hour + 11) % 12) + 1;
    }

    oss << std::setfill('0')
       << std::right
       << std::setw(2)
       << hour << ':'
       << std::setw(2)
       << this->minute << ':'
       << std::setw(2)
       << this->second;

    if (this->milliseconds != 0)
    {
        oss << '.' << std::setw(3) << this->milliseconds;
    }

    if (twelwe_hour)
    {
        oss << (is_am ? "am" : "pm");
    }

    return oss.str();
}

// Increases the time by one second.
void Time::increment()
{
    if (++this->second == 60)
    {
        this->second = 0;
        if (++this->minute == 60)
        {
            this->minute = 0;
            if (++this->hour == 24)
            {
                this->hour = 0;
            }
        }
    }
}

Time &Time::operator++()
{
    increment();
    return *this;
}

Time Time::operator++(int)
{
    Time copy = *this;
    increment();
    return copy;
}

int Time::operator-(const Time &b) const
{
    return this->get_timestamp() - b.get_timestamp();
};

bool Time::operator<(const Time &b) const
{
    return this->get_timestamp() < b.get_timestamp();
};

bool Time::operator>(const Time &b) const
{
    return this->get_timestamp() > b.get_timestamp();
};

bool Time::operator<=(const Time &b) const
{
    return this->get_timestamp() <= b.get_timestamp();
};

bool Time::operator>=(const Time &b) const
{
    return this->get_timestamp() >= b.get_timestamp();
};

bool Time::operator==(const Time &b) const
{
    return this->get_timestamp() == b.get_timestamp();
};

bool Time::operator!=(const Time &b) const
{
    return this->get_timestamp() != b.get_timestamp();
};

std::ostream &operator<<(std::ostream &os, const Time &b)
{
    os << b.to_string();
    return os;
};
