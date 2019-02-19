#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/Fraction.hpp>


using namespace Cbb;


TEST_CASE("Construction", "[Fraction]")
{
    SECTION("Default construction")
    {
        constexpr auto f = Fraction();

        REQUIRE(f.num() == int{});
        REQUIRE(f.den() == int{});
    }
    SECTION("Construction with a numerator and denominator")
    {
        constexpr auto f1 = Fraction(3, 4);

        REQUIRE(f1.num() == 3);
        REQUIRE(f1.den() == 4);

        constexpr auto f2 = Fraction(-3, -4);

        REQUIRE(f2.num() == 3);
        REQUIRE(f2.den() == 4);
    }
    SECTION("Copy construction")
    {
        constexpr auto f = Fraction(-5, 6);
        constexpr auto c = Fraction(f);

        REQUIRE(c.num() == -5);
        REQUIRE(c.den() == 6);
    }
    SECTION("Construction with only a numerator")
    {
        constexpr auto f = Fraction(5);

        REQUIRE(f.num() == 5);
        REQUIRE(f.den() == 1);
    }
    SECTION("Converting construction from a numerator and denominator")
    {
        constexpr Fraction f1 = {3, 4};

        REQUIRE(f1.num() == 3);
        REQUIRE(f1.den() == 4);

        constexpr Fraction f2 = {-3, -4};

        REQUIRE(f2.num() == 3);
        REQUIRE(f2.den() == 4);
    }
    SECTION("Converting construction from a single integer")
    {
        constexpr Fraction f = 5;

        REQUIRE(f.num() == 5);
        REQUIRE(f.den() == 1);
    }
}

TEST_CASE("Comparison", "[Fraction]")
{
    SECTION("Equal to")
    {
        SECTION("Symbollically equal fractions")
        {
            REQUIRE(Fraction(4, 5) == Fraction(4, 5));
        }
        SECTION("Symbollically different but equivalent fractions")
        {
            REQUIRE(Fraction(8, 10) == Fraction(4, 5));
        }
        SECTION("Inequivalent fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) == Fraction(3, 7));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) == Fraction(4, 0));
            REQUIRE_FALSE(Fraction(4, 0) == Fraction(4, 5));
            REQUIRE_FALSE(Fraction(4, 0) == Fraction(4, 0));
        }
    }
    SECTION("Not equal to")
    {
        SECTION("Symbollically equal fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) != Fraction(4, 5));
        }
        SECTION("Symbollically different but equivalent fractions")
        {
            REQUIRE_FALSE(Fraction(8, 10) != Fraction(4, 5));
        }
        SECTION("Inequalavent fractions")
        {
            REQUIRE(Fraction(4, 5) != Fraction(3, 7));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE(Fraction(4, 5) != Fraction(4, 0));
            REQUIRE(Fraction(4, 0) != Fraction(4, 5));
            REQUIRE(Fraction(4, 0) != Fraction(4, 0));
        }
    }
    SECTION("Less than")
    {
        SECTION("Left is less than right")
        {
            REQUIRE(Fraction(1, 3) < Fraction(4, 5));
        }
        SECTION("Left equals right")
        {
            REQUIRE_FALSE(Fraction(1, 3) < Fraction(1, 3));
        }
        SECTION("Left is greater than right")
        {
            REQUIRE_FALSE(Fraction(4, 5) < Fraction(1, 3));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) < Fraction(4, 0));
            REQUIRE_FALSE(Fraction(4, 0) < Fraction(4, 5));
            REQUIRE_FALSE(Fraction(4, 0) < Fraction(4, 0));
        }
    }
    SECTION("Less than or equal to")
    {
        SECTION("Left is less than right")
        {
            REQUIRE(Fraction(1, 3) <= Fraction(4, 5));
        }
        SECTION("Left equals right")
        {
            REQUIRE(Fraction(1, 3) <= Fraction(1, 3));
        }
        SECTION("Left is greater than right")
        {
            REQUIRE_FALSE(Fraction(4, 5) <= Fraction(1, 3));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) <= Fraction(4, 0));
            REQUIRE_FALSE(Fraction(4, 0) <= Fraction(4, 5));
            REQUIRE_FALSE(Fraction(4, 0) <= Fraction(4, 0));
        }
    }
    SECTION("Greater than")
    {
        SECTION("Left is less than right")
        {
            REQUIRE_FALSE(Fraction(1, 3) > Fraction(4, 5));
        }
        SECTION("Left equals right")
        {
            REQUIRE_FALSE(Fraction(1, 3) > Fraction(1, 3));
        }
        SECTION("Left is greater than right")
        {
            REQUIRE(Fraction(4, 5) > Fraction(1, 3));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) > Fraction(4, 0));
            REQUIRE_FALSE(Fraction(4, 0) > Fraction(4, 5));
            REQUIRE_FALSE(Fraction(4, 0) > Fraction(4, 0));
        }
    }
    SECTION("Greater than or equal to")
    {
        SECTION("Left is less than right")
        {
            REQUIRE_FALSE(Fraction(1, 3) >= Fraction(4, 5));
        }
        SECTION("Left equals right")
        {
            REQUIRE(Fraction(1, 3) >= Fraction(1, 3));
        }
        SECTION("Left is greater than right")
        {
            REQUIRE(Fraction(4, 5) >= Fraction(1, 3));
        }
        SECTION("Undefined fractions")
        {
            REQUIRE_FALSE(Fraction(4, 5) >= Fraction(4, 0));
            REQUIRE_FALSE(Fraction(4, 0) >= Fraction(4, 5));
            REQUIRE_FALSE(Fraction(4, 0) >= Fraction(4, 0));
        }
    }
}

