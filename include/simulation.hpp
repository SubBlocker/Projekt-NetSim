#ifndef SIMULATION_HXX
#define SIMULATION_HXX

#include "factory.hpp"


void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)>&& rf);


class SpecificTurnsReportNotifier {
public:
    explicit SpecificTurnsReportNotifier(const std::set<Time>& turns) : turns_(turns) {};

    bool should_generate_report(Time t);

private:
    std::set<Time> turns_;
};


class IntervalReportNotifier {
public:
    explicit IntervalReportNotifier(TimeOffset to) : to_(to) {};

    bool should_generate_report(Time t);

private:
    TimeOffset to_;
};


#endif //SIMULATION_HXX