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

    a.sort();
    check_general_empty(a);
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
    std::vector<int> a_vals{};
    CHECK_THROWS(check_general_mult_elem(a, a_vals)); // 0 elements
    push_back(a, a_vals, 136613);
    CHECK_THROWS(check_general_mult_elem(a, a_vals)); // 1 element
    push_back(a, a_vals, 13);
    CHECK_NOTHROW(check_general_mult_elem(a, a_vals)); // 2 elements
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

        int new_val{13};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);
            check_general_empty(b);
        }

        // Check that modification of b doesn't affect other
    }
    SECTION("'Other' has one element")
    {
        int other_val{3};
        other.push_back(other_val);

        LinkedList b{other};

        check_general_one_elem(b, other_val);
        check_general_one_elem(other, other_val); // Check that other is unchanged

        int new_val{other_val + 31};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.push_back(new_val);
            check_general_one_elem(other, other_val);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.pop_back();
            other.push_back(new_val);
            check_general_one_elem(b, other_val);
        }
    }
    SECTION("'Other' has more than one element")
    {
        std::vector<int> other_vals{};
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
    LinkedList other{};
    SECTION("'Other' is empty")
    {
        LinkedList b{};
        b = other;
        check_general_empty(b);
        check_general_empty(other);

        // Check that self assignment doesn't change b
        b = b;
        check_general_empty(b);

        int new_val{13};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);
            check_general_empty(b);
        }
    }
    SECTION("'Other' has one element")
    {
        int other_val{3};
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

TEST_CASE("Move Constructor")
{
    LinkedList other{};

    SECTION("'Other' is empty")
    {
        LinkedList b{std::move(other)};
        check_general_empty(b);
#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        check_general_empty(other); // Check that other is emptied

        int new_val{13};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);
            check_general_empty(b);
        }
#endif
    }

    SECTION("'Other' has one element")
    {
        int other_val{3};
        other.push_back(other_val);

        LinkedList b{std::move(other)};

        check_general_one_elem(b, other_val);
#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        check_general_empty(other);

        int new_val{other_val + 31};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.push_back(new_val);

            check_general_one_elem(b, new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);

            check_general_one_elem(b, other_val);
            check_general_one_elem(other, new_val);
        }
#endif
    }

    SECTION("'Other' has more than one element")
    {
        std::vector<int> other_vals{};
        push_back(other, other_vals, 1);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 7);

        LinkedList b{std::move(other)};

        check_general_mult_elem(b, other_vals);
#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        check_general_empty(other);

        int new_val{315};
        SECTION("Check that modification of b doesn't affect other")
        {
            push_back(b, other_vals, new_val);

            check_general_mult_elem(b, other_vals);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);

            check_general_mult_elem(b, other_vals);
            check_general_one_elem(other, new_val);
        }
#endif
    }
}

TEST_CASE("Move Assignment")
{
    LinkedList other{};

    SECTION("'Other' is empty")
    {
        LinkedList b{};
        b = std::move(other);
        check_general_empty(b);
        // check_general_empty(other); //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.

        // Check that self assignment doesn't change b
        b = std::move(b);
        check_general_empty(b);
#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        int new_val{13};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.push_back(new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);
            check_general_empty(b);
        }
#endif
    }

    SECTION("'Other' has one element")
    {
        int other_val{3};
        other.push_back(other_val);

        LinkedList b{};
        b = std::move(other);

        check_general_one_elem(b, other_val);
        // check_general_empty(other); // Check that other is emptied. //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.

        // Check that self assignment doesn't change b
        b = std::move(b);
        check_general_one_elem(b, other_val);

#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        int new_val{other_val + 31};
        SECTION("Check that modification of b doesn't affect other")
        {
            b.pop_back();
            b.push_back(new_val);
            check_general_one_elem(b, new_val);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);
            check_general_one_elem(b, other_val);
            check_general_one_elem(other, new_val); // other is no longer empty
        }
#endif
    }

    SECTION("'Other' has more than one element")
    {
        std::vector<int> other_vals{};
        push_back(other, other_vals, 1);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 3);
        push_back(other, other_vals, 7);

        LinkedList b{};
        b = std::move(other);

        check_general_mult_elem(b, other_vals);
        // check_general_empty(other); // Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.


        // Check that self assignment doesn't change b
        b = std::move(b);
        check_general_mult_elem(b, other_vals);

#if 0 //  Bra tänkt med att kolla på listan efter att ni anropat std::move, men tanken är att det enda giltiga att göra med ett element som flyttats från är att kalla destruktorn på det. Att ni tittar på objektet efteråt blir därför lite konstigt.
        int new_val{315};
        SECTION("Check that modification of b doesn't affect other")
        {
            push_back(b, other_vals, new_val);

            check_general_mult_elem(b, other_vals);
            check_general_empty(other);
        }
        SECTION("Check that modification of other doesn't affect b")
        {
            other.push_back(new_val);

            check_general_mult_elem(b, other_vals);
            check_general_one_elem(other, new_val);
        }
#endif
    }
}
