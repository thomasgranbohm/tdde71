#include "catch.hpp"
#include "expression.hpp"

TEST_CASE("simple expression")
{
    // Expression *a = new Expression("1 + 2 - 3");
    Expression *b = new Expression("1 + 2 - 3 / 4");

    SECTION("postfix")
    {
        // CHECK(a->to_postfix() == "1 2 + 3 -");
        CHECK(b->to_postfix() == "1 2 + 3 4 / -");
    }
    SECTION("prefix")
    {
        // CHECK(a->to_prefix() == "- + 1 2 3");
        CHECK(b->to_prefix() == "/ + 1 2 - 3 4");
    }
    SECTION("infix")
    {
        // CHECK(a->to_infix() == "( ( 1 + 2 ) - 3 )");
        CHECK(b->to_infix() == "( ( 1 + 2 ) - ( 3 / 4 ) )");
    }
}

TEST_CASE("harder expression")
{
    Expression *e = new Expression("1 + 2 - 3 * 4 / 5 ^ 6");

    SECTION("postfix")
    {
        CHECK(e->to_postfix() == "1 2 + 3 4 * 5 6 ^ / -");
    }
    SECTION("prefix")
    {
        CHECK(e->to_prefix() == "- + 1 2 / * 3 4 ^ 5 6");
    }
    SECTION("infix")
    {
        CHECK(e->to_infix() == "( ( 1 + 2 ) - ( ( 3 * 4 ) / ( 5 ^ 6 ) ) )");
    }
}