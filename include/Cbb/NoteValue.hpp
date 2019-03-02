#pragma once

#include <Cbb/Fraction.hpp>

#include <cmath>
#include <stdexcept>


namespace Cbb {


enum NoteValueBase {
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

    constexpr NoteValue() = default;
    constexpr NoteValue(Base base, Tuplet tuplet = duplet, unsigned int numDots = 0) noexcept;
    constexpr NoteValue(Base base, unsigned int numDots) noexcept;

    constexpr Base getBase() const noexcept { return b; }
    constexpr Tuplet getTuplet() const noexcept { return t; }
    constexpr unsigned int getNumDots() const noexcept { return d; }

    friend constexpr bool symbolicallyEqual(const NoteValue& left, const NoteValue& right) noexcept;
    friend constexpr bool notSymbolicallyEqual(const NoteValue& left,
                                               const NoteValue& right) noexcept;

    friend constexpr Fraction relativeValue(const NoteValue& base) noexcept;

private:
    Base b = wholeNote;
    Tuplet t = duplet;
    unsigned int d = 0;
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
constexpr Fraction calculateDotAugmentation(unsigned int numDots) noexcept;


// ================================ Template and inline definitions ================================


constexpr NoteValue::NoteValue(const Base base,
                               const Tuplet tuplet,
                               const unsigned int numDots) noexcept :
    b{base},
    t{tuplet},
    d{numDots}
{
}

constexpr NoteValue::NoteValue(const Base base, const unsigned int numDots) noexcept :
    NoteValue{base, duplet, numDots}
{
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

constexpr Fraction relativeValue(const NoteValue::Base base) noexcept
{
    switch (base)
    {
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
    return {2, tuplet};
}

constexpr Fraction calculateDotAugmentation(const unsigned int numDots) noexcept
{
    const auto twoToThePowerOfNumDots = static_cast<long long>(1ULL << numDots);

    return 2 - Fraction(1, twoToThePowerOfNumDots);
}

constexpr Fraction relativeValue(const NoteValue& noteValue) noexcept
{
    return relativeValue(noteValue.b) * calculateTupletAugmentation(noteValue.t)
           * calculateDotAugmentation(noteValue.d);
}


}; // namespace Cbb
