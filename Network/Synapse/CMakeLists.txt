add_library (Synapse Synapse.h StaticSynapse.h StaticSynapse.cpp RateCodingSynapse.h RateCodingSynapse.cpp)

target_link_libraries(Synapse Network)
