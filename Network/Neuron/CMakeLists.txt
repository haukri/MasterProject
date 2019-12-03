add_library(Neuron Neuron.h LIF.h LIF.cpp Izhikevich.h Izhikevich.cpp)

target_link_libraries(Neuron Network)
