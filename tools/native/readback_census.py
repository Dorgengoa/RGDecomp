#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of the renderer -> game-logic data flows (docs/NATIVE-RENDER.md "Renderer -> logic
data flows"; history 2026-11-01 (renderdep)).

    python tools/native/readback_census.py [--check] [-v]

The game can only learn something from the GS / renderer through a few doors.  This lists every
site of them, in the compiled game set (game/src, overrides/src: an override replaces the game
file of the same stem) and in the port's runtime (src/):

  game side   sceGsExecStoreImage / GsDownloadImage_140f20 (local->host image read-backs),
              rg_gs_reg_r64 / rg_gs_priv_r64 (GS privileged registers: CSR, PMODE, DISPFBn,
              ...), sceGsSyncPath / sceGsSyncV (waits on the GS: timing only, no data);
  runtime     who serves them: assignments of rg_gs_store_hook, calls of gs_read_fifo /
              gpu_mem_read / gs_read_priv (the producers behind the game-side doors).

Each site must be on the allowlist below with its class:
  DATA-LOGIC  renderer data that reaches game state (a renderless build must reproduce it);
  DATA-VISUAL renderer data that only goes back to the screen (captures re-uploaded as textures);
  REG         a register the port derives from deterministic state (vsync count, own writes);
  SYNC        a wait (no data: deterministic in headless runs, the worker drained);
  SERVE       a runtime producer (must exist in every build kind, rendered AND renderless).
--check exits 1 when a site is not on the list (a NEW renderer -> logic door: classify it, and
if it carries data make sure renderless builds serve it the same way) or when a listed site is
gone (stale entry); --inject adds a fake unlisted site (the control: must fail).  Pure text scan, ~4 s.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

GAME_API = re.compile(r"\b(sceGsExecStoreImage|GsDownloadImage_140f20|rg_gs_reg_r64|rg_gs_priv_r64|"
                      r"sceGsSyncPath(?:_109030)?|sceGsSyncV)\s*\(")
RT_API = re.compile(r"\b(rg_gs_store_hook\s*=(?!=)|gs_read_fifo\s*\(|gpu_mem_read\s*\(|gs_read_priv\s*\()")
DECL = re.compile(r"^\s*(extern|asm|(?:static\s+)?(?:inline\s+)?(?:void|int|s32|u32|u64|uint32_t|uint64_t|"
                  r"unsigned(?:\s+long)*|long)\b[^=;]*\b\w+\s*\([^)]*\)\s*[;{]?\s*$)")

# (stem, api): (class, why)
GAME_ALLOW = {
    ("GfxEndFrame_141c20", "sceGsExecStoreImage"):
        ("DATA-LOGIC", "lens-flare 8x8 Z probe -> slot z; renderless: runtime.c sw_store (software GS)"),
    ("GfxEndFrame_141c20", "sceGsSyncPath_109030"): ("SYNC", "after the probe read"),
    ("GsDownloadImage_140f20", "sceGsExecStoreImage"):
        ("DATA-VISUAL", "screen capture for ScreenFadeBlockCaptureFrame / MenuCaptureScreenTex"),
    ("GsDownloadImage_140f20", "sceGsSyncPath_109030"): ("SYNC", "after the capture"),
    ("ScreenFadeBlockCaptureFrame_177ed0", "GsDownloadImage_140f20"):
        ("DATA-VISUAL", "fade capture: pixels re-uploaded as a texture"),
    ("MenuCaptureScreenTex_298810", "GsDownloadImage_140f20"):
        ("DATA-VISUAL", "menu background capture: pixels re-uploaded as a texture"),
    ("GfxVblankStartHandler_15df20", "rg_gs_reg_r64"):
        ("REG", "CSR.FIELD: from the vsync count (nr_hw.c / gs model), not from drawing"),
    ("SysInitHardware_15e670", "rg_gs_reg_r64"): ("REG", "PMODE read-modify-write of its own value"),
    ("SysInitHardware_15e670", "sceGsSyncV"): ("SYNC", "boot"),
    ("GsDbufPutEnv_144150", "rg_gs_reg_r64"): ("REG", "PMODE / DISPFB1 / DISPLAY1: the game's own writes"),
    ("GsDbufPutEnv_144150", "sceGsSyncV"): ("SYNC", "display switch"),
    ("GsClearDoubleBuffers_15e600", "sceGsSyncV"): ("SYNC", "clear"),
    ("GsClearDoubleBuffers_15e600", "sceGsSyncPath_109030"): ("SYNC", "clear"),
    ("GfxSetVideoMode_1451f0", "sceGsSyncV"): ("SYNC", "mode set"),
    ("GfxSetVideoMode_1451f0", "sceGsSyncPath_109030"): ("SYNC", "mode set"),
    ("FixedTexUploadImpl_15d680", "sceGsSyncPath_109030"): ("SYNC", "texture upload"),
    ("PadWaitReady_1849e0", "sceGsSyncV"): ("SYNC", "pad wait"),
    ("PadPortOpen_184ed0", "sceGsSyncV"): ("SYNC", "pad open"),
    ("title_TitleSessionInit_4f0cb0", "sceGsSyncV"): ("SYNC", "title"),
}

