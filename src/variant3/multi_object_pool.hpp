#pragma once

#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/type_index.hpp>
#include "object_pool.hpp"

namespace variant3 {
namespace detail {
template <typename T> struct get_resource;
template <typename ResourceType, typename Constructor>
struct get_resource<object_pool<ResourceType, Constructor>> {
    using type = ResourceType;
};
}
template <typename T>
using get_resource_t = typename detail::get_resource<T>::type;

template <typename... ObjectPools> class multi_object_pool {
  public:
    multi_object_pool(ObjectPools &&... pools)
        : map_(boost::fusion::make_pair<get_resource_t<ObjectPools>>(
              std::move(pools))...) {}

    template <typename T> std::shared_ptr<handle<T>> get_resource() {
        return boost::fusion::at_key<T>(map_).get_resource();
    }

  private:
    using map_type = boost::fusion::map<
        boost::fusion::pair<get_resource_t<ObjectPools>, ObjectPools>...>;
    map_type map_;
};

template <typename... ObjectPools>
multi_object_pool<ObjectPools...>
make_multi_object_pool(ObjectPools &&... object_pools) {
    return multi_object_pool<ObjectPools...>(std::move(object_pools)...);
}
}
