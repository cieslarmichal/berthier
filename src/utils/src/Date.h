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
    Date(const std::string&);

    std::string toString() const;

    date::year_month_day yearMonthDay;
};

bool operator==(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream&, const Date&);
}