#pragma once

enum EventType { Spike, Current, No };

struct Event {
    EventType type = EventType::No;
    virtual void setWeight(double w) {}
};

struct SpikeEvent : Event {
    SpikeEvent() {
        type = EventType::Spike;
    }
    SpikeEvent(int n_multiplicity, double n_weight) {
        type = EventType::Spike;
        multiplicity = n_multiplicity;
        weight = n_weight;
    }
    void setWeight(double w) {
        weight = w;
    }
    int multiplicity = 0;
    double weight = 0.0;
};

struct CurrentEvent : Event {
    CurrentEvent() {
        type = EventType::Current;
    }
    CurrentEvent(double n_current, double n_weight) {
        type = EventType::Current;
        current = n_current;
        weight = n_weight;
    }
    void setWeight(double w) {
        weight = w;
    }
    double current = 0.0;
    double weight = 0.0;
};

struct NoEvent : Event {
    NoEvent() {
       type = EventType::No;
    }
};
