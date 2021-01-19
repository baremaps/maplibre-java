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
    add_jar(maplibre java/com/baremaps/maplibre/MapLibre.java native/libmaplibrenative.so)
endif()

if(APPLE)
    add_jar(maplibre java/com/baremaps/maplibre/MapLibre.java native/libmaplibrenative.dylib)
endif()
    
if (WIN32)
    add_jar(maplibre java/com/baremaps/maplibre/MapLibre.java native/maplibrenative.dll)
endif()

add_dependencies(maplibre maplibrenative)
