#!/usr/bin/env bash
set -euo pipefail
bash "$(dirname "$0")/show-versions.sh"
for compiler in g++ clang++; do
  build_dir="build-${compiler//+/p}"
  cmake -S . -B "$build_dir" -DCMAKE_CXX_COMPILER="$compiler" -DCMAKE_BUILD_TYPE=Debug
  cmake --build "$build_dir" --parallel 2
  ctest --test-dir "$build_dir" --no-tests=error --output-on-failure
done
