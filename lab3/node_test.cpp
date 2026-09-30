#include <limits>
#include <memory>

#include "operand.hpp"
#include "operator.hpp"
#include "catch.hpp"

TEST_CASE("operand real")
{
    Operand *pi{new Real{3.14}};

    CHECK(pi->evaluate() == 3.14);
    CHECK(pi->postfix() == "3.140");
}

TEST_CASE("addition")
// TEST_CASE is like a loop doing one SECTION each iteration
// meaning we get a fresh "pi" and "e" for each section
{
    // Done each iteration of the TEST_CASE
    Node *pi = new Real{3.14};
    Node *e = new Real{2.72};

    SECTION("commutative case pi+e") // Done the first iteration only
    {
        Node *pluslr = new Addition{pi, e};

        CHECK(pluslr->evaluate() == 5.86);
        CHECK(pluslr->postfix() == "3.140 2.720 +");
    }

    SECTION("commutative case e+pi") // Done the second iteration only
    {
        Node *plusrl = new Addition{e, pi};

        CHECK(plusrl->evaluate() == 5.86);
        CHECK(plusrl->postfix() == "2.720 3.140 +");
    }

    // Note: reusing "pi" and "e" to create several Addition nodes will
    // make memory deallocation difficult, using SECTION to have a new
    // set of pi and e for each section solves this.
    // Doing the actual deallocation is your task once you have suitable
    // destructors.
}

// If catch report 0.42 != 0.42 you are likely to have a small
// rounding error in some invisible decimal place. In such case you
// can compare if the difference is small enough to consider two
// doubles equal anyway.
bool compare_equal(double a, double b)
{
    return std::abs(a - b) <= 0.001; // only care about thosands in our calculations
}

TEST_CASE("test case ignoring rounding errors")
{
    Node *a = new Real{0.01};
    Node *b = new Real{0.09};

    SECTION("testing add with rounding error")
    {
        Node *plus = new Addition{a, b};

        // abs() exists in several versions, a bad combination of includes
        // and namespaces will land you in the old C-version for integers
        // without any warning, we test for this!
        CHECK(std::abs(-0.1) == 0.1); // make sure we use floating point "abs"

        // CHECK( plus->evaluate() == 0.1 ); // Rounding error!!
        CHECK(compare_equal(plus->evaluate(), 0.1));
    }
}

TEST_CASE("operand integer")
{
    Operand *i = new Integer{7};

    CHECK(i->evaluate() == 7);
    CHECK(i->postfix() == "7");
}

TEST_CASE("conversion to string")
{
    Node *a = new Addition{new Subtraction{new Real{1.0},
                                           new Integer{1}},
                           new Multiplication{new Integer{2},
                                              new Integer{5}}};
    SECTION("prefix")
    {
        CHECK(a->prefix() == "+ - 1.000 1 * 2 5");
    }
    SECTION("infix")
    {
        CHECK(a->infix() == "( ( 1.000 - 1 ) + ( 2 * 5 ) )");
    }
    SECTION("postfix")
    {
        CHECK(a->postfix() == "1.000 1 - 2 5 * +");
    }
}

TEST_CASE("infix, postfix, prefix all the operators")
{
    SECTION("Addition")
    {
        Node *a = new Addition{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 + 420.000 )");
        CHECK(a->prefix() == "+ 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 +");
    }
    SECTION("Subtraction")
    {
        Node *a = new Subtraction{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 - 420.000 )");
        CHECK(a->prefix() == "- 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 -");
    }
    SECTION("Multiplication")
    {
        Node *a = new Multiplication{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 * 420.000 )");
        CHECK(a->prefix() == "* 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 *");
    }
    SECTION("Division")
    {
        Node *a = new Division{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 / 420.000 )");
        CHECK(a->prefix() == "/ 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 /");
    }
    SECTION("Power")
    {
        Node *a = new Power{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 ^ 420.000 )");
        CHECK(a->prefix() == "^ 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 ^");
    }
    SECTION("Modulo")
    {
        Node *a = new Modulo{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 % 420.000 )");
        CHECK(a->prefix() == "% 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 %");
    }
    SECTION("Condition")
    {
        Node *a = new Condition{new Integer{1337}, new Real{420}};
        CHECK(a->infix() == "( 1337 ? 420.000 )");
        CHECK(a->prefix() == "? 1337 420.000");
        CHECK(a->postfix() == "1337 420.000 ?");
    }
}

TEST_CASE("condition operator")
{
    Node *a = new Condition{
        new Subtraction{new Integer{2001}, new Real{1984}},
        new Division{new Integer{60}, new Integer{61}}};
    Node *b = new Condition{
        new Integer{0},
        new Division{new Integer{60}, new Integer{61}}};

    SECTION("should pass")
    {
        CHECK(compare_equal(a->evaluate(), 0.9836065574));
    }
    SECTION("shouldn't pass")
    {
        CHECK(b->evaluate() == 0);
    }
}
