#include <Cbb/Midi.hpp>

#include <cmath>


namespace Cbb {
namespace Midi {


NoteNumber frequencyHzToNoteNumber(const double frequencyHz, const Tuning tuning) noexcept
{
    return NoteNumber(A4
                      + int(std::roundf(12.0 * std::log2(frequencyHz / tuning.frequencyOfA4Hz))));
}

double noteNumberToFrequencyHz(const NoteNumber number, const Tuning tuning) noexcept
{
    return std::pow(2.0, double(number - A4) / 12.0) * tuning.frequencyOfA4Hz;
}


}; // namespace Midi
}; // namespace Cbb
