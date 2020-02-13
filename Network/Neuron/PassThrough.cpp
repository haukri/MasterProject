#include "PassThrough.h"
#include <iostream>
#include <limits>

using namespace std;

PassThrough::PassThrough() : param(new PassThrough_param) {
    initialize();
}

PassThrough::PassThrough(PassThrough_param* param) : param(param) { 
    initialize();
}

Event* PassThrough::update(double n_dt) {
    if(eventType == EventType::Spike) {
        return new SpikeEvent(multiplicity, weight);
    }
    else {
        return new NoEvent();
    }
}

void PassThrough::resetInput() { }

void PassThrough::handleEvent(Event* e) {
    if(e->type == EventType::Spike) {
        eventType = EventType::Spike;
        multiplicity = static_cast<SpikeEvent*>(e)->multiplicity;
        weight = static_cast<SpikeEvent*>(e)->weight;
    }
    else {
        eventType = EventType::No;
    }
}

PassThrough::~PassThrough() { }