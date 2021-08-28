#ifndef STUFF_FUNCTION_TRAITS_HPP
#define STUFF_FUNCTION_TRAITS_HPP

namespace stuff
{

template<class R, class... Args>
struct function_traits {};

template<class R, class... Args>
constexpr auto get_function_traits(R (*)(Args...)) {
    return function_traits<R, Args...>{};
}

} // namespace stuff

#endif // STUFF_FUNCTION_TRAITS_HPP