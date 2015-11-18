cmake_minimum_required(VERSION 3.3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

project(TDOA-net)

add_subdirectory(googletest/googlemock)
#add_subdirectory(googletest/googletest)
include_directories(SYSTEM googletest/googletest/include)
include_directories(SYSTEM googletest/googlemock/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wpedantic -Wextra ")
include_directories (${CMAKE_SOURCE_DIR}/..)

add_executable(TDOA-net
		TDOA-net.cpp
		TDOAEstimatePosition.h)

add_executable(TDOAEstimatePosition_unittest
		${GTestLib}
		test/TDOAEstimatePosition_unittest.cpp
       TDOAEstimatePosition.h
		)

target_link_libraries(TDOAEstimatePosition_unittest gmock gmock_main)

