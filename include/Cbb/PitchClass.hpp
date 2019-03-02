#pragma once

#include <string>


namespace Cbb {


enum Letter { C = 0, D = 2, E = 4, F = 5, G = 7, A = 9, B = 11 };

enum Accidental { doubleFlat = -2, flat, natural, sharp, doubleSharp };

struct PitchClassLabel final {
    Letter letter = C;
    Accidental accidental = natural;

    constexpr PitchClassLabel() = default;
    constexpr PitchClassLabel(Letter l, Accidental a = natural);
};

constexpr bool operator==(const PitchClassLabel& left, const PitchClassLabel& right) noexcept;
constexpr bool operator!=(const PitchClassLabel& left, const PitchClassLabel& right) noexcept;

constexpr int toPitchClass(const PitchClassLabel& label) noexcept;


// ================================ Template and inline definitions ================================


constexpr PitchClassLabel::PitchClassLabel(const Letter l, const Accidental a) :
    letter{l},
    accidental{a}
{
}

constexpr bool operator==(const PitchClassLabel& left, const PitchClassLabel& right) noexcept
{
    return left.letter == right.letter && left.accidental == right.accidental;
}

constexpr bool operator!=(const PitchClassLabel& left, const PitchClassLabel& right) noexcept
{
    return !(left == right);
}

constexpr int toPitchClass(const PitchClassLabel& label) noexcept
{
    const auto remainder = (label.letter + label.accidental) % 12;

    if (remainder < 0)
        return remainder + 12;

    return remainder;
}


}; // namespace Cbb
