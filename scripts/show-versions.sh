#!/usr/bin/env bash
set -euo pipefail
for tool in gcc g++ clang++ cmake clang-format clang-tidy cppcheck; do
  "$tool" --version | sed -n '1p'
done
