#include "Time.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

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

int get_next_integer(std::stringstream &ss, int n)
{
    char c{};
    std::stringstream cs;

    for (int i = 0; i < n; i++)
    {
        ss >> c;

        if (ss.fail())
            throw std::logic_error(ERROR_VALID_INTEGER);
        else if (c < ASCII_ZERO || c > ASCII_NINE)
            throw std::logic_error(ERROR_ILLEGAL_CHAR);

        cs << c;
    }

    return std::stoi(cs.str());
}

void skip_char(std::stringstream &ss, char desired)
{
    char c{};
    ss >> c;
    if (ss.fail())
        throw std::logic_error(ERROR_VALID_INTEGER);
    else if (c != desired)
        throw std::logic_error(ERROR_ILLEGAL_CHAR);
}

Time::Time(const std::string &str) : hour{0}, minute{0}, second{0}, milliseconds{0}
{
    int n_chars = str.size();

    if (n_chars > 12 || n_chars < 8)
    {
        throw std::out_of_range(ERROR_ABNORMAL_TIMESTAMP);
    }

    std::stringstream ss{str};

    this->hour = get_next_integer(ss, 2);
    skip_char(ss, ASCII_COLON);
    this->minute = get_next_integer(ss, 2);
    skip_char(ss, ASCII_COLON);
    this->second = get_next_integer(ss, 2);

    if (n_chars > 8)
    {
        skip_char(ss, ASCII_DOT);
        this->milliseconds = get_next_integer(ss, 3);
    }

    check_values();
}

bool Time::is_am() const
{
    return this->hour < 12;
}

std::string Time::to_string(bool twelwe_hour) const
{
    std::stringstream ss{};

    bool is_am = this->is_am();

    int hour{this->hour};

    if (twelwe_hour)
    {
        hour = ((hour + 11) % 12) + 1;
    }

    ss << std::setfill('0')
       << std::right
       << std::setw(2)
       << hour << ':'
       << std::setw(2)
       << this->minute << ':'
       << std::setw(2)
       << this->second;

    if (this->milliseconds != 0)
    {
        ss << '.' << this->milliseconds;
    }

    if (twelwe_hour)
    {
        ss << (is_am ? "am" : "pm");
    }

    return ss.str();
}

void Time::increment()
{
    if (++second == 60)
    {
        second %= 60;
        if (++minute == 60)
        {
            minute %= 60;
            if (++hour == 24)
            {
                hour %= 24;
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

std::ostream &Time::operator<<(std::ostream &os)
{
    os << this->to_string();
    return os;
};
