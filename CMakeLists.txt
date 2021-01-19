cmake_minimum_required(VERSION 3.17)

project(maplibre)

set(CMAKE_CXX_STANDARD 14)

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

include_directories(${JNI_INCLUDE_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/maplibre-gl-native EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/native)

if(UNIX AND NOT APPLE)
    add_jar(maplibre-linux java/com/baremaps/maplibre/MapLibre.java native/libmaplibre-native.so)
    add_dependencies(maplibre-linux maplibre-native)
endif()

if(APPLE)
    add_jar(maplibre-macos java/com/baremaps/maplibre/MapLibre.java native/libmaplibre-native.dylib)
    add_dependencies(maplibre-macos maplibre-native)
endif()
