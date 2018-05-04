cmake_minimum_required(VERSION 3.10)
project(noise)

find_package(wxWidgets COMPONENTS core base REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -stdlib=libc++ -std=c++14 ")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include( "${wxWidgets_USE_FILE}" )

set(SOURCE_FILES Window.cpp 
                 3dparty/FastNoise.h 
                 3dparty/FastNoise.cpp
                 3dparty/tinyxml2.h 
                 3dparty/tinyxml2.cpp)

add_executable(noise  ${SOURCE_FILES})
target_link_libraries(noise ${wxWidgets_LIBRARIES}) 
