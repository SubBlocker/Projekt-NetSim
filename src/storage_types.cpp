#include "storage_types.hpp"


void PackageQueue::push(Package&& package){
    container_.emplace_back(std::move(package));
}

Package PackageQueue::pop(){
    Package res;
    switch (type_)
    {
    case PackageQueueType::FIFO:
        res = std::move(container_.front());
        container_.pop_front();
        break;
    case PackageQueueType::LIFO:
        res = std::move(container_.back());
        container_.pop_back();
        break;
    default:
        break;
    }
    return res;
}