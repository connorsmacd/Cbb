#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cbb/power_of_2_constants.hpp>


using namespace cbb;
using namespace ieme::fraction_literals;


TEST_CASE("power_of_2 construction", "[power_of_2]")
{
  SECTION("default") { STATIC_REQUIRE(power_of_2().get_exponent() == 0); }

  SECTION("from exponent")
  {
    STATIC_REQUIRE(power_of_2(power_of_2::from_exponent, -2).get_exponent()
                   == -2);
  }

  SECTION("from fraction")
  {
    SECTION("> 1")
    {
      STATIC_REQUIRE(power_of_2(fraction(8)).get_exponent() == 3);
    }

    SECTION("1")
    {
      STATIC_REQUIRE(power_of_2(fraction(1)).get_exponent() == 0);
    }

    SECTION("< 1")
    {
      STATIC_REQUIRE(power_of_2(1 / 16_fr).get_exponent() == -4);
    }
  }
}

TEST_CASE("power_of_2::get_value", "[power_of_2]")
{
  STATIC_REQUIRE(numbers::one_8th.get_value() == 1 / 8_fr);
  STATIC_REQUIRE(numbers::_1.get_value() == 1);
  STATIC_REQUIRE(numbers::_32.get_value() == 32);
}

TEST_CASE("power_of_2 comparison operators", "[power_of_2]")
{
  SECTION("equality")
  {
    STATIC_REQUIRE(numbers::one_half == numbers::one_half);
    STATIC_REQUIRE_FALSE(numbers::one_half != numbers::one_half);

    STATIC_REQUIRE(numbers::one_half == 1 / 2_fr);
    STATIC_REQUIRE_FALSE(numbers::one_half != 1 / 2_fr);

    STATIC_REQUIRE(1 / 2_fr == numbers::one_half);
    STATIC_REQUIRE_FALSE(1 / 2_fr != numbers::one_half);

    STATIC_REQUIRE(numbers::_4 == 4);
    STATIC_REQUIRE_FALSE(numbers::_4 != 4);

    STATIC_REQUIRE(4 == numbers::_4);
    STATIC_REQUIRE_FALSE(4 != numbers::_4);

    STATIC_REQUIRE_FALSE(numbers::one_half == numbers::one_quarter);
    STATIC_REQUIRE(numbers::one_half != numbers::one_quarter);

    STATIC_REQUIRE_FALSE(numbers::one_half == 1 / 3_fr);
    STATIC_REQUIRE(numbers::one_half != 1 / 3_fr);

    STATIC_REQUIRE_FALSE(1 / 3_fr == numbers::one_half);
    STATIC_REQUIRE(1 / 3_fr != numbers::one_half);

    STATIC_REQUIRE_FALSE(numbers::_4 == 5);
    STATIC_REQUIRE(numbers::_4 != 5);

    STATIC_REQUIRE_FALSE(-2 == numbers::_4);
    STATIC_REQUIRE(-2 != numbers::_4);
  }

  SECTION("order")
  {
    STATIC_REQUIRE_FALSE(numbers::one_16th < numbers::one_16th);
    STATIC_REQUIRE(numbers::one_16th <= numbers::one_16th);
    STATIC_REQUIRE_FALSE(numbers::one_16th > numbers::one_16th);
    STATIC_REQUIRE(numbers::one_16th >= numbers::one_16th);

    STATIC_REQUIRE_FALSE(numbers::one_16th < 1 / 16_fr);
    STATIC_REQUIRE(numbers::one_16th <= 1 / 16_fr);
    STATIC_REQUIRE_FALSE(numbers::one_16th > 1 / 16_fr);
    STATIC_REQUIRE(numbers::one_16th >= 1 / 16_fr);

    STATIC_REQUIRE_FALSE(1 / 16_fr < numbers::one_16th);
    STATIC_REQUIRE(1 / 16_fr <= numbers::one_16th);
    STATIC_REQUIRE_FALSE(1 / 16_fr > numbers::one_16th);
    STATIC_REQUIRE(1 / 16_fr >= numbers::one_16th);

    STATIC_REQUIRE(numbers::one_16th < numbers::one_8th);
    STATIC_REQUIRE(numbers::one_16th <= numbers::one_8th);
    STATIC_REQUIRE_FALSE(numbers::one_16th > numbers::one_8th);
    STATIC_REQUIRE_FALSE(numbers::one_16th >= numbers::one_8th);

    STATIC_REQUIRE(numbers::one_16th < 1 / 15_fr);
    STATIC_REQUIRE(numbers::one_16th <= 1 / 15_fr);
    STATIC_REQUIRE_FALSE(numbers::one_16th > 1 / 15_fr);
    STATIC_REQUIRE_FALSE(numbers::one_16th >= 1 / 15_fr);

    STATIC_REQUIRE(1 / 9_fr < numbers::one_8th);
    STATIC_REQUIRE(1 / 9_fr <= numbers::one_8th);
    STATIC_REQUIRE_FALSE(1 / 9_fr > numbers::one_8th);
    STATIC_REQUIRE_FALSE(1 / 9_fr >= numbers::one_8th);

    STATIC_REQUIRE_FALSE(numbers::one_8th < numbers::one_16th);
    STATIC_REQUIRE_FALSE(numbers::one_8th <= numbers::one_16th);
    STATIC_REQUIRE(numbers::one_8th > numbers::one_16th);
    STATIC_REQUIRE(numbers::one_8th >= numbers::one_16th);

    STATIC_REQUIRE_FALSE(numbers::one_8th < 1 / 9_fr);
    STATIC_REQUIRE_FALSE(numbers::one_8th <= 1 / 9_fr);
    STATIC_REQUIRE(numbers::one_8th > 1 / 9_fr);
    STATIC_REQUIRE(numbers::one_8th >= 1 / 9_fr);

    STATIC_REQUIRE_FALSE(1 / 15_fr < numbers::one_16th);
    STATIC_REQUIRE_FALSE(1 / 15_fr <= numbers::one_16th);
    STATIC_REQUIRE(1 / 15_fr > numbers::one_16th);
    STATIC_REQUIRE(1 / 15_fr >= numbers::one_16th);
  }
}

