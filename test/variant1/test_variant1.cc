#include "variant1/object_pool.hpp"
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

TEST(variant1, all) {
    std::cout << "main" << std::endl;
    auto my_pool = std::make_shared<variant1::object_pool<resource>>(
        "pool1"); // if we want to use
    // shared_from_this() on the pool,
    // we need a shared_ptr to the pool
    auto h1 = my_pool->get_resource();
    auto h2 = my_pool->get_resource();
    { auto h3 = my_pool->get_resource(); }
    auto h4 = my_pool->get_resource();

    std::cout << "----" << std::endl;
    {
        auto my_pool2 =
            std::make_shared<variant1::object_pool<resource>>("pool2");
        h1 = my_pool2->get_resource();
        auto h5 = my_pool2->get_resource();
    }
    std::cout << "----" << std::endl;
}
