#pragma once

#include <string>

namespace utils
{
struct Date
{
    explicit Date();
    Date(unsigned secondsSinceEpoch);
    Date(unsigned year, unsigned month, unsigned day);

    time_t getSecondsSinceEpoch() const;
    std::string toString() const;

    unsigned year, month, day;
};
}