#include <iostream>
#include <memory>
#include <vector>

#include "handle.hpp"
#include "handle_manager.hpp"

namespace variant3 {
template <typename ResourceType> class object_pool {
  public:
    size_t allocate_resource() {
        resources_.emplace_back(std::make_shared<ResourceType>());
        return last_id();
    }

    std::shared_ptr<handle<ResourceType>> get_resource() {
        auto id = handle_manager_->get_id();
        if (!id)
            id = allocate_resource();

        std::cout << "pool_size = " << resources_.size() << std::endl;
        std::cout << "passing handle to resource id = " << id.value()
                  << std::endl;
        return std::make_shared<handle<ResourceType>>(
            id.value(), resources_[id.value()], handle_manager_);
    }

    object_pool() : handle_manager_(std::make_shared<handle_manager>()) {}

    ~object_pool() {}

  private:
    std::vector<std::shared_ptr<ResourceType>> resources_;
    std::shared_ptr<handle_manager> handle_manager_;

    size_t last_id() { return resources_.size() - 1; }
};
}
