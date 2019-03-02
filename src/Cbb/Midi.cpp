#include <Cbb/Midi.hpp>

#include <cmath>


namespace Cbb {
namespace Midi {


NoteNumber frequencyHzToNoteNumber(const float frequencyHz, const Tuning tuning) noexcept
{
    return NoteNumber(A4 + int(roundf(12.0f * std::log2(frequencyHz / tuning.frequencyOfA4Hz))));
}

float noteNumberToFrequencyHz(const NoteNumber number, const Tuning tuning) noexcept
{
    return std::pow(2.0f, float(number - A4) / 12.0f) * tuning.frequencyOfA4Hz;
}


}; // namespace Midi
}; // namespace Cbb
