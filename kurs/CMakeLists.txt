cmake_minimum_required(VERSION 3.10)
project(kurs)

find_package(OpenCV REQUIRED highgui imgproc core )


set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp 3dparty/cvui.h 3dparty/FastNoise.h 3dparty/FastNoise.cpp 3dparty/tinyxml2/tinyxml2.h 3dparty/tinyxml2/tinyxml2.cpp)
add_executable(kurs  ${SOURCE_FILES})
target_link_libraries(kurs ${OpenCV_LIBS}) 
