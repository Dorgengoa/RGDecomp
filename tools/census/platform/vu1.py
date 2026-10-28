#!/usr/bin/env python3
"""platform_vu1.tsv -- VU microprograms and VU0 micro-mode use.

The retail microcode lives in MAIN .data as DMA-tagged VIF packets
(0x436C00..0x446000).  VuMicrocodeTableInitMaybe_152830 fills a
[4][12][4] table of packet pointers (a renderer variant = (pass, kind) and
three RET-tagged pieces each) plus a parallel table of per-variant data
packet lists.  This census parses every DMA-tagged VIF packet in that range
whose VIF stream contains an MPG, i.e. every microcode upload piece.

kind column:
  mpg          one MPG upload block: packet address, VU (VU1 or VU0 by the
               VIF channel that sends it), destination (bytes in micro mem),
               instruction count, sha1 of the code, packet tag
  variant      a (i,j) entry of the table: the k=0..2 pieces -> MPG blocks
               (statically read from VuMicrocodeTableInitMaybe_152830's C:
               plane 0 is written explicitly, planes 1..3 copy plane 0 and
               then patch -- patches listed from the source)
  vif0_upload  the VIF0 packet sent by Vif0SendInitPacketMaybe_13bcc0
               (VU0 micro program)
  vcallms      a VCALLMS/VCALLMSR instruction (VU0 micro mode) in code
  mscal_site   a call to DmaPktAddMscalCall_145b20 (VU1 MSCAL kicks queued
               in game DMA lists) with its constant arguments
  code_ref     functions that take the address of a microcode packet or of
               the table (lui+addiu) -- the uploaders
"""
from __future__ import annotations

import hashlib
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

LO, HI = 0x436C00, 0x446000
TAG_ID = {0: "REFE", 1: "CNT", 2: "NEXT", 3: "REF", 4: "REFS", 5: "CALL", 6: "RET", 7: "END"}
COLS = ["kind", "addr", "vu", "dest", "insns", "bytes", "sha1", "tag", "used_by",
        "detail"]


def vif_stream(m, start, nwords):
    """Parse VIF codes from start for nwords words; yield (cmd, num, imm, at, payload_addr)."""
    i = 0
    out = []
    while i < nwords:
        a = start + 4 * i
        w = m.word(a)
        if w is None:
            break
        cmd, num, imm = (w >> 24) & 0x7F, (w >> 16) & 0xFF, w & 0xFFFF
        i += 1
        if cmd == 0x4A:  # MPG
            if i % 2:
                i += 1   # data is 64-bit aligned
            n = num or 256
            out.append(("MPG", n, imm, a, start + 4 * i))
            i += 2 * n
        elif cmd in (0x50, 0x51):  # DIRECT/DIRECTHL
            i = (i + 3) & ~3
            out.append(("DIRECT", imm or 65536, 0, a, start + 4 * i))
            i += 4 * (imm or 65536)
        elif cmd == 0x20:
            i += 1
            out.append(("STMASK", 0, 0, a, 0))
        elif cmd in (0x30, 0x31):
            i += 4
            out.append(("STROW" if cmd == 0x30 else "STCOL", 0, 0, a, 0))
        elif cmd >= 0x60:  # UNPACK
            vn, vl = (cmd >> 2) & 3, cmd & 3
            bits = (32 >> vl) * (vn + 1)
            n = num or 256
            words = (bits * n + 31) // 32
            out.append(("UNPACK", n, imm, a, start + 4 * i))
            i += words
        else:
            name = {0: "NOP", 1: "STCYCL", 2: "OFFSET", 3: "BASE", 4: "ITOP", 5: "STMOD",
                    6: "MSKPATH3", 7: "MARK", 0x10: "FLUSHE", 0x11: "FLUSH", 0x13: "FLUSHA",
                    0x14: "MSCAL", 0x15: "MSCALF", 0x17: "MSCNT"}.get(cmd, f"?{cmd:02X}")
            out.append((name, num, imm, a, 0))
    return out


