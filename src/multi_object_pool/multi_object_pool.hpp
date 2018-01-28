#pragma once

#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/type_index.hpp>
#include "../variant2/object_pool.hpp"

namespace variant2 {
template <typename... ResourceTypes> class multi_object_pool {
  public:
    multi_object_pool()
        : map_(boost::fusion::make_pair<ResourceTypes>(
              object_pool<ResourceTypes>(
                  boost::typeindex::type_id<ResourceTypes>().name()))...) {}

    template <typename T> std::shared_ptr<handle<T>> get_resource() {
        return boost::fusion::at_key<T>(map_).get_resource();
    }

  private:
    using map_type = boost::fusion::map<
        boost::fusion::pair<ResourceTypes, object_pool<ResourceTypes>>...>;
    map_type map_;
};
}
