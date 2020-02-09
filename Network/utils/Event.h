#pragma once

enum EventType { Spike, Current, No, Value };

struct Event {
    EventType type = EventType::No;
    virtual void setWeight(double w) {}
    virtual ~Event() {};
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
    ~SpikeEvent() {};
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
    ~CurrentEvent() {};
};

struct NoEvent : Event {
    NoEvent() {
       type = EventType::No;
    }
    ~NoEvent() {};
};

struct ValueEvent : Event {
    ValueEvent() {
        type = EventType::Value;
    }
    ValueEvent(double n_value) {
        type = EventType::Value;
        value = n_value;
    }
    void setWeight(double w) {}
    void setValue(double v) {
        value = v;
    }
    double value = 0.0;
    ~ValueEvent() {};
};
