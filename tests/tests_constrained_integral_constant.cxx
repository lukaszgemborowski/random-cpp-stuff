#include "constrained_integral_constant.hpp"
#include "integral_constant_literals.hpp"
#include "catch.hpp"

using DayInt = stuff::ranged_integral_constant<int, 1, 31>;

static_assert(DayInt::validate(DayInt::make<1>) == true);
static_assert(DayInt::validate(DayInt::make<15>) == true);
static_assert(DayInt::validate(DayInt::make<31>) == true);

static_assert(DayInt::validate(DayInt::make<0>) == false);
static_assert(DayInt::validate(DayInt::make<32>) == false);

TEST_CASE("Range constrained int construction", "[constrained_integral_constant][range_constrain]")
{
    auto func = [](DayInt) {};

    REQUIRE_NOTHROW(func(DayInt::make<10>));
    // won't compile: REQUIRE_NOTHROW(func(DayInt::make<32>));

    REQUIRE_NOTHROW(func(10));
    REQUIRE_THROWS(func(0));
    REQUIRE_THROWS(func(32));
}

TEST_CASE("Range constrained int with literal", "[constrained_integral_constant][literals]")
{
    using namespace stuff::literals;
    DayInt{10_ic};
    //  won't compile: DayInt{32_ic};
}

TEST_CASE("Set constrained int construction", "[constrained_integral_constant][set_constrain]")
{
    using namespace stuff::literals;
    using SetOfValues = stuff::set_integral_constant<int, 1, 3, 5>;

    SetOfValues{1_ic};
    SetOfValues{3_ic};
    SetOfValues{5_ic};

    // won't compile: SetOfValues{10_ic};
}