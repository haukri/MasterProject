add_library (Network Network.h Network.cpp)

add_subdirectory(ANN)
add_subdirectory(Neuron)
add_subdirectory(Population)
add_subdirectory(Synapse)

target_link_libraries(Network ANN Neuron Population Synapse)