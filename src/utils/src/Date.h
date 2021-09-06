#pragma once

#include <chrono>
#include <date/date.h>
#include <string>

namespace utils
{
class Date
{
public:
    explicit Date();
    Date(unsigned year, unsigned month, unsigned day);
    Date(const std::string&);

    std::string toString() const;
    friend bool operator==(const Date& lhs, const Date& rhs);

private:
    date::year_month_day yearMonthDay;
};

bool operator==(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream&, const Date&);
}