cmake_minimum_required(VERSION 3.10)
project(noise)

find_package(OpenCV REQUIRED highgui imgproc core )


set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp FastNoise.h FastNoise.cpp)
add_executable(noise  ${SOURCE_FILES})
target_link_libraries(noise ${OpenCV_LIBS}) 
