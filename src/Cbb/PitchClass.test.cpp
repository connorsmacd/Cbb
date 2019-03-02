#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/PitchClass.hpp>


using namespace Cbb;


TEST_CASE("A pitch class label can be default constructed to C natural", "[PitchClass]")
{
    constexpr auto p = PitchClassLabel();

    REQUIRE(p.letter == C);
    REQUIRE(p.accidental == natural);
}

TEST_CASE("A pitch class label can be constructed with just a letter", "[PitchClass]")
{
    constexpr auto p = PitchClassLabel(G);

    REQUIRE(p.letter == G);
    REQUIRE(p.accidental == natural);
}

TEST_CASE("A pitch class label can be constructed with a letter and accidental", "[PitchClass]")
{
    constexpr auto p = PitchClassLabel(D, sharp);

    REQUIRE(p.letter == D);
    REQUIRE(p.accidental == sharp);
}

TEST_CASE("Identical pitch class labels are equivalent", "[PitchClass]")
{
    REQUIRE(PitchClassLabel(A, flat) == PitchClassLabel(A, flat));
    REQUIRE_FALSE(PitchClassLabel(A, flat) != PitchClassLabel(A, flat));
}

TEST_CASE("Different pitch class labels are not equivalent", "[PitchClass]")
{
    REQUIRE_FALSE(PitchClassLabel(A, flat) == PitchClassLabel(E, doubleSharp));
    REQUIRE(PitchClassLabel(A, flat) != PitchClassLabel(E, doubleSharp));
}

TEST_CASE("The pitch class of F# is 6", "[PitchClass]")
{
    REQUIRE(toPitchClass({F, sharp}) == 6);
}

TEST_CASE("The pitch class of B# is 0", "[PitchClass]")
{
    REQUIRE(toPitchClass({B, sharp}) == 0);
}

TEST_CASE("The pitch class of Cb is 11", "[PitchClass]")
{
    REQUIRE(toPitchClass({C, flat}) == 11);
}

TEST_CASE("A# has the same pitch class as Bb", "[PitchClass]")
{
    REQUIRE(toPitchClass({A, sharp}) == toPitchClass({B, flat}));
}
