add_library(maplibre-native SHARED MapLibre.cpp)
target_link_libraries(maplibre-native PRIVATE mbgl-core mbgl-compiler-options)
