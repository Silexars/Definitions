#pragma once

#include "any_function.h"

namespace Veritas {
    class any_method : public any_function {
        public:
            template <class C, class ...Args>
            any_method(void (C::*m)(Args...), C *object) :
                any_function(
                    std::function<void(Args...)>(
                        [=](Args... args) -> void {
                            (object->*m)(args...);
                        }
                    )
                )
            {}

            template <class R, class C, class ...Args>
            any_method(R (C::*m)(Args...), C *object) :
                any_function(
                    std::function<R(Args...)>(
                        [=](Args... args) -> R {
                            return (object->*m)(args...);
                        }
                    )
                )
            {}
    };
}
