#include "package.hpp"
#include <list>

enum class PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile {
public:
    virtual ~IPackageStockpile() = default;
    virtual void push(Package&& package) = 0;
    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;

    using const_iterator = std::list<Package>::const_iterator;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
};


class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type) : type_(type) {}

    void push(Package&& package) override {
        container_.push_back(std::move(package));
    }

    bool empty() const override { return container_.empty(); }
    std::size_t size() const override { return container_.size(); }

    Package pop() override; 

    PackageQueueType get_queue_type() const override { return type_; }

    const_iterator begin() const override { return container_.begin(); }
    const_iterator end() const override { return container_.end(); }
    const_iterator cbegin() const override { return container_.cbegin(); }
    const_iterator cend() const override { return container_.cend(); }

private:
    PackageQueueType type_;
    std::list<Package> container_; 
};