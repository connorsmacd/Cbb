#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/Midi.hpp>


using namespace Catch::literals;
using namespace Cbb;
using namespace Cbb::Midi;


TEST_CASE("The note number of 440 Hz is A4 in A440", "[Midi]")
{
    REQUIRE(frequencyHzToNoteNumber(440.0, A440) == A4);
}

TEST_CASE("The note number of 432 Hz is A4 in A432", "[Midi]")
{
    REQUIRE(frequencyHzToNoteNumber(432.0, A432) == A4);
}

TEST_CASE("The note number of 261.63 Hz is C4 in A440", "[Midi]")
{
    REQUIRE(frequencyHzToNoteNumber(261.63, A440) == C4);
}

TEST_CASE("The note number of 200 Hz rounds to G3 in A440", "[Midi]")
{
    REQUIRE(frequencyHzToNoteNumber(200.0, A440) == G3);
}

TEST_CASE("The frequency of A4 is 440 Hz in A440", "[Midi]")
{
    REQUIRE(noteNumberToFrequencyHz(A4, A440) == Approx(440.0).epsilon(0.01));
}

TEST_CASE("The frequency of A4 is 432 Hz in A432", "[Midi]")
{
    REQUIRE(noteNumberToFrequencyHz(A4, A432) == Approx(432.0).epsilon(0.01));
}

TEST_CASE("The frequency of C4 is 261.63 Hz in A440", "[Midi]")
{
    REQUIRE(noteNumberToFrequencyHz(C4, A440) == Approx(261.63).epsilon(0.01));
}
