
#include "types.hpp"

class Package {
public:
    Package();
    Package(ElementID id);
    Package(Package&& package);
    Package& operator=(Package&& other) noexcept;
    ElementID get_id() const {return id_;};

    ~Package();
    Package(const Package&) = delete;
    Package& operator=(const Package&) = delete;
private:
    ElementID id_;
};
