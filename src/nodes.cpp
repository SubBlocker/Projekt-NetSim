#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    std::size_t n = preferences_.size();

    if (!n) {
        preferences_[r] = 1.0;
        return;
    }

    double probability = 1.0 / (n + 1);

    for (auto& receiver : preferences_) {
        receiver.second = probability;
    }

    preferences_[r] = probability;

}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    auto receiver_to_remove = preferences_.find(r);
    if (receiver_to_remove == preferences_.end()) return;
    preferences_.erase(receiver_to_remove);

    std::size_t n = preferences_.size();
    if (!n) return;

    double probability = 1.0 / n;

    for (auto& receiver : preferences_) {
        receiver.second = probability;
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    auto probability = pg_();
    if (probability < 0 || probability > 1) {
        return nullptr;
    }

    double distribution = 0.0;

    for (auto& receiver : preferences_) {
        distribution += receiver.second;

        if (distribution < 0 || distribution > 1) {
            return nullptr;
        }
        if (probability <= distribution) {
            return receiver.first;
        }
    }

    return nullptr;
}

void PackageSender::send_package() {
    if (!buffer_.has_value()) return;

    IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
    receiver->receive_package(std::move(*buffer_));
    buffer_.reset();
}

void Ramp::deliver_goods(Time t) {
    if (!buffer_) {
        push_package(Package());
        buffer_.emplace(id_);
        t_ = t;
        return;
    }

    if (t == t_ + di_) {
        push_package(Package());
    }
}

Worker::Worker(ElementID id, TimeOffset process_time, std::unique_ptr<IPackageQueue> q): 
    id_(id), 
    process_time_(process_time),
    q_(std::move(q)){
    };

void Worker::do_work(Time t) {
    if (!q_->empty() && !currently_processed_.has_value()) {
        start_time_ = t;
        currently_processed_.emplace(q_->pop());
    }
    if (t - start_time_ + 1 >= process_time_) {
        push_package(std::move(currently_processed_.value()));
        currently_processed_.reset();
    }
    
}