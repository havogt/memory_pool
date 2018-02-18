#include <iostream>
#include <memory>
#include <boost/optional.hpp>

namespace variant3 {

class handle_manager {
  public:
    boost::optional<size_t> get_id() {
        if (free_ids.size() > 0) {
            size_t id = free_ids.back();
            free_ids.pop_back();
            return id;
        } else
            return boost::none;
    }

    void release_id(std::size_t id) {
        std::cout << "releasing handle " << id << std::endl;
        free_ids.push_back(id);
    }

  private:
    std::vector<size_t> free_ids;
};

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

    // TODO this should probably be a shared_ptr
    operator ResourceType() { return *resource_; }

    std::shared_ptr<ResourceType> get() { return resource_; }

  private:
    std::size_t id_;
    std::shared_ptr<ResourceType> resource_;
    std::weak_ptr<handle_manager> handle_manager_;
};
}
