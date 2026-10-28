#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Summarise an rgprof sample file against rg-game.map.
   anal.py PROF.tsv TIMES.tsv MAP EXE [--fields a-b] [--top N] [--thread TID]
Each sample: leaf in the exe -> its symbol; leaf in a DLL (driver, ntdll waits,
CRT) -> attributed to the first exe return address (call-checked) on the stack.
Buckets by library: game (EE code), vu1, vif/dmac, gs, gpu, host, ..."""
import sys, bisect, struct, argparse, collections, os

ap = argparse.ArgumentParser()
ap.add_argument("prof"); ap.add_argument("times"); ap.add_argument("map"); ap.add_argument("exe")
ap.add_argument("--fields", default="")
ap.add_argument("--top", type=int, default=25)
ap.add_argument("--offset", type=float, default=None, help="ms from profiler start to field 1 start")
a = ap.parse_args()

# ---- map
syms = []
for ln in open(a.map, errors="replace"):
    p = ln.split()
    if len(p) == 4 and p[0].startswith("0001:"):
        try: va = int(p[2], 16)
        except ValueError: continue
        syms.append((va - 0x400000, p[1], p[3]))
syms.sort()
sva = [s[0] for s in syms]

def sym(rva):
    i = bisect.bisect_right(sva, rva) - 1
    return syms[i] if i >= 0 else (0, "?", "?")

# ---- PE text for call checks
pe = open(a.exe, "rb").read()
e = struct.unpack_from("<I", pe, 0x3C)[0]
nsec = struct.unpack_from("<H", pe, e + 6)[0]
optsz = struct.unpack_from("<H", pe, e + 20)[0]
secs = []
for i in range(nsec):
    o = e + 24 + optsz + 40 * i
    name = pe[o:o + 8].rstrip(b"\0")
    vsz, vaddr, rsz, raw = struct.unpack_from("<IIII", pe, o + 8)
    secs.append((vaddr, max(vsz, rsz), raw))
def byte_at(rva):
    for va, sz, raw in secs:
        if va <= rva < va + sz: return pe[raw + rva - va] if raw + rva - va < len(pe) else None
    return None
def is_ret(rva):
    b = [byte_at(rva - k) for k in range(1, 8)]
    if None in b: return False
    if b[4] == 0xE8: return True                       # call rel32
    if b[5] == 0xFF and (b[4] & 0x38) == 0x10: return True   # call [disp32] / modrm 6 bytes
    if b[1] == 0xFF and (b[0] & 0x38) == 0x10 and (b[0] & 0xC0) == 0xC0: return True  # call reg
    if b[2] == 0xFF and (b[1] & 0x38) == 0x10 and (b[1] & 0xC0) == 0x40: return True  # call [r+d8]
    if b[5] == 0xFF and (b[4] & 0x38) == 0x10 and (b[4] & 0xC0) == 0x80: return True
    if b[1] == 0xFF and (b[0] & 0x38) == 0x10 and (b[0] & 0xC0) == 0x00: return True  # call [reg]
    if b[2] == 0xFF and b[1] == 0x14: return True      # call [sib]
    return False

def bucket(lib, name):
    l = lib.split(":")[0]
    if ":" not in lib or l.startswith("rg_game") or l.startswith("ovl_"):
        return "game"
    m = {"rg_ps2_vu": "vu1", "rg_ps2_vif": "vif/dmac", "rg_ps2_dmac": "vif/dmac", "rg_ps2_hwbus": "vif/dmac",
         "rg_ps2_gs": "gs model", "rg_gpu": "gpu", "rg_host": "host", "SDL3-static": "host",
         "rg_sce_vu0": "vu0", "rg_ps2_sound": "audio", "rg_ps2_spu": "audio", "rg_ps2_iop": "iop",
         "rg_ps2_iop_hle": "iop", "rg_ps2_kernel": "kernel", "rg_movie": "movie", "rg_ps2_cdvd": "cdvd",
         "rg_settings": "host"}
    if l in m: return m[l]
    if l.startswith("rg_sce"): return "sce libs"
    if l in ("libucrt", "libvcruntime", "libcmt", "libcpmt"): return "crt"
    return l

# ---- samples
mods = {}
rows = []
for ln in open(a.prof):
    if ln.startswith("#mod"):
        p = ln.rstrip("\n").split("\t"); mods[int(p[2], 16)] = (int(p[3], 16), os.path.basename(p[4]))
        continue
    if ln.startswith("#"): continue
    p = ln.split()
    rows.append((float(p[0]), int(p[1]), int(p[2], 16), [int(x, 16) for x in p[3:]]))
exe_base = min((b for b, (s, n) in mods.items() if n.lower().endswith(".exe")), default=0x400000)
modl = sorted((b, s, n) for b, (s, n) in mods.items())
def modname(va):
    for b, s, n in modl:
        if b <= va < b + s: return n
    return "?"

# field windows
ft = [float(l.split()[1]) for l in open(a.times) if l.strip() and not l.startswith("#") and l.split()[0].isdigit()]
cum = [0.0]
for w in ft: cum.append(cum[-1] + w)
off = a.offset
if off is None:
    # the process start: the first sample time; field 1 begins shortly after
    off = rows[0][0] if rows else 0.0
lo_f, hi_f = 1, len(ft)
if a.fields:
    lo_f, hi_f = [int(x) for x in a.fields.split("-")]
t_lo, t_hi = off + cum[lo_f - 1], off + cum[min(hi_f, len(ft))]
sel = [r for r in rows if t_lo <= r[0] < t_hi]
nfields = min(hi_f, len(ft)) - lo_f + 1
wall = t_hi - t_lo
print("fields %d-%d: %d fields, wall %.1f s, %.2f ms/field, %d samples" % (lo_f, hi_f, nfields, wall / 1000, wall / nfields, len(sel)))

per_thread = collections.Counter(r[1] for r in sel)
for tid, n in per_thread.most_common(int(os.environ.get("RG_PROF_THREADS", "3"))):
    rs = [r for r in sel if r[1] == tid]
    times = sorted(r[0] for r in rs)
    period = (times[-1] - times[0]) / max(1, len(times) - 1) if len(times) > 1 else 1
    bk = collections.Counter(); syc = collections.Counter(); leafmod = collections.Counter()
    busy = 0
    for t, _, eip, stk in rs:
        if exe_base <= eip < exe_base + 0x2000000:
            s = sym(eip - exe_base); b = bucket(s[2], s[1]); where = s[1]; lm = "exe"
            if b == "crt":
                for w in stk:
                    if is_ret(w - exe_base):
                        s2 = sym(w - exe_base)
                        if bucket(s2[2], s2[1]) != "crt":
                            b = bucket(s2[2], s2[1]); where = s[1] + " <- " + s2[1]; break
        else:
            lm = modname(eip); b = "?"; where = lm
            for w in stk:
                if is_ret(w - exe_base):
                    s2 = sym(w - exe_base)
                    if bucket(s2[2], s2[1]) == "crt": continue
                    b = bucket(s2[2], s2[1]); where = lm + " <- " + s2[1]; break
            low = lm.lower()
            if low in ("ntdll.dll", "kernelbase.dll", "kernel32.dll", "win32u.dll") :
                b = b + " [os/wait]"
            elif low.startswith("nv") or low in ("d3d11.dll", "dxgi.dll", "d3d10warp.dll"):
                b = b + " [driver]"
            else:
                b = b + " [" + lm + "]"
        bk[b] += 1; syc[where] += 1; leafmod[lm] += 1
    print("\n== thread %d: %d samples (%.0f%% of window at %.2f ms/sample)" % (tid, n, 100.0 * n * period / wall if wall else 0, period))
    for b, c in bk.most_common(18):
        print("  %-28s %6.1f%%  %6.2f ms/field" % (b, 100.0 * c / n, c * period / nfields))
    print("  -- top")
    for w, c in syc.most_common(a.top):
        print("  %6.1f%%  %s" % (100.0 * c / n, w))
