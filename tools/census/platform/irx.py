"""IOP module (IRX) reader for the SIF RPC census.

Reads every retail IRX in work/MODULES plus each module inside IOPRP300.IMG
(a ROMDIR image), and finds:
  - the module name/version (PT_SCE_IOPMOD header)
  - its import stubs (0x41E00000 tables: `jr $ra; addiu $0,$0,N`)
  - every call to sifcmd export 17 (sceSifRegisterRpc) and 15
    (sceSifBindRpc), with the server id in $a1 recovered by a backward scan
    for lui/ori/addiu into $5 in the same straight-line stretch.
"""
from __future__ import annotations

import struct
from pathlib import Path

MOD_DIR = Path("../work/MODULES")
SIFCMD_EXPORTS = {14: "sceSifInitRpc", 15: "sceSifBindRpc", 16: "sceSifCallRpc",
                  17: "sceSifRegisterRpc", 22: "sceSifRpcLoop"}


def romdir(data: bytes):
    ents, i = [], 0
    while True:
        name, ext, size = struct.unpack_from("<10sHI", data, i * 16)
        if name[0] == 0:
            break
        ents.append((name.rstrip(b"\0").decode(), size))
        i += 1
    off = 0
    for name, size in ents:
        yield name, data[off:off + size]
        off += (size + 15) & ~15


def modules():
    for p in sorted(MOD_DIR.glob("*.IRX")):
        yield p.name, p.stem, p.read_bytes()
    img = MOD_DIR / "IOPRP300.IMG"
    if img.exists():
        for name, blob in romdir(img.read_bytes()):
            if blob[:4] == b"\x7fELF":
                yield f"IOPRP300.IMG:{name}", name, blob


def parse(blob: bytes):
    """-> dict(name, version, text(bytes), vbase, imports{addr:(lib,n)})"""
    phoff = struct.unpack_from("<I", blob, 0x1C)[0]
    phnum = struct.unpack_from("<H", blob, 0x2C)[0]
    info = {"name": "?", "version": "", "text": b"", "vbase": 0, "imports": {}}
    for i in range(phnum):
        ty, off, va, pa, fsz, msz, fl, al = struct.unpack_from("<8I", blob, phoff + 32 * i)
        if ty == 0x70000080:  # PT_SCE_IOPMOD
            ver = struct.unpack_from("<H", blob, off + 0x18)[0]
            nm = blob[off + 0x1A:off + 0x1A + 64].split(b"\0")[0]
            info["name"] = nm.decode("latin-1")
            info["version"] = f"{ver >> 8}.{ver & 0xFF}"
        elif ty == 1 and not info["text"]:
            info["text"] = blob[off:off + fsz]
            info["vbase"] = va
    t = info["text"]
    n = len(t) // 4
    ws = struct.unpack_from(f"<{n}I", t, 0)
    i = 0
    while i < n:
        if ws[i] == 0x41E00000 and i + 5 < n:
            lib = t[4 * i + 12:4 * i + 20].split(b"\0")[0].decode("latin-1")
            j = i + 5
            while j + 1 < n and ws[j] == 0x03E00008 and (ws[j + 1] >> 16) == 0x2400:
                info["imports"][info["vbase"] + 4 * j] = (lib, ws[j + 1] & 0xFFFF)
                j += 2
            i = j
        else:
            i += 1
    info["words"] = ws
    return info


def sx16(v):
    return v - 0x10000 if v & 0x8000 else v


def rpc_sites(info):
    """[(kind, site_vaddr, sid or None)] for RegisterRpc/BindRpc calls."""
    ws, vb = info["words"], info["vbase"]
    out = []
    for i, w in enumerate(ws):
        if (w >> 26) != 3:
            continue
        tgt = (w & 0x3FFFFFF) << 2
        imp = info["imports"].get(tgt)
        if not imp or imp[0] != "sifcmd" or imp[1] not in (15, 17):
            continue
        # backward scan (incl. delay slot) for $5
        val, hi = None, None
        seq = list(range(max(0, i - 16), i)) + [i + 1]
        regs = {}
        for k in seq:
            x = ws[k]
            op, rs, rt = x >> 26, (x >> 21) & 31, (x >> 16) & 31
            if op in (2, 3) and k != i + 1:
                regs = {}
                continue
            if op == 0x0F:
                regs[rt] = (x & 0xFFFF) << 16
            elif op == 0x0D:
                b = regs.get(rs, 0 if rs == 0 else None)
                regs[rt] = None if b is None else b | (x & 0xFFFF)
            elif op == 0x09:
                b = regs.get(rs, 0 if rs == 0 else None)
                regs[rt] = None if b is None else (b + sx16(x & 0xFFFF)) & 0xFFFFFFFF
            elif op == 0 and (x & 63) in (0x21, 0x25):
                rd = (x >> 11) & 31
                a, b = regs.get(rs, 0 if rs == 0 else None), regs.get(rt, 0 if rt == 0 else None)
                regs[rd] = a if b == 0 else (b if a == 0 else None)
            elif op in (0x23, 0x20, 0x24, 0x21, 0x25):
                regs[rt] = None
        val = regs.get(5)
        out.append((SIFCMD_EXPORTS[imp[1]], vb + 4 * i, val))
    return out
