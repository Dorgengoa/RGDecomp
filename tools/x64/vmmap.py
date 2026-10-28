#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Address-space census of a running process (docs/X64-PLAN.md 0.6): the x64 exe is linked
/LARGEADDRESSAWARE:NO, so its whole user space is 2 GB; this shows who holds it.

    python tools/x64/vmmap.py PID [--top 25] [--min-mb 1]
    python tools/x64/vmmap.py --exe-like x64-windows [--wait 60] [--when-commit 200] ...
        (the first rg-game whose path contains the text; --when-commit waits until the run
        has left the machine-wide slot wait and committed that much private memory)

Walks VirtualQueryEx over the process, groups regions by allocation base, and prints the
totals per type (image / mapped / private) and state (commit / reserve / free), the
largest free block, and the largest allocations with their module or mapped-file name.
"""
from __future__ import annotations

import argparse
import ctypes
import ctypes.wintypes as wt
import subprocess
import sys
import time

PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_READ = 0x0010
MEM_COMMIT, MEM_RESERVE, MEM_FREE = 0x1000, 0x2000, 0x10000
MEM_IMAGE, MEM_MAPPED, MEM_PRIVATE = 0x1000000, 0x40000, 0x20000


class MBI(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_uint64), ("AllocationBase", ctypes.c_uint64),
                ("AllocationProtect", wt.DWORD), ("PartitionId", wt.WORD), ("__a", wt.WORD),
                ("RegionSize", ctypes.c_uint64), ("State", wt.DWORD), ("Protect", wt.DWORD),
                ("Type", wt.DWORD), ("__b", wt.DWORD)]


k32 = ctypes.WinDLL("kernel32", use_last_error=True)
psapi = ctypes.WinDLL("psapi", use_last_error=True)
k32.OpenProcess.restype = wt.HANDLE
k32.VirtualQueryEx.argtypes = [wt.HANDLE, ctypes.c_uint64, ctypes.POINTER(MBI), ctypes.c_size_t]
k32.VirtualQueryEx.restype = ctypes.c_size_t
psapi.GetMappedFileNameW.argtypes = [wt.HANDLE, ctypes.c_uint64, wt.LPWSTR, wt.DWORD]


def find_pid(text: str, wait: float) -> int | None:
    end = time.time() + wait
    while True:
        out = subprocess.run(["powershell", "-NoProfile", "-Command",
                              "Get-Process rg-game -ErrorAction SilentlyContinue | "
                              "ForEach-Object { \"$($_.Id)`t$($_.Path)\" }"],
                             capture_output=True, text=True).stdout
        for ln in out.splitlines():
            pid, _, path = ln.partition("\t")
            if text.lower() in path.lower():
                return int(pid)
        if time.time() > end:
            return None
        time.sleep(2)


def private_commit(pid: int) -> int:
    h = k32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, pid)
    if not h:
        raise SystemExit(f"vmmap: process {pid} gone")
    addr, mbi, n = 0, MBI(), 0
    while addr < (1 << 47) and k32.VirtualQueryEx(h, addr, ctypes.byref(mbi), ctypes.sizeof(mbi)):
        if mbi.State == MEM_COMMIT and mbi.Type == MEM_PRIVATE:
            n += mbi.RegionSize
        addr = mbi.BaseAddress + mbi.RegionSize
    k32.CloseHandle(h)
    return n


def census(pid: int, top: int, min_mb: float, below: int = 1 << 47) -> int:
    h = k32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, pid)
    if not h:
        print(f"vmmap: cannot open {pid} ({ctypes.get_last_error()})")
        return 1
    addr, mbi = 0, MBI()
    allocs: dict[int, list] = {}
    tot: dict[tuple, int] = {}
    free_max = 0
    while addr < below and k32.VirtualQueryEx(h, addr, ctypes.byref(mbi), ctypes.sizeof(mbi)):
        size = min(mbi.RegionSize, below - mbi.BaseAddress)
        if mbi.State == MEM_FREE:
            free_max = max(free_max, size)
            tot[("free", "-")] = tot.get(("free", "-"), 0) + size
        else:
            ty = {MEM_IMAGE: "image", MEM_MAPPED: "mapped", MEM_PRIVATE: "private"}.get(mbi.Type, hex(mbi.Type))
            st = "commit" if mbi.State == MEM_COMMIT else "reserve"
            tot[(ty, st)] = tot.get((ty, st), 0) + size
            a = allocs.setdefault(mbi.AllocationBase, [ty, 0, 0])
            a[1] += size
            if st == "commit":
                a[2] += size
        addr = mbi.BaseAddress + size
    mb = lambda n: n / 1048576
    used = sum(v for k, v in tot.items() if k[0] != "free" and k[0] != "-")
    print(f"pid {pid}: used {mb(used):.0f} MB (top {mb(addr):.0f} MB of space walked), largest free block {mb(free_max):.1f} MB")
    for k in sorted(tot):
        print(f"  {k[0]:8} {k[1]:8} {mb(tot[k]):9.1f} MB")
    buf = ctypes.create_unicode_buffer(520)
    rows = sorted(allocs.items(), key=lambda kv: -kv[1][1])
    print(f"largest allocations (>= {min_mb} MB):")
    for base, (ty, size, com) in rows[:top]:
        if mb(size) < min_mb:
            break
        name = ""
        if ty in ("image", "mapped") and psapi.GetMappedFileNameW(h, base, buf, 520):
            name = buf.value.rsplit("\\", 1)[-1]
        print(f"  {base:016x} {ty:8} {mb(size):8.1f} MB (commit {mb(com):7.1f}) {name}")
    k32.CloseHandle(h)
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("pid", nargs="?", type=int)
    ap.add_argument("--exe-like")
    ap.add_argument("--wait", type=float, default=0)
    ap.add_argument("--top", type=int, default=25)
    ap.add_argument("--min-mb", type=float, default=1)
    ap.add_argument("--below-mb", type=int, default=0,
                    help="walk only the space below this address (2048: an x64 LAA:NO exe's NULL-hint space)")
    ap.add_argument("--when-commit", type=float, default=0,
                    help="poll (2 s) until the private commit is at least this many MB (the run left the slot wait)")
    a = ap.parse_args()
    pid = a.pid or (find_pid(a.exe_like, a.wait) if a.exe_like else None)
    if not pid:
        print("vmmap: no process")
        return 1
    while a.when_commit and private_commit(pid) < a.when_commit * 1048576:
        time.sleep(2)
    return census(pid, a.top, a.min_mb, (a.below_mb << 20) if a.below_mb else 1 << 47)


if __name__ == "__main__":
    sys.exit(main())
