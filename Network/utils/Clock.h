#pragma once

#include <iostream>

class Clock
{
    private:
        /* Here will be the instance stored. */
        static Clock* instance;

        /* Private constructor to prevent instancing. */
        Clock();

        double current_time;
        double dt;

    public:
        /* Static access method. */
        static Clock* getInstance();
        double getCurrentTime();
        void setDt(double);
        double getDt();
        void tick();
        void tick(double);
};