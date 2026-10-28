#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of the game's IOP / SIF / pad / memory-card surface (docs/NATIVE-IOP.md section 1).

    python tools/native/iop_census.py static  [--out census/native_iop_static.tsv]
    python tools/native/iop_census.py dynamic CENSUS.tsv [CENSUS2.tsv ...] [--out census/native_iop_dynamic.tsv]
    python tools/native/iop_census.py compare NATIVE.tsv HLE.tsv

static   scans game/src with overrides in place of the files they replace (the build's
         view) for every call into the IOP-facing SDK surface: SIF RPC / DMA / iopheap /
         loadfile / iopcontrol / fileio (sceSif*, sceFsReset, sceOpen...), libsdr
         (sceSdRemote*), libpad (scePad*), libmc (sceMc*), and the game's own IOP
         wrappers (IopHeap*, SifDmaSendSync*, IopLoadModuleRetry, LoadIopModules,
         IopRebootWithImage).  For each call site: caller, callee, unit, whether the
         unit is an override, plus the callers of the callers up to 2 levels (the game
         API layer that reaches the IOP).  Units excluded from the build (asm SDK units,
         game/EXCLUDED.tsv) are skipped: the port provides those functions itself.
dynamic  reads the table rg-game writes at exit with RG_IOP_CENSUS=path (layer api =
         SDK entries the game reached, hle = entries into src/ps2/{sif,iop}, padman /
         mcserv, the sound HLE; unconverted = native-mode IOP uses with no native
         service) and prints / writes the merged counts.  RPC rows carry
         id = (sid & 0xFFFFF) << 12 | fno.
compare  native vs hle census of the same route: which SDK entries each mode reached,
         and the proof line (HLE entries in native mode, must be 0).

