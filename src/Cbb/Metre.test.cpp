#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Cbb/Metre.hpp>

#include <sstream>


using namespace Cbb;


TEST_CASE("A time signature can be default-constructed")
{
    constexpr auto ts = TimeSignature();

    REQUIRE(ts.top() == 0);
    REQUIRE(ts.bottom() == 0);
}

TEST_CASE("A time signature can be constructed with a top & bottom")
{
    constexpr auto ts = TimeSignature(2, 9);

    REQUIRE(ts.top() == 2);
    REQUIRE(ts.bottom() == 9);
}

TEST_CASE("The beat unit of a time signature can be retrieved")
{
    constexpr auto ts = TimeSignature(7, 8);

    REQUIRE(ts.beatUnit() == eighthNote);
}

TEST_CASE("Time signatures with identical tops and bottoms are equal")
{
    SECTION("Identical time signatures")
    {
        constexpr auto ts1 = TimeSignature(5, 4);
        constexpr auto ts2 = TimeSignature(5, 4);

        REQUIRE(ts1 == ts2);
        REQUIRE_FALSE(ts1 != ts2);
    }

    SECTION("Different time signatures")
    {
        constexpr auto ts1 = TimeSignature(5, 4);
        constexpr auto ts2 = TimeSignature(7, 9);

        REQUIRE_FALSE(ts1 == ts2);
        REQUIRE(ts1 != ts2);
    }
}

TEST_CASE("Metric positions with the same bar and beat are equal")
{
    SECTION("Identical metric positions")
    {
        constexpr auto mp1 = MetricPosition(4, Fraction(5, 7));
        constexpr auto mp2 = MetricPosition(4, Fraction(5, 7));

        REQUIRE(mp1 == mp2);
        REQUIRE_FALSE(mp1 != mp2);
    }

    SECTION("Different metric positions")
    {
        constexpr auto mp1 = MetricPosition(4, Fraction(5, 7));
        constexpr auto mp2 = MetricPosition(3, Fraction(6, 7));

        REQUIRE_FALSE(mp1 == mp2);
        REQUIRE(mp1 != mp2);
    }
}

TEST_CASE("A metric position is less than another metric position with a greater bar number")
{
    SECTION("Same bar numbers")
    {
        constexpr auto mp1 = MetricPosition(4);
        constexpr auto mp2 = MetricPosition(4);

        REQUIRE_FALSE(mp1 < mp2);
        REQUIRE(mp1 <= mp2);
        REQUIRE(mp1 >= mp2);
        REQUIRE_FALSE(mp1 > mp2);
    }

    SECTION("Different bar numbers")
    {
        constexpr auto mp1 = MetricPosition(4);
        constexpr auto mp2 = MetricPosition(5);

        REQUIRE(mp1 < mp2);
        REQUIRE(mp1 <= mp2);
        REQUIRE_FALSE(mp1 >= mp2);
        REQUIRE_FALSE(mp1 > mp2);
    }
}

TEST_CASE(
    "A metric position is less than another metric position with the same bar but greater beat")
{
    SECTION("Same bar numbers and beats")
    {
        constexpr auto mp1 = MetricPosition(4, Fraction(11, 29));
        constexpr auto mp2 = MetricPosition(4, Fraction(11, 29));

        REQUIRE_FALSE(mp1 < mp2);
        REQUIRE(mp1 <= mp2);
        REQUIRE(mp1 >= mp2);
        REQUIRE_FALSE(mp1 > mp2);
    }

    SECTION("Different bar numbers")
    {
        constexpr auto mp1 = MetricPosition(4, Fraction(11, 29));
        constexpr auto mp2 = MetricPosition(4, Fraction(12, 29));

        REQUIRE(mp1 < mp2);
        REQUIRE(mp1 <= mp2);
        REQUIRE_FALSE(mp1 >= mp2);
        REQUIRE_FALSE(mp1 > mp2);
    }
}

SCENARIO("Time signatures can be added and removed from metric structures")
{
    GIVEN("a metric structure with a default time signature of 4/4")
    {
        auto metricStructure = MetricStructure(TimeSignature(4, 4), 120);

        THEN("there is a single time signature change to 4/4 at bar 0")
        {
            const auto timeSigChanges = metricStructure.timeSignatureChanges();

            REQUIRE(timeSigChanges.size() == 1);
            REQUIRE(timeSigChanges[0].first == 0);
            REQUIRE(timeSigChanges[0].second == TimeSignature(4, 4));
        }

        WHEN("a time signature change to 7/4 is added at bar 12")
        {
            metricStructure.addTimeSignatureChange(12, TimeSignature(3, 4));

            THEN("there are time signature changes of 4/4 at bar 0 and 3/4 at bar 12")
            {
                const auto timeSigChanges = metricStructure.timeSignatureChanges();

                REQUIRE(timeSigChanges.size() == 2);
                REQUIRE(timeSigChanges[0].first == 0);
                REQUIRE(timeSigChanges[0].second == TimeSignature(4, 4));
                REQUIRE(timeSigChanges[1].first == 12);
                REQUIRE(timeSigChanges[1].second == TimeSignature(3, 4));
            }

            AND_WHEN("a time signature change is erased at bar 12")
            {
                const auto ok = metricStructure.eraseTimeSignatureChangeAt(12);

                THEN("the operation succeeds") { REQUIRE(ok); }
                AND_THEN("there is a single time signature change to 4/4 at bar 0")
                {
                    const auto timeSigChanges = metricStructure.timeSignatureChanges();

                    REQUIRE(timeSigChanges.size() == 1);
                    REQUIRE(timeSigChanges[0].first == 0);
                    REQUIRE(timeSigChanges[0].second == TimeSignature(4, 4));
                }
            }
        }

        WHEN("a time signature change is erased at bar 11 where there is no time signature change")
        {
            const auto ok = metricStructure.eraseTimeSignatureChangeAt(11);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }

        WHEN("a time signature change is erased at bar 0 where the initial time signature is")
        {
            const auto ok = metricStructure.eraseTimeSignatureChangeAt(0);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }

        WHEN("a time signature change is erased at bar -5 which is invalid")
        {
            const auto ok = metricStructure.eraseTimeSignatureChangeAt(-5);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }
    }
}

