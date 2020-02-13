#pragma once

#include <iostream>
#include <vector>
#include "Network/utils/Event.h"
#include "Network/utils/Clock.h"
#include <string>
#include "Network/Neuron/Neuron.h"
#include "Network/utils/Logging.h"
#include "Network/Neuron/CurrentGenerator.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/Neuron/LIF.h"
#include "Network/Neuron/SignalGenerator.h"
#include "Network/Neuron/PassThrough.h"
#include <string>

class Population
{
public:

    Population() {};

    Population(int amount, std::string modelName) {
        numberOfNeurons = amount;
        initialize();
        if(modelName == "iaf") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new LIF());
            }
        }
        else if(modelName == "izhikevich") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new Izhikevich((long)this, i));
            }
        }
        else if(modelName == "CurrentGenerator") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new CurrentGenerator());
            }
        }
        else if(modelName == "SignalGenerator") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new SignalGenerator());
            }
        }
        else if(modelName == "PassThrough") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new PassThrough());
            }
        }
    }

    Population(int amount, std::string modelName, Parameters* param) {
        numberOfNeurons = amount;
        initialize();
        if(modelName == "iaf") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new LIF(static_cast<LIF_param*>(param)));
            }
        }
        else if(modelName == "izhikevich") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new Izhikevich((long)this, i, static_cast<Izhikevich_param*>(param)));
            }
        }
        else if(modelName == "CurrentGenerator") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new CurrentGenerator(static_cast<CurrentGenerator_param*>(param)));
            }
        }
        else if(modelName == "SignalGenerator") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new SignalGenerator(static_cast<SignalGenerator_param*>(param)));
            }
        }
        else if(modelName == "PassThrough") {
            for(int i = 0; i < amount; i++) {
                neurons.push_back(new PassThrough(static_cast<PassThrough_param*>(param)));
            }
        }
        else {
            // TODOS throw exception
        }
    }

    virtual void update() {
        while(current_time < clock->getCurrentTime()) {
            resetOutput();
            for(int i = 0; i < numberOfNeurons; i++) {
                output[i] = neurons[i]->update(clock->getDt());
                logger->logEvent((long)this, i, output[i]->type);
                neurons[i]->resetInput();
            }
            current_time += clock->getDt();
        }
    }

    virtual int getNumberOfNeurons() {
        return numberOfNeurons;
    }

    virtual std::vector<Event*> getEvents() {
        return output;
    }

    void initialize() {
        output = std::vector<Event*>(numberOfNeurons, NULL);
        clock = Clock::getInstance();
        logger = Logging::getInstance();
    }

    void resetOutput() {
        for(int i = 0; i < output.size(); i++) {
            if(output[i]) {
                delete output[i];
                output[i] = NULL;
            }
        }
    }

    virtual void setInput(int neuronIndex, Event* e) {
        if(neuronIndex < 0 || neuronIndex >= neurons.size()) {
            std::cout << "Index of input neuron out of range!" << std::endl;
            throw "Index of input neuron out of range!";
        }
        neurons[neuronIndex]->handleEvent(e);

    }

    virtual ~Population() {};

    std::vector<Event*> output;
    int numberOfNeurons;
    std::vector<Neuron*> neurons;
    double current_time;
    Clock* clock;
    Logging* logger;

private:

};
