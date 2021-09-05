#include "Date.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace utils
{
Date::Date()
{
    std::time_t epochTime;
    std::time(&epochTime);
    tm* timeInfo = std::localtime(&epochTime);
    year = 1900 + timeInfo->tm_year;
    month = timeInfo->tm_mon + 1;
    day = timeInfo->tm_mday;
    hour = timeInfo->tm_hour;
    minute = timeInfo->tm_min;
    second = timeInfo->tm_sec;
}

Date::Date(unsigned int secondsSinceEpoch)
{
    std::chrono::system_clock::time_point tp{std::chrono::seconds{secondsSinceEpoch}};
    std::cerr << tp.time_since_epoch().count();
    std::time_t epochTime = secondsSinceEpoch;
    tm* timeInfo = std::gmtime(&epochTime);
    year = 1900 + timeInfo->tm_year;
    month = timeInfo->tm_mon + 1;
    day = timeInfo->tm_mday;
    hour = timeInfo->tm_hour;
    minute = timeInfo->tm_min;
    second = timeInfo->tm_sec;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute,
           unsigned int second)
    : year{year}, month{month}, day{day}, hour{hour}, minute{minute}, second{second}
{
}

time_t Date::getSecondsSinceEpoch() const
{
    tm tm{};
    tm.tm_year = static_cast<int>(year)-1900;
    tm.tm_mon = static_cast<int>(month)-1;
    tm.tm_mday = static_cast<int>(day);
    tm.tm_hour = static_cast<int>(hour);
    tm.tm_min = static_cast<int>(minute);
    tm.tm_sec = static_cast<int>(second);
    tm.tm_isdst = -1;

    std::stringstream ss("Jan 9 2014 12:35:34");
    ss >> std::get_time(&tm, "%b %d %Y %H:%M:%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    return std::mktime(&tm);
}

std::string Date::toString() const
{
    std::stringstream ss;
    const auto secondsSinceEpoch = getSecondsSinceEpoch();
    ss << std::put_time(std::gmtime(&secondsSinceEpoch), "%c %Z");
    return ss.str();
}
}