cmake_minimum_required(VERSION 2.8.9)
project(MasterProject)

SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
 
add_subdirectory(Network)
add_subdirectory(Test)
add_subdirectory(Eigen)