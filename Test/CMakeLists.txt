add_executable (networkTest main.cpp)
add_executable (neuronTest neuronTest.cpp)

target_link_libraries (networkTest Network)
target_link_libraries (neuronTest Network)