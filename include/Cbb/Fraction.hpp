#pragma once

#include <istream>
#include <numeric>
#include <ostream>


namespace Cbb {


    class Fraction final {

    public:
        constexpr Fraction() = default;
        constexpr Fraction (long long numerator, long long denominator = 1) noexcept;

        constexpr long long num() const noexcept { return n; }
        constexpr long long den() const noexcept { return d; }
        constexpr long long numerator() const noexcept { return num(); }
        constexpr long long denominator() const noexcept { return den(); }

        friend std::ostream& operator<< (std::ostream& stream, const Fraction& fraction) noexcept;
        friend std::istream& operator>> (std::istream& stream, Fraction& fraction) noexcept;
 
    private:
        long long n = {},
                  d = {};
    };

    constexpr Fraction operator+ (const Fraction& fraction) noexcept;
    constexpr Fraction operator- (const Fraction& fraction) noexcept;

    constexpr Fraction operator+ (const Fraction& augend, const Fraction& addend) noexcept;
    constexpr Fraction operator- (const Fraction& minuend, const Fraction& subtrahend) noexcept;
    constexpr Fraction operator* (const Fraction& multiplicand, const Fraction& multiplier) noexcept;
    constexpr Fraction operator/ (const Fraction& dividend, const Fraction& divisor) noexcept;

    constexpr bool operator== (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool operator!= (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool operator<  (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool operator<= (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool operator>  (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool operator>= (const Fraction& left, const Fraction& right) noexcept;

    constexpr bool symbollicallyEqual (const Fraction& left, const Fraction& right) noexcept;
    constexpr bool notSymbollicallyEqual (const Fraction& left, const Fraction& right) noexcept;

    constexpr long long num (const Fraction& fraction) noexcept;
    constexpr long long den (const Fraction& fraction) noexcept;
    constexpr long long numerator (const Fraction& fraction) noexcept;
    constexpr long long denominator (const Fraction& fraction) noexcept;

    constexpr Fraction reduce (const Fraction& fraction) noexcept;
    constexpr Fraction reciprocal (const Fraction& fraction) noexcept;
    constexpr float decimal (const Fraction& fraction) noexcept;

    constexpr bool isPositive (const Fraction& fraction) noexcept;
    constexpr bool isNegative (const Fraction& fraction) noexcept;
    constexpr bool isInteger (const Fraction& fraction) noexcept;
    constexpr bool isUndefined (const Fraction& fraction) noexcept;


    // ============================== Template and inline definitions ==============================


    constexpr Fraction::Fraction (const long long numerator, const long long denominator) noexcept
    {
        if (numerator > 0 || denominator > 0)
        {
            n = numerator;
            d = denominator;
        }
        else
        {
            n = -numerator;
            d = -denominator;
        }
    }

    constexpr Fraction operator+ (const Fraction& fraction) noexcept
    {
        return fraction;
    }

    constexpr Fraction operator- (const Fraction& fraction) noexcept
    {
        return {-fraction.num(), fraction.den()};
    }

    constexpr Fraction operator+ (const Fraction& augend, const Fraction& addend) noexcept
    {
        const auto lcm = std::lcm(augend.den(), addend.den());

        return {augend.num() * (lcm / augend.den()) + addend.num() * (lcm / addend.den()), lcm};
    }

    constexpr Fraction operator- (const Fraction& minuend, const Fraction& subtrahend) noexcept
    {
        return minuend + -subtrahend;
    }

    constexpr Fraction operator* (const Fraction& multiplicand, const Fraction& multiplier) noexcept
    {
        return {multiplicand.num() * multiplier.num(), multiplicand.den() * multiplier.den()};
    }

    constexpr Fraction operator/ (const Fraction& dividend, const Fraction& divisor) noexcept
    {
        return dividend * reciprocal(divisor);
    }

    constexpr bool operator== (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return decimal(left) == decimal(right);
    }

    constexpr bool operator!= (const Fraction& left, const Fraction& right) noexcept
    {
        return ! (left == right);
    }

    constexpr bool operator< (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return decimal(left) < decimal(right);
    }

    constexpr bool operator<= (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return decimal(left) <= decimal(right);
    }

    constexpr bool operator> (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return decimal(left) > decimal(right);
    }

    constexpr bool operator>= (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return decimal(left) >= decimal(right);
    }

    constexpr bool symbollicallyEqual (const Fraction& left, const Fraction& right) noexcept
    {
        return left.num() == right.num() && left.den() == right.den();
    }

    constexpr bool notSymbollicallyEqual (const Fraction& left, const Fraction& right) noexcept
    {
        return ! symbollicallyEqual(left, right);
    }

    constexpr long long num (const Fraction& fraction) noexcept
    {
        return fraction.num();
    }

    constexpr long long den (const Fraction& fraction) noexcept
    {
        return fraction.den();
    }

    constexpr long long numerator (const Fraction& fraction) noexcept
    {
        return num(fraction);
    }

    constexpr long long denominator (const Fraction& fraction) noexcept
    {
        return den(fraction);
    }

    constexpr Fraction reduce (const Fraction& fraction) noexcept
    {
        const auto gcd = std::gcd(fraction.num(), fraction.den());

        return {fraction.num() / gcd, fraction.den() / gcd};
    }

    constexpr Fraction reciprocal (const Fraction& fraction) noexcept
    {
        return {fraction.den(), fraction.num()};
    }

    constexpr float decimal (const Fraction& fraction) noexcept
    {
        return float(fraction.num()) / float(fraction.den());
    }

    constexpr bool isPositive (const Fraction& fraction) noexcept
    {
        return fraction.num() > 0 && fraction.den() > 0;
    }

    constexpr bool isNegative (const Fraction& fraction) noexcept
    {
        return fraction.num() < 0 || fraction.den() < 0;
    }

    constexpr bool isInteger (const Fraction& fraction) noexcept
    {
        return 0 == fraction.num() % fraction.den();
    }

    constexpr bool isUndefined (const Fraction& fraction) noexcept
    {
        return 0 == fraction.den();
    }


}; // namespace Cbb