def packet(m, a):
    """A DMA-tagged VIF packet at a: (tag name, qwc, vif ops)."""
    lo = m.word(a)
    if lo is None:
        return None
    qwc, tid = lo & 0xFFFF, (lo >> 28) & 7
    hi_tag = m.word(a + 4)
    if hi_tag is None:
        return None
    # VIF stream = the tag's two upper words + qwc qwords
    ops = vif_stream(m, a + 8, 2 + 4 * qwc)
    return TAG_ID[tid], qwc, ops


_KEYS = None


def mpg_at_keys(m):
    return _KEYS


def main():
    global _KEYS
    facts, imgs, edges, files = C.cached()
    m = imgs["main"]
    rows = []
    # -- every MPG-bearing packet in the microcode range
    mpg_at = {}     # packet addr -> list of (dest, n, sha1, bytes)
    a = LO
    while a < HI:
        w0, w1, w2, w3 = (m.word(a + 4 * k) for k in range(4))
        tid = (w0 >> 28) & 7
        if w1 == 0 and (w0 & 0x0FFF0000) == 0 and tid in (1, 6, 7) and \
                ((w3 >> 24) & 0x7F) == 0x4A:
            p = packet(m, a)
            blocks = []
            for op, n, imm, at, pay in p[2]:
                if op == "MPG":
                    code = m.data[pay - m.base: pay - m.base + 8 * n]
                    blocks.append((imm * 8, n, hashlib.sha1(code).hexdigest()[:12], len(code)))
            if blocks:
                mpg_at[a] = (p[0], p[1], blocks, [o[0] for o in p[2]])
            a += 16 * (1 + p[1])
            continue
        a += 16
    # VIF0 packet
    vif0 = 0x445810
    _KEYS = set(mpg_at)
    # -- table from source
    pf = facts.get(("main", "VuMicrocodeTableInitMaybe_152830"))
    src = files.get(("main", pf[0])) if pf else ""
    assign = re.findall(r"p->a\[(\d+)\]\[(\d+)\]\[(\d+)\]\s*=\s*D_([0-9A-F]{8})", src or "")
    used = defaultdict(set)
    var = defaultdict(dict)
    for i, j, k, d in assign:
        var[(int(i), int(j))][int(k)] = int(d, 16)
        used[int(d, 16)].add(f"a[{i}][{j}][{k}]")
    # per-variant data packet lists (b table targets): 0x449DD0..0x449EF0
    for la in range(0x449DD0, 0x449EF0, 4):
        v = m.word(la)
        if v and LO <= v < HI:
            used[v].add(f"list@0x{la & ~0xF:06X}[{(la & 0xF) // 4}]")
    dref = defaultdict(list)
    for o in range(0, len(m.data) - 3, 4):
        v = struct.unpack_from("<I", m.data, o)[0]
        if v in mpg_at_keys(m):
            la = m.base + o
            if not 0x449DD0 <= la < 0x449EF0 and m.fn_at(la) is None:
                dref[v].append(la)
    for v, las in dref.items():
        used[v].add("data@" + ",".join(f"0x{x:06X}" for x in las[:4]))
    # planes 1..3 = copy of plane 0, then patched (assignments above override)
    for i in (1, 2, 3):
        for j in range(12):
            base = dict(var.get((0, j), {}))
            base.update(var.get((i, j), {}))
            if base:
                var[(i, j)] = base
    # -- code refs into the microcode range / table
    refs = defaultdict(set)
    for iname, im in imgs.items():
        for f in im.fns:
            hi = {}
            for pc, w in C.insns(im, f):
                op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
                if op == 0x0F:
                    hi[rt] = (w & 0xFFFF) << 16
                elif op in (0x09, 0x0D) and rs in hi:
                    v = (hi[rs] + C.sx16(w & 0xFFFF)) & 0xFFFFFFFF if op == 9 else hi[rs] | (w & 0xFFFF)
                    if LO <= v < HI or 0x449DD0 <= v < 0x449EF0:
                        refs[v].add(f.name)
    for pa, (tag, qwc, blocks, ops) in sorted(mpg_at.items()):
        vu = "VU0(VIF0)" if pa == vif0 else "VU1(VIF1)"
        for dest, n, h, nb in blocks:
            rows.append({"kind": "mpg", "addr": f"0x{pa:06X}", "vu": vu,
                         "dest": f"0x{dest:04X}", "insns": n, "bytes": nb, "sha1": h,
                         "tag": f"{tag} qwc=0x{qwc:X}",
                         "used_by": " ".join(sorted(used.get(pa, set()))[:6]) +
                         (f" (+{len(used[pa]) - 6})" if len(used.get(pa, ())) > 6 else ""),
                         "detail": "code refs: " + " ".join(sorted(refs.get(pa, set())))
                         + " | vif: " + " ".join(ops)})
    for (i, j), ks in sorted(var.items()):
        parts = []
        tot = 0
        for k in sorted(ks):
            pa = ks[k]
            b = mpg_at.get(pa)
            if pa == 0x436CA0:
                parts.append(f"k{k}=empty")
            elif b:
                parts.append(f"k{k}=0x{pa:06X}[" + ",".join(f"@0x{d:X}+{n}" for d, n, _, _ in b[2]) + "]")
                tot += sum(n for _, n, _, _ in b[2])
            else:
                parts.append(f"k{k}=0x{pa:06X}(no MPG)")
        rows.append({"kind": "variant", "addr": f"a[{i}][{j}]", "vu": "VU1(VIF1)",
                     "insns": tot, "detail": " ".join(parts)})
    # VCALLMS
    for iname, im in imgs.items():
        for f in im.fns:
            for pc, x in C.insns(im, f):
                if x >> 26 == 0x12 and (x >> 25) & 1 and (x & 0x3F) in (0x38, 0x39):
                    ms = (x & 0x3F) == 0x38
                    rows.append({"kind": "vcallms", "addr": f"0x{pc:06X}", "vu": "VU0",
                                 "dest": f"0x{((x >> 6) & 0x7FFF) * 8:04X}" if ms else "CMSAR0",
                                 "used_by": f.name,
                                 "detail": ("game" if f.is_game else "/".join(f.lib)) +
                                           (" vcallms" if ms else " vcallmsr")})
    # MSCAL call sites
    t = m.by_name.get("DmaPktAddMscalCall_145b20")
    if t:
        for iname, im in imgs.items():
            for f in im.fns:
                for site, tgt, (r, _, _) in C.callsites(im, f, {t.addr}, imgs):
                    rows.append({"kind": "mscal_site", "addr": f"0x{site:06X}",
                                 "vu": "VU1", "used_by": f.name,
                                 "detail": f"call-tag target={C.fmt(r.get(5), imgs, iname)} "
                                           f"(qword D_0047DE60 pushed first)"})
    for v, fs in sorted(refs.items()):
        if v not in mpg_at and not 0x449DD0 <= v < 0x449EF0:
            continue
        rows.append({"kind": "code_ref", "addr": f"0x{v:06X}", "used_by": " ".join(sorted(fs)),
                     "detail": "microcode table" if v >= 0x449DD0 else
                     ("MPG packet" if v in mpg_at else "microcode-range data")})
    nm = sum(len(b[2]) for b in mpg_at.values())
    uniq = len({h for b in mpg_at.values() for _, _, h, _ in b[2]})
    C.write_tsv(C.OUT / "platform_vu1.tsv", COLS, rows, C.meta(
        "vu1", {"rows": len(rows), "mpg_packets": len(mpg_at), "mpg_blocks": nm,
                "unique_code_hashes": uniq,
                "note": "dest/bytes are VU micro-memory byte addresses/sizes; "
                        "insns = 64-bit VU instruction pairs"}))
    print(len(mpg_at), "packets", nm, "MPG blocks", uniq, "unique")


if __name__ == "__main__":
    main()
