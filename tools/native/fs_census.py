#!/usr/bin/env python3
"""Census of every disc / file access path in the game (docs/NATIVE-FS.md).

    python tools/native/fs_census.py static  [--out census/native_fs_static.tsv]
    python tools/native/fs_census.py dynamic RUN.jsonl [--manifest data/MANIFEST.tsv]
                                             [--out census/native_fs_dynamic.tsv]
    python tools/native/fs_census.py stream A.jsonl B.jsonl [--manifest ...] [--show N]

static   scans game/src (with overrides/ in place of the files they replace) for
         call sites of the disc-access SDK surface (sceCd*, FILEIO sce{Open,Read,..},
         the overlay file loader) and climbs the caller graph to the game's own file
         API.  One row per (caller, callee) edge with its level (1 = calls the SDK
         directly) and per-call-site facts: sync/async sceCdSync mode, sector math.
dynamic  reads a timing record (RG_TIMING JSONL, docs/TIMING-LOCKSTEP.md) and maps
         every disc read to the file it touches: "sceCdRead" records (LSN, sectors;
         the CDVD model) through MANIFEST.tsv, "FsRead" records (native fs) directly.
         One row per file: reads, bytes, sector alignment, vbl span.
stream   compares the read streams of two records (e.g. the CDVD baseline and a
         native run): each read as (file, offset, bytes) in order.  Prints the
         reads in the same position, the reads that only moved (a reorder: both
         streams hold the same multiset), and every read only one side has.
         Exit 0 when the multisets are equal.

Pure text processing, no build needed; rerun after every snapshot bump.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]

# The SDK surface that reaches the disc or the IOP file servers.
LEVEL0 = re.compile(
    r"^(sceCd\w+|CdDiskReadyNewMaybe_\w+|"
    r"sce(Open|Close|Read|Write|Lseek|Lseek64|Remove|Mkdir|Rmdir|Dopen|Dread|Dclose|"
    r"Getstat|Chstat|Ioctl|Ioctl2|Rename|Readlink|Symlink|FsReset)(_[0-9a-f]+)?|"
    r"FileReadAll_1004b0|OverlayLoadFile_100410|sceSifLoadModule\w*)$")

# names that look like calls but are not
NOT_CALL = {"if", "for", "while", "switch", "return", "sizeof", "defined"}

CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
DEF_RE = re.compile(r"^[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*\([^;]*$")


def strip_comments(src: str) -> str:
    src = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), src, flags=re.S)
    src = re.sub(r"//[^\n]*", "", src)
    src = re.sub(r'"(\\.|[^"\\])*"', '""', src)
    src = re.sub(r"'(\\.|[^'\\])*'", "''", src)
    return src


def game_sources() -> dict[str, Path]:
    """relpath -> file actually compiled (override if present)."""
    out: dict[str, Path] = {}
    for base in (PORT / "game" / "src",):
        for p in base.rglob("*"):
            if p.suffix in (".c", ".cpp"):
                out[p.relative_to(PORT / "game").as_posix()] = p
    ovr = PORT / "overrides"
    for p in ovr.rglob("*"):
        if p.suffix in (".c", ".cpp"):
            out[p.relative_to(ovr).as_posix()] = p
    return out


def scan_file(path: Path):
    """Yield (function, callee, line, text) for calls inside function bodies."""
    src = strip_comments(path.read_text(encoding="utf-8", errors="replace"))
    depth = 0
    cur = None
    pending = None
    src = re.sub(r'extern\s*""\s*\{', "", src)   # extern "C" { ... } blocks
    for ln, line in enumerate(src.splitlines(), 1):
        s = line.strip()
        if s.startswith("#"):
            continue
        if depth == 0:
            m = DEF_RE.match(s)
            if m and m.group(1) not in NOT_CALL:
                pending = m.group(1)
        opened = line.count("{")
        if depth == 0 and opened and pending:
            cur = pending
            pending = None
        if depth > 0 or (opened and cur):
            for m in CALL_RE.finditer(line):
                name = m.group(1)
                if cur is None or name in NOT_CALL or name == cur:
                    continue
                yield cur, name, ln, s
        depth += opened - line.count("}")
        if depth <= 0:
            depth = 0
            if not opened:
                pass
            cur = None if line.count("}") else cur
        if s.endswith(";") and depth == 0:
            pending = None


def cmd_static(a) -> int:
    srcs = game_sources()
    calls: dict[str, set[str]] = defaultdict(set)       # caller -> callees
    sites: dict[tuple[str, str], list[str]] = defaultdict(list)
    where: dict[str, str] = {}
    for rel, p in sorted(srcs.items()):
        for fn, callee, ln, text in scan_file(p):
            calls[fn].add(callee)
            where.setdefault(fn, rel)
            sites[(fn, callee)].append(f"{ln}:{text[:90]}")
    callers: dict[str, set[str]] = defaultdict(set)
    for fn, cs in calls.items():
        for c in cs:
            callers[c].add(fn)
    level0 = sorted({c for cs in calls.values() for c in cs if LEVEL0.match(c)})
    # BFS upward
    level: dict[str, int] = {}
    frontier = set()
    for s in level0:
        for c in callers.get(s, ()):
            if not LEVEL0.match(c):
                level.setdefault(c, 1)
                frontier.add(c)
    for depth in (2, 3):
        nxt = set()
        for f in frontier:
            for c in callers.get(f, ()):
                if c not in level and not LEVEL0.match(c):
                    level[c] = depth
                    nxt.add(c)
        frontier = nxt
    rows = []
    for fn, lv in sorted(level.items(), key=lambda kv: (kv[1], kv[0])):
        for callee in sorted(calls[fn]):
            if LEVEL0.match(callee) or (callee in level and level[callee] < lv):
                st = sites[(fn, callee)]
                facts = []
                txt = " ".join(st)
                if callee == "sceCdSync":
                    modes = sorted(set(re.findall(r"sceCdSync\s*\(\s*([^)]*)\)", txt)))
                    facts.append("sync-mode=" + ",".join(modes))
                if re.search(r"lsn|>>\s*11|0x800|0x7FF|bsize", " ".join(
                        t.split(":", 1)[1] for t in st), re.I):
                    facts.append("sector-math")
                rows.append((lv, fn, where.get(fn, "?"), callee, len(st), ";".join(facts)))
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# fs_census.py static: callers of the disc/file SDK surface (level 1) and\n"
                "# their callers (levels 2-3).  callee = an SDK symbol or a lower-level caller.\n")
        f.write("level\tfunction\tfile\tcallee\tsites\tfacts\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")
    by_level = defaultdict(set)
    for lv, fn, *_ in rows:
        by_level[lv].add(fn)
    used0 = sorted({r[3] for r in rows if LEVEL0.match(r[3])})
    print(f"SDK symbols reached: {len(used0)}: {' '.join(used0)}")
    for lv in sorted(by_level):
        print(f"level {lv}: {len(by_level[lv])} functions")
    l1 = sorted(by_level[1])
    print("level 1:", " ".join(l1))
    print(f"wrote {out} ({len(rows)} edges)")
    return 0


def load_manifest(path: Path):
    """[(img_start, nsect, path, size)] sorted; and layer geometry."""
    ext = []
    vols = {}
    for ln in path.read_text(encoding="utf-8").splitlines():
        if ln.startswith("# volume"):
            _, layer, base, size = ln.replace("# volume", "#volume").split()
            vols[int(layer)] = (int(base), int(size))
            continue
        if ln.startswith("# section"):
            break
        if ln.startswith("#") or ln.startswith("path\t"):
            continue
        cols = ln.split("\t")
        p, size = cols[0], int(cols[1])
        copies = cols[4].split(",") if len(cols) > 4 and cols[4] else [f"L0:{cols[3]}"]
        for c in copies:
            _, lba = c.split(":")
            ext.append((int(lba), max(1, (size + 2047) // 2048), p, size))
    ext.sort()
    l1 = vols[1][0] + 16 if 1 in vols else None
    return ext, l1


def lsn_to_file(ext, l1, lsn):
    import bisect
    img = lsn - 16 if (l1 is not None and lsn >= l1) else lsn
    i = bisect.bisect_right(ext, (img, 1 << 62)) - 1
    if i >= 0:
        s, n, p, size = ext[i]
        if s <= img < s + n:
            return p, (img - s) * 2048, size
    return None, img * 2048, 0


def cmd_dynamic(a) -> int:
    ext, l1 = load_manifest(Path(a.manifest))
    per = defaultdict(lambda: {"reads": 0, "bytes": 0, "aligned": 0, "v0": None, "v1": None,
                               "maxlen": 0, "src": set(), "past_eof": 0})
    total = 0
    for line in open(a.jsonl, encoding="utf-8", errors="replace"):
        if '"sceCdRead"' not in line and '"FsRead"' not in line:
            continue
        try:
            r = json.loads(line)
        except Exception:
            continue
        if r.get("k") != "entry":
            continue
        v = r.get("vbl", 0)
        if r["fn"] == "sceCdRead":
            lsn, n = r["a"][0], r["a"][1]
            p, off, size = lsn_to_file(ext, l1, lsn)
            nbytes = n * 2048
            src = "cdvd"
        else:
            d = r.get("d") or []
            p = r.get("file") or "?"
            off = (d[0] | (d[1] << 32)) if len(d) > 1 else 0
            nbytes = d[2] if len(d) > 2 else 0
            size = d[3] if len(d) > 3 else 0
            src = "native"
        e = per[p or "<unmapped>"]
        e["reads"] += 1
        e["bytes"] += nbytes
        e["aligned"] += (off % 2048 == 0 and nbytes % 2048 == 0)
        e["maxlen"] = max(e["maxlen"], nbytes)
        e["past_eof"] += (size and off + nbytes > size)
        e["v0"] = v if e["v0"] is None else e["v0"]
        e["v1"] = v
        e["src"].add(src)
        total += 1
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write(f"# fs_census.py dynamic {Path(a.jsonl).name}: {total} reads\n")
        f.write("file\treads\tbytes\tsector_aligned\tmax_read\tpast_eof\tfirst_vbl\tlast_vbl\tsource\n")
        for p, e in sorted(per.items(), key=lambda kv: -kv[1]["bytes"]):
            f.write(f"{p}\t{e['reads']}\t{e['bytes']}\t{e['aligned']}\t{e['maxlen']}\t"
                    f"{e['past_eof']}\t{e['v0']}\t{e['v1']}\t{','.join(sorted(e['src']))}\n")
    print(f"{total} reads over {len(per)} files -> {out}")
    for p, e in sorted(per.items(), key=lambda kv: -kv[1]["bytes"])[:12]:
        print(f"  {p:28s} {e['reads']:6d} reads {e['bytes'] / 1e6:9.2f} MB")
    return 0


def read_stream(path: str, ext, l1) -> list:
    out = []
    for line in open(path, encoding="utf-8", errors="replace"):
        if '"sceCdRead"' not in line and '"FsRead"' not in line:
            continue
        try:
            r = json.loads(line)
        except Exception:
            continue
        if r.get("k") != "entry":
            continue
        if r["fn"] == "sceCdRead":
            p, off, _ = lsn_to_file(ext, l1, r["a"][0])
            n = r["a"][1] * 2048
        else:
            d = r.get("d") or []
            p = r.get("file") or "?"
            off = (d[0] | (d[1] << 32)) if len(d) > 1 else 0
            n = d[2] if len(d) > 2 else 0
        out.append((p or "<unmapped>", off, n, r.get("vbl", 0)))
    return out


def cmd_stream(a) -> int:
    from collections import Counter
    ext, l1 = load_manifest(Path(a.manifest))
    sa, sb = read_stream(a.a, ext, l1), read_stream(a.b, ext, l1)
    ka = [x[:3] for x in sa]
    kb = [x[:3] for x in sb]
    same = sum(1 for x, y in zip(ka, kb) if x == y)
    ca, cb = Counter(ka), Counter(kb)
    only_a, only_b = ca - cb, cb - ca
    print(f"A {a.a}: {len(ka)} reads, {sum(x[2] for x in ka) / 1e6:.1f} MB")
    print(f"B {a.b}: {len(kb)} reads, {sum(x[2] for x in kb) / 1e6:.1f} MB")
    print(f"same position: {same}; moved (reordered): {len(ka) - same - sum(only_a.values())}; "
          f"only in A: {sum(only_a.values())}; only in B: {sum(only_b.values())}")
    shown = 0
    for i, (x, y) in enumerate(zip(sa, sb)):
        if x[:3] != y[:3] and shown < a.show:
            print(f"  #{i}: A {x[0]}+0x{x[1]:x} {x[2]} (vbl {x[3]})  B {y[0]}+0x{y[1]:x} {y[2]} (vbl {y[3]})")
            shown += 1
    for k, n in list(only_a.items())[:a.show]:
        print(f"  only A: {k[0]}+0x{k[1]:x} {k[2]} x{n}")
    for k, n in list(only_b.items())[:a.show]:
        print(f"  only B: {k[0]}+0x{k[1]:x} {k[2]} x{n}")
    return 0 if not only_a and not only_b else 1


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("static")
    s.add_argument("--out", default=str(PORT / "census" / "native_fs_static.tsv"))
    d = sub.add_parser("dynamic")
    d.add_argument("jsonl")
    d.add_argument("--manifest", default=str(PORT / "data" / "MANIFEST.tsv"))
    d.add_argument("--out", default=str(PORT / "census" / "native_fs_dynamic.tsv"))
    t = sub.add_parser("stream")
    t.add_argument("a")
    t.add_argument("b")
    t.add_argument("--manifest", default=str(PORT / "data" / "MANIFEST.tsv"))
    t.add_argument("--show", type=int, default=20)
    a = ap.parse_args()
    if a.cmd == "stream":
        return cmd_stream(a)
    return cmd_static(a) if a.cmd == "static" else cmd_dynamic(a)


if __name__ == "__main__":
    sys.exit(main())
