#pragma once

#include <Cbb/Fraction.hpp>

#include <climits>
#include <cmath>
#include <stdexcept>
#include <vector>


namespace Cbb {


enum NoteValueBase {
    undefinedNoteValueBase,
    octupleWholeNote,
    quadrupleWholeNote,
    doubleWholeNote,
    wholeNote,
    halfNote,
    quarterNote,
    eighthNote,
    sixteenthNote,
    thirtySecondNote,
    sixtyFourthNote,
    oneHundredTwentyEighthNote,
    twoHundredFiftySixthNote,
    maxima = octupleWholeNote,
    longa = quadrupleWholeNote,
    breve = doubleWholeNote,
    semibreve = wholeNote,
    minim = halfNote,
    crotchet = quarterNote,
    quaver = eighthNote,
    semiquaver = sixteenthNote,
    demisemiquaver = thirtySecondNote,
    hemidemisemiquaver = sixtyFourthNote,
    semihemidemisemiquaver = oneHundredTwentyEighthNote,
    demisemihemidemisemiquaver = twoHundredFiftySixthNote,
};

enum Tuplet {
    undefinedTuplet,
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

class NoteValue final {

public:
    using Base = NoteValueBase;

    static constexpr std::size_t maxNumDots = sizeof(long long) * CHAR_BIT - 1;

    constexpr NoteValue() noexcept = default;
    constexpr NoteValue(Base base, Tuplet tuplet = duplet, std::size_t numDots = 0) noexcept;
    constexpr NoteValue(Base base, std::size_t numDots) noexcept;

    constexpr Base getBase() const noexcept { return b; }
    constexpr Tuplet getTuplet() const noexcept { return t; }
    constexpr std::size_t getNumDots() const noexcept { return d; }

    constexpr Fraction relativeValue() const noexcept;

    friend constexpr bool symbolicallyEqual(const NoteValue& left, const NoteValue& right) noexcept;
    friend constexpr bool notSymbolicallyEqual(const NoteValue& left,
                                               const NoteValue& right) noexcept;

private:
    Base b = wholeNote;
    Tuplet t = duplet;
    std::size_t d = 0;
};

// These compare based on relative value. It is possible for note values to have equivalent
// relative value, but different symbolic representation, e.g., quarter note triplet and half
// note sextuplet. For symbolic comparisons, use symbolicallyEqual() and notSymbolicallyEqual().
constexpr bool operator==(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator!=(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator<(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator<=(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator>(const NoteValue& left, const NoteValue& right) noexcept;
constexpr bool operator>=(const NoteValue& left, const NoteValue& right) noexcept;

constexpr Fraction relativeValue(NoteValueBase base) noexcept;
constexpr Fraction calculateTupletAugmentation(Tuplet tuplet) noexcept;
constexpr Fraction calculateDotAugmentation(std::size_t numDots) noexcept;
constexpr Fraction relativeValue(const NoteValue& noteValue) noexcept;

constexpr bool isDefined(const NoteValue& value) noexcept;
constexpr bool isUndefined(const NoteValue& value) noexcept;


// ================================ Template and inline definitions ================================


constexpr NoteValue::NoteValue(const Base base,
                               const Tuplet tuplet,
                               const std::size_t numDots) noexcept :
    b {base},
    t {tuplet},
    d {numDots}
{
}

constexpr NoteValue::NoteValue(const Base base, const std::size_t numDots) noexcept :
    NoteValue {base, duplet, numDots}
{
}

constexpr Fraction NoteValue::relativeValue() const noexcept
{
    return ::Cbb::relativeValue(b) * calculateTupletAugmentation(t) * calculateDotAugmentation(d);
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

constexpr bool symbolicallyEqual(const NoteValue& left, const NoteValue& right) noexcept
{
    return left.b == right.b && left.t == right.t && left.d == left.d;
}

constexpr bool notSymbolicallyEqual(const NoteValue& left, const NoteValue& right) noexcept
{
    return !symbolicallyEqual(left, right);
}

constexpr Fraction relativeValue(const NoteValueBase base) noexcept
{
    switch (base)
    {
        case undefinedNoteValueBase:
            return {0, 0};
        case octupleWholeNote:
            return 8;
        case quadrupleWholeNote:
            return 4;
        case doubleWholeNote:
            return 2;
        case wholeNote:
            return 1;
        case halfNote:
            return {1, 2};
        case quarterNote:
            return {1, 4};
        case eighthNote:
            return {1, 8};
        case sixteenthNote:
            return {1, 16};
        case thirtySecondNote:
            return {1, 32};
        case sixtyFourthNote:
            return {1, 64};
        case oneHundredTwentyEighthNote:
            return {1, 128};
        case twoHundredFiftySixthNote:
            return {1, 256};
    }

    return {0, 0};
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

    const auto twoToThePowerOfNumDots = static_cast<long long>(1ULL << numDots);

    return 2 - Fraction(1, twoToThePowerOfNumDots);
}

constexpr Fraction relativeValue(const NoteValue& noteValue) noexcept
{
    return noteValue.relativeValue();
}

constexpr bool isDefined(const NoteValue& value) noexcept
{
    return isDefined(relativeValue(value));
}

constexpr bool isUndefined(const NoteValue& value) noexcept
{
    return !isDefined(value);
}


}; // namespace Cbb
