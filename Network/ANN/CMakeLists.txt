add_library (ANN ANN.h ANN.cpp Layer.h Dense.h Dense.cpp activation_functions.h activation_functions.cpp)

target_link_libraries(ANN Network)
