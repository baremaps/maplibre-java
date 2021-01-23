FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
ENV DISPLAY :99

RUN apt-get update
RUN apt-get install --yes apt-transport-https ca-certificates gnupg software-properties-common wget

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
RUN apt-get update

RUN apt-get install --yes cmake cmake-data
RUN apt-get install --yes curl git build-essential zlib1g-dev automake libtool xutils-dev make cmake pkg-config python3-pip libcurl4-openssl-dev libpng-dev libsqlite3-dev libllvm3.9
RUN apt-get install --yes libjpeg-dev libuv1-dev libglfw3-dev libxi-dev libglu1-mesa-dev x11proto-randr-dev x11proto-xext-dev libxrandr-dev x11proto-xf86vidmode-dev libxxf86vm-dev libxcursor-dev libxinerama-dev
RUN apt-get install --yes openjdk-8-jdk maven

RUN apt-get --yes install libegl1-mesa-dev libgles2-mesa-dev libcairo2-dev libgbm-dev libllvm3.9 xvfb x11-utils icu-devtools libicu-dev

ADD display.sh /display.sh
RUN chmod a+x /display.sh

ENTRYPOINT bash /display.sh && /bin/bash
