#include "Common.h"

#include <algorithm>

namespace Common
{

namespace Math
{
    template <typename T>
    T clamp(const T& n, const T& lower, const T& upper) {
      return std::max(lower, std::min(n, upper));
    }
} // Math
} // Common
