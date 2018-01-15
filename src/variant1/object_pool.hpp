#include <iostream>
#include <memory>
#include <vector>

#include "handle.hpp"

namespace variant1 {
template <typename ResourceType>
class object_pool
    : public std::enable_shared_from_this<object_pool<ResourceType>> {
  public:
    void allocate_resource() {
        resources_.emplace_back(std::make_shared<ResourceType>(name_));
        available_resources.emplace_back(last_id());
    }

    std::shared_ptr<handle<ResourceType>> get_resource() {
        if (available_resources.size() == 0)
            allocate_resource();
        size_t id = available_resources.back();
        available_resources.pop_back();
        std::cout << "pool_size = " << resources_.size() << std::endl;
        std::cout << "passing handle to resource id = " << id << std::endl;
        return std::make_shared<handle<ResourceType>>(id, resources_[id],
                                                      this->shared_from_this());
    }

    void release(std::size_t id) {
        std::cout << "releasing handle " << id << " of pool " << name_
                  << std::endl;
        available_resources.push_back(id);
    }

    object_pool(std::string name) : name_(name) {
        std::cout << "pool created: " << name_ << std::endl;
    }

    ~object_pool() { std::cout << "pool freed: " << name_ << std::endl; }

  private:
    std::string name_;
    std::vector<std::shared_ptr<ResourceType>> resources_;
    std::vector<size_t> available_resources;

    size_t last_id() { return resources_.size() - 1; }
};
}
