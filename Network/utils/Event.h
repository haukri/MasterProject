#pragma once
#include "Network/utils/Clock.h"

enum EventType { Spike, Current, No, Value };

struct Event {
    EventType type = EventType::No;
    double eventTime;
    virtual void setWeight(double w) {}
    virtual ~Event() {};
};

struct SpikeEvent : Event {
    SpikeEvent() {
        type = EventType::Spike;
        eventTime = Clock::getInstance()->getCurrentTime();
    }
    SpikeEvent(int n_multiplicity, double n_weight) {
        type = EventType::Spike;
        eventTime = Clock::getInstance()->getCurrentTime();
        multiplicity = n_multiplicity;
        weight = n_weight;
    }
    void setWeight(double w) {
        weight = w;
    }
    int multiplicity = 1;
    double weight = 1.0;
    ~SpikeEvent() {};
};

struct CurrentEvent : Event {
    CurrentEvent() {
        type = EventType::Current;
        eventTime = Clock::getInstance()->getCurrentTime();
    }
    CurrentEvent(double n_current, double n_weight) {
        type = EventType::Current;
        eventTime = Clock::getInstance()->getCurrentTime();
        current = n_current;
        weight = n_weight;
    }
    void setWeight(double w) {
        weight = w;
    }
    double current = 0.0;
    double weight = 0.0;
    ~CurrentEvent() {};
};

struct NoEvent : Event {
    NoEvent() {
       type = EventType::No;
       eventTime = Clock::getInstance()->getCurrentTime();
    }
    ~NoEvent() {};
};

struct ValueEvent : Event {
    ValueEvent() {
        type = EventType::Value;
        eventTime = Clock::getInstance()->getCurrentTime();
    }
    ValueEvent(double n_value) {
        type = EventType::Value;
        eventTime = Clock::getInstance()->getCurrentTime();
        value = n_value;
    }
    void setWeight(double w) {}
    void setValue(double v) {
        value = v;
    }
    double value = 0.0;
    ~ValueEvent() {};
};
