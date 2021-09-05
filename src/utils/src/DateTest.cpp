#include "Date.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const auto year = 2021;
const auto month = 9;
const auto day = 5;
const auto hour = 22;
const auto minute = 7;
const auto second = 0;
}
class DateTest : public Test
{
public:
};

TEST_F(DateTest, createDefaultDate_shouldCreateCurrentDate)
{
    ASSERT_NO_THROW(Date());
}

TEST_F(DateTest, createDateFromSecondsSinceEpoch)
{
    const auto secondsSinceEpoch = 1630879620;

    const auto date = Date{secondsSinceEpoch};

    ASSERT_EQ(date.year, 2021);
    ASSERT_EQ(date.month, 9);
    ASSERT_EQ(date.day, 5);
    ASSERT_EQ(date.hour, 22);
    ASSERT_EQ(date.minute, 7);
    ASSERT_EQ(date.second, 0);
}

TEST_F(DateTest, createDateYearMonthDayHourMinuteSecond)
{
    const auto date = Date{year, month, day, hour, minute, second};

    ASSERT_EQ(date.year, 2021);
    ASSERT_EQ(date.month, 9);
    ASSERT_EQ(date.day, 5);
    ASSERT_EQ(date.hour, 22);
    ASSERT_EQ(date.minute, 7);
    ASSERT_EQ(date.second, 0);
}

TEST_F(DateTest, getSecondsSinceEpoch)
{
    const auto date = Date{year, month, day, hour, minute, second};

    const auto secondsSinceEpoch = date.getSecondsSinceEpoch();

    ASSERT_EQ(secondsSinceEpoch, 1630879620);
}

TEST_F(DateTest, toString)
{
    const auto date = Date{year, month, day, hour, minute, second};

    const auto dateAsString = date.toString();

    ASSERT_EQ(dateAsString, "Sun Sep  5 22:07:00 2021 GMT");
}

