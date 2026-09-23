#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

// Global constant error messages.
// These are stored in the header to expose them to programmers.
constexpr char ERROR_HOUR_RANGE[]         {"Hours outside range."};
constexpr char ERROR_MINUTE_RANGE[]       {"Minutes outside range."};
constexpr char ERROR_SECOND_RANGE[]       {"Seconds outside range."};
constexpr char ERROR_MILLISECOND_RANGE[]  {"Milliseconds outside range."};
constexpr char ERROR_VALID_INTEGER[]      {"Input was not an integer."};
constexpr char ERROR_ABNORMAL_TIMESTAMP[] {"Abnormal timestamp."};
constexpr char ERROR_ILLEGAL_CHAR[]       {"Illegal char."};

struct Time
{
public:
    Time() : hour{0}, minute{0}, second{0}, milliseconds{0} {};
    Time(int _hour, int _minute, int _second, int _milliseconds = 0);
    Time(const std::string &s);

    std::string to_string(bool twelwe_hour = false) const;
    
    // These are implicitly inline:
    bool is_am() const { return hour < 12; }
    int get_hour() const { return hour; }
    int get_minute() const { return minute; }
    int get_second() const { return second; }
    int get_millisecond() const { return milliseconds; }
    
    Time &operator++();   // Prefix
    Time operator++(int); // Postfix
    
    double operator-(const Time &b) const;
    bool operator<(const Time &b) const;
    bool operator>(const Time &b) const;
    bool operator<=(const Time &b) const;
    bool operator>=(const Time &b) const;
    bool operator==(const Time &b) const;
    bool operator!=(const Time &b) const;
    
private:
    int hour;
    int minute;
    int second;
    int milliseconds;
    
    void check_values() const;
    void increment();
    double get_timestamp() const { return hour * 60 * 60 + minute * 60 + second + milliseconds / 1000.0; } // Single precision ('float') cannot store the decimal part (milliseconds) accurately enough when (hour * 60 * 60 + minute * 60 + second) is large
};

std::ostream &operator<<(std::ostream &os, const Time &a);

#endif