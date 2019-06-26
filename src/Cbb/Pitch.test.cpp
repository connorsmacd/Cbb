#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/Pitch.hpp>


using namespace Cbb;


TEST_CASE("A default-constructed pitch class label is C natural", "[Pitch]")
{
    constexpr auto p = PitchClassLabel();

    REQUIRE(p.letter == C);
    REQUIRE(p.accidental == natural);
}

TEST_CASE("A pitch class label constructed with just a letter is the letter natural", "[Pitch]")
{
    constexpr auto p = PitchClassLabel(G);

    REQUIRE(p.letter == G);
    REQUIRE(p.accidental == natural);
}

TEST_CASE("A pitch class label constructed with a letter and accidental is the expected label",
          "[Pitch]")
{
    constexpr auto p = PitchClassLabel(D, sharp);

    REQUIRE(p.letter == D);
    REQUIRE(p.accidental == sharp);
}

TEST_CASE("Identical pitch class labels are equivalent", "[Pitch]")
{
    REQUIRE(PitchClassLabel(A, flat) == PitchClassLabel(A, flat));
    REQUIRE_FALSE(PitchClassLabel(A, flat) != PitchClassLabel(A, flat));
}

TEST_CASE("Different pitch class labels are not equivalent", "[Pitch]")
{
    REQUIRE_FALSE(PitchClassLabel(A, flat) == PitchClassLabel(E, doubleSharp));
    REQUIRE(PitchClassLabel(A, flat) != PitchClassLabel(E, doubleSharp));
}

TEST_CASE("The pitch class of F# is 6", "[Pitch]")
{
    REQUIRE(toPitchClass({F, sharp}) == 6);
}

TEST_CASE("The pitch class of B# is 0", "[Pitch]")
{
    REQUIRE(toPitchClass({B, sharp}) == 0);
}

TEST_CASE("The pitch class of Cb is 11", "[Pitch]")
{
    REQUIRE(toPitchClass({C, flat}) == 11);
}

TEST_CASE("A# has the same pitch class as Bb", "[Pitch]")
{
    REQUIRE(toPitchClass({A, sharp}) == toPitchClass({B, flat}));
}

TEST_CASE("A pitch label can be default constructed to C0", "[Pitch]")
{
    constexpr auto p = PitchLabel();

    REQUIRE(p.letter == C);
    REQUIRE(p.accidental == natural);
    REQUIRE(p.octave == 0);
}

TEST_CASE("A pitch label can be constructed with a letter, accidental, and octave", "[Pitch]")
{
    constexpr auto p = PitchLabel(A, sharp, 3);

    REQUIRE(p.letter == A);
    REQUIRE(p.accidental == sharp);
    REQUIRE(p.octave == 3);
}

TEST_CASE("A pitch label can be constructed from just a letter and octave", "[Pitch]")
{
    constexpr auto p = PitchLabel(F, 5);

    REQUIRE(p.letter == F);
    REQUIRE(p.accidental == natural);
    REQUIRE(p.octave == 5);
}

TEST_CASE("A pitch label can be constructed from a pitch class label and octave", "[Pitch]")
{
    constexpr auto p = PitchLabel(PitchClassLabel(E, flat), 4);

    REQUIRE(p.letter == E);
    REQUIRE(p.accidental == flat);
    REQUIRE(p.octave == 4);
}

TEST_CASE("A pitch label can be converted to a pitch class label", "[Pitch]")
{
    constexpr auto p = PitchLabel(G, flat, 2);
    constexpr auto pc = (PitchClassLabel) p;

    REQUIRE(pc.letter == G);
    REQUIRE(pc.accidental == flat);
}

TEST_CASE("Identical pitch labels are equivalent", "[Pitch]")
{
    REQUIRE(PitchLabel(C, doubleSharp, 7) == PitchLabel(C, doubleSharp, 7));
    REQUIRE_FALSE(PitchLabel(C, doubleSharp, 7) != PitchLabel(C, doubleSharp, 7));
}

TEST_CASE("Different pitch labels are not equivalent", "[Pitch]")
{
    REQUIRE_FALSE(PitchLabel(A, flat, 3) == PitchLabel(C, doubleSharp, 7));
    REQUIRE(PitchLabel(A, flat, 3) != PitchLabel(C, doubleSharp, 7));
}

TEST_CASE("A pitch can be default constructed to class 0 octave 0", "[Pitch]")
{
    constexpr auto p = Pitch();

    REQUIRE(p.getClass() == 0);
    REQUIRE(p.getOctave() == 0);
}

TEST_CASE("A pitch can be constructed from a pitch class and octave", "[Pitch]")
{
    constexpr auto p = Pitch(3, 7);

    REQUIRE(p.getClass() == 3);
    REQUIRE(p.getOctave() == 7);
}

TEST_CASE("A pitch can be constructed from a pitch label", "[Pitch]")
{
    constexpr auto p = Pitch(PitchLabel(F, sharp, 2));

    REQUIRE(p.getClass() == 6);
    REQUIRE(p.getOctave() == 2);
}

