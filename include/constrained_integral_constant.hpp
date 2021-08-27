#ifndef STUFF_CONSTRAINDER_INTEGRAL_CONSTANT_HPP
#define STUFF_CONSTRAINDER_INTEGRAL_CONSTANT_HPP

#define STUFF_CONSTRAINED_USE_LITERALS 1

#ifdef STUFF_CONSTRAINED_USE_LITERALS
# include "integral_constant_literals.hpp"
#endif

#include <type_traits>
#include <cassert>
#include <stdexcept>

namespace stuff
{

template<class T, T Min, T Max>
struct range_constrain {
    static constexpr auto validate(T const &val)
    {
        return val >= Min && val <= Max;
    }
};

template<class T, T... values>
struct set_constrain {
    static constexpr auto validate(T const &val)
    {
        return ((val == values) || ...);
    }
};

struct constrained_assert_tag;
struct constrained_throw_tag;

template<class T, class Constrain, class OnError = constrained_throw_tag>
class constrained_integral_constant
{
public:
    template<T Val>
    constexpr constrained_integral_constant(std::integral_constant<T, Val>)
        : value_ {Val}
    {
        static_assert(Constrain::validate(Val));
    }

#ifdef STUFF_CONSTRAINED_USE_LITERALS
    template<T Val>
    constexpr constrained_integral_constant(stuff::integral_constant<T, Val>)
        : value_ {Val}
    {
        static_assert(Constrain::validate(Val));
    }
#endif

    constexpr constrained_integral_constant(T Val)
        : value_ {Val}
    {
        if constexpr (std::is_same_v<OnError, constrained_assert_tag>) {
            assert(Constrain::validate(Val));
        }

        if constexpr (std::is_same_v<OnError, constrained_throw_tag>) {
            if (!Constrain::validate(Val)) {
                throw std::runtime_error("Value not in range");
            }
        }
    }

    constexpr T value() const
    {
        return value_;
    }

    static constexpr auto validate(T const& val)
    {
        return Constrain::validate(val);
    }

    // shorthand for integral_constant
    template<T Val>
    static constexpr std::integral_constant<T, Val> make{};

private:
    T const value_;
};

template<class T, T Min, T Max>
using ranged_integral_constant = constrained_integral_constant<
    T, range_constrain<T, Min, Max>>;

template<class T, T... values>
using set_integral_constant = constrained_integral_constant<
    T, set_constrain<T, values...>>;

} // namespace stuff

#endif