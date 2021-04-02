#ifndef CBB_NOTE_VALUE_HPP
#define CBB_NOTE_VALUE_HPP

#include <cbb/fraction.hpp>

#include <climits>


namespace cbb {


enum class note_value_base {
  _256th = -8,
  _128th,
  _64th,
  _32nd,
  _16th,
  _8th,
  quarter,
  half,
  whole,
  double_whole,
  quadruple_whole,
  octuple_whole,
  demisemihemidemisemiquaver = _256th,
  semihemidemisemiquaver = _128th,
  hemidemisemiquaver = _64th,
  demisemiquaver = _32nd,
  semiquaver = _16th,
  quaver = _8th,
  crotchet = quarter,
  minim = half,
  semibreve = whole,
  breve = double_whole,
  longa = quadruple_whole,
  maxima = octuple_whole,
};

constexpr fraction relative_value(note_value_base nvb) noexcept;


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

constexpr fraction factor_of(tuplet t) noexcept;


using dot_count_t = int;

static constexpr auto max_num_dots
  = static_cast<dot_count_t>(sizeof(long long) * CHAR_BIT - 1);

constexpr fraction dot_augmentation(dot_count_t num_dots) noexcept;


class note_value final {

public:
  using base = note_value_base;

  constexpr note_value() noexcept = default;

  constexpr note_value(base b,
                       tuplet t = tuplet::duplet,
                       dot_count_t num_dots = 0) noexcept;

  constexpr note_value(base b, dot_count_t num_dots) noexcept;

  constexpr base get_base() const noexcept { return base_; }

  constexpr tuplet get_tuplet() const noexcept { return tuplet_; }

  constexpr dot_count_t get_num_dots() const noexcept { return num_dots_; }

private:
  base base_ = base::whole;
  tuplet tuplet_ = tuplet::duplet;
  dot_count_t num_dots_ = 0;
};

constexpr fraction relative_value(note_value const& nv) noexcept;

constexpr bool operator==(note_value const& l, note_value const& r) noexcept;
constexpr bool operator!=(note_value const& l, note_value const& r) noexcept;
constexpr bool operator<(note_value const& l, note_value const& r) noexcept;
constexpr bool operator<=(note_value const& l, note_value const& r) noexcept;
constexpr bool operator>(note_value const& l, note_value const& r) noexcept;
constexpr bool operator>=(note_value const& l, note_value const& r) noexcept;


// =============================================================================


constexpr fraction relative_value(note_value_base const nvb) noexcept
{
  return ieme::pow2<fraction_rep_t, fraction_ops_t>(static_cast<int>(nvb));
}

constexpr fraction factor_of(tuplet const t) noexcept
{
  return {2, static_cast<fraction_rep_t>(t)};
}

constexpr fraction dot_augmentation(dot_count_t const num_dots) noexcept
{
  return 2 - ieme::pow2<fraction_rep_t, fraction_ops_t>(-num_dots);
}

constexpr note_value::note_value(base const b,
                                 tuplet const t,
                                 dot_count_t const num_dots) noexcept :
  base_ {b}, tuplet_ {t}, num_dots_ {num_dots}
{
}

constexpr note_value::note_value(base const b,
                                 dot_count_t const num_dots) noexcept :
  note_value {b, tuplet::duplet, num_dots}
{
}

constexpr fraction relative_value(note_value const& nv) noexcept
{
  return relative_value(nv.get_base()) * factor_of(nv.get_tuplet())
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


} // namespace cbb


#endif
