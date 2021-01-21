cmake_minimum_required(VERSION 3.17)

project(maplibre)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

include_directories(${JNI_INCLUDE_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/maplibre-gl-native EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/native)
