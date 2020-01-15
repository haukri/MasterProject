#pragma once

#include "Clock.h"
#include <vector>

enum ValueType { voltage, current };

class Logging
{
    private:
        /* Here will be the instance stored. */
        static Logging* instance;

        /* Private constructor to prevent instancing. */
        Logging();
        Clock* clock;
        std::vector<long> value_populationID;
        std::vector<int> value_neuronID;
        std::vector<int> value_valueType;
        std::vector<double> value_value;
        std::vector<double> value_time;

        std::vector<long> event_populationID;
        std::vector<int> event_neuronID;
        std::vector<int> event_eventType;
        std::vector<double> event_time;
        ~Logging();

    public:
        /* Static access method. */
        static Logging* getInstance();
        void logValue(long populationID, int neuronID, int valueType, double value);
        void logEvent(long populationID, int neuronID, int eventType);
        void saveLog();
};