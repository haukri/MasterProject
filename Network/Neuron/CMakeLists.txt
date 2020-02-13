add_library(Neuron Neuron.h LIF.h LIF.cpp Izhikevich.h Izhikevich.cpp CurrentGenerator.h CurrentGenerator.cpp SignalGenerator.h SignalGenerator.cpp PassThrough.h PassThrough.cpp)

target_link_libraries(Neuron Network)
