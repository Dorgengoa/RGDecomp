#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Capture the rg-game WINDOW as the desktop shows it (host overlays included: the settings
overlay, display.fps_counter), which --shot dumps and F12 window shots leave out by design.

    python tools/native/wincap.py --exe EXE --out DIR [--at 8,12] [--fields N] [-- rg-game args]

Starts EXE windowed (cwd = the exe's dir, RG_GPU=hw unless set) with the given args, grabs the
window's client area from the screen at each --at second (PIL.ImageGrab), writes DIR/capN.png,
then waits for the exe (--fields N ends it; default 1800).  Example (FPS counter, Vulkan):
    RG_GPU_API=vulkan python tools/native/wincap.py --exe out/playtest/rg-game-1025c.exe
        --out out/x --at 10,14 -- --set display.fps_counter=detailed
Needs an unlocked desktop (the window must be visible).
--dd: grab through DXGI Desktop Duplication (tools/native/ddcap.cpp, built on first use into
out/tools/ddcap.exe by tools/native/ddcap_build.cmd): the image the monitor shows, which is the
only one of the three that is not black for a Vulkan zero-copy (flip-model) window.
"""
from __future__ import annotations

import argparse
import ctypes
import ctypes.wintypes as wt
import os
import subprocess
import sys
import time
from pathlib import Path

from PIL import ImageGrab

user32 = ctypes.windll.user32
user32.WindowFromPoint.argtypes = [wt.POINT]
user32.WindowFromPoint.restype = wt.HWND
user32.GetAncestor.argtypes = [wt.HWND, ctypes.c_uint]
user32.GetAncestor.restype = wt.HWND
user32.SetWindowPos.argtypes = [wt.HWND, ctypes.c_ssize_t, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_uint]


def windows_of(pid: int):
    out = []

    @ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
    def cb(h, _):
        p = wt.DWORD()
        user32.GetWindowThreadProcessId(h, ctypes.byref(p))
        if p.value == pid and user32.IsWindowVisible(h):
            out.append(h)
        return True

    user32.EnumWindows(cb, 0)

    def area(h):
        x0, y0, x1, y1 = client_rect(h)
        return (x1 - x0) * (y1 - y0)
    # the game window first: the largest client area (SDL / Vulkan can add small helper windows)
    return sorted(out, key=area, reverse=True)


def client_rect(h):
    r = wt.RECT()
    user32.GetClientRect(h, ctypes.byref(r))
    pt = wt.POINT(0, 0)
    user32.ClientToScreen(h, ctypes.byref(pt))
    return pt.x, pt.y, pt.x + r.right, pt.y + r.bottom


def print_window(h):
    """PrintWindow(PW_RENDERFULLCONTENT): also captures flip-model / Vulkan swapchains, which a
    screen grab can return black"""
    from PIL import Image
    gdi32 = ctypes.windll.gdi32
    x0, y0, x1, y1 = client_rect(h)
    w, hh = x1 - x0, y1 - y0
    hdc = user32.GetDC(h)
    mdc = gdi32.CreateCompatibleDC(hdc)
    bmp = gdi32.CreateCompatibleBitmap(hdc, w, hh)
    gdi32.SelectObject(mdc, bmp)
    user32.PrintWindow(h, mdc, 3)   # PW_CLIENTONLY | PW_RENDERFULLCONTENT
    buf = ctypes.create_string_buffer(w * hh * 4)

    class BIH(ctypes.Structure):
        _fields_ = [("biSize", wt.DWORD), ("biWidth", wt.LONG), ("biHeight", wt.LONG), ("biPlanes", wt.WORD),
                    ("biBitCount", wt.WORD), ("biCompression", wt.DWORD), ("biSizeImage", wt.DWORD),
                    ("biXPelsPerMeter", wt.LONG), ("biYPelsPerMeter", wt.LONG), ("biClrUsed", wt.DWORD),
                    ("biClrImportant", wt.DWORD)]
    bi = BIH(ctypes.sizeof(BIH), w, -hh, 1, 32, 0, 0, 0, 0, 0, 0)
    gdi32.GetDIBits(mdc, bmp, 0, hh, buf, ctypes.byref(bi), 0)
    gdi32.DeleteObject(bmp)
    gdi32.DeleteDC(mdc)
    user32.ReleaseDC(h, hdc)
    return Image.frombuffer("RGB", (w, hh), buf, "raw", "BGRX", 0, 1)


DDCAP = Path(__file__).resolve().parents[2] / "out/tools/ddcap.exe"


def dd_grab(h, path: Path):
    """Desktop Duplication grab of the window's client area (ddcap.exe)"""
    from PIL import Image
    if not DDCAP.exists():
        subprocess.run(["cmd.exe", "/c", str(Path(__file__).resolve().parent / "ddcap_build.cmd"), str(DDCAP)], check=True)
    x0, y0, x1, y1 = client_rect(h)
    bmp = path.with_suffix(".bmp")
    r = subprocess.run([str(DDCAP), str(x0), str(y0), str(x1), str(y1), str(bmp)], capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError(r.stderr.strip())
    img = Image.open(bmp).convert("RGB")
    img.load()
    bmp.unlink()
    return img


def main(argv=None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = []
    if "--" in argv:
        k = argv.index("--")
        argv, extra = argv[:k], argv[k + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--at", default="8,12")
    ap.add_argument("--fields", type=int, default=1800)
    ap.add_argument("--printwindow", action="store_true",
                    help="PrintWindow instead of a screen grab (Vulkan / flip-model windows can grab black)")
    ap.add_argument("--burst", type=int, default=1, help="--dd: grabs per --at time (capI_K.png, K >= 1)")
    ap.add_argument("--dd", action="store_true",
                    help="DXGI Desktop Duplication (ddcap.exe): also a Vulkan zero-copy window")
    a = ap.parse_args(argv)
    try:
        ctypes.windll.shcore.SetProcessDpiAwareness(2)
    except Exception:
        pass
    exe = Path(a.exe).resolve()
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, RG_GPU=os.environ.get("RG_GPU", "hw"))
    p = subprocess.Popen([str(exe), "--fields", str(a.fields)] + extra, cwd=exe.parent, env=env,
                         stdout=open(out / "stdout.txt", "w"), stderr=open(out / "stderr.txt", "w"))
    t0 = time.time()
    n = 0
    for i, at in enumerate(float(x) for x in a.at.split(",")):
        while time.time() - t0 < at and p.poll() is None:
            time.sleep(0.1)
        hs = windows_of(p.pid)
        if not hs:
            print(f"wincap: no window at {at} s")
            continue
        if a.dd:
            # the duplicated image is the whole screen: raise the game window above everything
            # and refuse the grab when another window still covers it (never keep other content)
            user32.SetWindowPos(hs[0], -1, 0, 0, 0, 0, 0x0001 | 0x0002 | 0x0040)   # TOPMOST, NOSIZE|NOMOVE|SHOW
            time.sleep(0.6)
            x0, y0, x1, y1 = client_rect(hs[0])
            pts = [((x0 + x1) // 2, (y0 + y1) // 2), (x0 + 8, y0 + 8), (x1 - 8, y1 - 8)]
            covered = [pt for pt in pts if user32.GetAncestor(user32.WindowFromPoint(wt.POINT(*pt)), 2) != hs[0]]
            imgs = []
            for k in range(0 if covered else a.burst):
                x0, y0, x1, y1 = client_rect(hs[0])
                if x1 <= x0 or y1 <= y0 or user32.IsIconic(hs[0]):
                    print(f"wincap: {at} s grab {k}: the window is minimized: stop")
                    break
                imgs.append(dd_grab(hs[0], out / f"cap{i}_{k}.png"))
            user32.SetWindowPos(hs[0], -2, 0, 0, 0, 0, 0x0001 | 0x0002 | 0x0010)   # NOTOPMOST, no activate
            if not imgs:
                print(f"wincap: {at} s: the window is covered at {covered}: no capture")
                continue
            for k, im in enumerate(imgs[1:], 1):
                im.save(out / f"cap{i}_{k}.png")
                print(f"wincap: {out / f'cap{i}_{k}.png'} {im.size} mean {sum(im.convert('L').getdata()) / (im.size[0] * im.size[1]):.1f}")
            img = imgs[0]
        else:
            img = print_window(hs[0]) if a.printwindow else ImageGrab.grab(bbox=client_rect(hs[0]), all_screens=True)
        img.save(out / f"cap{i}.png")
        n += 1
        print(f"wincap: {out / f'cap{i}.png'} {img.size}")
    rc = p.wait()
    print(f"wincap: exe exit {rc}, {n} captures")
    return 0 if n else 1


if __name__ == "__main__":
    sys.exit(main())
