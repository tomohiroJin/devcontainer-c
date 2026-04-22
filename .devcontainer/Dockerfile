# ベースイメージとして Debian bookworm を使用（bullseye は 2026/06 頃 EOL 予定のため）
FROM debian:bookworm-slim

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive

# 必要なパッケージをインストール
# - build-essential / gcc-12 / g++-12 / clang-16 系は bookworm で利用可能な最新世代
# - libssl-dev は bookworm 以降 OpenSSL 3.x
RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends \
    ca-certificates \
    sudo \
    build-essential \
    gcc-12 \
    g++-12 \
    gdb \
    cmake \
    clang-16 \
    clang-format-16 \
    clang-tidy-16 \
    lldb-16 \
    python3 \
    python3-pip \
    git \
    cppcheck \
    libssl-dev \
    libgtest-dev \
    libboost-all-dev \
    wget \
    curl \
    pkg-config \
    meson \
    && rm -rf /var/lib/apt/lists/*

# GCC / Clang の既定バージョンを明示的に設定
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-16 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang-16 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-16 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-16 100

# Python パッケージを最新化（PEP 668 対応のため --break-system-packages を許容）
RUN python3 -m pip install --no-cache-dir --break-system-packages --upgrade pip \
    && python3 -m pip install --no-cache-dir --break-system-packages \
        'mako>=1.3' \
        'pyyaml>=6.0.2' \
        'setuptools>=75' \
        'wheel>=0.44' \
        lizard \
        flawfinder

# Google Test を固定タグでインストール
RUN git clone --depth 1 --branch v1.15.2 https://github.com/google/googletest.git /tmp/googletest \
    && cmake -S /tmp/googletest -B /tmp/googletest/build -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release \
    && cmake --build /tmp/googletest/build -j"$(nproc)" \
    && cmake --install /tmp/googletest/build \
    && rm -rf /tmp/googletest

# 非 root ユーザー vscode を作成し sudo 権限を付与
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m -s /bin/bash $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME
