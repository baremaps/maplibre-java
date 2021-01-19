# MapLibre Java

This proof of concept renders maps from Java with maplibre-gl-native. It builds on linux and macOS

```
git submodule update --init --recursive
cmake .
cmake --build .
javac MapLibre.java
javah MapLibre
java MapLibre
```