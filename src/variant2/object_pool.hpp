#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "handle.hpp"

namespace variant2 {
template <typename ResourceType> class object_pool {
  public:
    std::shared_ptr<handle<ResourceType>>
    make_handle(const std::shared_ptr<ResourceType> &resource) {
        auto new_handle = std::make_shared<handle<ResourceType>>(resource);
        objects_[resource] = std::weak_ptr<handle<ResourceType>>(new_handle);
        return new_handle;
    }

    std::shared_ptr<handle<ResourceType>> allocate_resource() {
        auto new_resource = std::make_shared<ResourceType>();
        auto new_handle = std::make_shared<handle<ResourceType>>(new_resource);
        objects_.emplace(std::make_pair(new_resource, new_handle));
        return new_handle;
    }

    std::shared_ptr<handle<ResourceType>> get_resource() {
        for (const auto &o : objects_) {
            if (o.second.expired()) // this handle is free
            {
                return make_handle(o.first);
            }
        }
        return allocate_resource();
    }

    object_pool() {}

    ~object_pool() {}

    size_t size() const { return objects_.size(); }

  private:
    std::map<std::shared_ptr<ResourceType>, std::weak_ptr<handle<ResourceType>>>
        objects_;
};
}
