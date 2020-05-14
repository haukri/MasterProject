#include "Logging.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

/* Null, because instance will be initialized on demand. */
Logging* Logging::instance = 0;

Logging* Logging::getInstance()
{
    if (instance == 0) {
        instance = new Logging();
    }
    return instance;
}

Logging::Logging()
{
    clock = Clock::getInstance();
}

void Logging::logValue(long populationID, int neuronID, int valueType, double value) {
    value_time.push_back(clock->getCurrentTime());
    value_populationID.push_back(populationID);
    value_neuronID.push_back(neuronID);
    value_valueType.push_back(valueType);
    value_value.push_back(value);
}

void Logging::logEvent(long populationID, int neuronID, int eventType) {
    // event_time.push_back(clock->getCurrentTime());
    // event_populationID.push_back(populationID);
    // event_neuronID.push_back(neuronID);
    // event_eventType.push_back(eventType);
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void Logging::saveLog() {
    ofstream outfile;
    unsigned int timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    outfile.open("/home/haukur/MasterProject/Logs/value_" + currentDateTime() + "_" + to_string(timeSinceEpoch) + ".csv");
    outfile << "time,populationID,neuronID,valueType,value" << endl;
    for(int i = 0; i < value_time.size(); i++) {
        outfile << value_time[i] << "," << value_populationID[i] << "," << value_neuronID[i] << ",";
        outfile << value_valueType[i] << "," << value_value[i] << endl;
    }
    outfile.close();
    outfile.open("/home/haukur/MasterProject/Logs/event_" + currentDateTime() + "_" + to_string(timeSinceEpoch) + ".csv");
    outfile << "time,populationID,neuronID,eventType" << endl;
    for(int i = 0; i < event_time.size(); i++) {
        outfile << event_time[i] << "," << event_populationID[i] << "," << event_neuronID[i] << ",";
        outfile << event_eventType[i] << endl;
    }
    outfile.close();
}