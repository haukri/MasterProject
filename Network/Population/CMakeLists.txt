add_library (Population Population.h SpikingPopulation.h SpikingPopulation.cpp ArtificialPopulation.h ArtificialPopulation.cpp)

target_link_libraries(Population Network)
