cmake_minimum_required(VERSION 3.10)
project(opencv_test1)

find_package(OpenCV REQUIRED highgui imgproc core )


set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp)
add_executable(opencv_test1 ${SOURCE_FILES})
target_link_libraries(opencv_test1 ${OpenCV_LIBS}) 
