#include <iostream>
#include <memory>
#include "handle_manager.hpp"

namespace variant3 {

template <typename ResourceType> class handle {
  public:
    handle(std::size_t id, std::shared_ptr<ResourceType> res,
           std::shared_ptr<handle_manager> handle_manager)
        : id_(id), resource_(res), handle_manager_(handle_manager) {
        std::cout << "creating a handle" << std::endl;
    }

    ~handle() {
        if (!handle_manager_.expired()) {
            auto lock_handle_manager = handle_manager_.lock();
            lock_handle_manager->release_id(id_);
        }
    }

    std::shared_ptr<ResourceType> get() { return resource_; }

  private:
    std::size_t id_;
    std::shared_ptr<ResourceType> resource_;
    std::weak_ptr<handle_manager> handle_manager_;
};
}
