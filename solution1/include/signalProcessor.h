#ifndef SIGNAL_PROCESSOR_H
#define SIGNAL_PROCESSOR_H

#include <iostream>
#include <vector>
#include "plane.h"
#include <eigen3/Eigen/Dense>
class SignalProcessor {
private:
    std::vector<std::vector<double>> falling_signals_dat;
    Eigen::Vector3d ellipseCenter;
    Eigen::Vector3d direction;
    Eigen::Vector3d normal;
    std::vector<Eigen::Vector3d> falling_signals_dat_xyz;

    std::vector<std::vector<double>> pojectionSignals;
    std::vector<std::vector<double>> pojectionSignals2;
    std::vector<std::vector<double>> reconSignals;
    Plane antenna;
    Plane antenna2;

public:
    SignalProcessor(const Plane& antennaPlane, const Plane& antennaPlane2);
    void readSignal(const std::string& full_name);
    void findCenterEllips();
    void findDirection();
    void calcProjectionSignal();
    void findNormalToSignal();

};

#endif
