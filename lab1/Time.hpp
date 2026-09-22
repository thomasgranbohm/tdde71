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
    double get_timestamp() const { return hour * 60 * 60 + minute * 60 + second + milliseconds / 1000.0; } // Single precision ('float') cannot store the decimal part (milliseconds) accurately enough when (hour * 60 * 60 + minute * 60 + second) is large

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
    int hour, minute, second, milliseconds;
    void check_values() const;
    void increment();
};

std::ostream &operator<<(std::ostream &os, const Time &a);

#endif