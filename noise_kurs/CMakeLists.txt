cmake_minimum_required(VERSION 3.10)
project(noise)

find_package(wxWidgets COMPONENTS core base REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -stdlib=libc++ -std=c++14")
set(CMAKE_WXWINDOWS_CXX_FLAGS "wx-config -static=yes")
set(INCLUDE_DIRS "include")
add_subdirectory(3dparty)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include( "${wxWidgets_USE_FILE}" )
include_directories(${INCLUDE_DIRS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(noise MACOSX_BUNDLE ${SRC_FILES} ${INCLUDE_DIRS})

target_link_libraries(noise FastNoise tinyxml2 ${wxWidgets_LIBRARIES}) 


