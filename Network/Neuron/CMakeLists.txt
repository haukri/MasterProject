add_library(Neuron Neuron.h LIF.h LIF.cpp Izhikevich.h Izhikevich.cpp CurrentGenerator.h CurrentGenerator.cpp)

target_link_libraries(Neuron Network)
