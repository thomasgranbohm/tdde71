#include "catch.hpp"

#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm> // For std::sort

#include "LinkedList.h"

void check_general_empty(LinkedList const &l)
{
    CHECK(l.is_empty());
    CHECK(l.get_size() == 0);
    CHECK_THROWS(l.front());
    CHECK_THROWS(l.back());
    CHECK_THROWS(l.get(0));
    CHECK_THROWS(l.get(-1));
    CHECK_THROWS(l.get(1));
    CHECK(l.to_string() == "[]");
}

TEST_CASE("Empty list")
{
    LinkedList a{};

    check_general_empty(a);

    CHECK_THROWS(a.pop_back());
    CHECK_THROWS(a.pop_front());
}

void check_general_one_elem(LinkedList const &l, const int v)
{
    CHECK_FALSE(l.is_empty());
    CHECK(l.get_size() == 1);
    CHECK_FALSE(l.is_empty());
    CHECK(l.front() == v);
    CHECK(l.back() == v);
    CHECK(l.get(0) == v);
    CHECK_THROWS(l.get(-1));
    CHECK_THROWS(l.get(1));
    std::ostringstream oss{};
    oss << '[' << v << ']';
    CHECK(l.to_string() == oss.str());
}

TEST_CASE("List with one element")
{
    LinkedList a{};
    int a_val{1};
    a.push_back(a_val);

    LinkedList b{};
    int b_val{-4};
    b.push_front(b_val);

    SECTION("General")
    {
        check_general_one_elem(a, a_val);
        check_general_one_elem(b, b_val);
    }

    SECTION("Sorting")
    {
        a.sort();
        check_general_one_elem(a, a_val);

        b.sort();
        check_general_one_elem(b, b_val);
    }

    SECTION("Pop Front")
    {
        int a_elem = a.pop_front();
        CHECK(a_elem == a_val);

        int b_elem = b.pop_front();
        CHECK(b_elem == b_val);

        check_general_empty(a);
        check_general_empty(b);

        CHECK_THROWS(a.pop_front());
        CHECK_THROWS(a.pop_back());
    }

    SECTION("Pop Back")
    {
        int a_elem = a.pop_back();
        CHECK(a_elem == a_val);

        int b_elem = b.pop_back();
        CHECK(b_elem == b_val);

        check_general_empty(a);
        check_general_empty(b);

        CHECK_THROWS(a.pop_back());
        CHECK_THROWS(a.pop_front());
    }
}

void push_front(LinkedList &l, std::vector<int> &l_vals, const int value)
{
    l.push_front(value);
    l_vals.insert(l_vals.begin(), value);
}

void push_back(LinkedList &l, std::vector<int> &l_vals, const int value)
{
    l.push_back(value);
    l_vals.push_back(value);
}

int pop_front(LinkedList &l, std::vector<int> &l_vals)
{
    int popped = l.pop_front();
    l_vals.erase(l_vals.begin());
    return popped;
}

int pop_back(LinkedList &l, std::vector<int> &l_vals)
{
    int popped = l.pop_back();
    l_vals.erase(l_vals.end());
    return popped;
}

void check_general_mult_elem(LinkedList const &l, std::vector<int> const &l_vals)
{
    long unsigned int const nr_of_elems{l_vals.size()};
    if (nr_of_elems < 2)
        throw std::logic_error("Do not call check_general_mult_elem on a list "
                               "with less than two elements!");
    CHECK(l.is_empty() == l_vals.empty());
    CHECK(l.get_size() == nr_of_elems);
    CHECK(l.front() == l_vals.front());
    CHECK(l.back() == l_vals.back());

    CHECK_THROWS(l.get(-1));
    CHECK_THROWS(l.get(nr_of_elems));

    // Check get for all values, and build string
    unsigned int i{0};
    std::ostringstream oss{};
    oss << '[';
    for (int v : l_vals)
    {
        CHECK(l.get(i) == v);

        oss << v;

        if (i < nr_of_elems - 1) // Add ", " to the string, except in last iteration
            oss << ", ";

        i++;
    }

    oss << ']';
    CHECK(l.to_string() == oss.str());
}

