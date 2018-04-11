cmake_minimum_required(VERSION 3.10)
project(lab1)

find_package(OpenCV REQUIRED highgui imgproc core )


set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp)
add_executable(lab1  ${SOURCE_FILES})
target_link_libraries(lab1 ${OpenCV_LIBS}) 
