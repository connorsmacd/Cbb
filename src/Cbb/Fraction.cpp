#include <Cbb/Fraction.hpp>

#include <limits>


namespace Cbb {


std::ostream& operator<<(std::ostream& stream, const Fraction& fraction) noexcept
{
    stream << fraction.n << '/' << fraction.d;
    return stream;
}

std::istream& operator>>(std::istream& stream, Fraction& fraction) noexcept
{
    stream >> fraction.n;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    stream >> fraction.d;

    return stream;
}


}; // namespace Cbb
