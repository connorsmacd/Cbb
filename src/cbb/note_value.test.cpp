#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cbb/note_value.hpp>


using namespace cbb;
using namespace ieme::fraction_literals;


TEST_CASE("note_value_base relative value", "[note_value]")
{
  REQUIRE(relative_value(note_value_base::_256th) == 1 / 256_Fr);
  REQUIRE(relative_value(note_value_base::_128th) == 1 / 128_Fr);
  REQUIRE(relative_value(note_value_base::_64th) == 1 / 64_Fr);
  REQUIRE(relative_value(note_value_base::_32nd) == 1 / 32_Fr);
  REQUIRE(relative_value(note_value_base::_16th) == 1 / 16_Fr);
  REQUIRE(relative_value(note_value_base::_8th) == 1 / 8_Fr);
  REQUIRE(relative_value(note_value_base::quarter) == 1 / 4_Fr);
  REQUIRE(relative_value(note_value_base::half) == 1 / 2_Fr);
  REQUIRE(relative_value(note_value_base::whole) == 1);
  REQUIRE(relative_value(note_value_base::double_whole) == 2);
  REQUIRE(relative_value(note_value_base::quadruple_whole) == 4);
  REQUIRE(relative_value(note_value_base::octuple_whole) == 8);
  REQUIRE(relative_value(note_value_base::demisemihemidemisemiquaver)
          == 1 / 256_Fr);
  REQUIRE(relative_value(note_value_base::semihemidemisemiquaver)
          == 1 / 128_Fr);
  REQUIRE(relative_value(note_value_base::hemidemisemiquaver) == 1 / 64_Fr);
  REQUIRE(relative_value(note_value_base::demisemiquaver) == 1 / 32_Fr);
  REQUIRE(relative_value(note_value_base::semiquaver) == 1 / 16_Fr);
  REQUIRE(relative_value(note_value_base::quaver) == 1 / 8_Fr);
  REQUIRE(relative_value(note_value_base::crotchet) == 1 / 4_Fr);
  REQUIRE(relative_value(note_value_base::minim) == 1 / 2_Fr);
  REQUIRE(relative_value(note_value_base::semibreve) == 1);
  REQUIRE(relative_value(note_value_base::breve) == 2);
  REQUIRE(relative_value(note_value_base::longa) == 4);
  REQUIRE(relative_value(note_value_base::maxima) == 8);
}

TEST_CASE("note_value construction", "[note_value]")
{
  SECTION("default")
  {
    constexpr auto nv = note_value();

    REQUIRE(nv.get_base() == note_value_base::whole);
    REQUIRE(nv.get_tuplet() == tuplet::duplet);
    REQUIRE(nv.get_num_dots() == 0);
  }

  SECTION("with base")
  {
    constexpr auto nv = note_value(note_value_base::_8th);

    REQUIRE(nv.get_base() == note_value_base::_8th);
    REQUIRE(nv.get_tuplet() == tuplet::duplet);
    REQUIRE(nv.get_num_dots() == 0);
  }

  SECTION("with base and tuplet")
  {
    constexpr auto nv = note_value(note_value_base::_16th, tuplet::triplet);

    REQUIRE(nv.get_base() == note_value_base::_16th);
    REQUIRE(nv.get_tuplet() == tuplet::triplet);
    REQUIRE(nv.get_num_dots() == 0);
  }

  SECTION("with base and dot count")
  {
    constexpr auto nv = note_value(note_value_base::half, 3);

    REQUIRE(nv.get_base() == note_value_base::half);
    REQUIRE(nv.get_tuplet() == tuplet::duplet);
    REQUIRE(nv.get_num_dots() == 3);
  }

  SECTION("with base, tuplet, and dot count")
  {
    constexpr auto nv
      = note_value(note_value_base::quarter, tuplet::quintuplet, 4);

    REQUIRE(nv.get_base() == note_value_base::quarter);
    REQUIRE(nv.get_tuplet() == tuplet::quintuplet);
    REQUIRE(nv.get_num_dots() == 4);
  }
}

TEST_CASE("note_value relative value", "[note_value]")
{
  REQUIRE(relative_value(note_value()) == 1);
  REQUIRE(relative_value(note_value(note_value_base::quarter)) == 1 / 4_Fr);
  REQUIRE(relative_value(note_value(note_value_base::_8th, tuplet::triplet))
          == 1 / 12_Fr);
  REQUIRE(relative_value(note_value(note_value_base::half, 3)) == 15 / 16_Fr);
  REQUIRE(
    relative_value(note_value(note_value_base::_16th, tuplet::quintuplet, 1))
    == 3 / 80_Fr);
}

TEST_CASE("note_value comparison", "[note_value]")
{
  SECTION("equality")
  {
    REQUIRE(note_value(note_value_base::_8th)
            == note_value(note_value_base::_8th));
    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  != note_value(note_value_base::_8th));

    REQUIRE(note_value(note_value_base::half, tuplet::triplet)
            == note_value(note_value_base::half, tuplet::triplet));
    REQUIRE_FALSE(note_value(note_value_base::whole, tuplet::sextuplet)
                  != note_value(note_value_base::whole, tuplet::sextuplet));

    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  == note_value(note_value_base::_16th));
    REQUIRE(note_value(note_value_base::_8th)
            != note_value(note_value_base::_16th));
  }

  SECTION("order")
  {
    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  < note_value(note_value_base::_8th));
    REQUIRE(note_value(note_value_base::_8th)
            <= note_value(note_value_base::_8th));
    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  > note_value(note_value_base::_8th));
    REQUIRE(note_value(note_value_base::_8th)
            >= note_value(note_value_base::_8th));

    
  }
}
