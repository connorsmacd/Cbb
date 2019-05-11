#pragma once

#include <Cbb/Midi.hpp>
#include <Cbb/PitchClass.hpp>
#include <Cbb/Tuning.hpp>


namespace Cbb {


struct PitchLabel final {
    Letter letter = C;
    Accidental accidental = natural;
    int octave = {};

    constexpr PitchLabel() = default;
    constexpr PitchLabel(Letter l, Accidental a, int o) noexcept;
    constexpr PitchLabel(Letter l, int o) noexcept;
    constexpr PitchLabel(const PitchClassLabel& label, int o) noexcept;

    constexpr operator PitchClassLabel() const noexcept { return {letter, accidental}; }
};

constexpr bool operator==(const PitchLabel& left, const PitchLabel& right) noexcept;
constexpr bool operator!=(const PitchLabel& left, const PitchLabel& right) noexcept;

class Pitch final {

public:
    constexpr Pitch() = default;
    constexpr Pitch(int pitchClass, int octave) noexcept;
    constexpr Pitch(Letter letter, Accidental accidental, int octave) noexcept;
    constexpr Pitch(const PitchLabel& label) noexcept;
    constexpr Pitch(Midi::NoteNumber number) noexcept;
    Pitch(float frequencyHz, Tuning tuning = A440) noexcept;

    constexpr int getClass() const noexcept { return clas; }
    constexpr int getOctave() const noexcept { return oct; }
    constexpr Midi::NoteNumber getNoteNumber() const noexcept;
    float getFrequencyHz(Tuning tuning = A440) const noexcept;

    friend constexpr bool operator==(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator!=(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator<(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator<=(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator>(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator>=(const Pitch& left, const Pitch& right) noexcept;

private:
    int clas = {}, oct = {};
};


// ================================ Template and inline definitions ================================


constexpr PitchLabel::PitchLabel(const Letter l, const Accidental a, const int o) noexcept :
    letter {l},
    accidental {a},
    octave {o}
{
}

constexpr PitchLabel::PitchLabel(const Letter l, const int o) noexcept : PitchLabel {l, natural, o}
{
}

constexpr PitchLabel::PitchLabel(const PitchClassLabel& label, int o) noexcept :
    PitchLabel {label.letter, label.accidental, o}
{
}

constexpr bool operator==(const PitchLabel& left, const PitchLabel& right) noexcept
{
    return left.letter == right.letter && left.accidental == right.accidental
           && left.octave == right.octave;
}

constexpr bool operator!=(const PitchLabel& left, const PitchLabel& right) noexcept
{
    return !(left == right);
}

constexpr Pitch::Pitch(const int pitchClass, const int octave) noexcept :
    clas {pitchClass},
    oct {octave}
{
}

constexpr Pitch::Pitch(const Letter letter,
                       const Accidental accidental,
                       const int octave) noexcept :
    Pitch {toPitchClass({letter, accidental}), octave}
{
}

constexpr Pitch::Pitch(const PitchLabel& label) noexcept :
    Pitch {label.letter, label.accidental, label.octave}
{
}

constexpr Pitch::Pitch(const Midi::NoteNumber number) noexcept :
    clas {number % 12},
    oct {number / 12 - 1}
{
}

constexpr Midi::NoteNumber Pitch::getNoteNumber() const noexcept
{
    return Midi::NoteNumber(clas + (oct + 1) * 12);
}

constexpr bool operator==(const Pitch& left, const Pitch& right) noexcept
{
    return left.clas == right.clas && left.oct == right.oct;
}

constexpr bool operator!=(const Pitch& left, const Pitch& right) noexcept
{
    return !(left == right);
}

constexpr bool operator<(const Pitch& left, const Pitch& right) noexcept
{
    return (left.oct != right.oct) ? left.oct < right.oct : left.clas < right.clas;
}

constexpr bool operator<=(const Pitch& left, const Pitch& right) noexcept
{
    return !(left > right);
}

constexpr bool operator>(const Pitch& left, const Pitch& right) noexcept
{
    return right < left;
}

constexpr bool operator>=(const Pitch& left, const Pitch& right) noexcept
{
    return !(left < right);
}


}; // namespace Cbb
