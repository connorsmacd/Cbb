#ifndef CBB_NOTE_VALUE_HPP
#define CBB_NOTE_VALUE_HPP

#include <cbb/fraction.hpp>

#include <climits>
#include <vector>


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


class composite_note_value {

public:
  using size_type = std::vector<note_value>::size_type;
  using iterator = std::vector<note_value>::iterator;
  using const_iterator = std::vector<note_value>::const_iterator;
  using reverse_iterator = std::vector<note_value>::reverse_iterator;
  using const_reverse_iterator
    = std::vector<note_value>::const_reverse_iterator;

  composite_note_value() = default;

  composite_note_value(std::initializer_list<note_value> nvs);

  explicit composite_note_value(note_value const& nv);

  composite_note_value& append(composite_note_value const& cnv);

  composite_note_value& append(note_value const& nv);

  composite_note_value& prepend(composite_note_value const& cnv);

  composite_note_value& prepend(note_value const& nv);

  note_value const& operator[](size_type index) const;

  note_value& operator[](size_type index);

  note_value const& at(size_type index) const;

  note_value& at(size_type index);

  size_type size() const noexcept { return values_.size(); }

  bool is_single() const noexcept { return size() == 1; }

  bool is_tied() const noexcept { return size() > 1; }

  iterator begin() noexcept { return values_.begin(); }
  const_iterator begin() const noexcept { return values_.begin(); }
  const_iterator cbegin() const noexcept { return values_.cbegin(); }

  iterator end() noexcept { return values_.end(); }
  const_iterator end() const noexcept { return values_.end(); }
  const_iterator cend() const noexcept { return values_.cend(); }

  reverse_iterator rbegin() noexcept { return values_.rbegin(); }
  const_reverse_iterator rbegin() const noexcept { return values_.rbegin(); }
  const_reverse_iterator crbegin() const noexcept { return values_.crbegin(); }

  reverse_iterator rend() noexcept { return values_.rend(); }
  const_reverse_iterator rend() const noexcept { return values_.rend(); }
  const_reverse_iterator crend() const noexcept { return values_.crend(); }

private:
  std::vector<note_value> values_ = {note_value()};
};

fraction relative_value(composite_note_value const& cnv) noexcept;

bool operator==(composite_note_value const& l,
                composite_note_value const& r) noexcept;

bool operator==(composite_note_value const& l, note_value const& r) noexcept;

bool operator==(note_value const& l, composite_note_value const& r) noexcept;

bool operator!=(composite_note_value const& l,
                composite_note_value const& r) noexcept;

bool operator!=(composite_note_value const& l, note_value const& r) noexcept;

bool operator!=(note_value const& l, composite_note_value const& r) noexcept;

bool operator<(composite_note_value const& l,
               composite_note_value const& r) noexcept;

bool operator<(composite_note_value const& l, note_value const& r) noexcept;

bool operator<(note_value const& l, composite_note_value const& r) noexcept;

bool operator<=(composite_note_value const& l,
                composite_note_value const& r) noexcept;

bool operator<=(composite_note_value const& l, note_value const& r) noexcept;

bool operator<=(note_value const& l, composite_note_value const& r) noexcept;

bool operator>(composite_note_value const& l,
               composite_note_value const& r) noexcept;

bool operator>(composite_note_value const& l, note_value const& r) noexcept;

bool operator>(note_value const& l, composite_note_value const& r) noexcept;

bool operator>=(composite_note_value const& l,
                composite_note_value const& r) noexcept;

bool operator>=(composite_note_value const& l, note_value const& r) noexcept;

bool operator>=(note_value const& l, composite_note_value const& r) noexcept;

composite_note_value& operator+=(composite_note_value& l,
                                 composite_note_value const& r);

composite_note_value& operator+=(composite_note_value& l,
                                 composite_note_value&& r);

composite_note_value& operator+=(composite_note_value& l, note_value const& r);

composite_note_value operator+(note_value const& l, note_value const& r);

composite_note_value operator+(composite_note_value const& l,
                               composite_note_value const& r);

composite_note_value operator+(composite_note_value&& l,
                               composite_note_value const& r);

composite_note_value operator+(composite_note_value const& l,
                               composite_note_value&& r);

composite_note_value operator+(composite_note_value const& l,
                               note_value const& r);

composite_note_value operator+(composite_note_value&& l, note_value const& r);

composite_note_value operator+(note_value const& l,
                               composite_note_value const& r);

composite_note_value operator+(note_value const& l, composite_note_value&& r);


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
