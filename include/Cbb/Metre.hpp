#pragma once

#include <Cbb/Fraction.hpp>
#include <Cbb/NoteValue.hpp>

#include <chrono>
#include <functional>
#include <map>
#include <vector>


namespace Cbb {


class TimeSignature final {

public:
    constexpr TimeSignature() noexcept = default;
    constexpr TimeSignature(int top, int bottom) noexcept;

    constexpr int top() const noexcept { return top_; }
    constexpr int bottom() const noexcept { return bottom_; }

    constexpr NoteValue beatUnit() const noexcept;

    friend constexpr bool operator==(const TimeSignature& left,
                                     const TimeSignature& right) noexcept;
    friend constexpr bool operator!=(const TimeSignature& left,
                                     const TimeSignature& right) noexcept;

private:
    int top_ = 0;
    int bottom_ = 0;
};


using BarNumber = long long;

struct MetricPosition final {
    BarNumber bar = 0;
    Fraction beat = 0;

    constexpr MetricPosition() noexcept = default;
    constexpr MetricPosition(BarNumber initBar, const Fraction& initBeat = 0) noexcept;
};

constexpr bool operator==(const MetricPosition& left, const MetricPosition& right) noexcept;
constexpr bool operator!=(const MetricPosition& left, const MetricPosition& right) noexcept;
constexpr bool operator<(const MetricPosition& left, const MetricPosition& right) noexcept;
constexpr bool operator<=(const MetricPosition& left, const MetricPosition& right) noexcept;
constexpr bool operator>(const MetricPosition& left, const MetricPosition& right) noexcept;
constexpr bool operator>=(const MetricPosition& left, const MetricPosition& right) noexcept;


using TempoBpm = Fraction;

class MetricStructure final {

public:
    MetricStructure(const TimeSignature& defaultTimeSignature, const TempoBpm& defaultBpm);

    void addTimeSignatureChange(BarNumber bar, const TimeSignature& timeSignature);

    void addBpmChange(const MetricPosition& position, const TempoBpm& bpm);

    bool eraseTimeSignatureChangeAt(BarNumber bar);

    bool eraseBpmChangeAt(const MetricPosition& position);

    std::vector<std::pair<BarNumber, TimeSignature>> timeSignatureChanges() const;

    std::vector<std::pair<MetricPosition, TempoBpm>> bpmChanges() const;

    std::pair<BarNumber, TimeSignature>
    lastestTimeSignatureChange(const MetricPosition& position) const;

    std::pair<MetricPosition, TempoBpm> lastestBpmChange(const MetricPosition& position) const;

private:
    TimeSignature defaultTimeSignature_;
    TempoBpm defaultBpm_;

    std::map<BarNumber, TimeSignature, std::greater<BarNumber>> timeSignatureChanges_;
    std::map<MetricPosition, TempoBpm, std::greater<MetricPosition>> bpmChanges_;
};


// =================================================================================================


constexpr TimeSignature::TimeSignature(const int top, const int bottom) noexcept :
    top_ {top},
    bottom_ {bottom}
{
}

constexpr NoteValue TimeSignature::beatUnit() const noexcept
{
    return UnitFraction(bottom_);
}

constexpr bool operator==(const TimeSignature& left, const TimeSignature& right) noexcept
{
    return left.top_ == right.top_ && left.bottom_ == right.bottom_;
}

constexpr bool operator!=(const TimeSignature& left, const TimeSignature& right) noexcept
{
    return !(left == right);
}

constexpr MetricPosition::MetricPosition(const BarNumber initBar,
                                         const Fraction& initBeat) noexcept :
    bar {initBar},
    beat {initBeat}
{
}

constexpr bool operator==(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return left.bar == right.bar && left.beat == right.beat;
}

constexpr bool operator!=(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return !(left == right);
}

constexpr bool operator<(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return (left.bar != right.bar) ? left.bar < right.bar : left.beat < right.beat;
}

constexpr bool operator<=(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return !(left > right);
}

constexpr bool operator>(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return right < left;
}

constexpr bool operator>=(const MetricPosition& left, const MetricPosition& right) noexcept
{
    return !(left < right);
}


}; // namespace Cbb
