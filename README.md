# MapLibre Java

This proof of concept renders maps from Java with maplibre-gl-native.

```
git submodule update --init --recursive
cmake --build .
javac MapLibre.java
javah MapLibre
java MapLibre
```