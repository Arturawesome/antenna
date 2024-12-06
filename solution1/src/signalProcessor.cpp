#include "signalProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
SignalProcessor::SignalProcessor(const Plane& antennaPlane):
                                antenna(antennaPlane)
{
    std::cout << "SignalProcessor constructor called." << std::endl;
}

void SignalProcessor::process() {
    std::cout << "SignalProcessor process function called." << std::endl;
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
        std::cout<<"i = "<<i<<"; j = "<<j<<"; k = "<<k<<"\n";
        falling_signals_dat.push_back({i, j, k});
    }
    f.close();
    pojectionSignals.reserve(falling_signals_dat.size() * 3);
}

void SignalProcessor:: reconstructionOfSignal(){
    double* normVector = antenna.getNormalVector();
    double modulNormVector = sqrt(pow(normVector[0], 2) + pow(normVector[1], 2)+ pow(normVector[2], 2));
    double unitnormVector[3] = { normVector[0] / modulNormVector, normVector[1] / modulNormVector, normVector[2] / modulNormVector };

    for(std::vector<double>& pr_signal: pojectionSignals){
        double dotProduct = pr_signal[0] * unitnormVector[0] + pr_signal[1] * unitnormVector[1] + pr_signal[2] * unitnormVector[2];
        double rec_i, rec_j, rec_k;
        std::cout<<" 2Dot = "<<dotProduct<<"\n";
        rec_i = pr_signal[0] - 2 * dotProduct * unitnormVector[0];
        rec_j = pr_signal[1] - 2 * dotProduct * unitnormVector[1];
        rec_k = pr_signal[2] - 2 * dotProduct * unitnormVector[2];
        reconSignals.push_back({rec_i, rec_j, rec_k});
        std::cout<<"reconstructionOfSignal: "<<rec_i<<" "<<rec_j<<" "<<rec_k<<"\n";
    }


}

void SignalProcessor:: calcProjectionSignal(){

    double* normVector = antenna.getNormalVector();
    double modulNormVector = sqrt(pow(normVector[0], 2) + pow(normVector[1], 2)+ pow(normVector[2], 2));



    for(std::vector<double>& signal: falling_signals_dat){
        double dotProduct = signal[0] * normVector[0] + signal[1] * normVector[1] + signal[2] * normVector[2];
        double in, jn, kn;
        in =signal[0] - dotProduct * normVector[0] /modulNormVector/modulNormVector;
        jn =signal[1] - dotProduct * normVector[1] /modulNormVector/modulNormVector;
        kn =signal[2] - dotProduct * normVector[2] /modulNormVector/modulNormVector;
        pojectionSignals.push_back({in, jn, kn});
        std::cout<<"calcProjectionSignal: "<<in<<" "<<jn<<" "<<kn<<"\n";

    }


}







