SCENARIO("BPM changes can be added and removed from metric structures")
{
    GIVEN("a metric structure with a default BPM of 120")
    {
        auto metricStructure = MetricStructure(TimeSignature(4, 4), 120);

        THEN("there is a BPM change to 120 at 0.0")
        {
            const auto bpmChanges = metricStructure.bpmChanges();

            REQUIRE(bpmChanges.size() == 1);
            REQUIRE(bpmChanges[0].first == 0);
            REQUIRE(bpmChanges[0].second == 120);
        }

        WHEN("a BPM change to 150 1/2 is added at position 12 3/8")
        {
            metricStructure.addBpmChange({12, {3, 8}}, 150 + Fraction(1, 2));

            THEN("there are BPM changes of 120 at position 0 and 150 1/2 at positon 12 3/8")
            {
                const auto bpmChanges = metricStructure.bpmChanges();

                REQUIRE(bpmChanges.size() == 2);
                REQUIRE(bpmChanges[0].first == 0);
                REQUIRE(bpmChanges[0].second == 120);
                REQUIRE(bpmChanges[1].first == MetricPosition(12, {3, 8}));
                REQUIRE(bpmChanges[1].second == 150 + Fraction(1, 2));
            }

            AND_WHEN("a BPM change is erased at bar 12 3/8")
            {
                const auto ok = metricStructure.eraseBpmChangeAt({12, {3, 8}});

                THEN("the operation succeeds") { REQUIRE(ok); }
                AND_THEN("there is a single BPM change to 120 at position 0")
                {
                    const auto bpmChanges = metricStructure.bpmChanges();

                    REQUIRE(bpmChanges.size() == 1);
                    REQUIRE(bpmChanges[0].first == 0);
                    REQUIRE(bpmChanges[0].second == 120);
                }
            }
        }

        WHEN("a BPM change is erased at position 11 where there is no BPM change")
        {
            const auto ok = metricStructure.eraseBpmChangeAt(11);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }

        WHEN("a BPM change is erased at position 0 where the initial BPM change is")
        {
            const auto ok = metricStructure.eraseBpmChangeAt(0);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }

        WHEN("a BPM change is erased at position -5 which is invalid")
        {
            const auto ok = metricStructure.eraseBpmChangeAt(-5);

            THEN("the operation fails") { REQUIRE_FALSE(ok); }
        }
    }
}

SCENARIO("The time signature at any given position can be found")
{
    GIVEN("a metric structure with time signature changes to 4/4 at 0 and 7/8 at 13")
    {
        auto metricStructure = MetricStructure(TimeSignature(4, 4), 120);
        metricStructure.addTimeSignatureChange(13, TimeSignature(3, 4));

        THEN("the latest time signature for position 0 is 4/4 at 0")
        {
            const auto change = metricStructure.lastestTimeSignatureChange(0);

            REQUIRE(change.first == 0);
            REQUIRE(change.second == TimeSignature(4, 4));
        }
        AND_THEN("the latest time signature for 12 3/4 is 4/4 at 0")
        {
            const auto change = metricStructure.lastestTimeSignatureChange({12, {3, 4}});

            REQUIRE(change.first == 0);
            REQUIRE(change.second == TimeSignature(4, 4));
        }
        AND_THEN("the latest time signature for position 13 is 3/4 at 13")
        {
            const auto change = metricStructure.lastestTimeSignatureChange(13);

            REQUIRE(change.first == 13);
            REQUIRE(change.second == TimeSignature(3, 4));
        }
        AND_THEN("the latest time signature for 500 11/17 is 3/4 at 13")
        {
            const auto change = metricStructure.lastestTimeSignatureChange({500, {11, 17}});

            REQUIRE(change.first == 13);
            REQUIRE(change.second == TimeSignature(3, 4));
        }
    }
}

SCENARIO("The BPM at any given position can be found")
{
    GIVEN("a metric structure with BPM changes to 120 at 0 and 100 1/3 at 17 1/7")
    {
        auto metricStructure = MetricStructure(TimeSignature(4, 4), 120);
        metricStructure.addBpmChange({17, {1, 7}}, 100 + Fraction(1, 3));

        THEN("the latest BPM for position 0 is 120 at 0")
        {
            const auto change = metricStructure.lastestBpmChange(0);

            REQUIRE(change.first == 0);
            REQUIRE(change.second == 120);
        }
        AND_THEN("the latest BPM for position 17 1/14 is 120 at 0")
        {
            const auto change = metricStructure.lastestBpmChange({17, {1, 14}});

            REQUIRE(change.first == 0);
            REQUIRE(change.second == 120);
        }
        AND_THEN("the latest BPM for position 17 1/7 is 100 1/3 at 17 1/7")
        {
            const auto change = metricStructure.lastestBpmChange({17, {1, 7}});

            REQUIRE(change.first == MetricPosition(17, {1, 7}));
            REQUIRE(change.second == 100 + Fraction(1, 3));
        }
        AND_THEN("the latest BPM for position 500 11/17 is 100 1/3 at 17 1/7")
        {
            const auto change = metricStructure.lastestBpmChange({500, {11, 17}});

            REQUIRE(change.first == MetricPosition(17, {1, 7}));
            REQUIRE(change.second == 100 + Fraction(1, 3));
        }
    }
}
