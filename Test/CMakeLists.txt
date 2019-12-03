add_executable (annTest main.cpp)
add_executable (neuronTest neuronTest.cpp)
add_executable (networkTest networkTest.cpp)

target_link_libraries (annTest Network)
target_link_libraries (neuronTest Network)
target_link_libraries (networkTest Network)