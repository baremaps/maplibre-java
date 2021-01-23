FROM ubuntu:18.04

ENV DISPLAY :99

RUN apt-get update
RUN apt-get install --yes \
    build-essential libgl-dev cmake libcurl4-gnutls-dev \
    libjpeg-dev libpng-dev zlib1g-dev pkg-config libglfw3-dev libuv1-dev llvm clang \
    libicu-dev openjdk-8-jdk maven xvfb git

ADD display.sh /display.sh
RUN chmod a+x /display.sh

ENTRYPOINT bash /display.sh && /bin/bash
