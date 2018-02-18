#include "variant3/multi_object_pool.hpp"
#include "gtest/gtest.h"
#include <memory>

class resource1 {
  public:
    resource1(std::string name = "default") : name_(name) {
        std::cout << "resource1 created: " << name_ << std::endl;
    }
    ~resource1() { std::cout << "resource1 freed: " << name_ << std::endl; }

  private:
    std::string name_;
};

class resource2 {
  public:
    resource2(std::string name = "default") : name_(name) {
        std::cout << "resource2 created: " << name_ << std::endl;
    }
    ~resource2() { std::cout << "resource2 freed: " << name_ << std::endl; }

  private:
    std::string name_;
};

TEST(multi_object_pool, get_resource) {
    auto pool = variant3::make_object_pool<resource1>("my resource1");
    static_assert(std::is_same<variant3::get_resource_t<decltype(pool)>,
                               resource1>::value,
                  "error");
}

TEST(multi_object_pool, all) {
    auto my_multi_pool = variant3::make_multi_object_pool(
        variant3::make_object_pool<resource1>("my resource1"),
        variant3::make_object_pool<resource2>("my resource2"));

    auto res1 = my_multi_pool.get_resource<resource1>();
    auto res2 = my_multi_pool.get_resource<resource2>();
}
