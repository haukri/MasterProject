add_library (ANN ANN.h ANN.cpp Layer.h Dense.h Dense.cpp)

target_link_libraries(ANN Network)
