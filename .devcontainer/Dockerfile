# ベースイメージとして軽量な Debian Slim を使用
FROM debian:bullseye-slim

# 必要なパッケージをインストール
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    software-properties-common \
    build-essential \
    gcc \
    g++ \
    gdb \
    cmake \
    clang \
    clang-format \
    python3 \
    python3-pip \
    git \
    cppcheck \
    libssl-dev \
    libgtest-dev \
    libboost-all-dev \
    wget \
    pkg-config \
    meson \
    libcairo2-dev \
    libgirepository1.0-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# PyYAMLをAPTで削除
RUN apt-get remove --purge -y python3-yaml

# pip のアップデート
RUN pip3 install --upgrade pip
# 必要なPythonパッケージのアップデート
RUN python3 -m pip install \
    mako==1.2.2 \
    pyyaml==5.4 \
    setuptools==65.5.1 \
    wheel==0.38.1 \
    lizard \
    flawfinder

# GoogleTest のインストール
RUN git clone https://github.com/google/googletest.git /tmp/googletest \
    && cd /tmp/googletest \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr . \
    && make -j$(nproc) \
    && make install \
    && rm -rf /tmp/googletest
