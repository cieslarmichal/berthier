#pragma once

#include <string>
#include <date/date.h>
#include <chrono>

namespace utils
{
struct Date
{
    explicit Date();
    Date(unsigned year, unsigned month, unsigned day);

    std::string toString() const;

    date::year_month_day yearMonthDay;
};
}