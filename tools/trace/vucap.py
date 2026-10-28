# SPDX-License-Identifier: CC0-1.0
"""VU1/VIF1 frame capture from a running portable PCSX2 (docs/VALIDATION.md
item 5; capture format VIFCAP1 from docs/VU.md).

Everything here is learned by observation, never from PCSX2's source:

* PCSX2's savestate zip holds vu1Memory.bin / vu1MicroMem.bin (16 KB each),
  eeHwRegs.bin (the 64 KB 0x10000000 register page) and, in
  'PCSX2 Internal Structures.dat', a 'vuMicroRegs' block with the VU0 and VU1
  register files (VF0 = (0,0,0,1.0) marks each). The layout used below was
  inferred from those files (see VU_REGS_*).
* The live process holds the same bytes. locate() takes one savestate,
  freezes the CPU thread at the next vsync and searches the process for
  them, giving the host addresses to read at later vsyncs. That makes
  consecutive-vsync captures possible without consecutive savestates (PINE
  save requests issued while the CPU thread is frozen hang PCSX2).

A capture of game frame F (VIFCAP1, little-endian):
    "VIFCAP1\\0" u32 n_records, records {u32 kind, u32 bytes, payload}:
    kind 1  VU1 state (start of frame): data[16384] code[16384] vf[32][4]u32
            vi[16]u16 acc[4]u32 q p i r mac status clip tpc (u32 each)
    kind 2  VIF1 regs (start of frame): cl wl mode mask row[4] col[4] base
            ofst tops itops dbf (u32 each)
    kind 3  VIF1 words: the DMA chain the game kicked (Vif1DmaStart_15e070),
            walked from EE RAM at the next vsync; tag upper halves included
            when TTE=1 (D_CTRL... the game's CHCR has TTE set: see report)
    kind 5  (extension) VU1 data memory at the END of the frame (next
            vsync), the replay's expected result
    kind 7  (extension) VU1 code memory at the end of the frame
    kind 6  (extension) meta: u32 frame, game vbl, kick Count, chain addr,
            chain qwords, vsync cycles before/after
"""
import struct
import zipfile

VF0 = bytes(12) + struct.pack("<f", 1.0)
# Observed in v2.6.3 states: 'vuMicroRegs' tag (32-byte name) + 16 bytes,
# then VU0's VURegs, VU1's follows at +VU_REGS_STRIDE.
VU_REGS_STRIDE = 0x5B6
VF_OFF, VI_OFF, VI_STRIDE = 0x000, 0x200, 0x10
ACC_OFF = 0x400


def state_parts(path):
    z = zipfile.ZipFile(path)
    internal = z.read("PCSX2 Internal Structures.dat")
    t = internal.find(b"vuMicroRegs\0")
    vu0 = internal.find(VF0, t)
    return {
        "ee": z.read("eeMemory.bin"),
        "vu1mem": z.read("vu1Memory.bin"), "vu1code": z.read("vu1MicroMem.bin"),
        "vu0mem": z.read("vu0Memory.bin"), "vu0code": z.read("vu0MicroMem.bin"),
        "hw": z.read("eeHwRegs.bin"),
        "vu0regs": internal[vu0:vu0 + VU_REGS_STRIDE],
        "vu1regs": internal[vu0 + VU_REGS_STRIDE:vu0 + 2 * VU_REGS_STRIDE],
        "internal": internal,
    }


def regs_fields(r):
    vf = r[VF_OFF:VF_OFF + 0x200]
    vi = [struct.unpack_from("<I", r, VI_OFF + VI_STRIDE * k)[0] for k in range(32)]
    acc = r[ACC_OFF:ACC_OFF + 16]
    return vf, vi, acc


def vif1_regs_from_hw(hw):
    """VIF1 registers at 0x10003C00 (eeHwRegs offset 0x3C00), 16-byte spaced:
    STAT FBRST ERR MARK CYCLE MODE NUM MASK CODE ITOPS BASE OFST TOPS ITOP TOP
    ... R0-R3 at +0x100, C0-C3 at +0x140 (EE User's Manual register map)."""
    g = lambda o: struct.unpack_from("<I", hw, 0x3C00 + o)[0]
    cyc = g(0x40)
    return {"cl": cyc & 0xFF, "wl": (cyc >> 8) & 0xFF, "mode": g(0x50), "mask": g(0x70),
            "row": [g(0x100 + 0x10 * k) for k in range(4)], "col": [g(0x140 + 0x10 * k) for k in range(4)],
            "base": g(0xA0), "ofst": g(0xB0), "tops": g(0xC0), "itops": g(0x90),
            "dbf": (g(0x00) >> 7) & 1, "stat": g(0x00), "top": g(0xE0), "itop": g(0xD0)}


