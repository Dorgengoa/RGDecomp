#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Sample where a running (i686) rg-game spends its time: a hang / spin finder
(docs/NATIVE-THREADS.md "Tools").  No debugger needed.

    python tools/native/thread_sample.py PID [--map build/nthreads-i686/rg-game.map]
                                             [--samples 20] [--interval 0.05] [--frames 12]

Suspends each thread of the process briefly (Wow64SuspendThread / Wow64GetThreadContext),
reads EIP and walks the EBP chain (frame pointers: the port builds keep them in most code;
a frame without one ends the walk early), names every address from the link map and prints,
per thread, the most frequent stacks.  Read-only apart from the short suspensions.
Windows, 64-bit Python, 32-bit target.
"""
import argparse
import bisect
import collections
import ctypes
import ctypes.wintypes as W
import re
import sys
import time

k32 = ctypes.WinDLL("kernel32", use_last_error=True)
TH32CS_SNAPTHREAD = 0x4
THREAD_ALL = 0x001F03FF
PROCESS_VM_READ = 0x10
PROCESS_QUERY_INFORMATION = 0x400
WOW64_CONTEXT_CONTROL = 0x00010001
WOW64_CONTEXT_INTEGER = 0x00010002


class THREADENTRY32(ctypes.Structure):
    _fields_ = [("dwSize", W.DWORD), ("cntUsage", W.DWORD), ("th32ThreadID", W.DWORD),
                ("th32OwnerProcessID", W.DWORD), ("tpBasePri", W.LONG), ("tpDeltaPri", W.LONG),
                ("dwFlags", W.DWORD)]


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("ContextFlags", W.DWORD), ("Dr", W.DWORD * 6), ("FloatSave", ctypes.c_byte * 112),
                ("SegGs", W.DWORD), ("SegFs", W.DWORD), ("SegEs", W.DWORD), ("SegDs", W.DWORD),
                ("Edi", W.DWORD), ("Esi", W.DWORD), ("Ebx", W.DWORD), ("Edx", W.DWORD), ("Ecx", W.DWORD),
                ("Eax", W.DWORD), ("Ebp", W.DWORD), ("Eip", W.DWORD), ("SegCs", W.DWORD),
                ("EFlags", W.DWORD), ("Esp", W.DWORD), ("SegSs", W.DWORD), ("Ext", ctypes.c_byte * 512)]


def load_map(path):
    rx = re.compile(r"^\s*0001:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8,16})\s+(\S.*)$", re.I)
    syms = []
    for ln in open(path, encoding="utf-8", errors="replace"):
        m = rx.match(ln)
        if m:
            syms.append((int(m.group(2), 16), m.group(1).lstrip("_"), m.group(3).strip()))
    syms.sort()
    return [s[0] for s in syms], syms


def name(addrs, syms, a):
    i = bisect.bisect_right(addrs, a) - 1
    if i < 0:
        return "%08x" % a
    s = syms[i]
    off = a - s[0]
    return "%s+%x" % (s[1], off) if off < 0x100000 else "%08x" % a


def threads_of(pid):
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


def read32(hp, a):
    buf = W.DWORD()
    n = ctypes.c_size_t()
    if not k32.ReadProcessMemory(hp, ctypes.c_void_p(a), ctypes.byref(buf), 4, ctypes.byref(n)) or n.value != 4:
        return None
    return buf.value


def sample(hp, tid, frames):
    ht = k32.OpenThread(THREAD_ALL, False, tid)
    if not ht:
        return None
    try:
        if k32.Wow64SuspendThread(ht) == 0xFFFFFFFF:
            return None
        ctx = WOW64_CONTEXT()
        ctx.ContextFlags = WOW64_CONTEXT_CONTROL | WOW64_CONTEXT_INTEGER
        ok = k32.Wow64GetThreadContext(ht, ctypes.byref(ctx))
        stack = []
        if ok:
            stack.append(ctx.Eip)
            ebp = ctx.Ebp
            for _ in range(frames):
                if not ebp or ebp & 3:
                    break
                ret = read32(hp, ebp + 4)
                nxt = read32(hp, ebp)
                if ret is None or nxt is None or nxt <= ebp:
                    break
                stack.append(ret)
                ebp = nxt
        k32.ResumeThread(ht)
        return stack
    finally:
        k32.CloseHandle(ht)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("pid", type=int)
    ap.add_argument("--map", default="build/nthreads-i686/rg-game.map")
    ap.add_argument("--samples", type=int, default=20)
    ap.add_argument("--interval", type=float, default=0.05)
    ap.add_argument("--frames", type=int, default=12)
    ap.add_argument("--top", type=int, default=3)
    a = ap.parse_args()
    addrs, syms = load_map(a.map)
    hp = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, a.pid)
    if not hp:
        sys.exit("cannot open process %d (error %d)" % (a.pid, ctypes.get_last_error()))
    per = collections.defaultdict(collections.Counter)
    for _ in range(a.samples):
        for tid in threads_of(a.pid):
            st = sample(hp, tid, a.frames)
            if st:
                per[tid][tuple(name(addrs, syms, x) for x in st)] += 1
        time.sleep(a.interval)
    for tid, c in per.items():
        # threads parked in system DLLs (no frame named from the map) are idle workers
        if all(all(re.fullmatch(r"[0-9a-f]{8}", f) for f in s) for s in c):
            continue
        print("thread %d:" % tid)
        for st, n in c.most_common(a.top):
            print("  %3d x  %s" % (n, "  <-  ".join(st)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
