#include <iostream>
#include <memory>
#include <vector>

#include "handle.hpp"

namespace variant3 {

template <typename T, typename... CtorArgs> class object_constructor {
  public:
    object_constructor(CtorArgs &&... args) : args_{args...} {}

    std::shared_ptr<T> create_object() {
        return invoke(std::make_index_sequence<sizeof...(CtorArgs)>());
    }

  private:
    std::tuple<CtorArgs...> args_;

    template <size_t... Ints>
    std::shared_ptr<T> invoke(std::integer_sequence<size_t, Ints...>) {
        return std::make_shared<T>(std::get<Ints>(args_)...);
    }
};

template <typename T, typename... CtorArgs>
object_constructor<T, CtorArgs...>
make_object_constructor(CtorArgs &&... args) {
    return object_constructor<T, CtorArgs...>(args...);
}

template <typename ResourceType,
          typename Constructor = object_constructor<ResourceType>>
class object_pool {
  public:
    size_t allocate_resource() {
        resources_.emplace_back(constructor_.create_object());
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

    object_pool(object_pool &&other) = default;
    object_pool(const object_pool &other) = default;

    //    template <typename... Args>
    //    object_pool(Args &&... args)
    //        : constructor_(args...),
    //          handle_manager_(std::make_shared<handle_manager>()) {}

    // TODO this should be only enabled if Constructor has no arguments
    object_pool()
        : constructor_(), handle_manager_(std::make_shared<handle_manager>()) {}

    object_pool(const Constructor &constructor)
        : constructor_(constructor),
          handle_manager_(std::make_shared<handle_manager>()) {}

    ~object_pool() {}

  private:
    Constructor constructor_;
    std::shared_ptr<handle_manager> handle_manager_;
    std::vector<std::shared_ptr<ResourceType>>
        resources_; // TODO test copying an object pool.

    size_t last_id() { return resources_.size() - 1; }
};

template <typename ResourceType, typename... CtorArgs>
auto make_object_pool(CtorArgs &&... args)
    -> object_pool<ResourceType,
                   decltype(make_object_constructor<ResourceType>(args...))> {
    return object_pool<
        ResourceType, decltype(make_object_constructor<ResourceType>(args...))>(
        make_object_constructor<ResourceType>(args...));
}
}
