#include "signalProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <eigen3/Eigen/Dense>
SignalProcessor::SignalProcessor(const Plane& antennaPlane, const Plane& antennaPlane2):
                                antenna(antennaPlane), antenna2(antennaPlane2)
{
    ellipseCenter.setZero();
    direction.setZero();
}

void SignalProcessor::findDirection() {
    findCenterEllips();
    findNormalToSignal();
    direction = (ellipseCenter + normal);///.normalized();
    std::cout<<"direction:\n";
    std::cout<<"x = "<<direction.x()<<"; y = "<<direction.y()<<"; z = "<<direction.z()<<"\n";
}


void SignalProcessor:: readSignal(const std::string& full_name){
    //f.open(full_name.c_str());
    std::ifstream f(full_name);
    if(!f) std::cout<<full_name<<" do not exist";

    std::string line;
    std::getline(f, line);

    while(std::getline(f, line)){
        std::stringstream ss(line);
        double i, j, k;
        ss >> i;
        ss >> j;
        ss >> k;
        falling_signals_dat.push_back({i, j, k});
        falling_signals_dat_xyz.push_back({i, j, k});
    }

    f.close();
    pojectionSignals.reserve(falling_signals_dat.size() * 3);
}


void SignalProcessor:: findCenterEllips() {
    for(Eigen::Vector3d e: falling_signals_dat_xyz){
        ellipseCenter += e;
    }
    ellipseCenter /=falling_signals_dat_xyz.size();
    std::cout<<"findCenterEllips: ";
    std::cout<<ellipseCenter.x()<<"; "<<ellipseCenter.y()<<"; "<<ellipseCenter.z()<<"\n";

}


void SignalProcessor:: findNormalToSignal(){
    Eigen::MatrixXd A(falling_signals_dat_xyz.size(), 3);
    for(int i = 0; i < falling_signals_dat_xyz.size(); ++i){
        A.row(i) = falling_signals_dat_xyz[i].transpose();
    }

    Eigen:: JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
    normal = svd.matrixV().col(2);//.normalized();
    std::cout<<"findNormalToSignal: ";
    std::cout<<normal.x()<<"; "<<normal.y()<<"; "<<normal.z()<<"\n";
}























void SignalProcessor:: calcProjectionSignal(){
    double* normVector = antenna.getNormalVector();
    double* normVector2 = antenna2.getNormalVector();
    double modulNormVector = sqrt(pow(normVector[0], 2) + pow(normVector[1], 2)+ pow(normVector[2], 2));
    double modulNormVector2 = sqrt(pow(normVector2[0], 2) + pow(normVector2[1], 2)+ pow(normVector2[2], 2));

    for(std::vector<double>& signal: falling_signals_dat){
        double dotProduct = signal[0] * normVector[0] + signal[1] * normVector[1] + signal[2] * normVector[2];
        double dotProduct2 = signal[0] * normVector2[0] + signal[1] * normVector2[1] + signal[2] * normVector2[2];
        double in, jn, kn;
        in =signal[0] - dotProduct * normVector[0] /modulNormVector/modulNormVector;
        jn =signal[1] - dotProduct * normVector[1] /modulNormVector/modulNormVector;
        kn =signal[2] - dotProduct * normVector[2] /modulNormVector/modulNormVector;
        pojectionSignals.push_back({in, jn, kn});
        std::cout<<"calcProjectionSignal1: "<<in<<" "<<jn<<" "<<kn<<"\n";

        in =signal[0] - dotProduct2 * normVector2[0] /modulNormVector2/modulNormVector2;
        jn =signal[1] - dotProduct2 * normVector2[1] /modulNormVector2/modulNormVector2;
        kn =signal[2] - dotProduct2 * normVector2[2] /modulNormVector2/modulNormVector2;
        pojectionSignals2.push_back({in, jn, kn});
        std::cout<<"calcProjectionSignal2: "<<in<<" "<<jn<<" "<<kn<<"\n";
    }
}







































