#pragma once

#include <Cbb/Fraction.hpp>

#include <climits>
#include <cmath>
#include <vector>


namespace Cbb {


// Each enumerator value is the binary log of its relative value
enum NoteValueBase {
    twoHundredFiftySixthNote = -8,
    oneHundredTwentyEighthNote,
    sixtyFourthNote,
    thirtySecondNote,
    sixteenthNote,
    eighthNote,
    quarterNote,
    halfNote,
    wholeNote,
    doubleWholeNote,
    quadrupleWholeNote,
    octupleWholeNote,
    demisemihemidemisemiquaver = twoHundredFiftySixthNote,
    semihemidemisemiquaver = oneHundredTwentyEighthNote,
    hemidemisemiquaver = sixtyFourthNote,
    demisemiquaver = thirtySecondNote,
    semiquaver = sixteenthNote,
    quaver = eighthNote,
    crotchet = quarterNote,
    minim = halfNote,
    semibreve = wholeNote,
    breve = doubleWholeNote,
    longa = quadrupleWholeNote,
    maxima = octupleWholeNote,
};

constexpr Fraction relativeValue(NoteValueBase value) noexcept;


enum Tuplet {
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

constexpr Fraction calculateTupletFactor(Tuplet tuplet) noexcept;


constexpr Fraction calculateDotAugmentation(std::size_t numDots) noexcept;


class NoteValue final {

public:
    using Base = NoteValueBase;

    static constexpr std::size_t maxNumDots = sizeof(long long) * CHAR_BIT - 1;

    constexpr NoteValue() noexcept = default;
    constexpr NoteValue(Base base, Tuplet tuplet = duplet, std::size_t numDots = 0) noexcept;
    constexpr NoteValue(Base base, std::size_t numDots) noexcept;
    constexpr NoteValue(const UnitFraction& unitFraction) noexcept;

    constexpr Base base() const noexcept { return base_; }
    constexpr Tuplet tuplet() const noexcept { return tuplet_; }
    constexpr std::size_t numDots() const noexcept { return numDots_; }

    constexpr Fraction relativeValue() const noexcept;

    friend constexpr Fraction operator/(const NoteValue& dividend,
                                        const NoteValue& divisor) noexcept;
    friend constexpr Fraction operator%(const NoteValue& dividend,
                                        const NoteValue& divisor) noexcept;

private:
    Base base_ = wholeNote;
    Tuplet tuplet_ = duplet;
    std::size_t numDots_ = {};
};

constexpr Fraction relativeValue(const NoteValue& noteValue) noexcept;

constexpr bool operator==(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator!=(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator<(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator<=(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator>(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator>=(const NoteValue& left, const NoteValue& right) noexcept;

constexpr Fraction operator/(const NoteValue& dividend, const NoteValue& divisor) noexcept;
constexpr Fraction operator%(const NoteValue& dividend, const NoteValue& divisor) noexcept;


// Uniformly represents either a single note value or a sequence of tied note values
// TODO: nested tuplets?
class CompositeNoteValue final {

public:
    CompositeNoteValue() = default;
    CompositeNoteValue(NoteValueBase base);
    CompositeNoteValue(const NoteValue& value);
    CompositeNoteValue(std::initializer_list<NoteValue> values);

    CompositeNoteValue& append(const CompositeNoteValue& value);
    CompositeNoteValue& operator+=(const CompositeNoteValue& value);

    CompositeNoteValue& prepend(const CompositeNoteValue& value);

    const NoteValue& operator[](std::size_t index) const;
    NoteValue& operator[](std::size_t index);

    std::size_t size() const noexcept { return values_.size(); }

    Fraction relativeValue() const noexcept;

    // TODO: make this a range

private:
    std::vector<NoteValue> values_ = {wholeNote};
};

Fraction relativeValue(const CompositeNoteValue& value) noexcept;

bool operator==(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;
bool operator!=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;
bool operator<(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;
bool operator<=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;
bool operator>(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;
bool operator>=(const CompositeNoteValue& left, const CompositeNoteValue& right) noexcept;

CompositeNoteValue operator+(const NoteValue& left, const NoteValue& right);
CompositeNoteValue operator+(const CompositeNoteValue& left, const CompositeNoteValue& right);

Fraction operator/(const CompositeNoteValue& dividend, const CompositeNoteValue& divisor) noexcept;
Fraction operator%(const CompositeNoteValue& dividend, const CompositeNoteValue& divisor) noexcept;


// =================================================================================================


constexpr Fraction relativeValue(const NoteValueBase value) noexcept
{
    return fractionPow2(value);
}

constexpr Fraction calculateTupletFactor(const Tuplet tuplet) noexcept
{
    if (tuplet < 2)
        return {0, 0};

    return {2, tuplet};
}

constexpr Fraction calculateDotAugmentation(const std::size_t numDots) noexcept
{
    if (numDots > NoteValue::maxNumDots)
        return {0, 0};

    return 2 - fractionPow2(-static_cast<int>(numDots));
}

constexpr NoteValue::NoteValue(const Base base,
                               const Tuplet tuplet,
                               const std::size_t numDots) noexcept :
    base_ {base},
    tuplet_ {tuplet},
    numDots_ {numDots}
{
}

constexpr NoteValue::NoteValue(const Base base, const std::size_t numDots) noexcept :
    NoteValue {base, duplet, numDots}
{
}

constexpr NoteValue::NoteValue(const UnitFraction& unitFraction) noexcept
{
    const auto numDivisions = reciprocalOf(unitFraction);

    // Get the exponent of the largest power of 2 that divides the number of divisions
    // and is not equal to the number of divisions
    const auto exponentOfGreatestDivisiblePow2 = [=]() {
        for (int result = 1; true; ++result)
        {
            const auto nextPow2 = fractionPow2(result + 1);

            if (numDivisions % nextPow2 != 0 || numDivisions == nextPow2)
                return result;
        }
    }();

    base_ = static_cast<Base>(-exponentOfGreatestDivisiblePow2 - 1);

    const auto tupletValue = numDivisions / fractionPow2(exponentOfGreatestDivisiblePow2);
    tuplet_ = static_cast<Tuplet>(numerator(reduce(tupletValue)));
}

constexpr Fraction NoteValue::relativeValue() const noexcept
{
    return ::Cbb::relativeValue(base_) * calculateTupletFactor(tuplet_)
           * calculateDotAugmentation(numDots_);
}

constexpr Fraction relativeValue(const NoteValue& noteValue) noexcept
{
    return noteValue.relativeValue();
}

constexpr bool operator==(const NoteValue& left, const NoteValue& right) noexcept
{
    return relativeValue(left) == relativeValue(right);
}

constexpr bool operator!=(const NoteValue& left, const NoteValue& right) noexcept
{
    return !(left == right);
}

constexpr bool operator<(const NoteValue& left, const NoteValue& right) noexcept
{
    return relativeValue(left) < relativeValue(right);
}

constexpr bool operator<=(const NoteValue& left, const NoteValue& right) noexcept
{
    return !(left > right);
}

constexpr bool operator>(const NoteValue& left, const NoteValue& right) noexcept
{
    return right < left;
}

constexpr bool operator>=(const NoteValue& left, const NoteValue& right) noexcept
{
    return !(left < right);
}

constexpr Fraction operator/(const NoteValue& dividend, const NoteValue& divisor) noexcept
{
    return relativeValue(dividend) / relativeValue(divisor);
}

constexpr Fraction operator%(const NoteValue& dividend, const NoteValue& divisor) noexcept
{
    return relativeValue(dividend) % relativeValue(divisor);
}


}; // namespace Cbb
