#include "catch.hpp"
#include "LinkedList.hpp"

TEST_CASE("General")
{
    SECTION("is_empty")
    {
        LinkedList a{};

        CHECK(a.is_empty());

        a.push_back(42);
        CHECK_FALSE(a.is_empty());
        CHECK(a.get_size() == 1);
    }

    SECTION("to_string")
    {
        LinkedList a{};

        CHECK(a.to_string() == "[]");

        a.push_back(4);
        CHECK(a.to_string() == "[4]");

        a.push_back(1);
        a.push_back(5);
        a.push_back(2);
        a.push_back(3);

        CHECK(a.to_string() == "[4, 1, 5, 2, 3]");

        a.pop_back();
        CHECK(a.to_string() == "[4, 1, 5, 2]");

        a.pop_front();
        CHECK(a.to_string() == "[1, 5, 2]");
    }

    SECTION("Getting")
    {
        LinkedList a{};
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        a.push_back(5);

        // Check overflow error
        CHECK_THROWS(a.get(6));

        // Check index moving
        CHECK(a.get(3) == 4);
        a.push_front(0);
        CHECK(a.get(3) == 3);
        CHECK(a.get(4) == 4);
    }

    SECTION("Copying")
    {
        LinkedList a{};

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        a.push_back(5);

        LinkedList b{a};
        LinkedList c{};
        c = a;

        a.push_back(a.pop_front());

        // Check complete copy
        CHECK(a.to_string() == "[2, 3, 4, 5, 1]");
        CHECK(b.to_string() == "[1, 2, 3, 4, 5]");
        CHECK(c.to_string() == "[1, 2, 3, 4, 5]");
    }
}