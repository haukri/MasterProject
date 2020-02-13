add_library (Synapse Synapse.h StaticSynapse.h StaticSynapse.cpp RateCodingSynapse.h RateCodingSynapse.cpp BSA_SpikeEncodingSynapse.h BSA_SpikeEncodingSynapse.cpp)

target_link_libraries(Synapse Network)