# (path relative to src/, api): (class, why)
RT_ALLOW = {
    ("native/render/nr_scene.c", "gpu_mem_read"): ("SERVE", "native_store / probe_async: the GPU's depth"),
    ("native/render/nr_scene.c", "gs_read_fifo"): ("SERVE", "native_store, GS-model builds"),
    ("native/render/nr_hw.c", "gs_read_priv"): ("SERVE", "privileged registers, GS-model builds"),
    ("runtime/runtime.c", "rg_gs_store_hook"):
        ("SERVE", "rendered: nr_native_store_fn; renderless: sw_store (the software GS)"),
    ("runtime/runtime.c", "gs_read_fifo"): ("SERVE", "sw_store (renderless builds)"),
    ("ps2/hwbus/hwbus.c", "gs_read_priv"): ("SERVE", "privileged register reads (emulated bus)"),
    ("ps2/dmac/dmac.c", "gs_read_fifo"): ("SERVE", "VIF1 GS->MEM DMA (emulated DMA path)"),
    ("ps2/gs/gs_rec.c", "gs_read_fifo"): ("SERVE", "GS record replay"),
}


def strip_comments(t: str) -> str:
    t = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def game_sites():
    files = {}
    for base in (ROOT / "game/src", ROOT / "overrides/src"):   # overrides win (later)
        for p in base.rglob("*"):
            if p.suffix in (".c", ".cpp") and "_data" not in p.parent.name:
                files[p.stem] = p
    out = {}
    for stem, p in files.items():
        try:
            t = p.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if not GAME_API.search(t):
            continue
        for i, ln in enumerate(strip_comments(t).splitlines(), 1):
            for m in GAME_API.finditer(ln):
                if DECL.match(ln) or stem == m.group(1):   # (a declaration / the SDK stub itself)
                    continue
                out.setdefault((stem, m.group(1)), []).append(f"{p.relative_to(ROOT).as_posix()}:{i}")
    return out


def rt_sites():
    out = {}
    src = ROOT / "src"
    for p in src.rglob("*"):
        if p.suffix not in (".c", ".cpp") or "sce" in p.relative_to(src).parts[:1]:
            continue
        t = p.read_text(encoding="utf-8", errors="replace")
        if not RT_API.search(t):
            continue
        rel = p.relative_to(src).as_posix()
        for i, ln in enumerate(strip_comments(t).splitlines(), 1):
            for m in RT_API.finditer(ln):
                if DECL.match(ln) or re.match(r"^\s*(uint32_t|int)\s+(gs_read_fifo|gpu_mem_read|gs_read_priv)\b", ln):
                    continue
                api = re.match(r"\w+", m.group(1)).group(0)
                out.setdefault((rel, api), []).append(f"src/{rel}:{i}")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("-v", action="store_true", help="print every site")
    ap.add_argument("--inject", action="store_true", help="control: add a fake unlisted read-back site")
    a = ap.parse_args()
    bad = 0
    gs = game_sites()
    if a.inject:
        gs[("InjectedProbe_000000", "sceGsExecStoreImage")] = ["(injected)"]
    for title, sites, allow in (("game", gs, GAME_ALLOW), ("runtime", rt_sites(), RT_ALLOW)):
        print(f"== {title}: {len(sites)} (site, api) pairs")
        for key in sorted(sites):
            cls, why = allow.get(key, ("NEW", "not classified: a new renderer -> logic door?"))
            if cls == "NEW":
                bad += 1
            print(f"  {cls:11s} {key[0]:40s} {key[1]:22s} {why}")
            if a.v or cls == "NEW":
                for s in sites[key]:
                    print(f"      {s}")
        for key in sorted(set(allow) - set(sites)):
            # a device implementation may be absent from this checkout (other backends)
            if title == "runtime" and not (ROOT / "src" / key[0]).exists():
                continue
            bad += 1
            print(f"  STALE       {key[0]:40s} {key[1]:22s} (listed, not found: update the allowlist)")
    print(f"{'FAIL' if bad else 'ok'}: {bad} unclassified / stale")
    return 1 if (a.check and bad) else 0


if __name__ == "__main__":
    sys.exit(main())
