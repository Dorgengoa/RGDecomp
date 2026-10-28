#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Where is a (32-bit) rg-game spinning?  Samples every thread's EIP and the stack words that
point into the image, symbolized with the exe's map (docs/TEST-FIXTURES.md "Factory and
Insectron drivers"; found the Insectron return-to-title hang).

    python tools/fixtures/hangsample.py PID [--samples 20] [--interval 0.1] [--map MAP] [--stack 64]

Windows only (64-bit Python, WOW64 target): OpenThread + SuspendThread +
Wow64GetThreadContext + ReadProcessMemory, then ResumeThread; the process is not otherwise
touched (no kill).  Output: per thread, the EIP histogram (symbol+offset) and, for the
busiest thread, the most common return-address chain (stack words inside the image's
.text, innermost first; heuristic, like rg-game's own crash report).
"""
from __future__ import annotations

import argparse
import collections
import ctypes
import ctypes.wintypes as W
import struct
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fxlib  # noqa: E402

k32 = ctypes.WinDLL("kernel32", use_last_error=True)
TH32CS_SNAPTHREAD = 4
THREAD_ALL = 0x001F03FF
PROCESS_VM_READ, PROCESS_QUERY = 0x10, 0x400
WOW64_CONTEXT_CONTROL, WOW64_CONTEXT_INTEGER = 0x10001, 0x10002


class THREADENTRY32(ctypes.Structure):
    _fields_ = [("dwSize", W.DWORD), ("cntUsage", W.DWORD), ("th32ThreadID", W.DWORD),
                ("th32OwnerProcessID", W.DWORD), ("tpBasePri", W.LONG), ("tpDeltaPri", W.LONG),
                ("dwFlags", W.DWORD)]


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("ContextFlags", W.DWORD)] + [(f"Dr{i}", W.DWORD) for i in (0, 1, 2, 3, 6, 7)] + \
               [("FloatSave", ctypes.c_byte * 112)] + \
               [(n, W.DWORD) for n in ("SegGs", "SegFs", "SegEs", "SegDs", "Edi", "Esi", "Ebx", "Edx", "Ecx",
                                       "Eax", "Ebp", "Eip", "SegCs", "EFlags", "Esp", "SegSs")] + \
               [("ExtendedRegisters", ctypes.c_byte * 512)]


def threads(pid):
    snap = k32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
    te = THREADENTRY32()
    te.dwSize = ctypes.sizeof(te)
    out = []
    ok = k32.Thread32First(snap, ctypes.byref(te))
    while ok:
        if te.th32OwnerProcessID == pid:
            out.append(te.th32ThreadID)
        ok = k32.Thread32Next(snap, ctypes.byref(te))
    k32.CloseHandle(snap)
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("pid", type=int)
    ap.add_argument("--samples", type=int, default=20)
    ap.add_argument("--interval", type=float, default=0.1)
    ap.add_argument("--map", help="rg-game.map (default: next to the process image)")
    ap.add_argument("--stack", type=int, default=64, help="stack words read per sample")
    a = ap.parse_args(argv)
    k32.OpenProcess.restype = W.HANDLE
    k32.OpenThread.restype = W.HANDLE
    hp = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY, False, a.pid)
    if not hp:
        raise SystemExit(f"hangsample: cannot open process {a.pid} ({ctypes.get_last_error()})")
    if a.map:
        mp = Path(a.map)
    else:
        buf = ctypes.create_unicode_buffer(1024)
        n = W.DWORD(1024)
        k32.QueryFullProcessImageNameW(hp, 0, buf, ctypes.byref(n))
        mp = Path(buf.value).with_suffix(".map")
    syms = fxlib.map_symbols(mp)
    import bisect
    keys = [s for s, _ in syms]
    base = 0x400000
    lo, hi = keys[0] + base, keys[-1] + base + 0x10000

    def name(va):
        r = va - base
        i = bisect.bisect_right(keys, r) - 1
        return f"{syms[i][1]}+{r - syms[i][0]:#x}" if i >= 0 and lo <= va < hi else f"{va:#010x}"

    eips = collections.defaultdict(collections.Counter)
    chains = collections.defaultdict(collections.Counter)
    for _ in range(a.samples):
        for tid in threads(a.pid):
            ht = k32.OpenThread(THREAD_ALL, False, tid)
            if not ht:
                continue
            if k32.SuspendThread(ht) == 0xFFFFFFFF:
                k32.CloseHandle(ht)
                continue
            ctx = WOW64_CONTEXT()
            ctx.ContextFlags = WOW64_CONTEXT_CONTROL | WOW64_CONTEXT_INTEGER
            ok = k32.Wow64GetThreadContext(ht, ctypes.byref(ctx))
            words = []
            if ok:
                sb = (ctypes.c_uint32 * a.stack)()
                got = ctypes.c_size_t()
                n = ctypes.sizeof(sb)
                while n >= 16:   # a read past the stack's top fails whole: shrink until it fits
                    if k32.ReadProcessMemory(hp, ctypes.c_void_p(ctx.Esp), sb, n, ctypes.byref(got)):
                        words = [w for w in sb[:got.value // 4] if lo <= w < hi]
                        break
                    n //= 2
            k32.ResumeThread(ht)
            k32.CloseHandle(ht)
            if ok:
                eips[tid][name(ctx.Eip)] += 1
                chains[tid][tuple(name(w) for w in words[:8])] += 1
        time.sleep(a.interval)
    busiest = sorted(eips, key=lambda t: -sum(1 for k in eips[t] if not k.startswith("0x")))
    for tid in busiest:
        c = eips[tid]
        inimg = sum(v for k, v in c.items() if not k.startswith("0x"))
        print(f"thread {tid}: {sum(c.values())} samples, {inimg} in the image")
        for k, v in c.most_common(6):
            print(f"   {v:4d}  {k}")
    if busiest:
        t = busiest[0]
        print(f"\nthread {t}: most common stack chains (innermost first):")
        for ch, v in chains[t].most_common(3):
            print(f"   {v:4d}  " + " <- ".join(ch))
    return 0


if __name__ == "__main__":
    sys.exit(main())
