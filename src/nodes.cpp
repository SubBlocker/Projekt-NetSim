#include "nodes.hpp"

Worker::Worker(ElementID id, TimeOffset process_time, std::unique_ptr<IPackageQueue> q): 
    id_(id), 
    process_time_(process_time),
    q_(std::move(q)){
    };

void Worker::do_work(Time t){
    if(!q_->empty() && !currently_processed_.has_value()){
        start_time_ = t;
        currently_processed_.emplace(q_->pop());
    }
    if( t - start_time_ >= process_time_){
        push_package(std::move(currently_processed_.value()));
        currently_processed_.reset();
    }
    
}