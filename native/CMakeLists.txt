add_library(maplibrenative SHARED MapLibre.cpp)
target_link_libraries(maplibrenative PRIVATE mbgl-core mbgl-compiler-options)
install(TARGETS maplibrenative)