Pure text processing, no build needed (dynamic needs a run).
"""
from __future__ import annotations

import argparse
import csv
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from fs_census import PORT, game_sources, scan_file  # noqa: E402

SURFACE = re.compile(
    r"^(sceSif\w+|isceSif\w+|sceFsReset\w*|sceOpen(_\w+)?|sceClose(_\w+)?|sceRead(_\w+)?|"
    r"sceWrite(_\w+)?|sceLseek(_\w+)?|sceSdRemote\w*|scePad\w+|sceMc\w+|"
    r"IopHeap\w+|SifDmaSendSync_\w+|IopLoadModuleRetry_\w+|LoadIopModules_\w+|"
    r"IopRebootWithImage_\w+)$")


def area(callee: str) -> str:
    if callee.startswith(("scePad",)):
        return "pad"
    if callee.startswith("sceMc"):
        return "memcard"
    if callee.startswith("sceSd"):
        return "sdremote"
    if re.match(r"^(sceOpen|sceClose|sceRead|sceWrite|sceLseek|sceFsReset)", callee):
        return "fileio"
    if re.search(r"Heap", callee):
        return "iopheap"
    if re.search(r"Dma", callee):
        return "sifdma"
    if re.search(r"LoadModule|LoadIopModules|LoadFile|LoadStart", callee):
        return "loadfile"
    if re.search(r"Reboot|SyncIop|ResetIop|AliveIop", callee):
        return "iopcontrol"
    if re.search(r"Rpc|Cmd|Sreg|Reg", callee):
        return "sifrpc"
    return "sif"


def excluded_units() -> set[str]:
    out = set()
    p = PORT / "game" / "EXCLUDED.tsv"
    if p.exists():
        with p.open(encoding="utf-8") as f:
            for row in csv.DictReader(f, delimiter="\t"):
                out.add(row.get("file", ""))
    return out


def cmd_static(a) -> int:
    srcs = game_sources()
    excl = excluded_units()
    calls = []                       # (caller, callee, rel, line, override)
    callers_of = defaultdict(set)    # callee -> callers (whole game, for the upward walk)
    for rel, path in sorted(srcs.items()):
        if rel in excl:
            continue
        ovr = "overrides" in path.parts
        for fn, callee, ln, _txt in scan_file(path):
            callers_of[callee].add(fn)
            if SURFACE.match(callee) and fn != callee:
                calls.append((fn, callee, rel, ln, ovr))
    rows = []
    for fn, callee, rel, ln, ovr in calls:
        up1 = sorted(callers_of.get(fn, ()))
        up2 = sorted({c for u in up1 for c in callers_of.get(u, ())})
        rows.append((area(callee), callee, fn, rel, ln, "override" if ovr else "game",
                     ",".join(up1[:6]) + ("..." if len(up1) > 6 else ""),
                     ",".join(up2[:6]) + ("..." if len(up2) > 6 else "")))
    rows.sort()
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f, delimiter="\t", lineterminator="\n")
        w.writerow(["area", "callee", "caller", "unit", "line", "kind", "callers_1", "callers_2"])
        w.writerows(rows)
    by = Counter(r[0] for r in rows)
    print(f"{len(rows)} call sites -> {out}")
    for k, v in sorted(by.items()):
        callers = sorted({r[2] for r in rows if r[0] == k})
        print(f"  {k:10s} {v:4d} sites, {len(callers)} callers: {', '.join(callers[:8])}{' ...' if len(callers) > 8 else ''}")
    return 0


def read_census(path: str) -> tuple[dict, dict]:
    rows: dict[tuple, int] = {}
    meta = {}
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        if line.startswith("# totals"):
            for kv in line.split("\t")[1:]:
                k, _, v = kv.partition(" ")
                meta[k] = int(v)
            continue
        if line.startswith("# rg_iop census"):
            m = re.search(r"mode (\w+)", line)
            meta["mode"] = m.group(1) if m else "?"
            continue
        if line.startswith("#") or line.startswith("layer\t") or not line.strip():
            continue
        layer, name, ident, n = line.split("\t")
        rows[(layer, name, ident)] = rows.get((layer, name, ident), 0) + int(n)
    return rows, meta


def fmt_id(name: str, ident: str) -> str:
    v = int(ident, 16)
    if v and name in ("sceSifCallRpc", "sif_rpc_call"):
        sid = v >> 12
        sid = sid | 0x80000000 if sid < 0x100000 and sid & 0xF0000 == 0 else sid
        return f"sid 0x{sid:X} fno 0x{v & 0xFFF:X}"
    return ident if v else ""


def cmd_dynamic(a) -> int:
    total: Counter = Counter()
    metas = []
    for p in a.census:
        rows, meta = read_census(p)
        metas.append((p, meta))
        for k, n in rows.items():
            total[k] += n
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f, delimiter="\t", lineterminator="\n")
        w.writerow(["layer", "name", "id", "what", "count"])
        for (layer, name, ident), n in sorted(total.items()):
            w.writerow([layer, name, ident, fmt_id(name, ident), n])
    for p, meta in metas:
        print(f"{p}: mode {meta.get('mode')}, api {meta.get('api')}, hle {meta.get('hle')}, "
              f"hle_in_native_mode {meta.get('hle_in_native_mode')}, unconverted {meta.get('unconverted', 0)}")
    for layer in ("api", "unconverted", "hle"):
        items = [(k, n) for k, n in total.items() if k[0] == layer]
        if not items:
            continue
        print(f"[{layer}] {len(items)} rows, {sum(n for _, n in items)} calls")
        for (l, name, ident), n in sorted(items, key=lambda x: -x[1])[: a.top]:
            print(f"  {n:10d}  {name} {fmt_id(name, ident)}")
    print(f"-> {out}")
    return 0


def cmd_compare(a) -> int:
    nat, nm = read_census(a.native)
    hle, hm = read_census(a.hle)

    def names(rows, layer):
        c = Counter()
        for (l, name, _i), n in rows.items():
            if l == layer:
                c[name] += n
        return c

    na, ha = names(nat, "api"), names(hle, "api")
    print(f"native: mode {nm.get('mode')}  hle entries {nm.get('hle')}  in native mode "
          f"{nm.get('hle_in_native_mode')}  unconverted {nm.get('unconverted', 0)}")
    print(f"hle:    mode {hm.get('mode')}  hle entries {hm.get('hle')}")
    print(f"{'SDK entry':32s} {'native':>10s} {'hle':>10s}")
    for k in sorted(set(na) | set(ha)):
        print(f"{k:32s} {na.get(k, 0):10d} {ha.get(k, 0):10d}")
    hh = names(hle, "hle")
    print(f"HLE layer entries in the hle run: {sum(hh.values())} "
          f"({', '.join(f'{k} {v}' for k, v in hh.most_common(8))})")
    ok = nm.get("hle_in_native_mode", 1) == 0 and nm.get("unconverted", 1) == 0
    print("PROOF: native run made 0 HLE entries and 0 unconverted IOP uses" if ok else
          "PROOF FAILED: native run entered the HLE or used the IOP")
    return 0 if ok else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("static")
    s.add_argument("--out", default=str(PORT / "census" / "native_iop_static.tsv"))
    d = sub.add_parser("dynamic")
    d.add_argument("census", nargs="+")
    d.add_argument("--top", type=int, default=40)
    d.add_argument("--out", default=str(PORT / "census" / "native_iop_dynamic.tsv"))
    c = sub.add_parser("compare")
    c.add_argument("native")
    c.add_argument("hle")
    a = ap.parse_args(argv)
    return {"static": cmd_static, "dynamic": cmd_dynamic, "compare": cmd_compare}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
