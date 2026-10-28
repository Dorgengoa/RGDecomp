#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare a GPU-renderer run of rg-game against the software-GS reference run.

Both runs are made with the same deterministic input and RG_GS_DUMP_DIR /
RG_GS_DUMP_FIELDS (src/runtime/runtime.c "dump_field"); each field N leaves
fNNNNN_display.png, fNNNNN_local.png, fNNNNN.vram and fNNNNN.regs.
docs/GPU.md "Real game validation".

    python tools/gpu_validate.py REF_DIR GPU_DIR [--diff-dir DIR] [--tag NAME]

Per field:
  display   the presented frame.  Same size: exact %, max channel diff,
            pixels beyond +-2.  Upscaled (GPU size = k x reference): the GPU
            frame box-filtered to native, compared the same way, plus
            "detail" = % of k x k blocks that are not uniform (0 means the
            upscaled frame is the native image replicated), measured on
            fNNNNN_target.png (the displayed buffer at the internal resolution,
            before the PCRTC merge) when present, else (in parentheses) on the
            display.
  local     gs_read_display of local memory after gpu_sync (native write-back).
  vram      differing bytes / differing 8 KB pages of the 4 MB local memory.
  regs      the privileged + general registers and the CLUT must be equal
            (proves the two runs fed the GS the same stream).
Diff images (|a-b| x 8, clipped) go to --diff-dir.
"""
import argparse
import os
import sys

import numpy as np
from PIL import Image


def load_png(p):
    return np.asarray(Image.open(p).convert("RGBA"), dtype=np.int16)


def cmp_img(a, b):
    d = np.abs(a[..., :3] - b[..., :3]).max(axis=2)
    n = d.size
    return {
        "exact": 100.0 * float((d == 0).sum()) / n,
        "max": int(d.max()) if n else 0,
        "beyond2": int((d > 2).sum()),
        "px": n,
    }, d


def box_down(img, k):
    h, w = img.shape[0] // k, img.shape[1] // k
    x = img[: h * k, : w * k].reshape(h, k, w, k, 4).astype(np.int32)
    return (x.sum(axis=(1, 3)) // (k * k)).astype(np.int16)


def block_detail(img, k):
    h, w = img.shape[0] // k, img.shape[1] // k
    x = img[: h * k, : w * k, :3].reshape(h, k, w, k, 3)
    mn = x.min(axis=(1, 3))
    mx = x.max(axis=(1, 3))
    return 100.0 * float((mx != mn).any(axis=2).sum()) / (h * w)


def save_diff(d, path):
    v = np.clip(d.astype(np.int32) * 8, 0, 255).astype(np.uint8)
    Image.fromarray(v, "L").save(path)


# General registers whose defined bits are fewer than the 64 an A+D write
# carries; the game writes some of them with host garbage above (a u64 built
# from a 32-bit value: COLCLAMP 0xa777e800000001 vs 0xb677e800000001), which
# no renderer reads.
REG_BITS = {0x22: 2, 0x3F: 0, 0x45: 1, 0x46: 1, 0x49: 1, 0x4A: 1, 0x4B: 1}


def reg_diff(a, b):
    pa = np.frombuffer(a[:1280], dtype=np.uint64).copy()
    pb = np.frombuffer(b[:1280], dtype=np.uint64).copy()
    for addr, bits in REG_BITS.items():
        m = np.uint64((1 << bits) - 1)
        pa[32 + addr] &= m
        pb[32 + addr] &= m
    out = []
    for i in np.nonzero(pa != pb)[0]:
        out.append(("preg%d" % i) if i < 32 else ("reg 0x%02X" % (i - 32)))
    if a[1280:] != b[1280:]:
        out.append("clut")
    return " ".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ref")
    ap.add_argument("gpu")
    ap.add_argument("--diff-dir")
    ap.add_argument("--tag", default="gpu")
    a = ap.parse_args()
    fields = sorted(
        int(f[1:6]) for f in os.listdir(a.ref) if f.startswith("f") and f.endswith(".vram")
    )
    if a.diff_dir:
        os.makedirs(a.diff_dir, exist_ok=True)
    print("| field | display exact | max | >2 px | detail | local exact | local max | vram bytes diff | pages | regs |")
    print("| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    bad = 0
    for f in fields:
        r = os.path.join(a.ref, "f%05d" % f)
        g = os.path.join(a.gpu, "f%05d" % f)
        if not os.path.exists(g + ".vram"):
            print("| %d | (missing in %s) |" % (f, a.gpu))
            bad += 1
            continue
        row = [str(f)]
        detail = "-"
        if os.path.exists(r + "_display.png") and os.path.exists(g + "_display.png"):
            ra, ga = load_png(r + "_display.png"), load_png(g + "_display.png")
            k = ga.shape[0] // ra.shape[0] if ra.shape[0] else 1
            if k > 1 and ga.shape[0] == k * ra.shape[0] and ga.shape[1] == k * ra.shape[1]:
                # sub-pixel detail of the displayed buffer itself (before the
                # PCRTC merge, whose internal-resolution anti-flicker filter
                # varies inside blocks on its own) when the run dumped it
                if os.path.exists(g + "_target.png"):
                    detail = "%.1f%%" % block_detail(load_png(g + "_target.png"), k)
                else:
                    detail = "(%.1f%%)" % block_detail(ga, k)
                if a.diff_dir:
                    Image.fromarray(ga.astype(np.uint8), "RGBA").save(
                        os.path.join(a.diff_dir, "%s_f%05d_display.png" % (a.tag, f)))
                ga = box_down(ga, k)
            if ga.shape != ra.shape:
                row += ["size %s vs %s" % (ga.shape[:2], ra.shape[:2]), "-", "-"]
            else:
                s, d = cmp_img(ra, ga)
                row += ["%.3f%%" % s["exact"], str(s["max"]), str(s["beyond2"])]
                if a.diff_dir and s["max"]:
                    save_diff(d, os.path.join(a.diff_dir, "%s_f%05d_display_diff.png" % (a.tag, f)))
        else:
            row += ["(no display)", "-", "-"]
        row.append(detail)
        if os.path.exists(r + "_local.png") and os.path.exists(g + "_local.png"):
            s, d = cmp_img(load_png(r + "_local.png"), load_png(g + "_local.png"))
            row += ["%.3f%%" % s["exact"], str(s["max"])]
            if a.diff_dir and s["max"]:
                save_diff(d, os.path.join(a.diff_dir, "%s_f%05d_local_diff.png" % (a.tag, f)))
        else:
            row += ["-", "-"]
        rv = np.fromfile(r + ".vram", dtype=np.uint8)
        gv = np.fromfile(g + ".vram", dtype=np.uint8)
        dv = rv != gv
        pages = int(dv.reshape(512, 8192).any(axis=1).sum())
        row += [str(int(dv.sum())), str(pages)]
        rd = reg_diff(open(r + ".regs", "rb").read(), open(g + ".regs", "rb").read())
        row.append(rd or "same")
        if rd or pages:
            bad += 1
        print("| " + " | ".join(row) + " |")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
