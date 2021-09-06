#include "Date.h"

#include "StringHelper.h"

namespace utils
{
namespace
{
const auto dateSeparator = "-";

date::year_month_day initializeYearMonthDayFromString(const std::string& dateAsString)
{
    const auto separatedDateString = StringHelper::split(dateAsString, dateSeparator);
    const int year = std::stoi(separatedDateString[0]);
    const unsigned int month = std::stoi(separatedDateString[1]);
    const unsigned int day = std::stoi(separatedDateString[2]);
    return date::year_month_day{date::year{year}, date::month{month}, date::day{day}};
}
}

Date::Date() : yearMonthDay{date::year_month_day{floor<date::days>(std::chrono::system_clock::now())}} {}

Date::Date(unsigned year, unsigned month, unsigned day)
    : yearMonthDay{date::year{static_cast<int>(year)}, date::month{month}, date::day{day}}
{
}

Date::Date(const std::string& dateAsString) : yearMonthDay{initializeYearMonthDayFromString(dateAsString)}
{
}

std::string Date::toString() const
{
    std::stringstream ss;
    ss << yearMonthDay;
    return ss.str();
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.yearMonthDay == rhs.yearMonthDay;
}

std::ostream& operator<<(std::ostream& ss, const Date& date)
{
    return ss << date.yearMonthDay;
}
}