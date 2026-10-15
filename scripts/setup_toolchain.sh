#!/bin/sh
# Download and install everything the build needs on a Linux x86-64 machine
# (or WSL). Run it on the build host -- with RGD_HOST=local that is this machine.
#
#   sh scripts/setup_toolchain.sh
#
# Installs, each checked against a pinned SHA-256:
#   tools/binutils/            decompals MIPS binutils (Linux), for this repository
#   $RGD_REMOTE_DIR/wibo       decompals wibo (runs the Windows compilers)
#   $RGD_REMOTE_DIR/mwcps2-3.0.1b210-060308/   Metrowerks mwccps2 / mwldps2
#   $RGD_EEGCC/sony29/         Sony ee-gcc 2.9-ee-991111-01
#   $RGD_EEGCC/cc1.sh          launcher for ee-gcc's 32-bit i386 programs
#
# ee-gcc needs the i386 C runtime: either install it system-wide
# (Debian/Ubuntu: `sudo dpkg --add-architecture i386 && sudo apt install libc6:i386`),
# or set RGD_I386_ROOT to a directory holding a private copy
# (<root>/usr/lib/i386-linux-gnu/ld-linux.so.2 and its libraries).
set -eu

ROOT=$(cd "$(dirname "$0")/.." && pwd)
REMOTE=$(eval echo "${RGD_REMOTE_DIR:-~/rgd}")
EEGCC=$(eval echo "${RGD_EEGCC:-\$HOME/eegcc}")
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

fetch() { # url sha256 -> $TMP/<name>
    f="$TMP/$(basename "$1")"
    echo "  downloading $(basename "$1")"
    curl -fsSL -o "$f" "$1"
    echo "$2  $f" | sha256sum -c --quiet - || { echo "checksum mismatch: $1" >&2; exit 1; }
}

C=https://github.com/decompme/compilers/releases/download/compilers
fetch https://github.com/decompals/binutils-mips-ps2-decompals/releases/download/v0.10/binutils-mips-ps2-decompals-linux-x86-64.tar.gz \
      9fe31ea3ee1a37536f9f0e2e12c668e7c3cb99e59f5154bd2f1fc4762473094c
fetch https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64 \
      13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af
fetch $C/mwcps2-3.0.1b210-060308.tar.gz \
      456746b70862a744a0be75585a4e163a142111843661cbb7e483230dd85502c5
fetch $C/ee-gcc2.9-991111-01.tar.xz \
      ed684fd98f89d36b0121caab311052089103e3b36241fcef4338cc9ea41c75b8

mkdir -p "$ROOT/tools/binutils"
tar xzf "$TMP/binutils-mips-ps2-decompals-linux-x86-64.tar.gz" -C "$ROOT/tools/binutils"

mkdir -p "$REMOTE/mwcps2-3.0.1b210-060308"
install -m 755 "$TMP/wibo-x86_64" "$REMOTE/wibo"
tar xzf "$TMP/mwcps2-3.0.1b210-060308.tar.gz" -C "$REMOTE/mwcps2-3.0.1b210-060308"

mkdir -p "$EEGCC/sony29"
tar xJf "$TMP/ee-gcc2.9-991111-01.tar.xz" -C "$EEGCC/sony29"
if [ -n "${RGD_I386_ROOT:-}" ]; then
    L="$RGD_I386_ROOT/usr/lib/i386-linux-gnu"
    printf '#!/bin/sh\nexec %s/ld-linux.so.2 --library-path %s "$@"\n' "$L" "$L" > "$EEGCC/cc1.sh"
elif [ -e /lib/ld-linux.so.2 ]; then
    printf '#!/bin/sh\nexec "$@"\n' > "$EEGCC/cc1.sh"
else
    echo "ee-gcc needs the i386 C runtime -- see the top of this script" >&2
    exit 1
fi
chmod 755 "$EEGCC/cc1.sh"

echo "toolchain ready:"
echo "  tools/binutils/   $REMOTE/{wibo,mwcps2-3.0.1b210-060308}   $EEGCC/{cc1.sh,sony29}"
