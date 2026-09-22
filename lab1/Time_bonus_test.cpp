// This file is complementary to Time_test.cpp.
// It only tests things related to the new millisecond functionality.

#include "catch.hpp"
#include "Time.hpp"
#include <sstream>

using namespace std;


TEST_CASE("Constructors and getters with milliseconds")
{
    SECTION("Default")
    {
        Time empty{};
        CHECK(empty.get_millisecond() == 0);
    }
    SECTION("Integer + Millisecond")
    {
        Time t0{0, 0, 0, 0};
        Time t1{12, 30, 30, 222};
        Time t2{23, 59, 59, 999};

        // Out of bounds:
        CHECK_THROWS(Time{13, 35, 60, 100});
        CHECK_THROWS(Time{13, 60, 35, 100});
        CHECK_THROWS(Time{24, 35, 35, 100});
        CHECK_THROWS(Time{13, 35, 35, 1000});
        CHECK_THROWS(Time{13, 35, 35, 1000});
        CHECK_THROWS(Time{13, 35, 35, 1000});
        CHECK_THROWS(Time{-1, 35, 35, 100});
        CHECK_THROWS(Time{35, -1, 35, 100});
        CHECK_THROWS(Time{35, 35, -1, 100});
        CHECK_THROWS(Time{35, 35, 35, -1});

        CHECK(t0.get_hour() == 0);
        CHECK(t0.get_minute() == 0);
        CHECK(t0.get_second() == 0);
        CHECK(t0.get_millisecond() == 0);
        CHECK(t1.get_hour() == 12);
        CHECK(t1.get_minute() == 30);
        CHECK(t1.get_second() == 30);
        CHECK(t1.get_millisecond() == 222);
        CHECK(t2.get_hour() == 23);
        CHECK(t2.get_minute() == 59);
        CHECK(t2.get_second() == 59);
        CHECK(t2.get_millisecond() == 999);
    }
    SECTION("String + Millisecond")
    {
        Time t0{"00:00:00.000"};
        Time t1{"12:30:30.222"};
        Time t2{"23:59:59.999"};

        // Out of bounds:
        CHECK_THROWS(Time{"13:35:60.100"});
        CHECK_THROWS(Time{"13:60:35.100"});
        CHECK_THROWS(Time{"24:35:35.100"});
        CHECK_THROWS(Time{"13:35:35.1000"});
        CHECK_THROWS(Time{"13:35:35.1000"});
        CHECK_THROWS(Time{"13:35:35.1000"});
        CHECK_THROWS(Time{"-1:35:35.100"});
        CHECK_THROWS(Time{"13:-3:35.100"});
        CHECK_THROWS(Time{"13:35:-3.100"});
        CHECK_THROWS(Time{"13:35:35.-10"});

        // Wrong format:
        CHECK_THROWS(Time{"123::456.100"});
        CHECK_THROWS(Time{"12:34:56:100"});
        CHECK_THROWS(Time{"12.34.56.100"});
        CHECK_THROWS(Time{"12.34.56:100"});
        CHECK_THROWS(Time{"12:3456.100"});
        CHECK_THROWS(Time{"12.34.56.10"});
        CHECK_THROWS(Time{"12.34.5:100"});
        CHECK_THROWS(Time{"12:3456.100"});
        CHECK_THROWS(Time{"12:34:56.100."});
        CHECK_THROWS(Time{"12:34:56.100.100"});
        CHECK_THROWS(Time{"a12:bb:35.123"});
        CHECK_THROWS(Time{"ab:cd:ef.ghi"});
        CHECK_THROWS(Time{"123456789"});

        CHECK(t0.get_hour() == 0);
        CHECK(t0.get_minute() == 0);
        CHECK(t0.get_second() == 0);
        CHECK(t0.get_millisecond() == 0);
        CHECK(t1.get_hour() == 12);
        CHECK(t1.get_minute() == 30);
        CHECK(t1.get_second() == 30);
        CHECK(t1.get_millisecond() == 222);
        CHECK(t2.get_hour() == 23);
        CHECK(t2.get_minute() == 59);
        CHECK(t2.get_second() == 59);
        CHECK(t2.get_millisecond() == 999);
    }
}