// For testing lists with multiple elements, we use
// std::vectors to keep track of the values our LinkedLists are storing.
// This enables us to write a general check function, check_general_mult_elem,
// that we can call instead manually writing things for every list.
// E.g. we can avoid the pain of manually writing
// "CHECK(l.to_string() == "[-135, -34, -4, 13, ...]" when we test sorting.

// First we test edge cases for check_general_mult_elem
TEST_CASE("check_general_mult_elem edge cases")
{
    LinkedList a{};
    std::vector<int> a_vals;
    CHECK_THROWS(check_general_mult_elem(a, a_vals));
    push_back(a, a_vals, 136613);
    CHECK_THROWS(check_general_mult_elem(a, a_vals));
    push_back(a, a_vals, 13);
    CHECK_NOTHROW(check_general_mult_elem(a, a_vals));
}

// Now we do the real test with multiple elements
TEST_CASE("List with multiple elements")
{
    LinkedList a{};
    std::vector<int> a_vals{};
    push_back(a, a_vals, 5);
    push_back(a, a_vals, -124);
    push_front(a, a_vals, -351);
    push_front(a, a_vals, 135315);
    push_front(a, a_vals, 0);
    check_general_mult_elem(a, a_vals);

    LinkedList b{};
    std::vector<int> b_vals{};
    push_front(b, b_vals, 4);
    push_back(b, b_vals, 4);
    push_back(b, b_vals, 4);
    check_general_mult_elem(b, b_vals);

    SECTION("Pop Front")
    {
        int a_front = a.front();
        int a_popped = pop_front(a, a_vals);
        CHECK(a_popped == a_front);
        check_general_mult_elem(a, a_vals);

        int b_front = b.front();
        int b_popped = pop_front(b, b_vals);
        CHECK(b_popped == b_front);
        check_general_mult_elem(b, b_vals);
    }

    SECTION("Pop Back")
    {
        int a_back = a.back();
        int a_popped = pop_back(a, a_vals);
        CHECK(a_popped == a_back);
        check_general_mult_elem(a, a_vals);

        int b_back = b.back();
        int b_popped = pop_back(b, b_vals);
        CHECK(b_popped == b_back);
        check_general_mult_elem(b, b_vals);
    }

    SECTION("Sort")
    {
        a.sort();
        std::sort(a_vals.begin(), a_vals.end());
        check_general_mult_elem(a, a_vals);

        b.sort();
        std::sort(b_vals.begin(), b_vals.end());
        check_general_mult_elem(b, b_vals);
    }
}

TEST_CASE("Copy Constructor")
{
    LinkedList other{};
    SECTION("'Other' is empty")
    {
        LinkedList b{other};
        check_general_empty(b);
        check_general_empty(other); // Check that other is unchanged

        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(13);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(13);
            check_general_empty(b);
        }

        // Check that modification of b doesn't affect other
    }
    SECTION("'Other' has one element")
    {
        int other_val = 3;
        other.push_back(other_val);
        LinkedList b{other};
        check_general_one_elem(b, other_val);
        check_general_one_elem(other, other_val); // Check that other is unchanged

        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.push_back(other_val + 31);
            check_general_one_elem(other, other_val);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.pop_back();
            other.push_back(other_val + 31);
            check_general_one_elem(b, other_val);
        }
    }
    SECTION("'Other' has more than one element")
    {
        std::vector<int> other_vals;
        push_back(other, other_vals, 1);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 7);
        LinkedList b{other};
        check_general_mult_elem(b, other_vals);
        check_general_mult_elem(other, other_vals); // Check that other is unchanged

        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.pop_front();
            b.push_back(315);
            check_general_mult_elem(other, other_vals);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.pop_back();
            other.pop_front();
            other.push_back(315);
            check_general_mult_elem(b, other_vals);
        }
    }
}

