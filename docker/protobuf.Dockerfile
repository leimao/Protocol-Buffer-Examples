FROM ubuntu:20.04

LABEL maintainer="Lei Mao <dukeleimao@gmail.com>"

ARG PROTOBUF_VERSION=3.14.0
ARG NUM_JOBS=8

ENV DEBIAN_FRONTEND noninteractive

# Install package dependencies
RUN apt-get update 
RUN apt-get install -y --no-install-recommends \
        build-essential \
        software-properties-common \
        autoconf \
        automake \
        libtool \
        pkg-config \
        ca-certificates \
        wget \
        git \
        curl \
        vim \
        gdb \
        valgrind \
        cmake
RUN apt-get clean

RUN cd /tmp && \
    apt-get install -y autoconf automake libtool curl make g++ unzip && \
    wget https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-cpp-${PROTOBUF_VERSION}.tar.gz && \
    tar xvzf protobuf-cpp-${PROTOBUF_VERSION}.tar.gz && \
    cd protobuf-${PROTOBUF_VERSION} && \
    ./configure && \
    make -j${NUM_JOBS} && \
    make check -j${NUM_JOBS} && \
    make install -j${NUM_JOBS} && \
    ldconfig
