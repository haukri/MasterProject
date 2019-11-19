add_library (Network Network.h Network.cpp)

add_subdirectory(ANN)
add_subdirectory(Neuron)

target_link_libraries(Network ANN)