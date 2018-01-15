#include <iostream>
#include <map>
#include <memory>
#include <vector>

class pool;

class resource {
  public:
    resource(std::string name = "default") : name_(name) {
        std::cout << "resource created: " << name_ << std::endl;
    }
    ~resource() { std::cout << "resource freed: " << name_ << std::endl; }

  private:
    std::string name_;
};

class handle {
  public:
    handle(std::size_t id, std::shared_ptr<resource> res,
           std::shared_ptr<pool> pool);
    ~handle();
    resource get() { return *resource_; }

  private:
    std::size_t id_;
    std::shared_ptr<resource> resource_;
    std::weak_ptr<pool> pool_;
};

class pool : public std::enable_shared_from_this<pool> {
  public:
    void allocate_resource() {
        resources_.emplace_back(std::make_shared<resource>(name_));
        available_resources.emplace_back(last_id());
    }

    std::shared_ptr<handle> get_resource() {
        if (available_resources.size() == 0)
            allocate_resource();
        size_t id = available_resources.back();
        available_resources.pop_back();
        std::cout << "pool_size = " << resources_.size() << std::endl;
        std::cout << "passing handle to resource id = " << id << std::endl;
        return std::make_shared<handle>(id, resources_[id], shared_from_this());
    }

    void release(std::size_t id) {
        std::cout << "releasing handle " << id << " of pool " << name_
                  << std::endl;
        available_resources.push_back(id);
    }

    pool(std::string name) : name_(name) {
        std::cout << "pool created: " << name_ << std::endl;
    }
    ~pool() { std::cout << "pool freed: " << name_ << std::endl; }

  private:
    std::string name_;
    std::vector<std::shared_ptr<resource>> resources_;
    std::vector<size_t> available_resources;

    size_t last_id() { return resources_.size() - 1; }
};

int main() {
    std::cout << "main" << std::endl;
    auto my_pool = std::make_shared<pool>("pool1"); // if we want to use
    // shared_from_this() on the pool,
    // we need a shared_ptr to the pool
    auto h1 = my_pool->get_resource();
    auto h2 = my_pool->get_resource();
    { auto h3 = my_pool->get_resource(); }
    auto h4 = my_pool->get_resource();

    std::cout << "----" << std::endl;
    {
        auto my_pool2 = std::make_shared<pool>("pool2");
        h1 = my_pool2->get_resource();
        auto h5 = my_pool2->get_resource();
    }
    std::cout << "----" << std::endl;
}
