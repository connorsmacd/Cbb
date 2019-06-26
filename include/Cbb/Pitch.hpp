#pragma once

#include <Cbb/Midi.hpp>
#include <Cbb/Tuning.hpp>


namespace Cbb {


enum Letter { C = 0, D = 2, E = 4, F = 5, G = 7, A = 9, B = 11 };

enum Accidental { doubleFlat = -2, flat, natural, sharp, doubleSharp };


struct PitchClassLabel final {
    Letter letter = C;
    Accidental accidental = natural;

    constexpr PitchClassLabel() noexcept = default;
    constexpr PitchClassLabel(Letter initLetter, Accidental initAccidental = natural);
};

constexpr bool operator==(const PitchClassLabel& left, const PitchClassLabel& right) noexcept;
constexpr bool operator!=(const PitchClassLabel& left, const PitchClassLabel& right) noexcept;

constexpr int toPitchClass(const PitchClassLabel& label) noexcept;


struct PitchLabel final {
    Letter letter = C;
    Accidental accidental = natural;
    int octave = {};

    constexpr PitchLabel() noexcept = default;
    constexpr PitchLabel(Letter initLetter, Accidental initAccidental, int initOctave) noexcept;
    constexpr PitchLabel(Letter initLetter, int initOctave) noexcept;
    constexpr PitchLabel(const PitchClassLabel& label, int initOctave) noexcept;

    constexpr operator PitchClassLabel() const noexcept { return {letter, accidental}; }
};

constexpr bool operator==(const PitchLabel& left, const PitchLabel& right) noexcept;
constexpr bool operator!=(const PitchLabel& left, const PitchLabel& right) noexcept;


class Pitch final {

public:
    constexpr Pitch() noexcept = default;
    constexpr Pitch(int cLass, int octave) noexcept;
    constexpr Pitch(const PitchLabel& label) noexcept;
    constexpr Pitch(Midi::NoteNumber number) noexcept;
    Pitch(double frequencyHz, Tuning tuning = A440) noexcept;

    constexpr Pitch& transposeSemitones(int semitones) noexcept;
    constexpr Pitch& transposeOctaves(int octaves) noexcept;

    constexpr int getClass() const noexcept { return class_; }
    constexpr int getOctave() const noexcept { return octave_; }
    constexpr Midi::NoteNumber getNoteNumber() const noexcept;
    double getFrequencyHz(Tuning tuning = A440) const noexcept;

    friend constexpr bool operator==(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator!=(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator<(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator<=(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator>(const Pitch& left, const Pitch& right) noexcept;
    friend constexpr bool operator>=(const Pitch& left, const Pitch& right) noexcept;

private:
    int class_ = {}, octave_ = {};
};

constexpr Pitch transposedSemitones(const Pitch& original, int semitones) noexcept;
constexpr Pitch transposedOctaves(const Pitch& original, int octaves) noexcept;


// =================================================================================================


constexpr PitchClassLabel::PitchClassLabel(const Letter initLetter,
                                           const Accidental initAccidental) :
    letter {initLetter},
    accidental {initAccidental}
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

    return (remainder >= 0) ? remainder : remainder + 12;
}

constexpr PitchLabel::PitchLabel(const Letter initLetter,
                                 const Accidental initAccidental,
                                 const int initOctave) noexcept :
    letter {initLetter},
    accidental {initAccidental},
    octave {initOctave}
{
}

constexpr PitchLabel::PitchLabel(const Letter initLetter, const int initOctave) noexcept :
    PitchLabel {initLetter, natural, initOctave}
{
}

constexpr PitchLabel::PitchLabel(const PitchClassLabel& label, int initOctave) noexcept :
    PitchLabel {label.letter, label.accidental, initOctave}
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

constexpr Pitch::Pitch(const int cLass, const int octave) noexcept :
    class_ {cLass},
    octave_ {octave}
{
}

constexpr Pitch::Pitch(const PitchLabel& label) noexcept :
    Pitch {toPitchClass(label), label.octave}
{
}

constexpr Pitch::Pitch(const Midi::NoteNumber number) noexcept :
    class_ {number % 12},
    octave_ {number / 12 - 1}
{
}

constexpr Pitch& Pitch::transposeSemitones(const int semitones) noexcept
{
    class_ += semitones % 12;

    if (class_ >= 12 )
    {
        class_ -= 12;
        transposeOctaves(1);
    }
    else if (class_ < 0)
    {
        class_ += 12;
        transposeOctaves(-1);
    }

    return transposeOctaves(semitones / 12);
}

constexpr Pitch& Pitch::transposeOctaves(const int octaves) noexcept
{
    octave_ += octaves;
    return *this;
}

constexpr Midi::NoteNumber Pitch::getNoteNumber() const noexcept
{
    return Midi::NoteNumber(class_ + (octave_ + 1) * 12);
}

constexpr bool operator==(const Pitch& left, const Pitch& right) noexcept
{
    return left.class_ == right.class_ && left.octave_ == right.octave_;
}

constexpr bool operator!=(const Pitch& left, const Pitch& right) noexcept
{
    return !(left == right);
}

constexpr bool operator<(const Pitch& left, const Pitch& right) noexcept
{
    return (left.octave_ != right.octave_) ? left.octave_ < right.octave_
                                           : left.class_ < right.class_;
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

constexpr Pitch transposedSemitones(const Pitch& original, const int semitones) noexcept
{
    return Pitch(original).transposeSemitones(semitones);
}

constexpr Pitch transposedOctaves(const Pitch& original, const int octaves) noexcept
{
    return Pitch(original).transposeOctaves(octaves);
}


}; // namespace Cbb
