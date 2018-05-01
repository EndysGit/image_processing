cmake_minimum_required(VERSION 3.10)
project(noise)

find_package(OpenCV REQUIRED)
find_package(wxWidgets COMPONENTS core base REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${OpenCV_INCLUDE_DIRS} )
include( "${wxWidgets_USE_FILE}" )

set(SOURCE_FILES Window.cpp 3dparty/FastNoise.h 3dparty/FastNoise.cpp)
add_executable(noise  ${SOURCE_FILES})
target_link_libraries(noise ${OpenCV_LIBS} ${wxWidgets_LIBRARIES}) 
