#include "package.hpp"


std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;


Package::Package() {
    if(freed_IDs.empty()){
        id_ = assigned_IDs.size() + 1;
        assigned_IDs.insert(id_);
    }else{
        id_ = *freed_IDs.begin();
        freed_IDs.erase(id_);
    }
}

Package& Package::operator=(Package&& package) noexcept {
    if (this == &package) {
        return *this;
    }
    if (id_ != -1) {
        freed_IDs.insert(id_);
    }
    id_ = package.id_;
    package.id_ = -1;
    return *this;
}


Package::Package(ElementID id) {
    assigned_IDs.insert(id);
    id_ = id;
}

Package::Package(Package&& package): id_(package.get_id()){
    package.id_ = -1;
}



Package::~Package() {
    if(id_ != -1){
        freed_IDs.insert(id_);
    }
}