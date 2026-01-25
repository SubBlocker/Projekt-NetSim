#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package {
    
public:
    Package();
    Package(ElementID id);
    Package(Package&& package);
    ElementID get_id() const {return id_;};

    ~Package();
    Package& operator=(Package&& package) noexcept;
private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID id_;
};

#endif
