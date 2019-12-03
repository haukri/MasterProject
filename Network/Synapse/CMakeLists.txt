add_library (Synapse Synapse.h Synapse.cpp StaticSynapse.h StaticSynapse.cpp)

target_link_libraries(Synapse Network)
