# SPDX-License-Identifier: CC0-1.0
"""Post-process rg-game RG_BREAK logs (docs/BRINGUP.md "Diagnostics added").

    brklog.py rows LOG [--map rg-game.map]
        one line per BRK hit: vbl, site name, eax, args, return site name
        (the image base is recovered per hit when ret_rva points at code;
        `--base-from-call` handles a break ON a `call reg` instruction, where
        sp[0] is the pushed argument == eax: base = eax - ret_rva, and ecx is
        resolved as the call target)
    brklog.py structdiff LOG EE_BIN GUEST_BASE [--size N] [--from-site RVA]
        each BRKDUMP (RG_BREAK_DUMP / RG_BREAK_DUMPARG) whose break's first
        argument is a guest pointer, diffed word by word against a PCSX2
        savestate's eeMemory.bin at (pointer - GUEST_BASE); words that look
        like a pointer on both sides are skipped.  GUEST_BASE is the
        "game RAM at XXXXXXXX" address the port prints at start-up.

Extract eeMemory.bin from a probe.py savestate (.p2s is a zip):
    python -c "import zipfile,sys;open(sys.argv[2],'wb').write(zipfile.ZipFile(sys.argv[1]).read('eeMemory.bin'))" S.p2s ee.bin
Original CC0 code.
"""
import argparse
import bisect
import re
import struct


def load_map(path):
    syms = []
    for line in open(path, encoding="latin-1"):
        m = re.match(r"\s*000[1-9]:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{16})\s+", line)
        if m:
            syms.append((int(m.group(2), 16) - 0x400000, m.group(1).lstrip("_")))
    syms.sort()
    return syms, [a for a, _ in syms]


def resolver(path):
    if not path:
        return lambda r: "%#x" % r
    syms, keys = load_map(path)

    def res(r):
        i = bisect.bisect_right(keys, r) - 1
        if i < 0:
            return "%#x" % r
        a, n = syms[i]
        return n if a == r else "%s+%#x" % (n, r - a)
    return res


def hits(path):
    lines = open(path, errors="replace").read().splitlines()
    for i, l in enumerate(lines):
        if not l.startswith("BRK "):
            continue
        f = dict(x.split("=", 1) for x in l.split()[1:] if "=" in x)
        args = [int(x, 16) for x in l.split("args=")[1].split()[:4]]
        dump = None
        stack = []
        for nxt in lines[i + 1:i + 4]:
            if nxt.startswith("BRKDUMP"):
                dump = bytes.fromhex(nxt[8:].replace(" ", ""))
            elif nxt.startswith("BRKSTACK"):
                # RG_BREAK_STACK: "BRKSTACK k:RVA ..." (image words in the first N stack words)
                stack = [int(w.split(":")[1], 16) for w in nxt.split()[1:] if ":" in w]
            elif nxt.startswith("BRK "):
                break
        ret = int(f["ret_rva"], 16) if "ret_rva" in f else (stack[0] if stack else 0)
        yield {"rva": int(f["rva"], 16), "vbl": int(f["vbl"]), "eax": int(f["eax"], 16),
               "ecx": int(f["ecx"], 16), "ret": ret, "args": args, "dump": dump,
               "stack": stack}


def cmd_rows(a):
    res = resolver(a.map)
    for h in hits(a.log):
        s = "%d %s eax=%08x args=%s" % (h["vbl"], res(h["rva"]), h["eax"],
                                         " ".join("%08x" % x for x in h["args"]))
        if a.base_from_call:
            base = (h["eax"] - h["ret"]) & 0xFFFFFFFF
            s += " target=%s" % res((h["ecx"] - base) & 0xFFFFFFFF)
        else:
            s += " from=%s" % res(h["ret"])
            if a.stack and len(h["stack"]) > 1:
                s += " <- " + " <- ".join(res(r) for r in h["stack"][1:a.stack])
        if h["dump"] is not None and a.words:
            s += " dump=" + " ".join("%08x" % w for w in
                                     struct.unpack_from("<%dI" % min(a.words, len(h["dump"]) // 4), h["dump"]))
        print(s)


def cmd_structdiff(a):
    m = open(a.ee_bin, "rb").read()
    base = int(a.guest_base, 16)
    seen = set()
    for h in hits(a.log):
        if h["dump"] is None or (a.from_site and h["rva"] != int(a.from_site, 0)):
            continue
        p = h["args"][0] if a.arg0 else h["eax"]
        if p in seen:
            continue
        seen.add(p)
        g = p - base
        d = h["dump"][:a.size] if a.size else h["dump"]
        r = m[g:g + len(d)]
        print("== %08x (guest %06x) vbl %d" % (p, g, h["vbl"]))
        for o in range(0, len(d) - 3, 4):
            pw, = struct.unpack_from("<I", d, o)
            rw, = struct.unpack_from("<I", r, o)
            if pw == rw:
                continue
            if (pw >> 24) in range(4, 0x80) and 0x100000 < rw < 0x2000000:
                continue            # host pointer vs guest pointer
            print("  +%03x port %08x retail %08x" % (o, pw, rw))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("rows")
    r.add_argument("log")
    r.add_argument("--map")
    r.add_argument("--base-from-call", action="store_true")
    r.add_argument("--words", type=int, default=0, help="print N dump words per hit")
    r.add_argument("--stack", type=int, default=0, help="print up to N BRKSTACK frames (RG_BREAK_STACK)")
    d = sub.add_parser("structdiff")
    d.add_argument("log")
    d.add_argument("ee_bin")
    d.add_argument("guest_base")
    d.add_argument("--size", type=lambda s: int(s, 0), default=0)
    d.add_argument("--from-site")
    d.add_argument("--arg0", action="store_true", help="the dumped object is the first argument, not eax")
    a = ap.parse_args()
    {"rows": cmd_rows, "structdiff": cmd_structdiff}[a.cmd](a)


if __name__ == "__main__":
    main()
