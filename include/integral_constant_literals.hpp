#ifndef STUFF_INTEGRAL_CONSTANT_LITERALS_HPP
#define STUFF_INTEGRAL_CONSTANT_LITERALS_HPP

#include <type_traits>

namespace stuff
{

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

    T res = 0;

    for (std::size_t i = 0; i < sizeof...(Chars); ++i) {
        res += chars[i] - '0';
        res *= 10;
    }  

    return res/10;
}

template<char... Chars> constexpr auto operator ""_ic () {
    return stuff::integral_constant<int, make_number<int, Chars...>()>{};
}

}
} // namespace stuff

#endif // STUFF_INTEGRAL_CONSTANT_LITERALS_HPP