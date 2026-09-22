#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

#define ERROR_HOUR_RANGE "Hours outside range."
#define ERROR_MINUTE_RANGE "Minutes outside range."
#define ERROR_SECOND_RANGE "Seconds outside range."
#define ERROR_MILLISECOND_RANGE "Milliseconds outside range."
#define ERROR_VALID_INTEGER "Input was not an integer."
#define ERROR_ABNORMAL_TIMESTAMP "Abnormal timestamp."
#define ERROR_ILLEGAL_CHAR "Illegal char."

#define ASCII_DOT 46
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define ASCII_COLON 58

struct Time
{
private:
    int hour, minute, second, milliseconds;
    void check_values();

    void increment();

public:
    Time() : hour{0}, minute{0}, second{0}, milliseconds{0} {};
    Time(int _hour, int _minute, int _second, int _milliseconds = 0);
    Time(const std::string &s);

    bool is_am() const;

    std::string to_string(bool twelwe_hour = false) const;

    inline int get_hour() const { return hour; }
    inline int get_minute() const { return minute; }
    inline int get_second() const { return second; }
    inline int get_millisecond() const { return milliseconds; }
    inline int get_timestamp() const { return hour * 60 * 60 + minute * 60 + second; }

    Time &operator++();   // Prefix
    Time operator++(int); // Postfix

    float operator-(const Time &b) const;
    bool operator<(const Time &b) const;
    bool operator>(const Time &b) const;
    bool operator<=(const Time &b) const;
    bool operator>=(const Time &b) const;
    bool operator==(const Time &b) const;
    bool operator!=(const Time &b) const;
};

std::ostream &operator<<(std::ostream &os, const Time &a);

#endif