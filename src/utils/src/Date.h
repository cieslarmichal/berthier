#pragma once

#include <string>

namespace utils
{
struct Date
{
    explicit Date();
    Date(unsigned secondsSinceEpoch);
    Date(unsigned year, unsigned month, unsigned day, unsigned hour = 0, unsigned minute = 0, unsigned second = 0);

    time_t getSecondsSinceEpoch() const;
    std::string toString() const;

    unsigned year, month, day, hour, minute, second;
};
}