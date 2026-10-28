#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Configure, build and test the port natively on Linux / WSL (i686 via -m32).
# docs/LINUX.md.  Usage:
#   tools/build-linux.sh [--clean] [--no-test] [extra cmake -D args...]
# Build dir: $RG_BUILD_DIR, default ~/rgport-build/linux-i686 (on the Linux
# file system: much faster than /mnt/<drive> under WSL, and it keeps the
# Windows build dirs under build/ untouched).
set -eu
here=$(cd "$(dirname "$0")/.." && pwd)
build=${RG_BUILD_DIR:-$HOME/rgport-build/linux-i686}
clean=0
test=1
while [ $# -gt 0 ]; do
  case "$1" in
    --clean) clean=1; shift ;;
    --no-test) test=0; shift ;;
    *) break ;;
  esac
done
for t in clang clang++ cmake ninja; do
  command -v "$t" >/dev/null 2>&1 || { echo "missing: $t (docs/LINUX.md)" >&2; exit 1; }
done
[ "$clean" = 1 ] && rm -rf "$build"
cmake -S "$here" -B "$build" -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$here/cmake/toolchain-linux-i686.cmake" \
  -DCMAKE_BUILD_TYPE=Release "$@"
cmake --build "$build"
"$build/rg-smoke"
if [ "$test" = 1 ]; then
  ctest --test-dir "$build" -j"$(nproc)" --output-on-failure
fi
