#include "catch.hpp"
#include "function_traits.hpp"
#include "constrained_integral_constant.hpp"

namespace {

template<class FuncTrait, class... Args>
struct check_argument_types;

template<class R, class... FunArgs, class... ProvidedArgs>
struct check_argument_types<stuff::function_traits<R, FunArgs...>, ProvidedArgs...> {
    static constexpr auto result = (sizeof...(FunArgs) == sizeof...(ProvidedArgs));
};

template<class Dest, class Src>
auto validate_one(Src const& src) -> decltype(Dest::validate(src))
{
    return Dest::validate(src);
}

template<class Dest>
auto validate_one(...) -> bool { return true; }

template<class R, class... FuncArgs, class... Args>
bool validate_call(stuff::function_traits<R, FuncArgs...>, Args... args) {
    static_assert(check_argument_types<stuff::function_traits<R, FuncArgs...>, Args...>::result);

    return (validate_one<FuncArgs>(args) && ...);
}

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
    CHECK(validate_call(stuff::get_function_traits(foo), "asd", 10_ic, 11));
    CHECK(validate_call(stuff::get_function_traits(foo), "asd", 10_ic, 12));
    CHECK(validate_call(stuff::get_function_traits(foo), "asd", 10_ic, 13) == false);

    CHECK(validate_call(stuff::get_function_traits(bar), 20, "1234") == true);

    // string is too long
    CHECK(validate_call(stuff::get_function_traits(bar), 20, "12345") == false);

    // day > 35
    CHECK(validate_call(stuff::get_function_traits(bar), 35, "1234") == false);
}

void bar()
{
    
}