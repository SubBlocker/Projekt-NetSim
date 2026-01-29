#ifndef SIMULATION_HXX
#define SIMULATION_HXX

#include "factory.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)>);



#endif //SIMULATION_HXX