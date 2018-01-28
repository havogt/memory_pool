#include "variant3/object_pool.hpp"
#include "gtest/gtest.h"
#include <memory>

class resource {
  public:
    resource(std::string name = "default") : name_(name) {
        std::cout << "resource created: " << name_ << std::endl;
    }
    ~resource() { std::cout << "resource freed: " << name_ << std::endl; }

  private:
    std::string name_;
};

TEST(variant3, all) {
    std::cout << "main" << std::endl;
    auto my_pool = variant3::object_pool<resource>();
    auto h0 = my_pool.get_resource();
    auto h1 = my_pool.get_resource();
    { auto h2 = my_pool.get_resource(); }
    auto h3 = my_pool.get_resource();

    std::cout << "----" << std::endl;
    {
        auto my_pool2 = variant3::object_pool<resource>();
        h0 = my_pool2.get_resource();
        auto h4 = my_pool2.get_resource();
        std::cout << "----" << std::endl;
    }
    std::cout << "----" << std::endl;
}
