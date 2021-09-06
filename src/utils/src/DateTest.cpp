#include "Date.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const auto year = 2021;
const auto month = 9;
const auto day = 6;
const std::string dateAsString{"2021-09-06"};
}

class DateTest : public Test
{
public:
};

TEST_F(DateTest, createDefaultDate_shouldCreateCurrentDate)
{
    ASSERT_NO_THROW(Date());
}

TEST_F(DateTest, createDateFromYearMonthDay)
{
    const auto date = Date{year, month, day};

    const auto actualDateAsString = date.toString();
    ASSERT_EQ(actualDateAsString, dateAsString);
}

TEST_F(DateTest, createDateFromString)
{
    const auto date = Date{dateAsString};

    const auto actualDateAsString = date.toString();
    ASSERT_EQ(actualDateAsString, dateAsString);
}

TEST_F(DateTest, toString)
{
    const auto date = Date{year, month, day};

    const auto actualDateAsString = date.toString();

    ASSERT_EQ(actualDateAsString, dateAsString);
}
