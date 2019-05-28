#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/NoteValue.hpp>


using namespace Cbb;


TEST_CASE("A note value can be default constructed to a regular whole note", "[NoteValue]")
{
    constexpr auto n = NoteValue();

    REQUIRE(n.getBase() == wholeNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value can be constructed with a base, tuplet, and dot count", "[NoteValue]")
{
    constexpr auto n = NoteValue(semiquaver, quintuplet, 4);

    REQUIRE(n.getBase() == semiquaver);
    REQUIRE(n.getTuplet() == quintuplet);
    REQUIRE(n.getNumDots() == 4);
}

TEST_CASE("A note value can be constructed from another NoteValue", "[NoteValue]")
{
    constexpr auto n = NoteValue(quaver, nonuplet, 3);
    constexpr auto c = NoteValue(n);

    REQUIRE(c.getBase() == quaver);
    REQUIRE(c.getTuplet() == nonuplet);
    REQUIRE(c.getNumDots() == 3);
}

TEST_CASE("A note value can be constructed from just a base and tuplet", "[NoteValue]")
{
    constexpr auto n = NoteValue(halfNote, septuplet);

    REQUIRE(n.getBase() == halfNote);
    REQUIRE(n.getTuplet() == septuplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value can be constructed from just a base and dot count", "[NoteValue]")
{
    constexpr auto n = NoteValue(sixtyFourthNote, 2);

    REQUIRE(n.getBase() == sixtyFourthNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 2);
} 

TEST_CASE("A note value can be constructed from just a base", "[NoteValue]")
{
    constexpr auto n = NoteValue(quarterNote);

    REQUIRE(n.getBase() == quarterNote);
    REQUIRE(n.getTuplet() == duplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value can be constructed from a unit fraction", "[NoteValue]")
{
    constexpr auto n = NoteValue(UnitFraction(36));

    REQUIRE(n.getBase() == eighthNote);
    REQUIRE(n.getTuplet() == nonuplet);
    REQUIRE(n.getNumDots() == 0);
}

TEST_CASE("A note value base has its expected relative value", "[NoteValue]")
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

TEST_CASE("A note value with no augmentation factors (duplet and 0 dot count) has the same "
          "relative value as its base",
          "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(quarterNote)) == Fraction(1, 4));
}

TEST_CASE("A note value with a non-duplet tuplet is augmented appropriately", "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(eighthNote, triplet)) == Fraction(1, 12));
}

TEST_CASE("A note value with a dot count is augemented appropriately", "[NoteValue]")
{
    REQUIRE(relativeValue(NoteValue(halfNote, 3)) == Fraction(15, 16));
}

TEST_CASE("A note value with both a non-duplet tuplet and dot count is augmented appropriately",
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
    "Note value is neither less than nor greater than a note value with the same relative value",
    "[NoteValue]")
{
    REQUIRE_FALSE(NoteValue(wholeNote, triplet) < NoteValue(wholeNote, triplet));
    REQUIRE(NoteValue(wholeNote, triplet) <= NoteValue(wholeNote, triplet));
    REQUIRE(NoteValue(wholeNote, triplet) >= NoteValue(wholeNote, triplet));
    REQUIRE_FALSE(NoteValue(wholeNote, triplet) > NoteValue(wholeNote, triplet));
}
