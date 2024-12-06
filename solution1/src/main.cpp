#include "plane.h"
#include "signalProcessor.h"

int main(){
    Plane plane(1, 1, 1);
    SignalProcessor signalProcessor(plane);

    signalProcessor.readSignal("/home/softmatter/Documents/Conferences/antena/proba.txt");

    plane.print();
    signalProcessor.process();
    signalProcessor.calcProjectionSignal();
}
