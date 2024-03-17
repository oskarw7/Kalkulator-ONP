FROM ubuntu:latest

LABEL authors="oskarwisniewski"

RUN apt-get update
RUN apt-get install -y build-essential cmake pkg-config git ninja-build valgrind nano gdb

RUN git clone https://github.com/jbeder/yaml-cpp
RUN mkdir -p  yaml-cpp/build && cd yaml-cpp/build
WORKDIR "yaml-cpp/build"
RUN cmake cmake -DCMAKE_CXX_FLAGS="-std=c++20"   -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ../ && cmake --build .  --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf yaml-cpp