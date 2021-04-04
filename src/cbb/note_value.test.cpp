#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cbb/note_value.hpp>


using namespace cbb;
using namespace ieme::fraction_literals;


TEST_CASE("note_value_base relative value", "[note_value]")
{
  REQUIRE(relative_value(note_value_base::_256th) == 1 / 256_fr);
  REQUIRE(relative_value(note_value_base::_128th) == 1 / 128_fr);
  REQUIRE(relative_value(note_value_base::_64th) == 1 / 64_fr);
  REQUIRE(relative_value(note_value_base::_32nd) == 1 / 32_fr);
  REQUIRE(relative_value(note_value_base::_16th) == 1 / 16_fr);
  REQUIRE(relative_value(note_value_base::_8th) == 1 / 8_fr);
  REQUIRE(relative_value(note_value_base::quarter) == 1 / 4_fr);
  REQUIRE(relative_value(note_value_base::half) == 1 / 2_fr);
  REQUIRE(relative_value(note_value_base::whole) == 1);
  REQUIRE(relative_value(note_value_base::double_whole) == 2);
  REQUIRE(relative_value(note_value_base::quadruple_whole) == 4);
  REQUIRE(relative_value(note_value_base::octuple_whole) == 8);
  REQUIRE(relative_value(note_value_base::demisemihemidemisemiquaver)
          == 1 / 256_fr);
  REQUIRE(relative_value(note_value_base::semihemidemisemiquaver)
          == 1 / 128_fr);
  REQUIRE(relative_value(note_value_base::hemidemisemiquaver) == 1 / 64_fr);
  REQUIRE(relative_value(note_value_base::demisemiquaver) == 1 / 32_fr);
  REQUIRE(relative_value(note_value_base::semiquaver) == 1 / 16_fr);
  REQUIRE(relative_value(note_value_base::quaver) == 1 / 8_fr);
  REQUIRE(relative_value(note_value_base::crotchet) == 1 / 4_fr);
  REQUIRE(relative_value(note_value_base::minim) == 1 / 2_fr);
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
  REQUIRE(relative_value(note_value(note_value_base::quarter)) == 1 / 4_fr);
  REQUIRE(relative_value(note_value(note_value_base::_8th, tuplet::triplet))
          == 1 / 12_fr);
  REQUIRE(relative_value(note_value(note_value_base::half, 3)) == 15 / 16_fr);
  REQUIRE(
    relative_value(note_value(note_value_base::_16th, tuplet::quintuplet, 1))
    == 3 / 80_fr);
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

    REQUIRE_FALSE(note_value(note_value_base::half, tuplet::triplet)
                  < note_value(note_value_base::half, tuplet::triplet));
    REQUIRE(note_value(note_value_base::whole, tuplet::sextuplet)
            <= note_value(note_value_base::whole, tuplet::sextuplet));
    REQUIRE_FALSE(note_value(note_value_base::half, tuplet::triplet)
                  > note_value(note_value_base::half, tuplet::triplet));
    REQUIRE(note_value(note_value_base::whole, tuplet::sextuplet)
            >= note_value(note_value_base::whole, tuplet::sextuplet));

    REQUIRE(note_value(note_value_base::_16th)
            < note_value(note_value_base::_8th));
    REQUIRE(note_value(note_value_base::_16th)
            <= note_value(note_value_base::_8th));
    REQUIRE_FALSE(note_value(note_value_base::_16th)
                  > note_value(note_value_base::_8th));
    REQUIRE_FALSE(note_value(note_value_base::_16th)
                  >= note_value(note_value_base::_8th));

    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  < note_value(note_value_base::_16th));
    REQUIRE_FALSE(note_value(note_value_base::_8th)
                  <= note_value(note_value_base::_16th));
    REQUIRE(note_value(note_value_base::_8th)
            > note_value(note_value_base::_16th));
    REQUIRE(note_value(note_value_base::_8th)
            >= note_value(note_value_base::_16th));
  }
}

