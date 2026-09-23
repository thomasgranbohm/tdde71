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

    SECTION("to_string, push and pop")
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

    SECTION("Getting, front and back")
    {
        LinkedList a{};
        CHECK_THROWS(a.front());
        CHECK_THROWS(a.back());

        a.push_back(1);
        CHECK(a.front() == 1);
        CHECK(a.back() == 1);

        a.push_back(2);
        CHECK(a.front() == 1);
        CHECK(a.back() == 2);

        a.push_back(3);
        a.push_back(4);
        a.push_back(5);

        CHECK(a.front() == 1);
        CHECK(a.back() == 5);

        a.push_front(7);
        CHECK(a.front() == 7);
        CHECK(a.back() == 5);

        CHECK(a.get(0) == 7);
        CHECK(a.get(5) == 5);
        // Check overflow error
        CHECK_THROWS(a.get(6));
        CHECK_THROWS(a.get(7));

        // Check index moving
        CHECK(a.get(4) == 4);
        a.push_front(0);
        CHECK(a.get(4) == 3);
        CHECK(a.get(5) == 4);
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
    SECTION("Move ctor")
    {
        LinkedList a{};

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        LinkedList b{std::move(a)}; // Move ctor
        CHECK(a.is_empty());
        CHECK(b.get(0) == 1);
        CHECK(b.get(1) == 2);
        CHECK(b.get(2) == 3);
    }
    SECTION("Move assignment")
    {
        LinkedList a{};
        LinkedList b{};
        b.push_back(3);

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        b = std::move(a); // Move assignment
        CHECK(a.is_empty());
        CHECK(b.get(0) == 1);
        CHECK(b.get(1) == 2);
        CHECK(b.get(2) == 3);
    }

    SECTION("Sorting")
    {
        LinkedList a{};

        a.push_back(7);
        a.push_back(12);
        a.push_back(15);
        a.push_back(20);
        a.push_back(8);
        a.push_back(19);
        a.push_back(16);
        a.push_back(5);
        a.push_back(13);
        a.push_back(3);

        a.sort();
        CHECK(a.to_string() == "[3, 5, 7, 8, 12, 13, 15, 16, 19, 20]");

        // Empty list
        LinkedList b{};
        b.sort();
        CHECK(b.to_string() == "[]");

        LinkedList c{};
        c.push_back(14);
        c.push_back(5);
        c.push_back(9);
        c.push_back(14);
        c.push_back(6);
        c.push_back(19);
        c.sort();
        CHECK(c.to_string() == "[5, 6, 9, 14, 14, 19]");

        // One element list
        LinkedList d{};
        d.push_front(5);
        d.sort();
        CHECK(d.to_string() == "[5]");

        // Two element list
        d.push_front(6);
        d.sort();
        CHECK(d.to_string() == "[5, 6]");

        // Two same element list
        LinkedList e{};
        e.push_front(6);
        e.push_front(6);
        e.sort();
        CHECK(e.to_string() == "[6, 6]");

        // Odd length element list
        LinkedList f{};
        f.push_front(14);
        f.push_front(7);
        f.push_front(14);
        f.sort();
        CHECK(f.to_string() == "[7, 14, 14]");
    }
}