#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cbb/note_value_constants.hpp>


using namespace cbb;
using namespace ieme::fraction_literals;


TEST_CASE("note_value construction", "[note_value]")
{
  SECTION("default")
  {
    constexpr auto nv = note_value();

    STATIC_REQUIRE(nv.get_power_of_2() == numbers::_1);
    STATIC_REQUIRE(nv.get_tuplet() == tuplet::duplet);
    STATIC_REQUIRE(nv.get_num_dots() == dot_count::none);
  }

  SECTION("with base")
  {
    constexpr auto nv = _8th_note;

    STATIC_REQUIRE(nv.get_power_of_2() == numbers::one_8th);
    STATIC_REQUIRE(nv.get_tuplet() == tuplet::duplet);
    STATIC_REQUIRE(nv.get_num_dots() == dot_count::none);
  }

  SECTION("with base and tuplet")
  {
    constexpr auto nv = note_value(numbers::one_16th, tuplet::triplet);

    STATIC_REQUIRE(nv.get_power_of_2() == numbers::one_16th);
    STATIC_REQUIRE(nv.get_tuplet() == tuplet::triplet);
    STATIC_REQUIRE(nv.get_num_dots() == dot_count::none);
  }

  SECTION("with base and dot count")
  {
    constexpr auto nv = note_value(numbers::one_half, dot_count::triple);

    STATIC_REQUIRE(nv.get_power_of_2() == numbers::one_half);
    STATIC_REQUIRE(nv.get_tuplet() == tuplet::duplet);
    STATIC_REQUIRE(nv.get_num_dots() == dot_count::triple);
  }

  SECTION("with base, tuplet, and dot count")
  {
    constexpr auto nv
      = note_value(numbers::one_quarter, tuplet::quintuplet, dot_count::single);

    STATIC_REQUIRE(nv.get_power_of_2() == numbers::one_quarter);
    STATIC_REQUIRE(nv.get_tuplet() == tuplet::quintuplet);
    STATIC_REQUIRE(nv.get_num_dots() == dot_count::single);
  }
}

TEST_CASE("note_value relative value", "[note_value]")
{
  STATIC_REQUIRE(relative_value(whole_note) == 1);
  STATIC_REQUIRE(relative_value(quarter_note) == 1 / 4_fr);
  STATIC_REQUIRE(relative_value(triplet_8th_note) == 1 / 12_fr);
  STATIC_REQUIRE(relative_value(half_note.with(dot_count::triple))
                 == 15 / 16_fr);
  STATIC_REQUIRE(
    relative_value(_16th_note.with(tuplet::quintuplet).with(dot_count::single))
    == 3 / 80_fr);
}

TEST_CASE("note_value comparison", "[note_value]")
{
  SECTION("equality")
  {
    STATIC_REQUIRE(_8th_note == _8th_note);
    STATIC_REQUIRE_FALSE(_8th_note != _8th_note);

    STATIC_REQUIRE(whole_note.with(tuplet::sextuplet) == triplet_half_note);
    STATIC_REQUIRE_FALSE(whole_note.with(tuplet::sextuplet)
                         != triplet_half_note);

    STATIC_REQUIRE_FALSE(_8th_note == _16th_note);
    STATIC_REQUIRE(_8th_note != _16th_note);
  }

  SECTION("order")
  {
    STATIC_REQUIRE_FALSE(_8th_note < _8th_note);
    STATIC_REQUIRE(_8th_note <= _8th_note);
    STATIC_REQUIRE_FALSE(_8th_note > _8th_note);
    STATIC_REQUIRE(_8th_note >= _8th_note);

    STATIC_REQUIRE_FALSE(quarter_note.with(tuplet::sextuplet)
                         < triplet_8th_note);
    STATIC_REQUIRE(quarter_note.with(tuplet::sextuplet) <= triplet_8th_note);
    STATIC_REQUIRE_FALSE(quarter_note.with(tuplet::sextuplet)
                         > triplet_8th_note);
    STATIC_REQUIRE(quarter_note.with(tuplet::sextuplet) >= triplet_8th_note);

    STATIC_REQUIRE(_16th_note < _8th_note);
    STATIC_REQUIRE(_16th_note <= _8th_note);
    STATIC_REQUIRE_FALSE(_16th_note > _8th_note);
    STATIC_REQUIRE_FALSE(_16th_note >= _8th_note);

    STATIC_REQUIRE_FALSE(_8th_note < _16th_note);
    STATIC_REQUIRE_FALSE(_8th_note <= _16th_note);
    STATIC_REQUIRE(_8th_note > _16th_note);
    STATIC_REQUIRE(_8th_note >= _16th_note);
  }
}

TEST_CASE("note_value arithmetic operators", "[note_value]")
{
  SECTION("operator*")
  {
    STATIC_REQUIRE(quarter_note * numbers::_2 == half_note);
    STATIC_REQUIRE(numbers::one_half * whole_note == half_note);
  }

  SECTION("operator/")
  {
    STATIC_REQUIRE(quarter_note / _8th_note == 2);
    STATIC_REQUIRE(quarter_note / numbers::_2 == _8th_note);
  }

  SECTION("operator%")
  {
    STATIC_REQUIRE(double_whole_note % half_note.with(dot_count::_double)
                   == 1 / 4_fr);
  }
}