TEST_CASE("composite_note_value construction", "[note_value]")
{
  SECTION("default")
  {
    auto const cnv = composite_note_value();

    REQUIRE(cnv.size() == 1);
    REQUIRE(cnv.at(0) == note_value());
  }

  SECTION("initializer_list")
  {
    auto const cnv = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    REQUIRE(cnv.size() == 2);
    REQUIRE(cnv.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv.at(1) == note_value(note_value_base::_16th));
  }

  SECTION("single note_value")
  {
    auto const cnv = composite_note_value(note_value(note_value_base::_32nd));

    REQUIRE(cnv.size() == 1);
    REQUIRE(cnv.at(0) == note_value(note_value_base::_32nd));
  }
}

TEST_CASE("composite_note_value access", "[note_value]")
{
  SECTION("operator[]")
  {
    auto const cnv = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    REQUIRE(cnv[0] == note_value(note_value_base::_8th));
    REQUIRE(cnv[1] == note_value(note_value_base::_16th));
  }

  SECTION("at")
  {
    auto const cnv = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    REQUIRE(cnv.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv.at(1) == note_value(note_value_base::_16th));
    REQUIRE_THROWS(cnv.at(2));
  }
}

TEST_CASE("composite_note_value single/tied queries", "[note_value]")
{
  SECTION("single")
  {
    auto const cnv = composite_note_value(note_value(note_value_base::_32nd));

    REQUIRE(cnv.is_single());
    REQUIRE_FALSE(cnv.is_tied());
  }

  SECTION("tied")
  {
    auto const cnv = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    REQUIRE_FALSE(cnv.is_single());
    REQUIRE(cnv.is_tied());
  }
}

TEST_CASE("composite_note_value append", "[note_value]")
{
  SECTION("composite_note_value")
  {
    SECTION("append()")
    {
      auto cnv = composite_note_value(note_value(note_value_base::_32nd));

      cnv.append(composite_note_value({note_value(note_value_base::_8th),
                                       note_value(note_value_base::_16th)}));

      REQUIRE(cnv.size() == 3);
      REQUIRE(cnv.at(0) == note_value(note_value_base::_32nd));
      REQUIRE(cnv.at(1) == note_value(note_value_base::_8th));
      REQUIRE(cnv.at(2) == note_value(note_value_base::_16th));
    }

    SECTION("operator+=")
    {
      auto cnv = composite_note_value(note_value(note_value_base::_32nd));

      cnv += composite_note_value({note_value(note_value_base::_8th),
                                   note_value(note_value_base::_16th)});

      REQUIRE(cnv.size() == 3);
      REQUIRE(cnv.at(0) == note_value(note_value_base::_32nd));
      REQUIRE(cnv.at(1) == note_value(note_value_base::_8th));
      REQUIRE(cnv.at(2) == note_value(note_value_base::_16th));
    }
  }

  SECTION("note_value")
  {
    SECTION("append()")
    {
      auto cnv = composite_note_value(note_value(note_value_base::_32nd));

      cnv.append(note_value(note_value_base::_8th));

      REQUIRE(cnv.size() == 2);
      REQUIRE(cnv.at(0) == note_value(note_value_base::_32nd));
      REQUIRE(cnv.at(1) == note_value(note_value_base::_8th));
    }

    SECTION("operator+=")
    {
      auto cnv = composite_note_value(note_value(note_value_base::_32nd));

      cnv += note_value(note_value_base::_8th);

      REQUIRE(cnv.size() == 2);
      REQUIRE(cnv.at(0) == note_value(note_value_base::_32nd));
      REQUIRE(cnv.at(1) == note_value(note_value_base::_8th));
    }
  }
}

