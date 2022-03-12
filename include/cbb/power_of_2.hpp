#ifndef CBB_POWER_OF_2_HPP
#define CBB_POWER_OF_2_HPP

#include <cbb/fraction.hpp>

#include <bitset>
#include <stdexcept>


namespace cbb {


class power_of_2 {

public:
  constexpr power_of_2() noexcept = default;

  explicit constexpr power_of_2(fraction value);

  struct from_exponent_t {
    explicit constexpr from_exponent_t() noexcept = default;
  };

  static constexpr auto from_exponent = from_exponent_t {};

  constexpr power_of_2(from_exponent_t, int exponent) noexcept;

  constexpr int get_exponent() const noexcept { return exponent_; }

  constexpr fraction get_value() const noexcept;

  explicit operator fraction() const noexcept { return get_value(); }

private:
  friend constexpr bool operator==(power_of_2 l, power_of_2 r) noexcept;
  friend constexpr bool operator<(power_of_2 l, power_of_2 r) noexcept;

  friend constexpr power_of_2 operator*(power_of_2 l, power_of_2 r) noexcept;
  friend constexpr power_of_2 operator/(power_of_2 l, power_of_2 r) noexcept;

  int exponent_ = 0;
};

constexpr bool operator==(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator==(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator==(fraction const& l, power_of_2 r) noexcept;

constexpr bool operator!=(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator!=(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator!=(fraction const& l, power_of_2 r) noexcept;

constexpr bool operator<(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator<(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator<(fraction const& l, power_of_2 r) noexcept;

constexpr bool operator<=(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator<=(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator<=(fraction const& l, power_of_2 r) noexcept;

constexpr bool operator>(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator>(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator>(fraction const& l, power_of_2 r) noexcept;

constexpr bool operator>=(power_of_2 l, power_of_2 r) noexcept;
constexpr bool operator>=(power_of_2 l, fraction const& r) noexcept;
constexpr bool operator>=(fraction const& l, power_of_2 r) noexcept;

constexpr power_of_2 operator+(power_of_2 p) noexcept;
constexpr fraction operator-(power_of_2 p) noexcept;

constexpr fraction operator+(power_of_2 l, power_of_2 r) noexcept;
constexpr fraction operator+(power_of_2 l, fraction const& r) noexcept;
constexpr fraction operator+(fraction const& l, power_of_2 r) noexcept;

constexpr fraction operator-(power_of_2 l, power_of_2 r) noexcept;
constexpr fraction operator-(power_of_2 l, fraction const& r) noexcept;
constexpr fraction operator-(fraction const& l, power_of_2 r) noexcept;

constexpr power_of_2 operator*(power_of_2 l, power_of_2 r) noexcept;
constexpr fraction operator*(power_of_2 l, fraction const& r) noexcept;
constexpr fraction operator*(fraction const& l, power_of_2 r) noexcept;

constexpr power_of_2 operator/(power_of_2 l, power_of_2 r) noexcept;
constexpr fraction operator/(power_of_2 l, fraction const& r) noexcept;
constexpr fraction operator/(fraction const& l, power_of_2 r) noexcept;

constexpr fraction operator%(power_of_2 l, power_of_2 r) noexcept;
constexpr fraction operator%(power_of_2 l, fraction const& r) noexcept;
constexpr fraction operator%(fraction const& l, power_of_2 r) noexcept;

constexpr power_of_2& operator*=(power_of_2& l, power_of_2 r) noexcept;
constexpr power_of_2& operator/=(power_of_2& l, power_of_2 r) noexcept;


// =================================================================================================


namespace detail {

// TODO: use <bit> for all of this in C++20

using bitset_t = std::bitset<sizeof(fraction_rep_t) * CHAR_BIT - 1>;

constexpr int assert_is_power_of_2(bitset_t const bitset)
{
  auto count = 0;

  for (std::size_t i = 0; i < bitset.size() && count < 2; ++i)
    if (bitset[i])
      ++count;

  return (count != 1) ? throw std::invalid_argument("not a power of 2")
                      : int {};
}

constexpr int sqrt_of_2(fraction_rep_t const value)
{
  auto const bitset = bitset_t(value);

  assert_is_power_of_2(bitset);

  auto result = 0;

  while (!bitset[result])
    ++result;

  return result;
}

constexpr int sqrt_of_2(fraction const value)
{
  auto const reduced_value = reduce(value);

  if (is_positive(reduced_value))
  {
    if (is_integer(reduced_value))
      return sqrt_of_2(reduced_value.numerator());

    if (is_unit_fraction(reduced_value))
      return -sqrt_of_2(reduced_value.denominator());
  }

  return true
           ? throw std::invalid_argument("a power of two must be a positive "
                                         "integer or a positive unit fraction")
           : int {};
}
} // namespace detail

constexpr power_of_2::power_of_2(fraction const value) :
  power_of_2 {from_exponent, detail::sqrt_of_2(value)}
{
}

constexpr power_of_2::power_of_2(from_exponent_t, int const exponent) noexcept :
  exponent_ {exponent}
{
}

constexpr fraction power_of_2::get_value() const noexcept
{
  return ieme::pow2<fraction_rep_t, fraction_ops_t>(exponent_);
}

constexpr bool operator==(power_of_2 const l, power_of_2 const r) noexcept
{
  return l.exponent_ == r.exponent_;
}

constexpr bool operator==(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() == r;
}

constexpr bool operator==(fraction const& l, power_of_2 const r) noexcept
{
  return r == l;
}

constexpr bool operator!=(power_of_2 const l, power_of_2 const r) noexcept
{
  return !(l == r);
}

constexpr bool operator!=(power_of_2 const l, fraction const& r) noexcept
{
  return !(l == r);
}

constexpr bool operator!=(fraction const& l, power_of_2 const r) noexcept
{
  return r != l;
}

constexpr bool operator<(power_of_2 const l, power_of_2 const r) noexcept
{
  return l.exponent_ < r.exponent_;
}

constexpr bool operator<(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() < r;
}

constexpr bool operator<(fraction const& l, power_of_2 const r) noexcept
{
  return l < r.get_value();
}

constexpr bool operator<=(power_of_2 const l, power_of_2 const r) noexcept
{
  return !(l > r);
}

constexpr bool operator<=(power_of_2 const l, fraction const& r) noexcept
{
  return !(l > r);
}

constexpr bool operator<=(fraction const& l, power_of_2 const r) noexcept
{
  return !(l > r);
}

constexpr bool operator>(power_of_2 const l, power_of_2 const r) noexcept
{
  return r < l;
}

constexpr bool operator>(power_of_2 const l, fraction const& r) noexcept
{
  return r < l;
}

constexpr bool operator>(fraction const& l, power_of_2 const r) noexcept
{
  return r < l;
}

constexpr bool operator>=(power_of_2 const l, power_of_2 const r) noexcept
{
  return !(l < r);
}

constexpr bool operator>=(power_of_2 const l, fraction const& r) noexcept
{
  return !(l < r);
}

constexpr bool operator>=(fraction const& l, power_of_2 const r) noexcept
{
  return !(l < r);
}

constexpr power_of_2 operator+(power_of_2 const p) noexcept
{
  return p;
}

constexpr fraction operator-(power_of_2 const p) noexcept
{
  return -p.get_value();
}

constexpr fraction operator+(power_of_2 const l, power_of_2 const r) noexcept
{
  return l + r.get_value();
}

constexpr fraction operator+(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() + r;
}

constexpr fraction operator+(fraction const& l, power_of_2 const r) noexcept
{
  return r + l;
}

constexpr fraction operator-(power_of_2 const l, power_of_2 const r) noexcept
{
  return l - r.get_value();
}

constexpr fraction operator-(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() - r;
}

constexpr fraction operator-(fraction const& l, power_of_2 const r) noexcept
{
  return l - r.get_value();
}

constexpr power_of_2 operator*(power_of_2 const l, power_of_2 const r) noexcept
{
  return power_of_2(power_of_2::from_exponent, l.exponent_ + r.exponent_);
}

constexpr fraction operator*(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() * r;
}

constexpr fraction operator*(fraction const& l, power_of_2 const r) noexcept
{
  return r * l;
}

constexpr power_of_2 operator/(power_of_2 const l, power_of_2 const r) noexcept
{
  return power_of_2(power_of_2::from_exponent, l.exponent_ - r.exponent_);
}

constexpr fraction operator/(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() / r;
}

constexpr fraction operator/(fraction const& l, power_of_2 const r) noexcept
{
  return l / r.get_value();
}

constexpr fraction operator%(power_of_2 const l, power_of_2 const r) noexcept
{
  return l % r.get_value();
}

constexpr fraction operator%(power_of_2 const l, fraction const& r) noexcept
{
  return l.get_value() % r;
}

constexpr fraction operator%(fraction const& l, power_of_2 const r) noexcept
{
  return l % r.get_value();
}

constexpr power_of_2& operator*=(power_of_2& l, power_of_2 r) noexcept
{
  return l = l * r;
}

constexpr power_of_2& operator/=(power_of_2& l, power_of_2 r) noexcept
{
  return l = l / r;
}


} // namespace cbb


#endif
