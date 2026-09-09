#ifndef TIME_H
#define TIME_H

#include <string>

#define ERROR_HOUR_RANGE "Hours outside range."
#define ERROR_MINUTE_RANGE "Minutes outside range."
#define ERROR_SECOND_RANGE "Seconds outside range."
#define ERROR_VALID_INTEGER "Input was not an integer."
#define ERROR_ABNORMAL_TIMESTAMP "Abnormal timestamp."

struct Time
{
private:
    int hour, minute, second;
    void check_values();

public:
    Time(int hour, int minute, int second);
    Time(const std::string &s);

    bool is_am() const;

    std::string to_string(bool twelwe_hour = false) const;

    inline int get_hour() const { return hour; }
    inline int get_minute() const { return minute; }
    inline int get_seconds() const { return second; }

    inline int get_timestamp() const { return hour * 60 * 60 + minute * 60 + second; }
};
#endif