#pragma once

#include <iostream>
#include <memory>

namespace variant2 {

template <typename ResourceType> class handle {
  public:
    handle(std::shared_ptr<ResourceType> res) : resource_(res) {}

    std::shared_ptr<ResourceType> get() { return resource_; }

  private:
    std::shared_ptr<ResourceType> resource_;
};
}
