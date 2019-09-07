#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/NoteValue.hpp>


using namespace Cbb;


TEST_CASE("A default-constructed note value is a basic whole note", "[NoteValue]")
{
    constexpr auto n = NoteValue();

    REQUIRE(n.base() == wholeNote);
    REQUIRE(n.tuplet() == duplet);
    REQUIRE(n.numDots() == 0);
}

TEST_CASE(
    "A note value constructed with a base, tuplet, and dot count produces the expected result",
    "[NoteValue]")
{
    constexpr auto n = NoteValue(semiquaver, quintuplet, 4);

    REQUIRE(n.base() == semiquaver);
    REQUIRE(n.tuplet() == quintuplet);
    REQUIRE(n.numDots() == 4);
}

TEST_CASE("A copy-constructed note value is a symbollicaly identical copy", "[NoteValue]")
{
    constexpr auto n = NoteValue(quaver, nonuplet, 3);
    constexpr auto c = NoteValue(n);

    REQUIRE(c.base() == quaver);
    REQUIRE(c.tuplet() == nonuplet);
    REQUIRE(c.numDots() == 3);
}

TEST_CASE("A note value constructed with just a base and a tuplet produces the expected base, "
          "expected tuplet, and no dots",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(halfNote, septuplet);

    REQUIRE(n.base() == halfNote);
    REQUIRE(n.tuplet() == septuplet);
    REQUIRE(n.numDots() == 0);
}

TEST_CASE("A note value constructed from just a base and dot count produces the expected base and "
          "expected dot count, and is a duplet",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(sixtyFourthNote, 2);

    REQUIRE(n.base() == sixtyFourthNote);
    REQUIRE(n.tuplet() == duplet);
    REQUIRE(n.numDots() == 2);
}

TEST_CASE("A note value constructed from just a base produces the expected basic note value",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(quarterNote);

    REQUIRE(n.base() == quarterNote);
    REQUIRE(n.tuplet() == duplet);
    REQUIRE(n.numDots() == 0);
}

TEST_CASE("A note value constructed from a unit fraction produces a note value with a relative "
          "value equal to the unit fraction",
          "[NoteValue]")
{
    constexpr auto n = NoteValue(UnitFraction(36));

    REQUIRE(n.base() == eighthNote);
    REQUIRE(n.tuplet() == nonuplet);
    REQUIRE(n.numDots() == 0);
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

TEST_CASE("A default-constructed composite note value is a single whole note", "[NoteValue]")
{
    const auto cnv = CompositeNoteValue();

    REQUIRE(cnv.size() == 1);
    REQUIRE(cnv[0] == wholeNote);
}

TEST_CASE(
    "A composite note value constructed with a just a base is a single note value of said base",
    "[NoteValue]")
{
    const auto cnv = CompositeNoteValue(eighthNote);

    REQUIRE(cnv.size() == 1);
    REQUIRE(cnv[0] == eighthNote);
}

TEST_CASE("A composite note value constructed with an initializer produces the specified sequence "
          "of note values (tied)",
          "[NoteValue]")
{
    const auto cnv = CompositeNoteValue({{quarterNote, triplet, 2}, eighthNote});

    REQUIRE(cnv.size() == 2);
    REQUIRE(cnv[0] == NoteValue(quarterNote, triplet, 2));
    REQUIRE(cnv[1] == eighthNote);
}

TEST_CASE("A composite note value's relative value is the sum of its continuent note values' "
          "relative values",
          "[NoteValue]")
{
    const auto a = NoteValue(eighthNote, quintuplet, 4);
    const auto b = NoteValue(sixteenthNote, triplet, 2);
    const auto c = CompositeNoteValue({a, b});

    REQUIRE(relativeValue(c) == relativeValue(a) + relativeValue(b));
}

TEST_CASE("Two note values of equal relative value are equivalent", "[NoteValue]")
{
    SECTION("Symbollically identical note values")
    {
        REQUIRE(CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}})
                == CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}}));
        REQUIRE_FALSE(CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}})
                      != CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}}));
    }

    SECTION("Symbollically different note values")
    {
        REQUIRE(CompositeNoteValue({{eighthNote, triplet, 2}, wholeNote})
                == CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}}));
        REQUIRE_FALSE(CompositeNoteValue({{eighthNote, triplet, 2}, wholeNote})
                      != CompositeNoteValue({wholeNote, {eighthNote, triplet, 2}}));
    }
}

