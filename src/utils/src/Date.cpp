#include "Date.h"

#include <chrono>
#include <iostream>

namespace utils
{
Date::Date() : yearMonthDay{date::year_month_day{floor<date::days>(std::chrono::system_clock::now())}} {}


Date::Date(unsigned year, unsigned month, unsigned day)
    : yearMonthDay{date::year{static_cast<int>(year)}, date::month{month}, date::day{day}}
{
}

std::string Date::toString() const
{
    std::stringstream ss;
    ss << yearMonthDay;
    return ss.str();
}
}