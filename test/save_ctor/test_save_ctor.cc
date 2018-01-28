#include "variant2/object_pool.hpp"
#include "gtest/gtest.h"
#include <iostream>

class class_with_strings {
  public:
    class_with_strings(std::string name1, std::string name2)
        : name1_(name1), name2_(name2) {}

    std::string name1_;
    std::string name2_;
};

template <typename... T> struct arg_wrapper { std::tuple<T...> args; };

template <typename T, typename... CtorArgs> struct ctor_forwarder {
    ctor_forwarder(CtorArgs &&... args) : args_{args...} {}

    T create_object() {
        return invoke(std::make_index_sequence<sizeof...(CtorArgs)>());
    }

    std::tuple<CtorArgs...> args_;

    template <size_t... Ints> T invoke(std::integer_sequence<size_t, Ints...>) {
        return T{std::get<Ints>(args_)...};
    }
};

template <typename T, typename... CtorArgs>
ctor_forwarder<T, CtorArgs...> make_ctor_forwarder(CtorArgs &&... args) {
    return ctor_forwarder<T, CtorArgs...>(args...);
}

TEST(save_ctor, all) {
    auto test = make_ctor_forwarder<class_with_strings>("bla1", "bla2");

    auto o1 = test.create_object();

    std::cout << o1.name1_ << std::endl;
    std::cout << o1.name2_ << std::endl;
}