TEST_CASE("Copy Assignment")
{
    SECTION("'Other' is empty")
    {
        LinkedList other{};
        LinkedList b{};
        b = other;
        check_general_empty(b);
        check_general_empty(other);

        // Check that self assignment doesn't change b
        b = b;
        check_general_empty(b);

        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(13);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(13);
            check_general_empty(b);
        }
    }
    SECTION("'Other' has one element")
    {
        LinkedList other{};
        int other_val = 3;
        other.push_back(other_val);
        LinkedList b{};
        b = other;
        check_general_one_elem(b, other_val);
        check_general_one_elem(other, other_val); // Check that other is unchanged

        // Check that self assignment doesn't change b
        b = b;
        check_general_one_elem(b, other_val);

        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.push_back(other_val + 31);
            check_general_one_elem(other, other_val);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.pop_back();
            other.push_back(other_val + 31);
            check_general_one_elem(b, other_val);
        }
    }
    SECTION("'Other' has more than one element")
    {
        LinkedList other{};
        std::vector<int> other_vals;
        push_back(other, other_vals, 1);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 7);
        LinkedList b{};
        b = other;
        check_general_mult_elem(b, other_vals);
        check_general_mult_elem(other, other_vals); // Check that other is unchanged

        // Check that self assignment doesn't change b
        b = b;
        check_general_mult_elem(b, other_vals);

        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.pop_front();
            b.push_back(315);
            check_general_mult_elem(other, other_vals);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.pop_back();
            other.pop_front();
            other.push_back(315);
            check_general_mult_elem(b, other_vals);
        }
    }
}

#if 0
TEST_CASE("List with multiple elements")
{
    LinkedList a{};
    a.push_back(4);
    a.push_back(2);
    a.push_back(0);

    SECTION("remove front element")
    {
        CHECK(a.pop_front() == 4);
        CHECK_THROWS(a.get(2));
        CHECK(a.get(0) == 2);
        CHECK(a.front() == 2);
        CHECK(a.back() == 0);
    }

    SECTION("sorting")
    {
        a.sort();
        CHECK(a.to_string() == "[0, 2, 4]");
        CHECK(a.front() == 0);
        CHECK(a.back() == 4);
    }
}

#endif


// TEST_CASE("General")
// {
//     SECTION("is_empty")
//     {
//         LinkedList a{};

//         CHECK(a.is_empty());

//         a.push_back(42);
//         CHECK_FALSE(a.is_empty());
//         CHECK(a.get_size() == 1);
//     }

//     SECTION("push") {
//         LinkedList a{};

//         a.push_back(8);
//     }

//     SECTION("to_string, push and pop, front and back")
//     {
//         LinkedList a{};

//         CHECK(a.to_string() == "[]");

//         a.push_back(4);
//         CHECK(a.to_string() == "[4]");
//         CHECK(a.front() == 4);
//         CHECK(a.back() == 4);

//         CHECK(a.pop_front() == 4);
//         CHECK_THROWS(a.front());

//         a.push_back(3);
//         CHECK(a.pop_back() == 3);
//         CHECK_THROWS(a.back());

//         a.push_back(4);
//         a.push_back(1);
//         a.push_back(5);
//         a.push_back(2);
//         a.push_back(3);

//         CHECK(a.to_string() == "[4, 1, 5, 2, 3]");
//         CHECK(a.front() == 4);
//         CHECK(a.back() == 3);

//         a.pop_back();
//         CHECK(a.to_string() == "[4, 1, 5, 2]");
//         CHECK(a.back() == 2);

//         a.pop_front();
//         CHECK(a.to_string() == "[1, 5, 2]");
//         CHECK(a.front() == 1);
//     }

//     SECTION("Getting, front and back")
//     {
//         LinkedList a{};
//         CHECK_THROWS(a.front());
//         CHECK_THROWS(a.back());

