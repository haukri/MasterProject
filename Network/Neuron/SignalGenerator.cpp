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
    double signalValue = sin(2*3.1415926535897*param->f*clock->getCurrentTime())/4+sin(2*3.1415926535897*(param->f+0.15)*clock->getCurrentTime())/4+1;
    logger->logValue(999, 0, EventType::Value, signalValue);
    return new ValueEvent(signalValue);
}

void SignalGenerator::resetInput() { }

void SignalGenerator::handleEvent(Event* e) { }

SignalGenerator::~SignalGenerator() { }