TEST_CASE("A pitch can be constructed from a MIDI note number", "[Pitch]")
{
    constexpr auto p = Pitch(Midi::Fs5);

    REQUIRE(p.getClass() == 6);
    REQUIRE(p.getOctave() == 5);
}

TEST_CASE("A pitch can be constructed from a frequency and tuning", "[Pitch]")
{
    // 311.13 Hz if D#4 in A440
    const auto p = Pitch(311.13, A440);

    REQUIRE(p.getClass() == 3);
    REQUIRE(p.getOctave() == 4);
}

TEST_CASE("Transposing a pitch by semitones raises the pitch by the specified number of semitones",
          "[Pitch]")
{
    REQUIRE(Pitch(PitchLabel(G, -1)).transposeSemitones(17) == Pitch(PitchLabel(C, 1)));
    REQUIRE(transposedSemitones(Pitch(PitchLabel(G, -1)), 17) == Pitch(PitchLabel(C, 1)));

    REQUIRE(Pitch(PitchLabel(C, 1)).transposeSemitones(-17) == Pitch(PitchLabel(G, -1)));
    REQUIRE(transposedSemitones(Pitch(PitchLabel(C, 1)), -17) == Pitch(PitchLabel(G, -1)));
}

TEST_CASE("Transposing a pitch by octaves raises the pitch by the specified number of octaves",
          "[Pitch]")
{
    REQUIRE(Pitch(PitchLabel(G, -1)).transposeOctaves(2) == Pitch(PitchLabel(G, 1)));
    REQUIRE(transposedOctaves(Pitch(PitchLabel(G, -1)), 2) == Pitch(PitchLabel(G, 1)));

    REQUIRE(Pitch(PitchLabel(G, 1)).transposeOctaves(-2) == Pitch(PitchLabel(G, -1)));
    REQUIRE(transposedOctaves(Pitch(PitchLabel(G, 1)), -2) == Pitch(PitchLabel(G, -1)));
}

TEST_CASE("A pitch's MIDI note number can be retrieved", "[Pitch]")
{
    REQUIRE(Pitch(Midi::As5).getNoteNumber() == Midi::As5);
}

TEST_CASE("A pitch's frequency can be retrieved", "[Pitch]")
{
    REQUIRE(Pitch(261.63, A440).getFrequencyHz() == Approx(261.63).epsilon(0.01));
}

TEST_CASE("Identical pitches are equivalent", "[Pitch]")
{
    REQUIRE(Pitch(5, 9) == Pitch(5, 9));
    REQUIRE_FALSE(Pitch(5, 9) != Pitch(5, 9));
}

TEST_CASE("Different pitches are not equivalent", "[Pitch]")
{
    REQUIRE_FALSE(Pitch(5, 9) == Pitch(2, 3));
    REQUIRE(Pitch(5, 9) != Pitch(2, 3));
}

TEST_CASE("A pitch with a lower octave is less than a pitch with a higher octave", "[Pitch]")
{
    REQUIRE(Pitch(8, 3) < Pitch(4, 4));
    REQUIRE(Pitch(8, 3) <= Pitch(4, 4));
    REQUIRE_FALSE(Pitch(8, 3) >= Pitch(4, 4));
    REQUIRE_FALSE(Pitch(8, 3) > Pitch(4, 4));
}

TEST_CASE("A pitch with the same octave but lower class is less than a pitch with a same octave "
          "but higher class",
          "[Pitch]")
{
    REQUIRE(Pitch(2, 3) < Pitch(4, 3));
    REQUIRE(Pitch(2, 3) <= Pitch(4, 3));
    REQUIRE_FALSE(Pitch(2, 3) >= Pitch(4, 3));
    REQUIRE_FALSE(Pitch(2, 3) > Pitch(4, 3));
}

TEST_CASE("A pitch with a higher octave is geater than a pitch with a lower octave", "[Pitch]")
{
    REQUIRE_FALSE(Pitch(2, 4) < Pitch(8, 3));
    REQUIRE_FALSE(Pitch(2, 4) <= Pitch(8, 3));
    REQUIRE(Pitch(2, 4) >= Pitch(8, 3));
    REQUIRE(Pitch(2, 4) > Pitch(8, 3));
}

TEST_CASE("A pitch with the same octave but higher class is geater than a pitch with a same octave "
          "but lower class",
          "[Pitch]")
{
    REQUIRE_FALSE(Pitch(6, 3) < Pitch(4, 3));
    REQUIRE_FALSE(Pitch(6, 3) <= Pitch(4, 3));
    REQUIRE(Pitch(6, 3) >= Pitch(4, 3));
    REQUIRE(Pitch(6, 3) > Pitch(4, 3));
}

TEST_CASE("Identical pitches are neither less than nor greater than eachother", "[Pitch]")
{
    REQUIRE_FALSE(Pitch(6, 3) < Pitch(6, 3));
    REQUIRE(Pitch(6, 3) <= Pitch(6, 3));
    REQUIRE(Pitch(6, 3) >= Pitch(6, 3));
    REQUIRE_FALSE(Pitch(6, 3) > Pitch(6, 3));
}
