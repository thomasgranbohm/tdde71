#include "catch.hpp"
#include "Time.hpp"

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
    CHECK_THROWS_WITH(Time{"-1:00:00"}, ERROR_HOUR_RANGE);

    CHECK_THROWS_WITH(Time{"10:83:02"}, ERROR_MINUTE_RANGE);
    CHECK_THROWS_WITH(Time{"10:-2.13:02"}, ERROR_MINUTE_RANGE);

    CHECK_THROWS_WITH(Time{"21:20:80"}, ERROR_SECOND_RANGE);
    CHECK_THROWS_WITH(Time{"21:20:-234"}, ERROR_SECOND_RANGE);
}

TEST_CASE("Edge cases")
{
    // Abnormal, should be "00:00:00"
    CHECK_THROWS(Time{24, 0, 0}, ERROR_HOUR_RANGE);
    CHECK_THROWS(Time{0, 60, 0}, ERROR_MINUTE_RANGE);
    CHECK_THROWS(Time{0, 0, 60}, ERROR_SECOND_RANGE);

    // Not a normal timestamp, shouldn't have negative sign
    CHECK_THROWS_WITH(Time{"10:-0:02"}, ERROR_ABNORMAL_TIMESTAMP);

    // Abnormal timestamps, all containing floats
    CHECK_THROWS_WITH(Time{"10.3:53:3"}, ERROR_ABNORMAL_TIMESTAMP);
    CHECK_THROWS_WITH(Time{"10:53.134:3"}, ERROR_ABNORMAL_TIMESTAMP);
    CHECK_THROWS_WITH(Time{"10:53:3.141529"}, ERROR_ABNORMAL_TIMESTAMP); // Ok, maybe not this one for the bonus points
}