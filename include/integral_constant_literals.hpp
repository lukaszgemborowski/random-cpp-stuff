#ifndef STUFF_INTEGRAL_CONSTANT_LITERALS_HPP
#define STUFF_INTEGRAL_CONSTANT_LITERALS_HPP

#include <type_traits>

namespace stuff
{

// simple std::integral_constant-compatbile class
// the main difference is lack of implcicit convertion to T
// it stops from -(integral_constant<T, v>) being automatically
// converted to a T instance
template<class T, T v>
struct integral_constant
{
    using value_type = T;
    using type = integral_constant<T, v>;

    static constexpr T value = v;

    operator std::integral_constant<T, v> () const {
        return std::integral_constant<T, v> {};
    }

    explicit operator T() const {
        return value;
    }
};

// this will convert -(integral_constant<T, v>) to integral_constant<T, -v>
// if T is a signed integer
template<class T, T v,
    typename = std::enable_if_t<std::is_signed_v<T>>>
integral_constant<T, -v> operator-(integral_constant<T, v>)
{
    return integral_constant<T, -v>{};
}

namespace literals
{
template<class T, char... Chars> constexpr T make_number() {
    char chars[sizeof...(Chars)] = {0};
    char *p = chars;
    ((*p++ = Chars), ...);

    T res = chars[0] - '0';

    for (std::size_t i = 1; i < sizeof...(Chars); ++i) {
        res *= 10;
        res += chars[i] - '0';
    }  

    return res;
}

template<char... Chars> constexpr auto operator ""_ic () {
    return stuff::integral_constant<int, make_number<int, Chars...>()>{};
}

}
} // namespace stuff

#endif // STUFF_INTEGRAL_CONSTANT_LITERALS_HPP