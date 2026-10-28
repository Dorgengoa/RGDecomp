#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Fetch the DirectX Shader Compiler (DXC) release that builds the Vulkan backend's SPIR-V shaders
(docs/NATIVE-VULKAN.md "Shaders").  DXC is a build tool only (NCSA / Apache-2.0 WITH LLVM-exception,
permissive); nothing of it is linked or shipped.  The Windows SDK's dxc.exe is built without SPIR-V
code generation, so the GitHub release is used.

    python tools/native/fetch_dxc.py [--dest ../tools/dxc]

Downloads the pinned archive (SHA-256 checked) to ../tools/dl and unpacks it to DEST; prints
the dxc path to pass as -DRG_DXC=... (the CMake also searches DEST/bin/x64 by default).
On Linux use the distribution's `directx-shader-compiler` / the Vulkan SDK's dxc, or the linux
archive below (`--linux`).
"""
import argparse
import hashlib
import sys
import tarfile
import urllib.request
import zipfile
from pathlib import Path

REL = "https://github.com/microsoft/DirectXShaderCompiler/releases/download/v1.9.2609/"
PKG = {
    "win": ("dxc_2026_09_29.zip", "ad31b1fc8443175d204f77a611fdb3ef2ec42759bdc2f1167368de24a4a7e7f1"),
    "linux": ("linux_dxc_2026_09_28.x86_x64.tar.gz", "96faadc7f5c282d2ffda49804beb4c3ee38127bc252b723234e3c5cdf7aa39a1"),
}

ap = argparse.ArgumentParser()
ap.add_argument("--dest", default="../tools/dxc")
ap.add_argument("--dl", default="../tools/dl")
ap.add_argument("--linux", action="store_true")
o = ap.parse_args()
name, sha = PKG["linux" if o.linux else "win"]
dl = Path(o.dl)
dl.mkdir(parents=True, exist_ok=True)
arc = dl / name
if not arc.exists() or hashlib.sha256(arc.read_bytes()).hexdigest() != sha:
    print(f"downloading {REL + name}")
    urllib.request.urlretrieve(REL + name, arc)
got = hashlib.sha256(arc.read_bytes()).hexdigest()
if got != sha:
    sys.exit(f"{arc}: SHA-256 {got} != pinned {sha}")
dest = Path(o.dest)
dest.mkdir(parents=True, exist_ok=True)
if name.endswith(".zip"):
    with zipfile.ZipFile(arc) as z:
        z.extractall(dest)
    exe = dest / "bin" / "x64" / "dxc.exe"
else:
    with tarfile.open(arc) as t:
        t.extractall(dest)
    exe = dest / "bin" / "dxc"
print(f"dxc: {exe}" if exe.exists() else f"unpacked to {dest} (dxc not at {exe}; look under it)")
