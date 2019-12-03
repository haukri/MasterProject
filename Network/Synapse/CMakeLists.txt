add_library (Synapse Synapse.h StaticSynapse.h StaticSynapse.cpp)

target_link_libraries(Synapse Network)
