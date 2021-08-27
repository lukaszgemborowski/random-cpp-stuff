#include "catch.hpp"
#include "integral_constant_literals.hpp"

using namespace stuff::literals;

TEST_CASE("Integral constant value", "[integral_constant_literals][int]")
{
    CHECK(static_cast<int>(42_ic) == 42);
    CHECK(static_cast<int>(-42_ic) == -42);
}