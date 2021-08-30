#ifndef STUFF_VALIDATE_CALL_HPP
#define STUFF_VALIDATE_CALL_HPP

namespace stuff
{

template<class... Args> struct function_arg_types{};

template<class FuncTrait, class... Args>
struct check_argument_types;

template<class R, class... FunArgs, class... ProvidedArgs>
struct check_argument_types<function_arg_types<R, FunArgs...>, ProvidedArgs...> {
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
bool validate_call_arguments(R (*)(FuncArgs...), Args... args) {
    static_assert(check_argument_types<function_arg_types<R, FuncArgs...>, Args...>::result);
    return (validate_one<FuncArgs>(args) && ...);
}

template<class T> struct call_result {
    T       value;
    bool    success;
};

} // namespace stuff

#endif // STUFF_VALIDATE_CALL_HPP