TEST_CASE("A composite note value of lesser relative value is less than a composite note value of "
          "greater relative value",
          "[NoteValue]")
{
    REQUIRE(CompositeNoteValue({quarterNote, eighthNote})
            < CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE(CompositeNoteValue({quarterNote, eighthNote})
            <= CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE_FALSE(CompositeNoteValue({quarterNote, eighthNote})
                  >= CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE_FALSE(CompositeNoteValue({quarterNote, eighthNote})
                  > CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
}

TEST_CASE("A composite note value of greater relative value is greater than a composite note value "
          "of lesser relative value",
          "[NoteValue]")
{
    REQUIRE_FALSE(CompositeNoteValue({quarterNote, eighthNote})
                  < CompositeNoteValue({{eighthNote, triplet}, eighthNote}));
    REQUIRE_FALSE(CompositeNoteValue({quarterNote, eighthNote})
                  <= CompositeNoteValue({{eighthNote, triplet}, eighthNote}));
    REQUIRE(CompositeNoteValue({quarterNote, eighthNote})
            >= CompositeNoteValue({{eighthNote, triplet}, eighthNote}));
    REQUIRE(CompositeNoteValue({quarterNote, eighthNote})
            > CompositeNoteValue({{eighthNote, triplet}, eighthNote}));
}

TEST_CASE("A composite note value is neither less than nor greater than a composite note value "
          "with the same relative value",
          "[NoteValue]")
{
    REQUIRE_FALSE(CompositeNoteValue({{wholeNote, triplet}, eighthNote})
                  < CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE(CompositeNoteValue({{wholeNote, triplet}, eighthNote})
            <= CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE(CompositeNoteValue({{wholeNote, triplet}, eighthNote})
            >= CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
    REQUIRE_FALSE(CompositeNoteValue({{wholeNote, triplet}, eighthNote})
                  > CompositeNoteValue({{wholeNote, triplet}, eighthNote}));
}

TEST_CASE("Appending to a note value places note values onto the end of a composite note value",
          "[NoteValue]")
{
    SECTION("Appending a single note value")
    {
        auto a = CompositeNoteValue({wholeNote, eighthNote});
        const auto b = NoteValue(quarterNote);

        REQUIRE(a.append(b) == CompositeNoteValue({wholeNote, eighthNote, quarterNote}));
    }

    SECTION("Appending a composite note value")
    {
        auto a = CompositeNoteValue({eighthNote, sixteenthNote});
        const auto b = CompositeNoteValue({thirtySecondNote, wholeNote});

        REQUIRE(a.append(b)
                == CompositeNoteValue({eighthNote, sixteenthNote, thirtySecondNote, wholeNote}));
    }
}

TEST_CASE("Prepending to a note vlaue places note values onto the start of a composite note value",
          "[NoteValue]")
{
    SECTION("Prepending a single note value")
    {
        auto a = CompositeNoteValue({wholeNote, eighthNote});
        const auto b = NoteValue(quarterNote);

        REQUIRE(a.prepend(b) == CompositeNoteValue({quarterNote, wholeNote, eighthNote}));
    }

    SECTION("Prepending a composite note value")
    {
        auto a = CompositeNoteValue({eighthNote, sixteenthNote});
        const auto b = CompositeNoteValue({thirtySecondNote, wholeNote});

        REQUIRE(a.prepend(b)
                == CompositeNoteValue({thirtySecondNote, wholeNote, eighthNote, sixteenthNote}));
    }
}

TEST_CASE("Adding one note value(s) to another produces a composite note value that is the left "
          "note value(s) tied with the right note value(s)",
          "[NoteValue]")
{
    SECTION("Two single note values")
    {
        const auto a = NoteValue(thirtySecondNote);
        const auto b = NoteValue(wholeNote);

        REQUIRE(a + b == CompositeNoteValue({thirtySecondNote, wholeNote}));
    }

    SECTION("A composite note value and a single note value")
    {
        const auto a = CompositeNoteValue({thirtySecondNote, eighthNote});
        const auto b = NoteValue(wholeNote);

        REQUIRE(a + b == CompositeNoteValue({thirtySecondNote, eighthNote, wholeNote}));
    }

    SECTION("A composite note value and a single note value")
    {
        const auto a = NoteValue(wholeNote);
        const auto b = CompositeNoteValue({thirtySecondNote, eighthNote});

        REQUIRE(a + b == CompositeNoteValue({wholeNote, thirtySecondNote, eighthNote}));
    }

    SECTION("Two composite note values")
    {
        const auto a = CompositeNoteValue({wholeNote, halfNote});
        const auto b = CompositeNoteValue({thirtySecondNote, eighthNote});

        REQUIRE(a + b == CompositeNoteValue({wholeNote, halfNote, thirtySecondNote, eighthNote}));
    }
}

TEST_CASE("Dividing one composite note value by another gives the ratio between them",
          "[NoteValue]")
{
    const auto a = CompositeNoteValue({halfNote, eighthNote});
    const auto b = CompositeNoteValue({wholeNote, sixteenthNote});

    REQUIRE(a / b == Fraction(10, 17));
}

TEST_CASE(
    "Using the remainder operator on two composite note values gives the remainder of the division "
    "between them",
    "[NoteValue]")
{
    const auto a = CompositeNoteValue({wholeNote, sixteenthNote});
    const auto b = CompositeNoteValue({halfNote, eighthNote});

    REQUIRE(a % b == Fraction(7, 16));
}

TEST_CASE("Composite note values are iterable", "[NoteValue]")
{
    auto v = CompositeNoteValue({wholeNote, halfNote, quarterNote});

    SECTION("Const forward iteration")
    {
        auto i = v.cbegin();

        REQUIRE(*i++ == v[0]);
        REQUIRE(*i++ == v[1]);
        REQUIRE(*i++ == v[2]);
        REQUIRE(i == v.cend());
    }

    SECTION("Non-const forward iteration")
    {
        auto i = v.begin();

        *i++ = twoHundredFiftySixthNote;
        *i++ = thirtySecondNote;
        *i++ = octupleWholeNote;

        REQUIRE(i == v.end());

        REQUIRE(v[0] == twoHundredFiftySixthNote);
        REQUIRE(v[1] == thirtySecondNote);
        REQUIRE(v[2] == octupleWholeNote);
    }

    SECTION("Const reverse iteration")
    {
        auto i = v.crbegin();

        REQUIRE(*i++ == v[2]);
        REQUIRE(*i++ == v[1]);
        REQUIRE(*i++ == v[0]);
        REQUIRE(i == v.crend());
    }

    SECTION("Non-const reverse iteration")
    {
        auto i = v.rbegin();

        *i++ = twoHundredFiftySixthNote;
        *i++ = thirtySecondNote;
        *i++ = octupleWholeNote;

        REQUIRE(i == v.rend());

        REQUIRE(v[2] == twoHundredFiftySixthNote);
        REQUIRE(v[1] == thirtySecondNote);
        REQUIRE(v[0] == octupleWholeNote);
    }
}
