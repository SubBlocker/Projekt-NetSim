#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "storage_types.hpp"
#include "nodes.hpp"
#include <list>
#include <map>
#include <string>
#include <istream>
#include <ostream>
#include <algorithm>
#include <utility>


class PackageSender;
enum class NodeColor;

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);

template<class Node>
class NodeCollection {
public:

    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node) { container.emplace_back(std::move(node)); }

    void remove_by_id(ElementID id) { container.remove_if([id](const Node& elem) { return elem.get_id() == id; }); }

    NodeCollection<Node>::iterator find_by_id(ElementID id) {
        return std::find_if(container.begin(), container.end(), [id](const Node& elem) {
            return elem.get_id() == id;
        });
    }

    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {
        return std::find_if(container.begin(), container.end(), [id](const Node& elem) {
            return elem.get_id() == id;
        });
    }

    iterator begin() { return container.begin(); }

    iterator end() { return container.end(); }

    const_iterator begin() const { return container.cbegin(); }

    const_iterator end() const { return container.cend(); }

    const_iterator cbegin() const { return container.cbegin(); }

    const_iterator cend() const { return container.cend(); }

private:
    container_t container;

};


#endif //NETSIM_FACTORY_HPP