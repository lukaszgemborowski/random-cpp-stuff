#include "catch.hpp"
#include "validate_call.hpp"
#include "constrained_integral_constant.hpp"

namespace {

using MonthInt = stuff::ranged_integral_constant<int, 1, 12>;
using DayInt = stuff::ranged_integral_constant<int, 1, 31>;

struct MyString {
    MyString(std::string init)
        : value {std::move(init)}
    {}

    static auto validate(std::string const& value) {
        return value.length() < 5;
    }

    std::string value;
};

void foo(char*, DayInt, MonthInt) {}
void bar(DayInt, MyString) {}

}

TEST_CASE("Validate all", "[validate_call]")
{
    using namespace stuff::literals;
    CHECK(stuff::validate_call_arguments(foo, "asd", 10_ic, 11));
    CHECK(stuff::validate_call_arguments(foo, "asd", 10_ic, 12));

    // 13 is not a valid month
    CHECK(stuff::validate_call_arguments(foo, "asd", 10_ic, 13) == false);

    // all OK
    CHECK(stuff::validate_call_arguments(bar, 20, "1234") == true);

    // string is too long
    CHECK(stuff::validate_call_arguments(bar, 20, "12345") == false);

    // day > 35
    CHECK(stuff::validate_call_arguments(bar, 35, "1234") == false);
}