TEST_CASE("power_of_2 arithmetic operators", "[power_of_2]")
{
  SECTION("unary operator+") { STATIC_REQUIRE(+numbers::_2 == numbers::_2); }

  SECTION("unary operator-") { STATIC_REQUIRE(-numbers::one_8th == -1 / 8_fr); }

  SECTION("binary operator+")
  {
    STATIC_REQUIRE(numbers::one_8th + numbers::one_half == 5 / 8_fr);
    STATIC_REQUIRE(numbers::one_8th + 3 / 4_fr == 7 / 8_fr);
    STATIC_REQUIRE(1 / 4_fr + numbers::one_8th == 3 / 8_fr);
  }

  SECTION("binary operator-")
  {
    STATIC_REQUIRE(numbers::one_half - numbers::one_8th == 3 / 8_fr);
    STATIC_REQUIRE(numbers::one_8th - 1 / 3_fr == -5 / 24_fr);
    STATIC_REQUIRE(1 / 4_fr - numbers::_1 == -3 / 4_fr);
  }

  SECTION("operator*")
  {
    STATIC_REQUIRE(numbers::_16 * numbers::one_quarter == numbers::_4);
    STATIC_REQUIRE(numbers::_16 * 1 / 3_fr == 16 / 3_fr);
    STATIC_REQUIRE(1 / 5_fr * numbers::one_half == 1 / 10_fr);
  }

  SECTION("operator/")
  {
    STATIC_REQUIRE(numbers::_16 / numbers::one_half == numbers::_32);
    STATIC_REQUIRE(numbers::_8 / (1 / 3_fr) == 24);
    STATIC_REQUIRE(1 / 5_fr / numbers::one_quarter == 4 / 5_fr);
  }

  SECTION("operator%")
  {
    STATIC_REQUIRE(numbers::_8 % numbers::_2 == 0);
    STATIC_REQUIRE(numbers::one_8th % numbers::_4 == numbers::one_8th);
    STATIC_REQUIRE(numbers::_8 % (3 / 7_fr) == 2 / 7_fr);
    STATIC_REQUIRE(3 / 11_fr % numbers::one_16th == 1 / 44_fr);
  }

  SECTION("operator*=")
  {
    static constexpr auto p = [&]() {
      auto p = numbers::one_half;
      p *= numbers::_8;
      return p;
    }();
    STATIC_REQUIRE(p == numbers::_4);
  }

  SECTION("operator/=")
  {
    static constexpr auto p = [&]() {
      auto p = numbers::_8;
      p /= numbers::_2;
      return p;
    }();
    STATIC_REQUIRE(p == numbers::_4);
  }
}
