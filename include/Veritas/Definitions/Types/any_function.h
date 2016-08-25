#pragma once

#include <functional>
#include <stdexcept>
#include "any.h"
#include "any_args.h"

template <typename R, typename... Args>
R any_function_call(std::function<R(Args...)> func, Veritas::any_args anyargs);

template <typename R>
R any_function_call(std::function<R()> func, Veritas::any_args anyargs) {
    if (anyargs.size() > 0) throw std::invalid_argument("oops, argument list too long");
    return func();
}

template <typename R, typename Arg0, typename... Args>
R any_function_call(std::function<R(Arg0, Args...)> func, Veritas::any_args anyargs) {
    if (anyargs.size() == 0) throw std::invalid_argument("oops, argument list too short");
    auto arg0 = Veritas::any_cast<typename std::remove_reference<Arg0>::type>(anyargs[0]);
    anyargs.erase(anyargs.begin());
    std::function<R(Args...)> lambda = ([=](Args... args) -> R { return func(arg0, args...); });
    return any_function_call(lambda, anyargs);
}

namespace Veritas {
    class any_function {
        public:
            template <class R, class... Args>
            any_function(std::function<R(Args...)> f) {
                any_f = ([=](any_args anyargs) -> any { return any(any_function_call(f, anyargs)); });
            }

            template <class... Args>
            any_function(std::function<void(Args...)> f) {
                any_f = ([=](any_args anyargs) -> any {
                    any_function_call(f, anyargs);
                    return any();
                });
            }

            template <class R, class... Args>
            any_function(R (*f)(Args...)) : any_function(std::function<R(Args...)>(f)) {}

            template <class... Args>
            any_function(void (*f)(Args...)) : any_function(std::function<void(Args...)>(f)) {}

            any operator()(const any_args& args);
        private:
            std::function<any(any_args)> any_f;
    };
}
