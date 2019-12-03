add_library(Neuron Neuron.h LIF.h LIF.cpp)

target_link_libraries(Neuron Network)