TEST_CASE("is_am with milliseconds")
{
    Time t0{"05:00:00.123"};
    Time t1{"14:00:00.123"};
    CHECK(t0.is_am());
    CHECK_FALSE(t1.is_am());
}

TEST_CASE("to_string with milliseconds")
{
    Time t5{12, 34, 56, 78};
    Time t6{12, 34, 56, 0};
    Time t7{"12:34:56.078"};
    Time t8{"12:34:56.000"};
    SECTION("24 hour format no argument")
    {
        CHECK(t5.to_string() == "12:34:56.078");
        CHECK(t6.to_string() == "12:34:56");
        CHECK(t7.to_string() == "12:34:56.078");
        CHECK(t8.to_string() == "12:34:56");
    }

    SECTION("24 hour format with argument")
    {
        CHECK(t5.to_string(false) == "12:34:56.078");
        CHECK(t6.to_string(false) == "12:34:56");
        CHECK(t7.to_string(false) == "12:34:56.078");
        CHECK(t8.to_string(false) == "12:34:56");
    }

    SECTION("12 hour format")
    {
        CHECK(t5.to_string(true) == "12:34:56.078pm");
        CHECK(t6.to_string(true) == "12:34:56pm");
        CHECK(t7.to_string(true) == "12:34:56.078pm");
        CHECK(t8.to_string(true) == "12:34:56pm");
    }
}

TEST_CASE("Operators with milliseconds")
{
    SECTION("Increment")
    {
        // Check prefix and postfix increment
        Time a{13, 37, 0, 400};
        CHECK((++a).to_string() == "13:37:01.400");
        CHECK((a++).to_string() == "13:37:01.400");
        CHECK(a.to_string() == "13:37:02.400");

        // Check minute passing
        Time b{13, 37, 59, 123};
        CHECK((++b).to_string() == "13:38:00.123");

        // Check hour passing
        Time c{13, 59, 59, 123};
        CHECK((++c).to_string() == "14:00:00.123");

        // Check day passing
        Time d{23, 59, 59, 123};
        CHECK((++d).to_string() == "00:00:00.123");
    }
    SECTION("Comparisons")
    {
        Time a{23, 59, 59};
        Time b{23, 59, 59, 1};
        Time c{23, 59, 59, 0};

        CHECK(a < b);
        CHECK_FALSE(a < c);
        CHECK_FALSE(b < c);

        CHECK_FALSE(a > b);
        CHECK_FALSE(a > c);
        CHECK(b > c);

        CHECK(a <= b);
        CHECK(a <= c);
        CHECK_FALSE(b <= c);

        CHECK_FALSE(a >= b);
        CHECK(a >= c);
        CHECK(b >= c);

        CHECK(b == b);
        CHECK_FALSE(a == b);
        CHECK_FALSE(b == c);
        CHECK(a == c);

        CHECK_FALSE(b != b);
        CHECK(a != b);
        CHECK_FALSE(a != c);
    }
    SECTION("Streaming")
    {
        Time t2{1, 2, 3, 4};
        ostringstream oss{};
        oss << t2;
        CHECK(oss.str() == t2.to_string());
    }
    SECTION("Subtraction")
    {
        Time t0{};
        Time t1{1, 2, 3};
        Time t2{1, 2, 3, 250};
        Time t3{1, 2, 4, 500};
        Time t4{1, 3, 4, 500};
        Time t5{2, 3, 4, 500};
        CHECK(t1 - t0 == 60.0f * 60.0f + 2 * 60.0f + 3.0f);
        CHECK(t2 - t1 == 0.25f);
        CHECK(t4 - t3 == 60.0f);
        CHECK(t5 - t4 == 60.0f * 60.0f);
    }
}
