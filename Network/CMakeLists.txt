add_library (Network Network.h Network.cpp)

add_subdirectory(ANN)

target_link_libraries(Network ANN)