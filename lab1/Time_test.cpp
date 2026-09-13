#include "catch.hpp"
#include "Time.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Constructors and getters")
{
    SECTION("Default")
    {
        Time empty{};
        CHECK(empty.get_hour() == 0);
        CHECK(empty.get_minute() == 0);
        CHECK(empty.get_second() == 0);
    }

    SECTION("Integer")
    {
        Time t0{0, 0, 0};
        Time t1{12, 30, 30};
        Time t2{23, 59, 59};

        // Out of bounds:
        CHECK_THROWS(Time{13, 35, 60});
        CHECK_THROWS(Time{13, 60, 35});
        CHECK_THROWS(Time{24, 35, 35});
        CHECK_THROWS( Time{-1,35,35} );
        CHECK_THROWS( Time{13,-1,35} );
        CHECK_THROWS( Time{13,35,-1} );

        CHECK(t0.get_hour() == 0);
        CHECK(t0.get_minute() == 0);
        CHECK(t0.get_second() == 0);
        CHECK(t1.get_hour() == 12);
        CHECK(t1.get_minute() == 30);
        CHECK(t1.get_second() == 30);
        CHECK(t2.get_hour() == 23);
        CHECK(t2.get_minute() == 59);
        CHECK(t2.get_second() == 59);
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

    SECTION("String")
    {
        Time t0{"00:00:00"};
        Time t1{"12:30:30"};
        Time t2{"23:59:59"};

        // Out of bounds:
        CHECK_THROWS(Time{"13:35:60"});
        CHECK_THROWS(Time{"13:60:35"});
        CHECK_THROWS(Time{"24:35:35"});
        CHECK_THROWS(Time{"-13:35:35"});
        CHECK_THROWS(Time{"13:-35:35"});
        CHECK_THROWS(Time{"13:35:-35"});

        // Wrong format:
        CHECK_THROWS(Time{"123::456"});
        CHECK_THROWS(Time{"12:34"});
        CHECK_THROWS(Time{"12.34.56"});
        CHECK_THROWS(Time("12:34:56.789.10"));
        CHECK_THROWS(Time("12:34:56.789:10"));
        CHECK_THROWS(Time("12:34:56.7.89"));

        CHECK(t0.get_hour() == 0);
        CHECK(t0.get_minute() == 0);
        CHECK(t0.get_second() == 0);
        CHECK(t1.get_hour() == 12);
        CHECK(t1.get_minute() == 30);
        CHECK(t1.get_second() == 30);
        CHECK(t2.get_hour() == 23);
        CHECK(t2.get_minute() == 59);
        CHECK(t2.get_second() == 59);
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
        CHECK_THROWS(Time{"-13:35:35.100"});
        CHECK_THROWS(Time{"13:-35:35.100"});
        CHECK_THROWS(Time{"13:35:-35.100"});
        CHECK_THROWS(Time{"13:35:35.-100"});

        // Wrong format:
        CHECK_THROWS(Time{"123::456.100"});
        CHECK_THROWS(Time{"12:34:56:100"});
        CHECK_THROWS(Time{"12.34.56.100"});
        CHECK_THROWS(Time{"12.34.56:100"});
        CHECK_THROWS(Time{"12:3456.100"});
        CHECK_THROWS(Time{"12.34.56.10"});
        CHECK_THROWS(Time{"12.34.5:100"});
        CHECK_THROWS(Time{"12:3456.100"});

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

TEST_CASE("is_am")
{
    Time t0{"05:00:00"};
    Time t1{"14:00:00"};
    CHECK(t0.is_am());
    CHECK_FALSE(t1.is_am());
}

TEST_CASE("to_string")
{
    Time t0{};
    Time t1{11, 59, 59};
    Time t2{12, 0, 0};
    Time t3{13, 0, 0};
    Time t4{23, 59, 59};
    Time t5{12, 34, 56, 78};
    Time t6{12, 34, 56, 0};
    Time t7{"12:34:56.078"};
    Time t8{"12:34:56.000"};
    SECTION("24 hour format no argument")
    {
        CHECK(t0.to_string() == "00:00:00");
        CHECK(t1.to_string() == "11:59:59");
        CHECK(t2.to_string() == "12:00:00");
        CHECK(t3.to_string() == "13:00:00");
        CHECK(t4.to_string() == "23:59:59");
        CHECK(t5.to_string() == "12:34:56.078");
        CHECK(t6.to_string() == "12:34:56");
        CHECK(t7.to_string() == "12:34:56.078");
        CHECK(t8.to_string() == "12:34:56");
    }

    SECTION("24 hour format with argument")
    {
        CHECK(t0.to_string(false) == "00:00:00");
        CHECK(t1.to_string(false) == "11:59:59");
        CHECK(t2.to_string(false) == "12:00:00");
        CHECK(t3.to_string(false) == "13:00:00");
        CHECK(t4.to_string(false) == "23:59:59");
        CHECK(t5.to_string(false) == "12:34:56.078");
        CHECK(t6.to_string(false) == "12:34:56");
        CHECK(t7.to_string(false) == "12:34:56.078");
        CHECK(t8.to_string(false) == "12:34:56");
    }

    SECTION("12 hour format")
    {
        CHECK(t0.to_string(true) == "12:00:00am");
        CHECK(t1.to_string(true) == "11:59:59am");
        CHECK(t2.to_string(true) == "12:00:00pm");
        CHECK(t3.to_string(true) == "01:00:00pm");
        CHECK(t4.to_string(true) == "11:59:59pm");
        CHECK(t5.to_string(true) == "12:34:56.078pm");
        CHECK(t6.to_string(true) == "12:34:56pm");
        CHECK(t7.to_string(true) == "12:34:56.078pm");
        CHECK(t8.to_string(true) == "12:34:56pm");
    }
}

TEST_CASE("Time stamp creation")
{
    // Errors on int init
    CHECK_THROWS(Time{25, 5, 20}, ERROR_HOUR_RANGE);
    CHECK_THROWS(Time{-14, 5, 20}, ERROR_HOUR_RANGE);
    CHECK_THROWS(Time{3, 65, 20}, ERROR_MINUTE_RANGE);
    CHECK_THROWS(Time{3, -2, 20}, ERROR_MINUTE_RANGE);
    CHECK_THROWS(Time{3, 20, 64}, ERROR_SECOND_RANGE);
    CHECK_THROWS(Time{3, 20, -1337}, ERROR_SECOND_RANGE);

    // Errors on string init
    CHECK_THROWS_WITH(Time{"25:00:00"}, ERROR_HOUR_RANGE);
    CHECK_THROWS_WITH(Time{"-1:00:00"}, ERROR_ILLEGAL_CHAR);

    CHECK_THROWS_WITH(Time{"10:83:02"}, ERROR_MINUTE_RANGE);
    CHECK_THROWS_WITH(Time{"10:-2.13:02"}, ERROR_ILLEGAL_CHAR);

    CHECK_THROWS_WITH(Time{"21:20:80"}, ERROR_SECOND_RANGE);
    CHECK_THROWS_WITH(Time{"21:20:-234"}, ERROR_ILLEGAL_CHAR);
}

TEST_CASE("Edge cases")
{
    // Abnormal, should be "00:00:00"
    CHECK_THROWS(Time{24, 0, 0}, ERROR_HOUR_RANGE);
    CHECK_THROWS(Time{0, 60, 0}, ERROR_MINUTE_RANGE);
    CHECK_THROWS(Time{0, 0, 60}, ERROR_SECOND_RANGE);

    // Not a normal timestamp, shouldn't have negative sign
    CHECK_THROWS_WITH(Time{"10:-0:02"}, ERROR_ILLEGAL_CHAR);

    // Abnormal timestamps, all containing floats
    CHECK_THROWS_WITH(Time{"10.3:53:3"}, ERROR_ILLEGAL_CHAR);
    CHECK_THROWS_WITH(Time{"10.3:5:3"}, ERROR_ILLEGAL_CHAR);
    CHECK_THROWS_WITH(Time{"10:53.134:3"}, ERROR_ILLEGAL_CHAR);
    CHECK_THROWS_WITH(Time{"10:53:3.141529"}, ERROR_ABNORMAL_TIMESTAMP); // Ok, maybe not this one for the bonus points
}

TEST_CASE("Operators")
{
    SECTION("Increment")
    {
        // Check prefix and postfix increment
        Time a{13, 37, 0, 400};
        CHECK((++a).to_string() == "13:37:01.400");
        CHECK((a++).to_string() == "13:37:01.400");
        CHECK(a.to_string() == "13:37:02.400");

        // Check minute passing
        Time b{13, 37, 59};
        CHECK((++b).to_string() == "13:38:00");

        // Check hour passing
        Time c{13, 59, 59};
        CHECK((++c).to_string() == "14:00:00");

        // Check day passing
        Time d{23, 59, 59};
        CHECK((++d).to_string() == "00:00:00");
    }
    SECTION("Decrement")
    {
        Time a{13, 37, 00};
        Time b{5, 40, 20};

        CHECK(a - b == 28600);
        CHECK(b - a == -28600);
        CHECK(a - a == 0);
    }
    SECTION("Comparisons")
    {
        Time a{13, 37, 0};
        Time b{17, 38, 0};

        CHECK(a < b);
        CHECK_FALSE(a > b);
        CHECK(a <= b);
        CHECK_FALSE(a >= b);

        CHECK(a == a);
        CHECK(a != b);
    }
    SECTION("Streaming")
    {
        Time t0{};
        Time t1{1, 2, 3};
        Time t2{1, 2, 3, 4};
        ostringstream oss{};
        SECTION("Test 1")
        {
            oss << t0;
            CHECK(oss.str() == t0.to_string());
        }
        SECTION("Test 2")
        {
            oss << t1;
            CHECK(oss.str() == t1.to_string());
        }
        SECTION("Test 3")
        {
            oss << t2;
            CHECK(oss.str() == t2.to_string());
        }
    }
}
