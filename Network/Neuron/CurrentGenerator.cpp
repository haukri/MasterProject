#include "CurrentGenerator.h"
#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

CurrentGenerator::CurrentGenerator() : param(new CurrentGenerator_param) { 
    clock = Clock::getInstance();
    initialize();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::default_random_engine(seed);
    distribution = std::normal_distribution<double>(param->noiseMean, param->noiseStd);
}

CurrentGenerator::CurrentGenerator(CurrentGenerator_param* param) : param(param) {
    clock = Clock::getInstance();
    initialize();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::default_random_engine(seed);
    distribution = std::normal_distribution<double>(param->noiseMean, param->noiseStd);
}

Event* CurrentGenerator::update(double n_dt) {
    if(param->ac_hz > 0) {
        return new CurrentEvent(param->I + sin(2*3.1415926535897*param->ac_hz*clock->getCurrentTime()) + distribution(generator)*param->noiseOn, 1.0);
    }
    return new CurrentEvent(param->I + distribution(generator)*param->noiseOn, 1.0);
}

void CurrentGenerator::resetInput() { }

void CurrentGenerator::handleEvent(Event* e) { }

CurrentGenerator::~CurrentGenerator() { }