TEST_CASE("Reduction", "[Fraction]")
{
    SECTION("Reducing a reducible fraction")
    {
        constexpr auto f = Fraction(12, 32);
        constexpr auto r = reduce(f);

        REQUIRE(r == Fraction(3, 8));
    }
    SECTION("Reducing an already irreducible fraction")
    {
        constexpr auto f = Fraction(7, 9);
        constexpr auto r = reduce(f);

        REQUIRE(r== Fraction(7, 9));
    }
}

TEST_CASE("Reciprocal calculation", "[Fraction]")
{
    constexpr auto f = Fraction(4, 19);
    constexpr auto r = reciprocal(f);

    REQUIRE(r == Fraction(19, 4));
}

TEST_CASE("Decimal conversion", "[Fraction]")
{
    constexpr auto f = Fraction(4, 5);
    constexpr float d = decimal(f);

    REQUIRE(d == 0.8f);
}

TEST_CASE("Promotion", "[Fraction]")
{
    constexpr auto f = Fraction(7, 10);
    constexpr auto n = +f;

    REQUIRE(n == Fraction(7, 10));
}

TEST_CASE("Negation", "[Fraction]")
{
    constexpr auto f = Fraction(7, 10);
    constexpr auto n = -f;

    REQUIRE(n == Fraction(-7, 10));
}

TEST_CASE("Positive check", "[Fraction]")
{
    REQUIRE(isPositive(Fraction(1, 6)));
    REQUIRE(isPositive(Fraction(-1, -6)));
    REQUIRE_FALSE(isPositive(Fraction(-1, 6)));
    REQUIRE_FALSE(isPositive(Fraction(1, -6)));
}

TEST_CASE("Negative check", "[Fraction]")
{
    REQUIRE(isNegative(Fraction(-1, 6)));
    REQUIRE(isNegative(Fraction(1, -6)));
    REQUIRE_FALSE(isNegative(Fraction(1, 6)));
    REQUIRE_FALSE(isNegative(Fraction(-1, -6)));
}

TEST_CASE("Integer check", "[Fraction]")
{
    REQUIRE(isInteger(Fraction(4, 2)));
    REQUIRE_FALSE(isInteger(Fraction(2, 5)));
}

TEST_CASE("Undefined check", "[Fraction]")
{
    REQUIRE(isUndefined(Fraction(4, 0)));
    REQUIRE_FALSE(isUndefined(Fraction(2, 5)));
}

TEST_CASE("Addition", "[Fraction]")
{
    SECTION("Fractions with a common denominator")
    {
        REQUIRE(Fraction(1, 5) + Fraction(3, 5) == Fraction(4, 5));
    }
    SECTION("Fractions without a common denominator")
    {
        REQUIRE(Fraction(2, 3) + Fraction(1, 4) == Fraction(11, 12));
    }
}

TEST_CASE("Subtraction", "[Fraction]")
{
    SECTION("Fractions with a common denominator")
    {
        REQUIRE(Fraction(1, 5) - Fraction(3, 5) == Fraction(-2, 5));
    }
    SECTION("Fractions without a common denominator")
    {
        REQUIRE(Fraction(2, 3) - Fraction(1, 4) == Fraction(5, 12));
    }
}

TEST_CASE("Mutiplication", "[Fraction]")
{
    REQUIRE(Fraction(2, 3) * Fraction(3, 7) == Fraction(6, 21));
}

TEST_CASE("Division", "[Fraction]")
{
    REQUIRE(Fraction(2, 3) / Fraction(3, 11) == Fraction(22, 9));
}
