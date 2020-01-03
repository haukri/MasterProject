#include "Clock.h"

/* Null, because instance will be initialized on demand. */
Clock* Clock::instance = 0;

Clock* Clock::getInstance()
{
    if (instance == 0) {
        instance = new Clock();
    }
    return instance;
}

Clock::Clock()
{
    current_time = 0.0;
    dt = 0.0;
}

double Clock::getCurrentTime() {
    return current_time;
}

void Clock::tick(double n_dt) {
    current_time += n_dt;
}

void Clock::tick() {
    current_time += dt;
}

void Clock::setDt(double n_dt) {
    dt = n_dt;
}

double Clock::getDt() {
    return dt;
}

