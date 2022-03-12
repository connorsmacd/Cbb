#ifndef CBB_POWER_OF_2_CONSTANTS_HPP
#define CBB_POWER_OF_2_CONSTANTS_HPP

#include <cbb/power_of_2.hpp>


namespace cbb::numbers {

static constexpr auto one_256th = power_of_2(fraction(1, 256));
static constexpr auto one_128th = power_of_2(fraction(1, 128));
static constexpr auto one_64th = power_of_2(fraction(1, 64));
static constexpr auto one_32nd = power_of_2(fraction(1, 32));
static constexpr auto one_16th = power_of_2(fraction(1, 16));
static constexpr auto one_8th = power_of_2(fraction(1, 8));
static constexpr auto one_4th = power_of_2(fraction(1, 4));
static constexpr auto one_quarter = power_of_2(one_4th);
static constexpr auto one_half = power_of_2(fraction(1, 2));
static constexpr auto _1 = power_of_2(1);
static constexpr auto _2 = power_of_2(2);
static constexpr auto _4 = power_of_2(4);
static constexpr auto _8 = power_of_2(8);
static constexpr auto _16 = power_of_2(16);
static constexpr auto _32 = power_of_2(32);
static constexpr auto _64 = power_of_2(64);
static constexpr auto _128 = power_of_2(128);
static constexpr auto _256 = power_of_2(256);

} // namespace cbb::numbers


#endif