TEST_CASE("composite_note_value prepend", "[note_value]")
{
  SECTION("composite_note_value")
  {
    auto cnv = composite_note_value(note_value(note_value_base::_32nd));

    cnv.prepend(composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)}));

    REQUIRE(cnv.size() == 3);
    REQUIRE(cnv.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv.at(1) == note_value(note_value_base::_16th));
    REQUIRE(cnv.at(2) == note_value(note_value_base::_32nd));
  }

  SECTION("note_value")
  {
    auto cnv = composite_note_value(note_value(note_value_base::_32nd));

    cnv.prepend(note_value(note_value_base::_8th));

    REQUIRE(cnv.size() == 2);
    REQUIRE(cnv.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv.at(1) == note_value(note_value_base::_32nd));
  }
}

TEST_CASE("composite_note_value operator+", "[note_value]")
{
  SECTION("note_value const& + note_value const&")
  {
    auto const cnv
      = note_value(note_value_base::_8th) + note_value(note_value_base::half);

    REQUIRE(cnv.size() == 2);
    REQUIRE(cnv.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv.at(1) == note_value(note_value_base::half));
  }

  SECTION("composite_note_value const& + composite_note_value const&")
  {
    auto const cnv_1 = composite_note_value(note_value(note_value_base::_32nd));
    auto const cnv_2 = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    auto const cnv_3 = cnv_1 + cnv_2;

    REQUIRE(cnv_3.size() == 3);
    REQUIRE(cnv_3.at(0) == note_value(note_value_base::_32nd));
    REQUIRE(cnv_3.at(1) == note_value(note_value_base::_8th));
    REQUIRE(cnv_3.at(2) == note_value(note_value_base::_16th));
  }

  SECTION("composite_note_value&& + composite_note_value const&")
  {
    auto cnv_1 = composite_note_value(note_value(note_value_base::_32nd));
    auto const cnv_2 = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    auto const cnv_3 = std::move(cnv_1) + cnv_2;

    REQUIRE(cnv_1.size() == 0);

    REQUIRE(cnv_3.size() == 3);
    REQUIRE(cnv_3.at(0) == note_value(note_value_base::_32nd));
    REQUIRE(cnv_3.at(1) == note_value(note_value_base::_8th));
    REQUIRE(cnv_3.at(2) == note_value(note_value_base::_16th));
  }

  SECTION("composite_note_value const& + composite_note_value&&")
  {
    auto const cnv_1 = composite_note_value(note_value(note_value_base::_32nd));
    auto cnv_2 = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    auto const cnv_3 = cnv_1 + std::move(cnv_2);

    REQUIRE(cnv_2.size() == 0);

    REQUIRE(cnv_3.size() == 3);
    REQUIRE(cnv_3.at(0) == note_value(note_value_base::_32nd));
    REQUIRE(cnv_3.at(1) == note_value(note_value_base::_8th));
    REQUIRE(cnv_3.at(2) == note_value(note_value_base::_16th));
  }

  SECTION("composite_note_value const& + note_value const&")
  {
    auto const cnv_1 = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    auto const cnv_2 = cnv_1 + note_value(note_value_base::half);

    REQUIRE(cnv_2.size() == 3);
    REQUIRE(cnv_2.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv_2.at(1) == note_value(note_value_base::_16th));
    REQUIRE(cnv_2.at(2) == note_value(note_value_base::half));
  }

  SECTION("composite_note_value&& + note_value const&")
  {
    auto cnv_1 = composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::_16th)});

    auto const cnv_2 = std::move(cnv_1) + note_value(note_value_base::half);

    REQUIRE(cnv_1.size() == 0);

    REQUIRE(cnv_2.size() == 3);
    REQUIRE(cnv_2.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv_2.at(1) == note_value(note_value_base::_16th));
    REQUIRE(cnv_2.at(2) == note_value(note_value_base::half));
  }

  SECTION("note_value const& + composite_note_value const&")
  {
    auto const cnv_1 = composite_note_value(
      {note_value(note_value_base::_16th), note_value(note_value_base::half)});

    auto const cnv_2 = note_value(note_value_base::_8th) + cnv_1;

    REQUIRE(cnv_2.size() == 3);
    REQUIRE(cnv_2.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv_2.at(1) == note_value(note_value_base::_16th));
    REQUIRE(cnv_2.at(2) == note_value(note_value_base::half));
  }

  SECTION("note_value const& + composite_note_value&&")
  {
    auto cnv_1 = composite_note_value(
      {note_value(note_value_base::_16th), note_value(note_value_base::half)});

    auto const cnv_2 = note_value(note_value_base::_8th) + std::move(cnv_1);

    REQUIRE(cnv_1.size() == 0);

    REQUIRE(cnv_2.size() == 3);
    REQUIRE(cnv_2.at(0) == note_value(note_value_base::_8th));
    REQUIRE(cnv_2.at(1) == note_value(note_value_base::_16th));
    REQUIRE(cnv_2.at(2) == note_value(note_value_base::half));
  }
}

