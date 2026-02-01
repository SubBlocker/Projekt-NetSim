#include "simulation.hpp"

void simulate(Factory &f, TimeOffset d, std::function<void(Factory &, Time)> &&rf) {
}

bool SpecificTurnsReportNotifier::should_generate_report(Time t) {
    return turns_.find(t) != turns_.cend();
}

bool IntervalReportNotifier::should_generate_report(Time t) {
    return t == 1 || t % to_ == 1;
}