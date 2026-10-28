#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Summarise the per-range census files of an RG_PERF_CENSUS run (docs/PERF-3D.md).

    census.py DIR [--elf SCUS_974.90] [--vu1-census census/platform_vu1.tsv] [--top N]

DIR holds fA-B_vu.tsv (src/ps2/vif/vif.c vif_census_dump) and fA-B_gs.tsv
(src/ps2/gs/gs_census.c gs_features_dump) for each field range.  Prints markdown:

  * VU1 microprograms by host time and call count; each (start address, code
    hash) is matched to the retail MPG packet(s) that upload exactly those
    bytes (census/platform_vu1.tsv rows + the retail ELF), so the table names
    the packet and its VuMicrocodeTableInit slots;
  * GS features: primitives / bounding-box pixels by blend equation, alpha
    test, destination alpha test, depth test, texture format (+CLUT), filter,
    frame / Z format, render-to-texture draws, local-memory transfers.
Ranges are per field (fields per range = B - A + 1)."""
import argparse, collections, glob, os, re, struct, sys

ap = argparse.ArgumentParser()
ap.add_argument("dir")
ap.add_argument("--elf", default=os.environ.get("RG_ELF", "../work/SCUS_974.90"))
ap.add_argument("--vu1-census", default=os.path.join(os.path.dirname(__file__), "..", "..", "census", "platform_vu1.tsv"))
ap.add_argument("--top", type=int, default=15)
a = ap.parse_args()


# ---------------------------------------------------------------- retail MPG images
def load_elf(path):
    try:
        d = open(path, "rb").read()
    except OSError:
        return None
    phoff, = struct.unpack_from("<I", d, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
    segs = []
    for i in range(phnum):
        o = phoff + i * phentsize
        typ, off, vaddr, paddr, filesz = struct.unpack_from("<IIIII", d, o)
        if typ == 1:
            segs.append((vaddr, off, filesz))
    return d, segs


def elf_bytes(elf, vaddr, n):
    d, segs = elf
    for va, off, sz in segs:
        if va <= vaddr and vaddr + n <= va + sz:
            return d[off + vaddr - va: off + vaddr - va + n]
    return None


def fnv(b):
    h = 2166136261
    for x in b:
        h = ((h ^ x) * 16777619) & 0xFFFFFFFF
    return h


def mpg_images():
    """packet address -> (16 KB VU1 code image, slots) for every retail VU1 MPG packet"""
    out = {}
    elf = load_elf(a.elf)
    if not elf or not os.path.exists(a.vu1_census):
        return out
    rows = collections.defaultdict(list)
    for ln in open(a.vu1_census, encoding="utf-8", errors="replace"):
        if ln.startswith("#") or ln.startswith("kind"):
            continue
        p = ln.rstrip("\n").split("\t")
        if len(p) < 9 or p[0] != "mpg" or "VU1" not in p[2]:
            continue
        rows[int(p[1], 16)].append((int(p[3], 16), int(p[4]), p[8]))
    for addr, blocks in rows.items():
        # the packet: a DMA tag (qword), then VIF words; walk the MPG commands
        hdr = elf_bytes(elf, addr, 16)
        if not hdr:
            continue
        qwc = struct.unpack_from("<I", hdr, 0)[0] & 0xFFFF
        body = elf_bytes(elf, addr + 8, 8 + qwc * 16)
        if not body:
            continue
        img = bytearray(0x4000)
        w = 0
        nw = len(body) // 4
        while w < nw:
            code = struct.unpack_from("<I", body, w * 4)[0]
            cmd = (code >> 24) & 0x7F
            num = (code >> 16) & 0xFF
            imm = code & 0xFFFF
            w += 1
            if cmd == 0x4A:   # MPG
                n = num if num else 256
                dest = imm * 8
                data = body[w * 4: w * 4 + n * 8]
                for k in range(len(data)):
                    img[(dest + k) & 0x3FFF] = data[k]
                w += n * 2
            elif cmd >= 0x60:   # UNPACK: skip its payload (not in MPG packets)
                break
            elif cmd in (0x50, 0x51):   # DIRECT(HL)
                w += (imm if imm else 65536) * 4
        out[addr] = (bytes(img), sorted(set(b[2] for b in blocks)))
    return out


IMGS = mpg_images()


def name_prog(pc, h):
    hits = []
    for addr, (img, slots) in IMGS.items():
        b = bytes(img[(pc + k) & 0x3FFF] for k in range(128))
        if fnv(b) == h:
            hits.append("0x%06X %s" % (addr, " ".join(slots)[:60]))
    return "; ".join(hits) if hits else "?"


# ---------------------------------------------------------------- per range
def ranges():
    rs = set()
    for f in glob.glob(os.path.join(a.dir, "f*-*_*.tsv")):
        m = re.match(r"f(\d+)-(\d+)_", os.path.basename(f))
        if m:
            rs.add((int(m.group(1)), int(m.group(2))))
    return sorted(rs)


def rows(path):
    out = []
    if not os.path.exists(path):
        return out
    for ln in open(path, encoding="utf-8", errors="replace"):
        if ln.startswith("#") or not ln.strip():
            continue
        out.append(ln.rstrip("\n").split("\t"))
    return out


for lo, hi in ranges():
    nf = hi - lo + 1
    print("## Fields %d-%d (%d fields)\n" % (lo, hi, nf))
    vu = rows(os.path.join(a.dir, "f%d-%d_vu.tsv" % (lo, hi)))
    vu = [r for r in vu if r[0] == "1"]
    tot_ms = sum(float(r[6]) for r in vu) or 1.0
    tot_pairs = sum(int(r[4]) for r in vu) or 1
    print("VU1: %.2f ms of host time and %.0f k pairs per field, %d programs (start address + code)\n"
          % (tot_ms / nf, tot_pairs / nf / 1000.0, len(vu)))
    print("| program (pc, code hash) | calls/field | k pairs/field | ms/field | share | retail MPG packet, VuMicrocodeTableInit slots |")
    print("| --- | --- | --- | --- | --- | --- |")
    for r in sorted(vu, key=lambda r: -float(r[6]))[:a.top]:
        pc, h = int(r[1], 16), int(r[2], 16)
        print("| %s %s | %.1f | %.1f | %.3f | %.1f %% | %s |" % (r[1], r[2], int(r[3]) / nf, int(r[4]) / nf / 1000.0,
              float(r[6]) / nf, 100.0 * float(r[6]) / tot_ms, name_prog(pc, h)))
    print()
    gs = rows(os.path.join(a.dir, "f%d-%d_gs.tsv" % (lo, hi)))
    draws = [r for r in gs if r[0] == "draw"]
    tot_p = sum(int(r[1]) for r in draws) or 1
    tot_px = sum(int(r[2]) for r in draws) or 1
    print("GS: %.0f primitives and %.0f k bounding-box pixels (native) per field\n" % (tot_p / nf, tot_px / nf / 1000.0))

    def facet(name, pat, none="-"):
        c = collections.Counter(); px = collections.Counter()
        for r in draws:
            m = re.findall(pat, r[5])
            k = " ".join(m) if m else none
            c[k] += int(r[1]); px[k] += int(r[2])
        print("| %s | prims/field | share | k px/field |" % name)
        print("| --- | --- | --- | --- |")
        for k, n in c.most_common(12):
            print("| %s | %.0f | %.1f %% | %.1f |" % (k, n / nf, 100.0 * n / tot_p, px[k] / nf / 1000.0))
        print()

    facet("primitive", r"^(\w+ \w+)")
    facet("blend (ABE)", r"blend\([^ ]+", "none")
    facet("alpha test", r"atest\d/fail\d", "off")
    facet("dest. alpha test", r"date\d", "off")
    facet("depth test / write", r"(z(?:ge|gt|never|notest)(?: zwrite)?)")
    facet("texture format", r"tex psm\w+(?: clut\d+)?", "untextured")
    facet("texture function / filter", r"tfx\d tcc\d mag\d min\d mxl\d lcm\d (?:uv|stq)", "untextured")
    facet("frame format", r"(fb\w\w(?: fbmsk)?)")
    facet("Z format (Z tested or written)", r"z3\w$", "no Z")
    facet("fog", r"fog", "off")
    rtt = sum(int(r[3]) for r in draws); rttc = sum(int(r[4]) for r in draws)
    print("Render to texture: %.1f primitives per field sample pages a draw of the range wrote, %.1f take their CLUT from such pages.\n"
          % (rtt / nf, rttc / nf))
    for r in gs:
        if r[0] == "xfer":
            print("- %s: %.2f transfers, %.1f KB per field" % (r[5], int(r[1]) / nf, int(r[2]) / nf / 1024.0))
    print()
    print("Top states by pixels:\n")
    print("| prims/field | k px/field | RTT prims | state |")
    print("| --- | --- | --- | --- |")
    for r in sorted(draws, key=lambda r: -int(r[2]))[:a.top]:
        print("| %.0f | %.1f | %.1f | %s |" % (int(r[1]) / nf, int(r[2]) / nf / 1000.0, int(r[3]) / nf, r[5]))
    print()
