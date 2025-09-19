#include "../headers/Patterns.h"

namespace patterns
{
bool SamePricesInRow(const std::deque<double>& data, const size_t n)
{
    size_t size = data.size();
    if (size < 2 or n < 2)
    {
        return false;
    }

    const double last = data.back();
    return std::all_of(data.end() - n, data.end(), [&](double value) { return value == last; });
}
} // namespace patterns