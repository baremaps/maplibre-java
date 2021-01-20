# MapLibre Java

This proof of concept enables headless map rendering with maplibre-gl-native from Java. 

```
git clone git@github.com:baremaps/maplibre-java.git
cd maplibre-java
git submodule update --init --recursive
cmake .
cmake --build .
java -cp maplibre-{linux|macos}.jar com.baremaps.maplibre.MapLibre
```