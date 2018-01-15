#include <iostream>
#include <memory>

namespace variant1 {

template <typename T> class object_pool;

template <typename ResourceType> class handle {
  public:
    handle(std::size_t id, std::shared_ptr<ResourceType> res,
           std::shared_ptr<object_pool<ResourceType>> pool)
        : id_(id), resource_(res), pool_(pool) {
        std::cout << "creating a handle" << std::endl;
    }

    ~handle() {
        if (!pool_.expired()) {
            auto pool = pool_.lock();
            pool->release(id_);
        }
    }

    ResourceType get() { return *resource_; }

  private:
    std::size_t id_;
    std::shared_ptr<ResourceType> resource_;
    std::weak_ptr<object_pool<ResourceType>> pool_;
};
}
