# syntax=docker/dockerfile:1
FROM debian:trixie-slim

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Optional CA bundle for managed build proxies; never persisted in an image layer.
RUN --mount=type=secret,id=proxy_ca \
    set -eu; \
    if [ -f /run/secrets/proxy_ca ]; then \
      export SSL_CERT_FILE=/run/secrets/proxy_ca; \
      printf 'Acquire::https::CaInfo "/run/secrets/proxy_ca";\n' > /etc/apt/apt.conf.d/99-build-ca; \
    fi; \
    apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends \
      ca-certificates sudo build-essential gdb cmake ninja-build \
      clang clang-format clang-tidy lldb git cppcheck \
      libssl-dev libgtest-dev libboost-dev curl pkg-config \
    && rm -rf /var/lib/apt/lists/* /etc/apt/apt.conf.d/99-build-ca

# GoogleTest is installed once, from Debian's security-maintained package set.
# No pip into the system interpreter and no second source installation.
RUN groupadd --gid "$USER_GID" "$USERNAME" \
    && useradd --uid "$USER_UID" --gid "$USER_GID" -m -s /bin/bash "$USERNAME" \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/"$USERNAME" \
    && chmod 0440 /etc/sudoers.d/"$USERNAME"
USER $USERNAME
