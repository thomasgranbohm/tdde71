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
        CHECK_THROWS(Time{-1, 35, 35});
        CHECK_THROWS(Time{13, -1, 35});
        CHECK_THROWS(Time{13, 35, -1});

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

        // Out of bounds:
        CHECK_THROWS(Time{"13:35:60"});
        CHECK_THROWS(Time{"13:60:35"});
        CHECK_THROWS(Time{"24:35:35"});
        CHECK_THROWS(Time{"-1:35:35"});
        CHECK_THROWS(Time{"13:-3:35"});
        CHECK_THROWS(Time{"13:35:-3"});

        // Wrong format:
        CHECK_THROWS(Time{"12:34:56:"});
        CHECK_THROWS(Time{":34:56"});
        CHECK_THROWS(Time{"1:34:56"});
        CHECK_THROWS(Time{"12:3:56"});
        CHECK_THROWS(Time{"12:34:5"});
        CHECK_THROWS(Time{"12::56"});
        CHECK_THROWS(Time{"123::456"});
        CHECK_THROWS(Time{"12:34:"});
        CHECK_THROWS(Time{"a12:bb:35"});
        CHECK_THROWS(Time{"12:334:56"});
        CHECK_THROWS(Time{"12:34:566"});
        CHECK_THROWS(Time{"1:34:566"});
        CHECK_THROWS(Time{"ab:cd:ef"});
        CHECK_THROWS(Time{"1"});
        CHECK_THROWS(Time{"12:34"});
        CHECK_THROWS(Time{"12.34.56"});
        CHECK_THROWS(Time("12:34:56.789.10"));
        CHECK_THROWS(Time("12:34:56.789:10"));
        CHECK_THROWS(Time("12:34:56.7.89"));
        CHECK_THROWS(Time{"ab:cd:ef"});
        CHECK_THROWS(Time{"123456"});

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

    Time t2{"00:00:00"};
    Time t3{"12:00:00"};

    CHECK(t2.is_am());
    CHECK_FALSE(t3.is_am());
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
        CHECK(t1.to_string() == "11:59:59");
        CHECK(t2.to_string() == "12:00:00");
        CHECK(t3.to_string() == "13:00:00");
        CHECK(t4.to_string() == "23:59:59");
    }

    SECTION("24 hour format with argument")
    {
        CHECK(t0.to_string(false) == "00:00:00");
        CHECK(t1.to_string(false) == "11:59:59");
        CHECK(t2.to_string(false) == "12:00:00");
        CHECK(t3.to_string(false) == "13:00:00");
        CHECK(t4.to_string(false) == "23:59:59");
    }

    SECTION("12 hour format")
    {
        CHECK(t0.to_string(true) == "12:00:00am");
        CHECK(t1.to_string(true) == "11:59:59am");
        CHECK(t2.to_string(true) == "12:00:00pm");
        CHECK(t3.to_string(true) == "01:00:00pm");
        CHECK(t4.to_string(true) == "11:59:59pm");
    }
}

TEST_CASE("operators")
{
    SECTION("Increment")
    {
        // Check prefix and postfix increment
        Time a{13, 37, 0};
        CHECK((++a).to_string() == "13:37:01");
        CHECK((a++).to_string() == "13:37:01");
        CHECK(a.to_string() == "13:37:02");

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
    SECTION("Comparisons")
    {
        Time a{13, 37, 0};
        Time b{14, 40, 1};

        CHECK(a < b);
        CHECK_FALSE(a < a);
        CHECK_FALSE(b < a);

        CHECK_FALSE(a > b);
        CHECK_FALSE(a > a);
        CHECK(b > a);

        CHECK(a <= b);
        CHECK(a <= a);
        CHECK_FALSE(b <= a);

        CHECK_FALSE(a >= b);
        CHECK(a >= a);
        CHECK(b >= a);

        CHECK(a == a);
        CHECK_FALSE(a == b);
        CHECK_FALSE(b == a);
        
        CHECK_FALSE(a != a);
        CHECK(a != b);
        CHECK(b != a);
    }
    SECTION("Streaming")
    {
        Time t0{};
        Time t1{1, 2, 3};
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
    }
}