def walk_chain(ee, tadr, tte=False, limit=1 << 20):
    """Walk a source-chain DMA list (EE User's Manual DMAtag: QWC [15:0], ID
    [30:28], ADDR [62:32]) and return the VIF word stream as the DMAC would
    deliver it. IDs: 0 refe, 1 cnt, 2 next, 3 ref, 4 refs, 5 call, 6 ret,
    7 end. Returns (words, tags) or raises on a malformed chain."""
    out = []
    tags = []
    stack = []
    addr = tadr & 0x1FFFFFF0
    n = 0
    while True:
        n += 1
        if n > limit:
            raise ValueError("chain too long")
        lo_, hi_ = struct.unpack_from("<II", ee, addr)
        qwc = lo_ & 0xFFFF
        tid = (lo_ >> 28) & 7
        irq = lo_ >> 31
        a = hi_ & 0x7FFFFFF0
        tags.append((addr, tid, qwc, a))
        if tte:
            out.append(struct.unpack_from("<4I", ee, addr)[2:4])
        if tid in (1, 5, 6, 7):          # data follows the tag
            src = addr + 16
        else:
            src = a & 0x1FFFFFF0
        if a & 0x80000000 and tid in (0, 3, 4):
            raise ValueError("scratchpad ref not supported")
        data = ee[src:src + 16 * qwc]
        out.append(struct.unpack("<%dI" % (4 * qwc), data) if qwc else ())
        if tid == 0:                       # refe
            break
        elif tid == 1:                     # cnt
            addr = src + 16 * qwc
        elif tid == 2:                     # next
            addr = a & 0x1FFFFFF0
        elif tid in (3, 4):                # ref / refs
            addr = addr + 16
        elif tid == 5:                     # call
            stack.append(src + 16 * qwc)
            if len(stack) > 2:
                raise ValueError("call depth")
            addr = a & 0x1FFFFFF0
        elif tid == 6:                     # ret
            if not stack:
                break
            addr = stack.pop()
        elif tid == 7:                     # end
            break
        if irq:
            pass                           # tag IRQ: the DMAC would stop if CHCR.TIE; game's chain uses none
    words = []
    for w in out:
        words.extend(w)
    return words, tags


def write_vifcap(path, recs):
    with open(path, "wb") as f:
        f.write(b"VIFCAP1\0" + struct.pack("<I", len(recs)))
        for kind, payload in recs:
            f.write(struct.pack("<II", kind, len(payload)) + payload)


def vu1_state_payload(mem, code, regs):
    vf, vi, acc = regs_fields(regs)
    vi16 = struct.pack("<16H", *[v & 0xFFFF for v in vi[:16]])
    # VI[16..] control registers: 16 status, 17 MAC, 18 clip, 20 R, 21 I,
    # 22 Q, 23 P, 26 TPC (VU manual's CCR numbering)
    q, p, i, r = vi[22], vi[23], vi[21], vi[20]
    mac, status, clip, tpc = vi[17], vi[16], vi[18], vi[26]
    return mem + code + vf + vi16 + acc + struct.pack("<8I", q, p, i, r, mac, status, clip, tpc)


def vif1_payload(v):
    return struct.pack("<4I", v["cl"], v["wl"], v["mode"], v["mask"]) + struct.pack("<4I", *v["row"]) + \
        struct.pack("<4I", *v["col"]) + struct.pack("<5I", v["base"], v["ofst"], v["tops"], v["itops"], v["dbf"])


# ------------------------------------------------------------------ build
def load_raw(path):
    z = zipfile.ZipFile(path)
    fr = {n[:-4]: z.read(n) for n in z.namelist() if n.endswith(".bin")}
    fr["cycle"] = int(z.read("cycle.txt"))
    return fr


