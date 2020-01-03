#pragma once

enum EventType { SpikeEvent, CurrentEvent };

struct Event {
};

struct SpikeEvent : Event {
    const EventType type = EventType::SpikeEvent;
    bool spike;
    int multiplicity;
};

struct CurrentEvent : Event {
    const EventType type = EventType::CurrentEvent;
    double current;
};
