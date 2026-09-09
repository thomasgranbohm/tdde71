#include "Time.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

void Time::check_values()
{
    if (this->hour < 0 || this->hour >= 24)
    {
        throw std::logic_error(ERROR_HOUR_RANGE);
    }
    if (this->minute < 0 || this->minute >= 60)
    {
        throw std::logic_error(ERROR_MINUTE_RANGE);
    }
    if (this->second < 0 || this->second >= 60)
    {
        throw std::logic_error(ERROR_SECOND_RANGE);
    }
}

Time::Time(int hour, int minute, int second) : hour{0}, minute{0}, second{0}
{
    this->hour = hour;
    this->minute = minute;
    this->second = second;

    Time::check_values();
}

Time::Time(const std::string &str) : hour{0}, minute{0}, second{0}
{
    std::stringstream ss{str};
    int temp{};

    if (ss >> temp)
    {
        this->hour = temp;
        std::cout << "hour: " << this->hour << std::endl;
        ss.clear();
        ss.ignore(1024, ':');
    }
    else
    {
        throw std::logic_error(ERROR_VALID_INTEGER);
    }

    if (ss >> temp)
    {
        this->minute = temp;
        std::cout << "minute: " << this->minute << std::endl;
        ss.clear();
        ss.ignore(1024, ':');
    }
    else
    {
        throw std::logic_error(ERROR_VALID_INTEGER);
    }

    if (ss >> temp)
    {
        this->second = temp;
        std::cout << "second: " << this->second << std::endl;
        ss.clear();
        ss.ignore(1024, ':');
    }
    else
    {
        throw std::logic_error(ERROR_VALID_INTEGER);
    }

    check_values();
    std::cout << this->to_string() << std::endl;
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

    if (twelwe_hour)
    {
        ss << (is_am ? "am" : "pm");
    }
    ss << std::endl;

    std::string s{};
    getline(ss, s);

    return s;
}

bool operator<(const Time &a, const Time &b)
{
    return a.get_timestamp() < b.get_timestamp();
};

bool operator>(const Time &a, const Time &b)
{
    return a.get_timestamp() > b.get_timestamp();
};

bool operator<=(const Time &a, const Time &b)
{
    return a.get_timestamp() <= b.get_timestamp();
};

bool operator>=(const Time &a, const Time &b)
{
    return a.get_timestamp() >= b.get_timestamp();
};

bool operator==(const Time &a, const Time &b)
{
    return a.get_timestamp() == b.get_timestamp();
};

bool operator!=(const Time &a, const Time &b)
{
    return a.get_timestamp() != b.get_timestamp();
};

std::ostream &operator<<(std::ostream &os, const Time &time)
{
    os << time.to_string();
    return os;
};
