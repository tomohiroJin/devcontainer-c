#!/usr/bin/env bash
set -euo pipefail
for tool in gcc g++ clang++ cmake clang-format clang-tidy cppcheck; do
  "$tool" --version | head -n 1
done
for compiler in g++ clang++; do
  build_dir="build-${compiler//+/p}"
  cmake -S . -B "$build_dir" -DCMAKE_CXX_COMPILER="$compiler" -DCMAKE_BUILD_TYPE=Debug
  cmake --build "$build_dir" --parallel 2
  ctest --test-dir "$build_dir" --output-on-failure
done
