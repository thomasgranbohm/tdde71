#include "catch.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#define ERROR_HOUR_RANGE "Hours outside range."
#define ERROR_MINUTE_RANGE "Minutes outside range."
#define ERROR_SECOND_RANGE "Seconds outside range."

struct Time
{
private:
    int hour, minute, second;

    void check_values()
    {

        if (this->hour < 0 || this->hour > 24)
        {
            throw std::logic_error(ERROR_HOUR_RANGE);
        }
        if (this->minute < 0 || this->minute > 60)
        {
            throw std::logic_error(ERROR_MINUTE_RANGE);
        }
        if (this->second < 0 || this->second > 60)
        {
            throw std::logic_error(ERROR_SECOND_RANGE);
        }
    }

public:
    Time(int hour, int minute, int second) : hour{0}, minute{0}, second{0}
    {
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        check_values();
    }
    Time(std::string str) : hour{0}, minute{0}, second{0}
    {
        std::stringstream ss{str};
        int temp{};

        ss >> temp;
        this->hour = temp;
        // std::cout << "hour: " << this->hour << std::endl;

        ss.ignore(1);
        ss >> temp;
        this->minute = temp;
        // std::cout << "minute: " << this->minute << std::endl;

        ss.ignore(1);
        ss >> temp;
        this->second = temp;
        // std::cout << "second: " << this->second << std::endl;

        check_values();
    }

    std::string to_string(bool twelwe_hour = false) const
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

    bool is_am() const
    {
        return this->hour < 12;
    }

    int get_hour()
    {
        return this->hour;
    }

    int get_minute()
    {
        return this->minute;
    }

    int get_second()
    {
        return this->second;
    }
};

TEST_CASE("Time stamps")
{

    Time a{4, 50, 20};
    Time b{15, 50, 20};
    Time c{0, 30, 10};
    Time d{12, 30, 10};

    CHECK(a.to_string() == "04:50:20");
    CHECK(a.to_string(true) == "04:50:20am");
    CHECK(b.to_string() == "15:50:20");
    CHECK(b.to_string(true) == "03:50:20pm");
    CHECK(c.to_string() == "00:30:10");
    CHECK(c.to_string(true) == "12:30:10am");
    CHECK(d.to_string() == "12:30:10");
    CHECK(d.to_string(true) == "12:30:10pm");
}

TEST_CASE("Time stamp creation")
{

    // Errors on int init
    CHECK_THROWS(Time{25, 5, 20}, ERROR_HOUR_RANGE);
    CHECK_THROWS(Time{3, 65, 20}, ERROR_MINUTE_RANGE);
    CHECK_THROWS(Time{3, 20, 64}, ERROR_SECOND_RANGE);

    // Errors on string init
    CHECK_THROWS_WITH(Time{"25:00:00"}, ERROR_HOUR_RANGE);
    CHECK_THROWS_WITH(Time{"-1:00:00"}, ERROR_HOUR_RANGE);

    CHECK_THROWS_WITH(Time{"10:83:02"}, ERROR_MINUTE_RANGE);
    CHECK_THROWS_WITH(Time{"10:-0,4812:02"}, ERROR_MINUTE_RANGE);

    CHECK_THROWS_WITH(Time{"21:20:80"}, ERROR_SECOND_RANGE);
    CHECK_THROWS_WITH(Time{"21:20:-234"}, ERROR_SECOND_RANGE);
}

TEST_CASE("Edge cases")
{
    CHECK_THROWS(Time{24, 0, 0});
}