TEST_CASE("composite_note_value relative value", "[note_value]")
{
  REQUIRE(
    relative_value(composite_note_value(
      {note_value(note_value_base::_8th), note_value(note_value_base::half)}))
    == 5 / 8_fr);
}

TEST_CASE("composite_note_value comparison", "[note_value]")
{
  SECTION("equivalence")
  {
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            == composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::half)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  != composite_note_value({note_value(note_value_base::_8th),
                                           note_value(note_value_base::half)}));

    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            == composite_note_value({note_value(note_value_base::half),
                                     note_value(note_value_base::_8th)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  != composite_note_value({note_value(note_value_base::half),
                                           note_value(note_value_base::_8th)}));

    REQUIRE_FALSE(
      composite_note_value(
        {note_value(note_value_base::_8th), note_value(note_value_base::half)})
      == composite_note_value({note_value(note_value_base::_8th),
                               note_value(note_value_base::quarter)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            != composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::quarter)}));
  }

  SECTION("order")
  {
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  < composite_note_value({note_value(note_value_base::_8th),
                                          note_value(note_value_base::half)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            <= composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::half)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  > composite_note_value({note_value(note_value_base::_8th),
                                          note_value(note_value_base::half)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            >= composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::half)}));

    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  < composite_note_value({note_value(note_value_base::half),
                                          note_value(note_value_base::_8th)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            <= composite_note_value({note_value(note_value_base::half),
                                     note_value(note_value_base::_8th)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::half)})
                  > composite_note_value({note_value(note_value_base::half),
                                          note_value(note_value_base::_8th)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            >= composite_note_value({note_value(note_value_base::half),
                                     note_value(note_value_base::_8th)}));

    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::quarter)})
            < composite_note_value({note_value(note_value_base::_8th),
                                    note_value(note_value_base::half)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::quarter)})
            <= composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::half)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::quarter)})
                  > composite_note_value({note_value(note_value_base::_8th),
                                          note_value(note_value_base::half)}));
    REQUIRE_FALSE(composite_note_value({note_value(note_value_base::_8th),
                                        note_value(note_value_base::quarter)})
                  >= composite_note_value({note_value(note_value_base::_8th),
                                           note_value(note_value_base::half)}));

    REQUIRE_FALSE(
      composite_note_value(
        {note_value(note_value_base::_8th), note_value(note_value_base::half)})
      < composite_note_value({note_value(note_value_base::_8th),
                              note_value(note_value_base::quarter)}));
    REQUIRE_FALSE(
      composite_note_value(
        {note_value(note_value_base::_8th), note_value(note_value_base::half)})
      <= composite_note_value({note_value(note_value_base::_8th),
                               note_value(note_value_base::quarter)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            > composite_note_value({note_value(note_value_base::_8th),
                                    note_value(note_value_base::quarter)}));
    REQUIRE(composite_note_value({note_value(note_value_base::_8th),
                                  note_value(note_value_base::half)})
            >= composite_note_value({note_value(note_value_base::_8th),
                                     note_value(note_value_base::quarter)}));
  }
}
