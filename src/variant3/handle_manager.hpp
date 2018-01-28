#pragma once
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
}