VU1_REGS_LIVE = 0x600     # VU1 VURegs after VU0's in the live process (see VALIDATION.md)


def build(jsonl, outdir, count_offset, regs_off=VU1_REGS_LIVE):
    """Pair consecutive raw vsync frames around each Vif1DmaStart kick and
    write VIFCAP1 files."""
    import json
    import os
    kicks, frames = [], []
    for line in open(jsonl, encoding="utf-8"):
        o = json.loads(line)
        if o["t"] == "r" and o["fn"] == "Vif1DmaStart":
            kicks.append(o)
        elif o["t"] == "vuframe":
            frames.append(o)
    frames.sort(key=lambda o: o["cycle"])
    os.makedirs(outdir, exist_ok=True)
    made = []
    for f0, f1 in zip(frames, frames[1:]):
        d = (f1["cycle"] - f0["cycle"]) & 0xFFFFFFFF
        if abs(d - 4920120) > 3000:
            continue
        inside = [k for k in kicks if 0 < ((k["cnt"] + count_offset - f0["cycle"]) & 0xFFFFFFFF) < d
                  and abs(k["vbl"] - f0["vbl"]) <= 3]     # the u32 cycle wraps every 873 frames
        if len(inside) != 1:
            continue
        k = inside[0]
        a, b = load_raw(f0["file"]), load_raw(f1["file"])
        d1a = struct.unpack("<8I", a["d1"])
        d1b = struct.unpack("<8I", b["d1"])
        busy0, busy1 = (d1a[0] >> 8) & 1, (d1b[0] >> 8) & 1
        # CHCR after the transfer (vsync k+1) holds the kick's mode; before
        # the kick it may hold another transfer's. Vif1DmaStart_15e070 sets
        # TTE (bit 6) itself before sceDmaSend.
        tte = (d1b[0] >> 6) & 1
        try:
            words, tags = walk_chain(b["ee"], k["a"][0], tte=bool(tte))
            words0, _ = walk_chain(a["ee"], k["a"][0], tte=bool(tte))
        except (ValueError, struct.error) as ex:
            print("frame %d: chain walk failed: %s" % (f0["vbl"], ex))
            continue
        stable = words0 == words
        vb = a["vublock"]
        mem0, code0 = vb[0x6000:0xA000], vb[0x2000:0x6000]
        mem1 = b["vublock"][0x6000:0xA000]
        regs1 = a["regs"][regs_off:regs_off + VU_REGS_STRIDE]
        page = bytearray(0x10000)
        for j in range(24):
            page[0x3C00 + 0x10 * j:0x3C04 + 0x10 * j] = a["vif1"][4 * j:4 * j + 4]
        vif = vif1_regs_from_hw(bytes(page))
        meta = struct.pack("<8I", f0["vbl"], f0["vbl"], k["cnt"], k["a"][0], len(words) // 4,
                           f0["cycle"], f1["cycle"], busy0 | (busy1 << 1) | (tte << 2) | (int(stable) << 3))
        recs = [(1, vu1_state_payload(mem0, code0, regs1)), (2, vif1_payload(vif)),
                (3, struct.pack("<%dI" % len(words), *words)), (5, mem1), (6, meta),
                (7, b["vublock"][0x2000:0x6000])]
        name = os.path.join(outdir, "%s_v%05d.vifcap" % (os.path.splitext(os.path.basename(jsonl))[0], f0["vbl"]))
        write_vifcap(name, recs)
        made.append(name)
        print("%s: kick %08x, %d tags, %d words, D1 busy before/after %d/%d, TTE %d, chain stable %s, "
              "VU1 mem changed %d qw" % (name, k["a"][0], len(tags), len(words), busy0, busy1, tte, stable,
                                         sum(1 for i in range(0, 0x4000, 16) if mem0[i:i + 16] != mem1[i:i + 16])))
    return made


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["build"])
    ap.add_argument("jsonl")
    ap.add_argument("--out", default="out/captures")
    ap.add_argument("--count-offset", type=int, required=True,
                    help="EE cycle - COP0 Count, from a savestate of the same run")
    ap.add_argument("--regs-off", type=lambda x: int(x, 0), default=VU1_REGS_LIVE)
    a = ap.parse_args()
    build(a.jsonl, a.out, a.count_offset, a.regs_off)
