#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Vendor the Vulkan backend's third-party headers into third_party/ (docs/NATIVE-VULKAN.md,
THIRD_PARTY_NOTICES.md): the Khronos Vulkan-Headers (Apache-2.0 OR MIT), volk (MIT, the
meta-loader: vulkan-1.dll / libvulkan.so.1 is loaded at run time, so the exe starts without
Vulkan) and the Vulkan Memory Allocator (MIT).  Only the files the build uses plus each
project's license are copied.  Pinned tags and archive SHA-256 below; re-run to re-vendor.

    python tools/native/fetch_vulkan_deps.py [--check]

--check: verify the vendored files against fresh archives (no writes).
"""
import argparse
import hashlib
import io
import sys
import tarfile
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DL = Path("../tools/dl")
# (name, url, sha256 of the archive, {archive path prefix: dest dir}, files (relative to prefix; dirs end with /))
DEPS = [
    ("Vulkan-Headers vulkan-sdk-1.4.363.0",
     "https://codeload.github.com/KhronosGroup/Vulkan-Headers/tar.gz/refs/tags/vulkan-sdk-1.4.363.0",
     None, "third_party/vulkan",
     ["include/vulkan/vulkan.h", "include/vulkan/vulkan_core.h", "include/vulkan/vk_platform.h",
      "include/vk_video/", "LICENSE.md"]),
    ("volk vulkan-sdk-1.4.363.0",
     "https://codeload.github.com/zeux/volk/tar.gz/refs/tags/vulkan-sdk-1.4.363.0",
     None, "third_party/volk", ["volk.h", "volk.c", "LICENSE.md"]),
    ("VulkanMemoryAllocator v3.4.0",
     "https://codeload.github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/tar.gz/refs/tags/v3.4.0",
     None, "third_party/vma", ["include/vk_mem_alloc.h", "LICENSE.txt"]),
]
PINS = ROOT / "third_party" / "VENDORED.txt"

ap = argparse.ArgumentParser()
ap.add_argument("--check", action="store_true")
o = ap.parse_args()
pins = {}
if PINS.exists():
    for line in PINS.read_text().splitlines():
        if line.startswith("#") or not line.strip():
            continue
        k, v = line.rsplit(" ", 1)
        pins[k] = v
DL.mkdir(parents=True, exist_ok=True)
bad = 0
out_pins = []
for name, url, sha, dest, files in DEPS:
    arc = DL / (name.replace(" ", "-") + ".tar.gz")
    if not arc.exists():
        print(f"downloading {url}")
        urllib.request.urlretrieve(url, arc)
    data = arc.read_bytes()
    got = hashlib.sha256(data).hexdigest()
    want = sha or pins.get(name)
    if want and want != got:
        sys.exit(f"{name}: archive SHA-256 {got} != pinned {want}")
    out_pins.append(f"{name} {got}")
    with tarfile.open(fileobj=io.BytesIO(data)) as t:
        members = t.getmembers()
        top = members[0].name.split("/")[0]
        for m in members:
            if not m.isfile():
                continue
            rel = m.name[len(top) + 1:]
            if not any(rel == f or (f.endswith("/") and rel.startswith(f)) for f in files):
                continue
            # flatten "include/" (third_party/vulkan/include/vulkan/..., third_party/vma/vk_mem_alloc.h)
            sub = rel
            if dest.endswith("vma") and rel.startswith("include/"):
                sub = rel[len("include/"):]
            p = ROOT / dest / sub
            body = t.extractfile(m).read()
            if o.check:
                if not p.exists() or p.read_bytes() != body:
                    print(f"DIFFERS: {p}")
                    bad += 1
            else:
                p.parent.mkdir(parents=True, exist_ok=True)
                p.write_bytes(body)
    print(f"{name}: {'checked' if o.check else 'vendored'} -> {dest} (archive sha256 {got})")
if not o.check:
    PINS.write_text("# tools/native/fetch_vulkan_deps.py: vendored archives and their SHA-256\n" +
                    "\n".join(out_pins) + "\n")
sys.exit(1 if bad else 0)
