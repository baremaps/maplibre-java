# MapLibre Java

This proof of concept enables headless map rendering with maplibre-gl-native from Java. 

```
git clone https://github.com/baremaps/maplibre-java.git
cd maplibre-java
git submodule update --init --recursive
cmake .
cmake --build .
mvn clean install
java -cp target/maplibre-java.jar com.baremaps.maplibre.MapLibre
```