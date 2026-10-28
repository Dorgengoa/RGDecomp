#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compile the derived x64 game tree (tools/x64/derive.py) TU by TU with full
codegen, from an i686 build's compile_commands.json, and classify the errors.
A CMake-free fast loop for the ptr32/addr32 stages (P7 step 2/3 gate before
the real x64 build).

    python tools/x64/xprobe.py --src build/x64-src --db build/<i686 dir> --out build/x64-xprobe
                               [-j 8] [--only REGEX] [--layout] [--retry-failed]

Per TU: x86_64-pc-windows-msvc, -m32 dropped, -include port/x64.h,
-fno-optimize-sibling-calls (a missed RG_FPC call site is then an isel error,
never a silent miscompile: tools/stages/ptr32.py), objects to <out>/obj.
--layout also dumps record layouts of the x64 compile and of the i686
compile of the ORIGINAL file and lists records whose size/offsets differ
(the ptr32 layout gate).  Results are cached in <out>/results.jsonl keyed by
the source hash + command; <out>/summary.txt has the error classes.
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import json
import re
import shlex
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

import os
ROOT = Path(os.environ.get("RG_PORT_ROOT", Path(__file__).resolve().parents[2]))
sys.path.insert(0, str(ROOT / "tools" / "census"))
from x64_probe import (LAYOUT, i686_cmd, parse_layouts, summarize_layouts)  # noqa: E402

DIAG_RE = re.compile(r"^(.*?):(\d+):(\d+): (error|fatal error): (.*?)(?: \[([^\]]+)\])?$")
BS = chr(92)


def norm(p: str) -> str:
    return p.replace(BS, "/")


def map_src(f: str, port: str, src: str) -> str | None:
    f = norm(f)
    for tree in ("game", "overrides", "missing"):
        pre = f"{port}/{tree}/"
        if f.startswith(pre):
            return f"{src}/{tree}/{f[len(pre):]}"
    return None


def x64_args(args: list[str], port: str, src: str, newsrc: str, obj: str, x64inc: str) -> list[str]:
    out, skip = [], False
    for a in args:
        if skip:
            skip = False
            continue
        if a == "-o":
            skip = True
            continue
        if a == "-c":
            continue
        if a.startswith("--target="):
            a = "--target=x86_64-pc-windows-msvc"
        if a == "-m32":
            continue
        if a.startswith("-I"):
            p = norm(a[2:])
            if p == f"{port}/game/include":
                a = f"-I{src}/game/include"
        if norm(a) in (norm(args[-1]),):
            a = newsrc
        out.append(a)
    # the source file (last arg) -> derived; x64 header first
    out = [out[0], f"-I{x64inc}", "-include", "port/x64.h"] + out[1:]
    out += ["-fno-optimize-sibling-calls", "-fno-jump-tables", "-fno-vectorize", "-fno-slp-vectorize", "-fno-caret-diagnostics", "-fno-color-diagnostics",
            "-c", "-o", obj]
    return out


def run(e, a, outdir: Path):
    args = shlex.split(norm(e["command"]), posix=True)
    f = norm(e["file"])
    port = norm(str(a.port))
    src = norm(str(Path(a.src).resolve()))
    newsrc = map_src(f, port, src)
    if newsrc is None:
        return None
    h = hashlib.sha1((Path(newsrc).read_bytes() if Path(newsrc).exists() else b"") + e["command"].encode()).hexdigest()
    obj = outdir / "obj" / (hashlib.sha1(f.encode()).hexdigest()[:16] + ".obj")
    obj.parent.mkdir(parents=True, exist_ok=True)
    xa = x64_args(args, port, src, newsrc, str(obj), norm(str(Path(a.x64inc).resolve())))
    if a.layout:
        # layouts are a front-end product: no object (the error gate is the full run)
        i = xa.index("-c")
        xa = xa[:i] + ["-fsyntax-only"] + xa[i + 3:] + LAYOUT
    r = subprocess.run(xa, cwd=e["directory"], capture_output=True, text=True,
                       encoding="utf-8", errors="replace")
    errs = []
    for ln in r.stderr.splitlines():
        m = DIAG_RE.match(ln)
        if m:
            errs.append([norm(m.group(1)), int(m.group(2)), m.group(5)])
        elif "Cannot select" in ln or "error in backend" in ln or "unsupported expression" in ln:
            errs.append([newsrc, 0, ln.strip()[:200]])
    res = {"file": f, "src": newsrc, "rc": r.returncode, "errs": errs, "h": h}
    if a.layout:
        r32 = subprocess.run(i686_cmd(args) + LAYOUT, cwd=e["directory"], capture_output=True,
                             text=True, encoding="utf-8", errors="replace")
        left = summarize_layouts(parse_layouts(r32.stdout), parse_layouts(r.stdout))
        res["left"] = [(d["name"], d["size32"], d["size64"]) for d in left]
        res["nrec"] = len(parse_layouts(r32.stdout))
    return res


