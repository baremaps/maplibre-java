cmake_minimum_required(VERSION 3.17)

project(maplibre)

set(CMAKE_CXX_STANDARD 14)

find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS})

add_library(maplibre SHARED MapLibre.h MapLibre.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/maplibre-gl-native EXCLUDE_FROM_ALL)

target_link_libraries(maplibre PRIVATE mbgl-core mbgl-compiler-options)

install(TARGETS maplibre DESTINATION .)
