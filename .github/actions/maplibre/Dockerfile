FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install --yes \
    build-essential libgl-dev cmake libcurl4-gnutls-dev \
    libjpeg-dev libpng-dev zlib1g-dev pkg-config libglfw3-dev libuv1-dev llvm clang \
    libicu-dev openjdk-8-jdk maven xvfb git

COPY compile.sh /usr/bin/compile.sh
RUN chmod a+x /usr/bin/compile.sh

ENTRYPOINT [ "/usr/bin/compile.sh" ]
