#pragma once

#include <Cbb/Fraction.hpp>

#include <climits>
#include <cmath>
#include <vector>


namespace Cbb {


class BasicNoteValue final {

public:
    constexpr BasicNoteValue() noexcept = default;
    constexpr BasicNoteValue(int baseTwoExponent) noexcept;

    constexpr Fraction relativeValue() const noexcept;

private:
    int baseTwoExponent_ = {};
};

constexpr Fraction relativeValue(const BasicNoteValue& value) noexcept;

constexpr bool operator==(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;
constexpr bool operator!=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;
constexpr bool operator<(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;
constexpr bool operator<=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;
constexpr bool operator>(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;
constexpr bool operator>=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept;


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

constexpr Fraction calculateTupletAugmentation(Tuplet tuplet) noexcept;


constexpr Fraction calculateDotAugmentation(std::size_t numDots) noexcept;


class NoteValue final {

public:
    static constexpr std::size_t maxNumDots = sizeof(long long) * CHAR_BIT - 1;

    constexpr NoteValue() noexcept = default;
    constexpr NoteValue(const BasicNoteValue& base,
                        Tuplet tuplet = duplet,
                        std::size_t numDots = 0) noexcept;
    constexpr NoteValue(const BasicNoteValue& base, std::size_t numDots) noexcept;

    constexpr const BasicNoteValue& getBase() const noexcept { return base_; }
    constexpr Tuplet getTuplet() const noexcept { return tuplet_; }
    constexpr std::size_t getNumDots() const noexcept { return numDots_; }

    constexpr Fraction relativeValue() const noexcept;

private:
    BasicNoteValue base_;
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


// =================================================================================================


constexpr BasicNoteValue::BasicNoteValue(const int baseTwoExponent) noexcept :
    baseTwoExponent_ {baseTwoExponent}
{
}

constexpr Fraction BasicNoteValue::relativeValue() const noexcept
{
    return fractionPow2(baseTwoExponent_);
}

constexpr Fraction relativeValue(const BasicNoteValue& value) noexcept
{
    return value.relativeValue();
}

constexpr bool operator==(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return relativeValue(left) == relativeValue(right);
}

constexpr bool operator!=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return !(left == right);
}

constexpr bool operator<(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return relativeValue(left) < relativeValue(right);
}

constexpr bool operator<=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return !(left > right);
}

constexpr bool operator>(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return right < left;
}

constexpr bool operator>=(const BasicNoteValue& left, const BasicNoteValue& right) noexcept
{
    return !(left > right);
}

constexpr Fraction calculateTupletAugmentation(const Tuplet tuplet) noexcept
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

constexpr NoteValue::NoteValue(const BasicNoteValue& base,
                               const Tuplet tuplet,
                               const std::size_t numDots) noexcept :
    base_ {base},
    tuplet_ {tuplet},
    numDots_ {numDots}
{
}

constexpr NoteValue::NoteValue(const BasicNoteValue& base, const std::size_t numDots) noexcept :
    NoteValue {base, duplet, numDots}
{
}

constexpr Fraction NoteValue::relativeValue() const noexcept
{
    return base_.relativeValue() * calculateTupletAugmentation(tuplet_)
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

static constexpr BasicNoteValue octupleWholeNote = 3;
static constexpr BasicNoteValue quadrupleWholeNote = 2;
static constexpr BasicNoteValue doubleWholeNote = 1;
static constexpr BasicNoteValue wholeNote = 0;
static constexpr BasicNoteValue halfNote = -1;
static constexpr BasicNoteValue quarterNote = -2;
static constexpr BasicNoteValue eighthNote = -3;
static constexpr BasicNoteValue sixteenthNote = -4;
static constexpr BasicNoteValue thirtySecondNote = -5;
static constexpr BasicNoteValue sixtyFourthNote = -6;
static constexpr BasicNoteValue oneHundredTwentyEighthNote = -7;
static constexpr BasicNoteValue twoHundredFiftySixthNote = -8;

static constexpr BasicNoteValue maxima = octupleWholeNote;
static constexpr BasicNoteValue longa = quadrupleWholeNote;
static constexpr BasicNoteValue breve = doubleWholeNote;
static constexpr BasicNoteValue semibreve = wholeNote;
static constexpr BasicNoteValue minim = halfNote;
static constexpr BasicNoteValue crotchet = quarterNote;
static constexpr BasicNoteValue quaver = eighthNote;
static constexpr BasicNoteValue semiquaver = sixteenthNote;
static constexpr BasicNoteValue demisemiquaver = thirtySecondNote;
static constexpr BasicNoteValue hemidemisemiquaver = sixtyFourthNote;
static constexpr BasicNoteValue semihemidemisemiquaver = oneHundredTwentyEighthNote;
static constexpr BasicNoteValue demisemihemidemisemiquaver = twoHundredFiftySixthNote;


}; // namespace Cbb
