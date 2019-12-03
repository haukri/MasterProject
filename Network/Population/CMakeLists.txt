add_library (Population Population.h SpikingPopulation.h SpikingPopulation.cpp)

target_link_libraries(Population Network)
