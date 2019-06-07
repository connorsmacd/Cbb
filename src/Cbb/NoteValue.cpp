#include <Cbb/NoteValue.hpp>

#include <algorithm>
#include <functional>
#include <stdexcept>


namespace Cbb {


CompositeNoteValue::CompositeNoteValue(const NoteValueBase base) :
    CompositeNoteValue {NoteValue(base)}
{
}

CompositeNoteValue::CompositeNoteValue(const NoteValue& value) : values_ {value} {}

CompositeNoteValue::CompositeNoteValue(const std::initializer_list<NoteValue> values) :
    values_ {values}
{
    if (values.size() == 0)
        throw std::invalid_argument("a composite note value cannot be empty");
}

CompositeNoteValue::CompositeNoteValue(const Fraction& relativeValue)
{
}

CompositeNoteValue& CompositeNoteValue::append(const NoteValue& value)
{
    values_.push_back(value);
    return *this;
}

CompositeNoteValue& CompositeNoteValue::append(const CompositeNoteValue& other)
{
    values_.insert(values_.end(), other.values_.begin(), other.values_.end());
    return *this;
}

CompositeNoteValue& CompositeNoteValue::prepend(const NoteValue& value)
{
    values_.insert(values_.begin(), value);
    return *this;
}

CompositeNoteValue& CompositeNoteValue::prepend(const CompositeNoteValue& other)
{
    values_.insert(values_.begin(), other.values_.begin(), other.values_.end());
    return *this;
}

const NoteValue& CompositeNoteValue::operator[](const std::size_t index) const
{
    return values_[index];
}

NoteValue& CompositeNoteValue::operator[](const std::size_t index)
{
    return values_[index];
}

Fraction CompositeNoteValue::relativeValue() const noexcept
{
    return std::transform_reduce(values_.begin(),
                                 values_.end(),
                                 Fraction(),
                                 std::plus<Fraction>(),
                                 std::mem_fn(&NoteValue::relativeValue));
}

Fraction relativeValue(const CompositeNoteValue& value) noexcept
{
    return value.relativeValue();
}

bool operator==(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return relativeValue(left) == relativeValue(right);
}

bool operator!=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return !(left == right);
}

bool operator<(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return relativeValue(left) < relativeValue(right);
}

bool operator<=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return !(left > right);
}

bool operator>(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return right < left;
}

bool operator>=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept
{
    return !(left < right);
}


}; // namespace Cbb
