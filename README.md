# MapLibre Java

This proof of concept enables headless map rendering with maplibre-gl-native from Java on Linux and MacOS. 

## Prerequisites

### Ubuntu

The following packages are required on Ubuntu 18.04:

```
apt-get update && \
    apt-get install -y build-essential libgl-dev cmake libcurl4-gnutls-dev \
    libjpeg-dev libpng-dev zlib1g-dev pkg-config libglfw3-dev libuv1-dev llvm clang \
    libicu-dev openjdk-8-jdk maven xvfb git
```

For headless rendering (server or container), you also need to start a display server:

```
export DISPLAY=:99
Xvfb ${DISPLAY} -screen 0 "1024x768x24" -ac +extension GLX +render -noreset -nolisten tcp &
```

The `docker` directory contains an image that replicates this configuration, including the display server.

```
cd docker
docker build . --tag maplibre-java
docker run -ti maplibre-java /bin/bash
```

A mesa bug prevent to render maps with Ubuntu 20.04. Help is welcome to solve this issue!

### MacOS

The following packages are required on MacOS:

```
brew install cmake ccache glfw ninja pkgconfig qt
```

## Building from source

The following commands install and build the sources of maplibre-java:

```
git clone https://github.com/baremaps/maplibre-java.git
cd maplibre-java
git submodule update --init --recursive
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build . --config Release
mvn clean install
```

The file `target/maplibre-java.jar` should have been created upon  successful completion.

## Execute



The following command should render a map in a file named `map.png` in the current directory.

```
java -cp target/maplibre-java.jar com.baremaps.maplibre.MapLibre
```

