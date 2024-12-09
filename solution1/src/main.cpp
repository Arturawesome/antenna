#include "plane.h"
#include "signalProcessor.h"

int main(){
    Plane plane(1, 1, 1);
    Plane plane2(1, 1, 1.1);
    SignalProcessor signalProcessor(plane, plane2);

    signalProcessor.readSignal("/home/artur/Documents/antenna/solution1/signals.txt");

    plane.print();


    signalProcessor.findDirection();
    //signalProcessor.findNormalToSignal();
    //signalProcessor.calcProjectionSignal();
    // signalProcessor.findDirection();
   // signalProcessor.reconstructionOfSignal();
    //signalProcessor.findNormalToSignal();


}
