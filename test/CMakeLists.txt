cmake_minimum_required(VERSION 3.10)
project(test_kr)

find_package(OpenCV REQUIRED highgui imgproc core )


set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp)
add_executable(test_kr  ${SOURCE_FILES})
target_link_libraries(test_kr ${OpenCV_LIBS}) 
