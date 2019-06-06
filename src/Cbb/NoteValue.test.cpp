#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/NoteValue.hpp>


using namespace Cbb;


TEST_CASE("A default-constructed note value is a basic whole note", "[NoteValue]")
{
    constexpr auto n = NoteValue();

    REQUIRE(n.getBase() == wholeNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE(
    "A note value constructed with a base, tuplet, and dot count produces the expected result",
    "[NoteValue]")
{
    constexpr auto n = NoteValue(semiquaver, quintuplet, 4);

    REQUIRE(n.getBase() == semiquaver);
    REQUIRE(n.getTuplet() == quintuplet);
    REQUIRE(n.getNumDots() == 4);
}

TEST_CASE("A copy-constructed note value is a symbollicaly identical copy", "[NoteValue]")
{
    constexpr auto n = NoteValue(quaver, nonuplet, 3);
    constexpr auto c = NoteValue(n);

    REQUIRE(c.getBase() == quaver);
    REQUIRE(c.getTuplet() == nonuplet);
    REQUIRE(c.getNumDots() == 3);
}

TEST_CASE("A note value constructed with just a base and a tuplet produces the expected base, "
          "expected tuplet, and no dots",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(halfNote, septuplet);

    REQUIRE(n.getBase() == halfNote);
    REQUIRE(n.getTuplet() == septuplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value constructed from just a base and dot count produces the expected base and "
          "expected dot count, and is a duplet",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(sixtyFourthNote, 2);

    REQUIRE(n.getBase() == sixtyFourthNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 2);
}

TEST_CASE("A note value constructed from just a base produces the expected basic note value",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(quarterNote);

    REQUIRE(n.getBase() == quarterNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value constructed from a unit fraction produces a note value with a relative "
          "value equal to the unit fraction",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(UnitFraction(36));

    REQUIRE(n.getBase() == eighthNote);
    REQUIRE(n.getTuplet() == nonuplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("All the common basic note values have the correct relative value", "[NoteValue]")
{
    REQUIRE(relativeValue(octupleWholeNote) == Fraction(8, 1));
    REQUIRE(relativeValue(quadrupleWholeNote) == Fraction(4, 1));
    REQUIRE(relativeValue(doubleWholeNote) == Fraction(2, 1));
    REQUIRE(relativeValue(wholeNote) == Fraction(1, 1));
    REQUIRE(relativeValue(halfNote) == Fraction(1, 2));
    REQUIRE(relativeValue(quarterNote) == Fraction(1, 4));
    REQUIRE(relativeValue(eighthNote) == Fraction(1, 8));
    REQUIRE(relativeValue(sixteenthNote) == Fraction(1, 16));
    REQUIRE(relativeValue(thirtySecondNote) == Fraction(1, 32));
    REQUIRE(relativeValue(sixtyFourthNote) == Fraction(1, 64));
    REQUIRE(relativeValue(oneHundredTwentyEighthNote) == Fraction(1, 128));
    REQUIRE(relativeValue(twoHundredFiftySixthNote) == Fraction(1, 256));
}

TEST_CASE("A note value with no augmentation factors (duplet and no dots) has the same "
          "relative value as its base",
          "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(quarterNote)) == Fraction(1, 4));
}

TEST_CASE("A note value with a non-duplet tuplet is augemented as expected", "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(eighthNote, triplet)) == Fraction(1, 12));
}

TEST_CASE("A note value with a non-zero dot count is augmented as expected", "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(halfNote, 3)) == Fraction(15, 16));
}

TEST_CASE("A note value with both a non-duplet tuplet and dot count is augmented as expected",
          "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(sixteenthNote, quintuplet, 1)) == Fraction(3, 80));
}

TEST_CASE("Note values with the same relative values are equivalent", "[NoteValue]")
{
    REQUIRE(NoteValue(minim, triplet, 2) == NoteValue(semibreve, sextuplet, 2));
    REQUIRE_FALSE(NoteValue(minim, triplet, 2) != NoteValue(semibreve, sextuplet, 2));
}

TEST_CASE("Note values with different relative values are not equalivalent", "[NoteValue]")
{
    REQUIRE_FALSE(NoteValue(minim, septuplet, 5) == NoteValue(breve, nonuplet, 1));
    REQUIRE(NoteValue(minim, septuplet, 5) != NoteValue(breve, nonuplet, 1));
}

TEST_CASE(
    "A note value of lesser relative value is less than a note value of greater relative value",
    "[NoteValue]")
{
    REQUIRE(NoteValue(quarterNote) < NoteValue(wholeNote, triplet));
    REQUIRE(NoteValue(quarterNote) <= NoteValue(wholeNote, triplet));
    REQUIRE_FALSE(NoteValue(quarterNote) >= NoteValue(wholeNote, triplet));
    REQUIRE_FALSE(NoteValue(quarterNote) > NoteValue(wholeNote, triplet));
}

TEST_CASE(
    "A note value of greater relative value is greater than a note value of lesser relative value",
    "[NoteValue]")
{
    REQUIRE_FALSE(NoteValue(quarterNote) < NoteValue(eighthNote, triplet));
    REQUIRE_FALSE(NoteValue(quarterNote) <= NoteValue(eighthNote, triplet));
    REQUIRE(NoteValue(quarterNote) >= NoteValue(eighthNote, triplet));
    REQUIRE(NoteValue(quarterNote) > NoteValue(eighthNote, triplet));
}

TEST_CASE(
    "A note value is neither less than nor greater than a note value with the same relative value",
    "[NoteValue]")
{
    REQUIRE_FALSE(NoteValue(wholeNote, triplet) < NoteValue(wholeNote, triplet));
    REQUIRE(NoteValue(wholeNote, triplet) <= NoteValue(wholeNote, triplet));
    REQUIRE(NoteValue(wholeNote, triplet) >= NoteValue(wholeNote, triplet));
    REQUIRE_FALSE(NoteValue(wholeNote, triplet) > NoteValue(wholeNote, triplet));
}

TEST_CASE("Dividing one note value by another gives the ratio between them", "[NoteValue]")
{
    REQUIRE(NoteValue(halfNote, triplet, 1) / NoteValue(wholeNote, quintuplet, 2)
            == Fraction(5, 7));
}

TEST_CASE("Using the remainder operator on two note values gives the remainder of the division "
          "between them",
          "[NoteValue]")
{
    REQUIRE(NoteValue(eighthNote, septuplet, 2) % NoteValue(thirtySecondNote, 1)
            == Fraction(1, 64));
}
