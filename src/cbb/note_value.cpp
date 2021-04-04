#include <cbb/note_value.hpp>

#include <algorithm>
#include <iterator>


namespace cbb {


// TODO: throw on empty construction
composite_note_value::composite_note_value(
  std::initializer_list<note_value> nvs) :
  values_ {std::move(nvs)}
{
}

composite_note_value::composite_note_value(note_value const& nv) :
  composite_note_value {nv}
{
}

composite_note_value&
composite_note_value::append(composite_note_value const& cnv)
{
  values_.reserve(size() + cnv.size());

  std::copy(cnv.begin(), cnv.end(), std::back_inserter(values_));

  return *this;
}

composite_note_value& composite_note_value::append(note_value const& nv)
{
  values_.push_back(nv);

  return *this;
}

composite_note_value&
composite_note_value::prepend(composite_note_value const& cnv)
{
  values_.insert(values_.begin(), cnv.begin(), cnv.end());

  return *this;
}

composite_note_value& composite_note_value::prepend(note_value const& nv)
{
  values_.insert(values_.begin(), nv);

  return *this;
}

note_value const& composite_note_value::operator[](size_type const index) const
{
  return values_[index];
}

note_value& composite_note_value::operator[](size_type const index)
{
  return values_[index];
}

note_value const& composite_note_value::at(size_type const index) const
{
  return values_.at(index);
}

note_value& composite_note_value::at(size_type const index)
{
  return values_.at(index);
}

fraction relative_value(composite_note_value const& cnv) noexcept
{
  return std::transform_reduce(
    cnv.begin(), cnv.end(), fraction(0), std::plus<>(), [&](auto const& nv) {
      return relative_value(nv);
    });
}

bool operator==(composite_note_value const& l,
                composite_note_value const& r) noexcept
{
  return relative_value(l) == relative_value(r);
}

bool operator==(composite_note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) == relative_value(r);
}

bool operator==(note_value const& l, composite_note_value const& r) noexcept
{
  return relative_value(l) == relative_value(r);
}

bool operator!=(composite_note_value const& l,
                composite_note_value const& r) noexcept
{
  return !(l == r);
}

bool operator!=(composite_note_value const& l, note_value const& r) noexcept
{
  return !(l == r);
}

bool operator!=(note_value const& l, composite_note_value const& r) noexcept
{
  return !(l == r);
}

bool operator<(composite_note_value const& l,
               composite_note_value const& r) noexcept
{
  return relative_value(l) < relative_value(r);
}

bool operator<(composite_note_value const& l, note_value const& r) noexcept
{
  return relative_value(l) < relative_value(r);
}

bool operator<(note_value const& l, composite_note_value const& r) noexcept
{
  return relative_value(l) < relative_value(r);
}

bool operator<=(composite_note_value const& l,
                composite_note_value const& r) noexcept
{
  return !(l > r);
}

bool operator<=(composite_note_value const& l, note_value const& r) noexcept
{
  return !(l > r);
}

bool operator<=(note_value const& l, composite_note_value const& r) noexcept
{
  return !(l > r);
}

bool operator>(composite_note_value const& l,
               composite_note_value const& r) noexcept
{
  return r < l;
}

bool operator>(composite_note_value const& l, note_value const& r) noexcept
{
  return r < l;
}

bool operator>(note_value const& l, composite_note_value const& r) noexcept
{
  return r < l;
}

bool operator>=(composite_note_value const& l,
                composite_note_value const& r) noexcept
{
  return !(l < r);
}

bool operator>=(composite_note_value const& l, note_value const& r) noexcept
{
  return !(l < r);
}

bool operator>=(note_value const& l, composite_note_value const& r) noexcept
{
  return !(l < r);
}

composite_note_value& operator+=(composite_note_value& l,
                                 composite_note_value const& r)
{
  return l.append(r);
}

composite_note_value& operator+=(composite_note_value& l,
                                 composite_note_value&& r)
{
  return l.append(std::move(r));
}

composite_note_value& operator+=(composite_note_value& l, note_value const& r)
{
  return l.append(r);
}

composite_note_value operator+(note_value const& l, note_value const& r)
{
  return {l, r};
}

composite_note_value operator+(composite_note_value const& l,
                               composite_note_value const& r)
{
  return composite_note_value(l).append(r);
}

composite_note_value operator+(composite_note_value&& l,
                               composite_note_value const& r)
{
  return composite_note_value(std::move(l)).append(r);
}

composite_note_value operator+(composite_note_value const& l,
                               composite_note_value&& r)
{
  return composite_note_value(std::move(r)).prepend(l);
}

composite_note_value operator+(composite_note_value const& l,
                               note_value const& r)
{
  return composite_note_value(l).append(r);
}

composite_note_value operator+(composite_note_value&& l, note_value const& r)
{
  return composite_note_value(std::move(l)).append(r);
}

composite_note_value operator+(note_value const& l,
                               composite_note_value const& r)
{
  return composite_note_value(l).append(r);
}

composite_note_value operator+(note_value const& l, composite_note_value&& r)
{
  return composite_note_value(std::move(r)).prepend(l);
}


} // namespace cbb
