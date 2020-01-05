#pragma once

enum EventType { Spike, Current, No };

struct Event {
    EventType type = EventType::No;
    virtual void add(Event e) {}
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
    void add(Event e) {
        weight += static_cast<SpikeEvent*>(&e)->weight;
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
    double current = 0.0;
    double weight = 0.0;
};

struct NoEvent : Event {
    NoEvent() {
       type = EventType::No;
    }
};
