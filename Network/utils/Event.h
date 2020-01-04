#pragma once

enum EventType { Spike, Current, No };

struct Event {
    EventType type = EventType::No;
};

struct SpikeEvent : Event {
    SpikeEvent() {
        type = EventType::Spike;
    }
    int multiplicity = 0;
    double weight = 0.0;
};

struct CurrentEvent : Event {
    CurrentEvent() {
        type = EventType::Current;
    }
    double current = 0.0;
    double weight = 0.0;
};

struct NoEvent : Event {
    NoEvent() {
       type = EventType::No;
    }
};
