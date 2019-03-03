#include <Cbb/Pitch.hpp>

#include <Cbb/Midi.hpp>


namespace Cbb {


Pitch::Pitch(const float frequencyHz, const Tuning tuning) noexcept :
    Pitch{Midi::frequencyHzToNoteNumber(frequencyHz, tuning)}
{
}

float Pitch::getFrequencyHz(const Tuning tuning) const noexcept
{
    return Midi::noteNumberToFrequencyHz(getNoteNumber(), tuning);
}


}; // namespace Cbb
