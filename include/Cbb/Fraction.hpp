#pragma once

#include <istream>
#include <numeric>
#include <ostream>
#include <utility>


namespace Cbb {


    class Fraction final {

    public:
        constexpr Fraction() = default;
        constexpr Fraction (long long numerator, long long denominator = 1) noexcept;

        constexpr long long num() const noexcept { return n; }
        constexpr long long den() const noexcept { return d; }
        constexpr long long numerator() const noexcept { return num(); }
        constexpr long long denominator() const noexcept { return den(); }

        constexpr Fraction withNumerator (long long numerator) const noexcept;
        constexpr Fraction withDenominator (long long denominator) const noexcept;
        constexpr Fraction withSwitchedSignPosition() const noexcept;
        constexpr Fraction withMinimalNegativeSigns() const noexcept;

        friend std::ostream& operator<< (std::ostream& stream, const Fraction& fraction) noexcept;
        friend std::istream& operator>> (std::istream& stream, Fraction& fraction) noexcept;
 
    private:
        long long n = {},
                  d = 1;
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
    constexpr long double decimal (const Fraction& fraction) noexcept;

    constexpr unsigned int numNegativeSigns (const Fraction& fraction) noexcept;

    constexpr bool isPositive (const Fraction& fraction) noexcept;
    constexpr bool isNegative (const Fraction& fraction) noexcept;
    constexpr bool isZero (const Fraction& fraction) noexcept;
    constexpr bool isInteger (const Fraction& fraction) noexcept;
    constexpr bool isDefined (const Fraction& fraction) noexcept;
    constexpr bool isUndefined (const Fraction& fraction) noexcept;


    // ============================== Template and inline definitions ==============================


    constexpr Fraction::Fraction (const long long numerator, const long long denominator) noexcept
        : n {numerator},
          d {denominator}
    {
    }

    constexpr Fraction Fraction::withNumerator (const long long numerator) const noexcept
    {
        return {numerator, d};
    }

    constexpr Fraction Fraction::withDenominator (const long long denominator) const noexcept
    {
        return {n, denominator};
    }

    constexpr Fraction Fraction::withSwitchedSignPosition() const noexcept
    {
        if (isPositive(*this))
            return *this;
        
        return {-n, -d};
    }

    constexpr Fraction Fraction::withMinimalNegativeSigns() const noexcept
    {
        if (numNegativeSigns(*this) < 2)
            return *this;
        
        return {-n, -d};
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
        if (augend.den() == addend.den())
            return {augend.num() + addend.num(), augend.den()};
        
        return {augend.num() * addend.den() + addend.num() * augend.den(),
                augend.den() * addend.den()};
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

        return left.num() * right.den() == right.num() * left.den();
    }

    constexpr bool operator!= (const Fraction& left, const Fraction& right) noexcept
    {
        return ! (left == right);
    }

    constexpr bool operator< (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return left.num() * right.den() < right.num() * left.den();
    }

    constexpr bool operator<= (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return left.num() * right.den() <= right.num() * left.den();
    }

    constexpr bool operator> (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return left.num() * right.den() > right.num() * left.den();
    }

    constexpr bool operator>= (const Fraction& left, const Fraction& right) noexcept
    {
        if (isUndefined(left) || isUndefined(right))
            return false;

        return left.num() * right.den() >= right.num() * left.den();
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

        return Fraction(fraction.num() / gcd, fraction.den() / gcd).withMinimalNegativeSigns();
    }

    constexpr Fraction reciprocal (const Fraction& fraction) noexcept
    {
        return {fraction.den(), fraction.num()};
    }

    constexpr long double decimal (const Fraction& fraction) noexcept
    {
        return static_cast<long double>(fraction.num()) / static_cast<long double>(fraction.den());
    }

    constexpr unsigned int numNegativeSigns (const Fraction& fraction) noexcept
    {
        return ((fraction.num() < 0) ? 1 : 0) + ((fraction.den() < 0) ? 1 : 0);
    }

    constexpr bool isPositive (const Fraction& fraction) noexcept
    {
        return (fraction.num() > 0 && fraction.den() > 0)
               || (fraction.num() < 0 && fraction.den() < 0);
    }

    constexpr bool isNegative (const Fraction& fraction) noexcept
    {
        return (fraction.num() > 0 && fraction.den() < 0)
               || (fraction.num() < 0 && fraction.den() > 0);
    }

    constexpr bool isZero (const Fraction& fraction) noexcept
    {
        return 0 == fraction.num() && isDefined(fraction);
    }

    constexpr bool isInteger (const Fraction& fraction) noexcept
    {
        return 0 == fraction.num() % fraction.den();
    }

    constexpr bool isDefined (const Fraction& fraction) noexcept
    {
        return 0 != fraction.den();
    }

    constexpr bool isUndefined (const Fraction& fraction) noexcept
    {
        return ! isDefined(fraction);
    }


}; // namespace Cbb
