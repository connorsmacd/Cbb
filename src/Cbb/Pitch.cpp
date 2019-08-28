#include <Cbb/Pitch.hpp>


namespace Cbb {


Pitch::Pitch(const double frequencyHz, const Tuning tuning) noexcept :
    Pitch {Midi::frequencyHzToNoteNumber(frequencyHz, tuning)}
{
}

double Pitch::frequencyHz(const Tuning tuning) const noexcept
{
    return Midi::noteNumberToFrequencyHz(noteNumber(), tuning);
}


}; // namespace Cbb
