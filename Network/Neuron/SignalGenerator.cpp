#include "SignalGenerator.h"
#include <iostream>
#include <limits>
#include <math.h>

using namespace std;

SignalGenerator::SignalGenerator() : param(new SignalGenerator_param) {
    clock = Clock::getInstance();
    initialize();
}

SignalGenerator::SignalGenerator(SignalGenerator_param* param) : param(param) {
    clock = Clock::getInstance();
    initialize();
}

Event* SignalGenerator::update(double n_dt) {
    double signalValue = 0;
    if(param->f1 > 0)
        signalValue += sin(2*3.1415926535897*param->f1*clock->getCurrentTime());
    if(param->f2 > 0)
        signalValue += sin(2*3.1415926535897*param->f2*clock->getCurrentTime());
    signalValue *= param->scale;
    signalValue += param->offset;
    logger->logValue(999, 0, EventType::Value, signalValue);
    return new ValueEvent(signalValue);
}

void SignalGenerator::resetInput() { }

void SignalGenerator::handleEvent(Event* e) { }

SignalGenerator::~SignalGenerator() { }