//         a.push_back(1);
//         CHECK(a.front() == 1);
//         CHECK(a.back() == 1);

//         a.push_back(2);
//         CHECK(a.front() == 1);
//         CHECK(a.back() == 2);

//         a.push_back(3);
//         a.push_back(4);
//         a.push_back(5);

//         CHECK(a.front() == 1);
//         CHECK(a.back() == 5);

//         a.push_front(7);
//         CHECK(a.front() == 7);
//         CHECK(a.back() == 5);

//         CHECK(a.get(0) == 7);
//         CHECK(a.get(5) == 5);
//         // Check overflow error
//         CHECK_THROWS(a.get(6));
//         CHECK_THROWS(a.get(7));

//         // Check index moving
//         CHECK(a.get(4) == 4);
//         a.push_front(0);
//         CHECK(a.get(4) == 3);
//         CHECK(a.get(5) == 4);
//     }

//     SECTION("Copying")
//     {
//         LinkedList a{};

//         a.push_back(1);
//         a.push_back(2);
//         a.push_back(3);
//         a.push_back(4);
//         a.push_back(5);

//         LinkedList b{a};
//         LinkedList c{};
//         c = a;

//         a.push_back(a.pop_front());

//         // Check complete copy
//         CHECK(a.to_string() == "[2, 3, 4, 5, 1]");
//         CHECK(b.to_string() == "[1, 2, 3, 4, 5]");
//         CHECK(c.to_string() == "[1, 2, 3, 4, 5]");
//     }
//     SECTION("Move ctor")
//     {
//         LinkedList a{};

//         a.push_back(1);
//         a.push_back(2);
//         a.push_back(3);

//         LinkedList b{std::move(a)}; // Move ctor
//         CHECK(a.is_empty());
//         CHECK(b.get(0) == 1);
//         CHECK(b.get(1) == 2);
//         CHECK(b.get(2) == 3);
//     }
//     SECTION("Move assignment")
//     {
//         LinkedList a{};
//         LinkedList b{};
//         b.push_back(3);

//         a.push_back(1);
//         a.push_back(2);
//         a.push_back(3);

//         b = std::move(a); // Move assignment
//         CHECK(a.is_empty());
//         CHECK(b.get(0) == 1);
//         CHECK(b.get(1) == 2);
//         CHECK(b.get(2) == 3);
//     }

//     SECTION("Sorting")
//     {
//         LinkedList a{};

//         a.push_back(7);
//         a.push_back(12);
//         a.push_back(15);
//         a.push_back(20);
//         a.push_back(8);
//         a.push_back(19);
//         a.push_back(16);
//         a.push_back(5);
//         a.push_back(13);
//         a.push_back(3);

//         a.sort();
//         CHECK(a.to_string() == "[3, 5, 7, 8, 12, 13, 15, 16, 19, 20]");

//         // Empty list
//         LinkedList b{};
//         b.sort();
//         CHECK(b.to_string() == "[]");

//         LinkedList c{};
//         c.push_back(14);
//         c.push_back(5);
//         c.push_back(9);
//         c.push_back(14);
//         c.push_back(6);
//         c.push_back(19);
//         c.sort();
//         CHECK(c.to_string() == "[5, 6, 9, 14, 14, 19]");

//         // One element list
//         LinkedList d{};
//         d.push_front(5);
//         d.sort();
//         CHECK(d.to_string() == "[5]");

//         // Two element list
//         d.push_front(6);
//         d.sort();
//         CHECK(d.to_string() == "[5, 6]");

//         // Two same element list
//         LinkedList e{};
//         e.push_front(6);
//         e.push_front(6);
//         e.sort();
//         CHECK(e.to_string() == "[6, 6]");

//         // Odd length element list
//         LinkedList f{};
//         f.push_front(14);
//         f.push_front(7);
//         f.push_front(14);
//         f.sort();
//         CHECK(f.to_string() == "[7, 14, 14]");
//     }
// }