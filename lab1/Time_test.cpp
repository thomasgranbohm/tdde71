#include "catch.hpp"
#include "Time.hpp"
#include <iostream>

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

        CHECK_THROWS(Time{13, 35, 60});
        CHECK_THROWS(Time{13, 60, 35});
        CHECK_THROWS(Time{24, 35, 35});

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

    SECTION("String")
    {
        Time t0{"00:00:00"};
        Time t1{"12:30:30"};
        Time t2{"23:59:59"};

        CHECK_THROWS(Time{"13:35:60"});
        CHECK_THROWS(Time{"13:60:35"});
        CHECK_THROWS(Time{"24:35:35"});

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
    SECTION("24 hour format no argument")
    {
        CHECK(t0.to_string() == "00:00:00");
    }

    // SECTION("24 hour format with argument")
    // {
    // }

    // SECTION("12 hour format")
    // {
    // }
}

TEST_CASE("Time stamps")
{

    Time a{4, 50, 20};
    Time b{15, 50, 20};
    Time c{0, 30, 10};
    Time d{12, 30, 10};

    CHECK(a.to_string() == "04:50:20");
    CHECK(a.to_string(true) == "04:50:20am");
    CHECK(b.to_string() == "15:50:20");
    CHECK(b.to_string(true) == "03:50:20pm");
    CHECK(c.to_string() == "00:30:10");
    CHECK(c.to_string(true) == "12:30:10am");
    CHECK(d.to_string() == "12:30:10");
    CHECK(d.to_string(true) == "12:30:10pm");

    Time e{12, 30, 10, 300};
    CHECK(e.to_string() == "12:30:10.300");
    CHECK(e.to_string(true) == "12:30:10.300pm");

    Time f{"12:30:10.300"};
    CHECK(f.to_string() == "12:30:10.300");
    CHECK(f.to_string(true) == "12:30:10.300pm");
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
        CHECK((a > b) == false);
        CHECK(a <= b);
        CHECK((a >= b) == false);

        CHECK(a == a);
        CHECK(a != b);
    }
    SECTION("Streaming")
    {
        Time a{13, 37, 20, 123};
        cout << a << endl; // TODO: Känns fel typ
        // FIXME: Blir fel hehehe
    }
}
