#ifndef SIGNAL_PROCESSOR_H
#define SIGNAL_PROCESSOR_H

#include <iostream>
#include <vector>
#include "plane.h"
class SignalProcessor {
private:
    std::vector<std::vector<double>> falling_signals_dat;
    std::vector<std::vector<double>> pojectionSignals;
    Plane antenna;

public:
    SignalProcessor(const Plane& antennaPlane);
    void readSignal(const std::string& full_name);
    void calcProjectionSignal();
    void process();
};

#endif
