#ifndef CBB_NOTE_VALUE_HPP
#define CBB_NOTE_VALUE_HPP

#include <cbb/power_of_2_constants.hpp>

#include <type_traits>


namespace cbb {


enum class tuplet {
  duplet = 2,
  triplet,
  quadruplet,
  quintuplet,
  sextuplet,
  septuplet,
  octuplet,
  nonuplet,
  decuplet,
};

constexpr fraction tuplet_factor(tuplet t) noexcept;


enum class dot_count {
  none,
  single,
  _double,
  triple,
};

constexpr fraction dot_augmentation(dot_count num_dots) noexcept;


class note_value final {

public:
  constexpr note_value() noexcept = default;

  constexpr explicit note_value(power_of_2 _power_of_2,
                                tuplet _tuplet = tuplet::duplet,
                                dot_count num_dots = dot_count::none) noexcept;

  constexpr note_value(power_of_2 _power_of_2, dot_count num_dots) noexcept;

  constexpr note_value with(power_of_2 new_power_of_2) const noexcept;

  constexpr note_value with(tuplet new_tuplet) const noexcept;

  constexpr note_value with(dot_count new_num_dots) const noexcept;

  constexpr power_of_2 get_power_of_2() const noexcept { return power_of_2_; }

  constexpr tuplet get_tuplet() const noexcept { return tuplet_; }

  constexpr dot_count get_num_dots() const noexcept { return num_dots_; }

private:
  power_of_2 power_of_2_ = numbers::_1;
  tuplet tuplet_ = tuplet::duplet;
  dot_count num_dots_ = dot_count::none;
};

constexpr fraction relative_value(note_value const& nv) noexcept;

constexpr bool operator==(note_value const& l, note_value const& r) noexcept;
constexpr bool operator!=(note_value const& l, note_value const& r) noexcept;
constexpr bool operator<(note_value const& l, note_value const& r) noexcept;
constexpr bool operator<=(note_value const& l, note_value const& r) noexcept;
constexpr bool operator>(note_value const& l, note_value const& r) noexcept;
constexpr bool operator>=(note_value const& l, note_value const& r) noexcept;

constexpr note_value operator*(note_value const& l, power_of_2 r) noexcept;
constexpr note_value operator*(power_of_2 l, note_value const& r) noexcept;

constexpr fraction operator/(note_value const& l, note_value const& r) noexcept;
constexpr note_value operator/(note_value const& l, power_of_2 r) noexcept;

constexpr fraction operator%(note_value const& l, note_value const& r) noexcept;


// =============================================================================


namespace detail {
template <typename EnumT>
constexpr std::underlying_type_t<EnumT> to_underlying(EnumT const e)
{
  return static_cast<std::underlying_type_t<EnumT>>(e);
}
} // namespace detail

constexpr fraction tuplet_factor(tuplet const t) noexcept
{
  return {2, detail::to_underlying(t)};
}

constexpr fraction dot_augmentation(dot_count const num_dots) noexcept
{
  return 2
         - power_of_2(power_of_2::from_exponent,
                      -detail::to_underlying(num_dots));
}

constexpr note_value::note_value(power_of_2 const _power_of_2,
                                 tuplet const _tuplet,
                                 dot_count const num_dots) noexcept :
  power_of_2_ {_power_of_2}, tuplet_ {_tuplet}, num_dots_ {num_dots}
{
}

constexpr note_value::note_value(power_of_2 const _power_of_2,
                                 dot_count const num_dots) noexcept :
  note_value {_power_of_2, tuplet::duplet, num_dots}
{
}

constexpr note_value
note_value::with(power_of_2 const new_power_of_2) const noexcept
{
  return note_value(new_power_of_2, tuplet_, num_dots_);
}

constexpr note_value note_value::with(tuplet const new_tuplet) const noexcept
{
  return note_value(power_of_2_, new_tuplet, num_dots_);
}

constexpr note_value
note_value::with(dot_count const new_num_dots) const noexcept
{
  return note_value(power_of_2_, tuplet_, new_num_dots);
}

constexpr fraction relative_value(note_value const& nv) noexcept
{
  return nv.get_power_of_2() * tuplet_factor(nv.get_tuplet())
         * dot_augmentation(nv.get_num_dots());
}

constexpr bool operator==(note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) == relative_value(r);
}

constexpr bool operator!=(note_value const& l, note_value const& r) noexcept
{
  return !(l == r);
}

constexpr bool operator<(note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) < relative_value(r);
}

constexpr bool operator<=(note_value const& l, note_value const& r) noexcept
{
  return !(l > r);
}

constexpr bool operator>(note_value const& l, note_value const& r) noexcept
{
  return r < l;
}

constexpr bool operator>=(note_value const& l, note_value const& r) noexcept
{
  return !(l < r);
}

constexpr note_value operator*(note_value const& l, power_of_2 const r) noexcept
{
  return l.with(l.get_power_of_2() * r);
}

constexpr note_value operator*(power_of_2 const l, note_value const& r) noexcept
{
  return r * l;
}

constexpr fraction operator/(note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) / relative_value(r);
}

constexpr note_value operator/(note_value const& l, power_of_2 const r) noexcept
{
  return l.with(l.get_power_of_2() / r);
}

constexpr fraction operator%(note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) % relative_value(r);
}


} // namespace cbb


#endif
