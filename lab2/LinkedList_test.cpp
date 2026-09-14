#include "catch.hpp"
#include "LinkedList.hpp"

TEST_CASE("General")
{
    LinkedList l{};

    CHECK(l.is_empty());
    CHECK(l.get_size() == 0);

    l.push_back(42);
    CHECK_FALSE(l.is_empty());
    CHECK(l.get_size() == 1);
    CHECK(l.to_string() == "[42]");

    l.push_back(93);
    l.push_front(21);
    l.push_back(7);

    CHECK(l.front() == 21);
    CHECK(l.back() == 7);
    CHECK(l.to_string() == "[21, 42, 93, 7]");
}