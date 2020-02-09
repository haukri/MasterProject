#include "CurrentGenerator.h"
#include <iostream>
#include <limits>

using namespace std;

CurrentGenerator::CurrentGenerator() : param(new CurrentGenerator_param) { 
    initialize();
}

CurrentGenerator::CurrentGenerator(CurrentGenerator_param* param) : param(param) { 
    initialize();
}

Event* CurrentGenerator::update(double n_dt) {
    return new CurrentEvent(param->I, 1.0);
}

void CurrentGenerator::resetInput() { }

void CurrentGenerator::handleEvent(Event* e) { }

CurrentGenerator::~CurrentGenerator() { }