#include "Date.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const auto year = 2021;
const auto month = 9;
const auto day = 6;
}

class DateTest : public Test
{
public:
};

TEST_F(DateTest, createDefaultDate_shouldCreateCurrentDate)
{
    ASSERT_NO_THROW(Date());
}

TEST_F(DateTest, createDateYearMonthDay)
{
    const auto date = Date{year, month, day};

    ASSERT_EQ(date.yearMonthDay.year(), date::year{year});
    ASSERT_EQ(date.yearMonthDay.month(), date::month{month});
    ASSERT_EQ(date.yearMonthDay.day(), date::day{day});
}

TEST_F(DateTest, toString)
{
    const auto date = Date{year, month, day};

    const auto dateAsString = date.toString();

    ASSERT_EQ(dateAsString, "2021-09-06");
}