def eclass(msg: str) -> str:
    m = re.sub(r"'[^']*'", "Q", msg)
    m = re.sub(r"\d+", "N", m)
    return m[:110]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default=str(ROOT / "build" / "x64-src"))
    ap.add_argument("--port", default=str(ROOT))
    ap.add_argument("--x64inc", default=str(ROOT / "include"))
    ap.add_argument("--db", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("-j", "--jobs", type=int, default=8)
    ap.add_argument("--only", default="")
    ap.add_argument("--layout", action="store_true")
    ap.add_argument("--every", type=int, default=1)
    ap.add_argument("--check", action="store_true",
                    help="exit 1 on any compile error or (with --layout) differing game record")
    a = ap.parse_args()
    a.port = Path(a.port)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    db = json.loads((Path(a.db) / "compile_commands.json").read_text(encoding="utf-8"))
    port = norm(str(a.port))
    ents = [e for e in db if map_src(e["file"], port, "x") and
            (not a.only or re.search(a.only, norm(e["file"])))]
    ents = ents[::a.every]
    cache = {}
    rp = out / "results.jsonl"
    if rp.exists():
        for ln in rp.read_text(encoding="utf-8").splitlines():
            try:
                d = json.loads(ln)
                cache[d["file"]] = d
            except Exception:
                pass
    todo = []
    src = norm(str(Path(a.src).resolve()))
    for e in ents:
        f = norm(e["file"])
        ns = map_src(f, port, src)
        h = hashlib.sha1((Path(ns).read_bytes() if Path(ns).exists() else b"") + e["command"].encode()).hexdigest()
        c = cache.get(f)
        if c and c.get("h") == h and (not a.layout or "left" in c):
            continue
        todo.append(e)
    print(f"{len(ents)} TUs, {len(todo)} to compile", flush=True)
    done = 0
    with open(rp, "a", encoding="utf-8") as fo, cf.ThreadPoolExecutor(a.jobs) as ex:
        for r in ex.map(lambda e: run(e, a, out), todo):
            if r is None:
                continue
            cache[r["file"]] = r
            fo.write(json.dumps(r) + "\n")
            done += 1
            if done % 500 == 0:
                print(f"  {done}/{len(todo)}", flush=True)
    res = [cache[norm(e["file"])] for e in ents if norm(e["file"]) in cache]
    fail = [r for r in res if r["rc"]]
    cls = Counter()
    tus = defaultdict(set)
    ex1 = {}
    for r in fail:
        for f, l, m in r["errs"]:
            k = eclass(m)
            cls[k] += 1
            tus[k].add(r["file"])
            ex1.setdefault(k, f"{f}:{l}: {m[:160]}")
    L = [f"{len(res)} TUs, {len(fail)} fail"]
    for k, v in cls.most_common(60):
        L.append(f"{v:6d} {len(tus[k]):5d}  {k}\n              e.g. {ex1[k]}")
    if a.layout:
        left = [(r["file"], n, s32, s64) for r in res for n, s32, s64 in r.get("left", [])]
        L.append(f"layout: {sum(r.get('nrec', 0) for r in res)} records compared, "
                 f"{len(left)} differ in {len({x[0] for x in left})} TUs")
        with open(out / "layout_left.tsv", "w", encoding="utf-8") as fo:
            fo.write("tu\trecord\tsize32\tsize64\n")
            for x in left:
                fo.write("\t".join(map(str, x)) + "\n")
    (out / "summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    with open(out / "fails.tsv", "w", encoding="utf-8") as fo:
        for r in fail:
            for f, l, m in r["errs"]:
                fo.write(f"{r['file']}\t{f}\t{l}\t{m}\n")
    print("\n".join(L[:80]))
    if a.check:
        # gate: no compile error, no game record whose layout differs (host-only structs
        # from the port's own include/ are allowed: HOST_RECORDS)
        game_left = [x for x in (left if a.layout else []) if x[1] not in HOST_RECORDS]
        print(f"xprobe check: {len(fail)} failing TUs, {len(game_left)} differing game records "
              f"-> {'FAIL' if fail or game_left else 'PASS'}")
        return 1 if fail or game_left else 0
    return 0


# port-side host structs visible to game TUs through include/port (never in game memory)
HOST_RECORDS = {"struct rg_thread_conv"}


if __name__ == "__main__":
    sys.exit(main())
