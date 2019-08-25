#include <Cbb/Metre.hpp>

#include <algorithm>


namespace Cbb {


MetricStructure::MetricStructure(const TimeSignature& defaultTimeSignature,
                                 const TempoBpm& defaultBpm) :
    defaultTimeSignature_ {defaultTimeSignature},
    defaultBpm_ {defaultBpm},
    timeSignatureChanges_ {{0, defaultTimeSignature}},
    bpmChanges_ {{0, defaultBpm}}
{
}

void MetricStructure::addTimeSignatureChange(const BarNumber bar,
                                             const TimeSignature& timeSignature)
{
    timeSignatureChanges_[bar] = timeSignature;
}

void MetricStructure::addBpmChange(const MetricPosition& position, const TempoBpm& bpm)
{
    bpmChanges_[position] = bpm;
}

bool MetricStructure::eraseTimeSignatureChangeAt(const BarNumber bar)
{
    if (bar <= 0)
        return false;

    const auto found = timeSignatureChanges_.find(bar);

    if (found == timeSignatureChanges_.end())
        return false;

    timeSignatureChanges_.erase(found);

    return true;
}

bool MetricStructure::eraseBpmChangeAt(const MetricPosition& position)
{
    if (position <= 0)
        return false;

    const auto found = bpmChanges_.find(position);

    if (found == bpmChanges_.end())
        return false;

    bpmChanges_.erase(found);

    return true;
}

std::vector<std::pair<BarNumber, TimeSignature>> MetricStructure::timeSignatureChanges() const
{
    return std::vector<std::pair<BarNumber, TimeSignature>>(timeSignatureChanges_.rbegin(),
                                                            timeSignatureChanges_.rend());
}

std::vector<std::pair<MetricPosition, TempoBpm>> MetricStructure::bpmChanges() const
{
    return std::vector<std::pair<MetricPosition, TempoBpm>>(bpmChanges_.rbegin(),
                                                            bpmChanges_.rend());
}

std::pair<BarNumber, TimeSignature>
MetricStructure::lastestTimeSignatureChange(const MetricPosition& position) const
{
    return *timeSignatureChanges_.lower_bound(position.bar);
}

std::pair<MetricPosition, TempoBpm>
MetricStructure::lastestBpmChange(const MetricPosition& position) const
{
    return *bpmChanges_.lower_bound(position);
}


}; // namespace Cbb
