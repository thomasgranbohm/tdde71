#include "operand.hpp"

#include <iomanip>
#include <sstream>
#include <string>

std::string Real::get_string() const
{
    std::ostringstream oss;
    oss << std::setprecision(3) << std::fixed << value;
    return oss.str();
}

std::string Integer::get_string() const
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}