# ベースイメージとして Debian を使用
FROM mcr.microsoft.com/vscode/devcontainers/base:bullseye

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
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
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# GoogleTest のインストール
RUN git clone https://github.com/google/googletest.git /tmp/googletest \
    && cd /tmp/googletest \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr . \
    && make -j$(nproc) \
    && make install \
    && rm -rf /tmp/googletest

# Lizard と FlawFinder をインストールします
RUN pip3 install lizard flawfinder