#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x64 probe compile (P7 census, docs/X64-PLAN.md): every translation unit of an
existing i686 build, recompiled for x86_64-pc-windows-msvc, diagnostics counted
by class, struct layouts compared with the i686 ones.  Nothing in the tree is
changed; all output goes to the scratch dir.

    python tools/census/x64_probe.py run   [--db build/soak2-i686] [--out build/x64-probe] [-j 4]
                                           [--limit N] [--only REGEX] [--no-layout]
    python tools/census/x64_probe.py report [--out build/x64-probe]

How each TU is compiled (the i686 command from <db>/compile_commands.json):
  x64 pass    --target=x86_64-pc-windows-msvc, -m32 / -w / -Wno-int-conversion
              dropped, + -Wpointer-to-int-cast -Wint-to-pointer-cast
              -Wshorten-64-to-32 -Wint-conversion(-as-warning)
              -Xclang -fdump-record-layouts.  Game TUs (game/, overrides/,
              missing/) are -fsyntax-only (front-end only, fast); port TUs
              (src/, tests/, tools/) are compiled to an object in
              <out>/obj so back-end errors (inline asm) show up too.
  i686 pass   the original command + -fsyntax-only -w -fdump-record-layouts
              (only for the layout comparison; --no-layout skips it).
Third-party TUs (_deps: SDL3) are skipped (SDL3 builds x64 upstream).

Results are cached per TU in <out>/results.jsonl (a re-run skips TUs already
done with the same command hash), so the run can be interrupted and resumed.
`report` writes:
  <out>/diag_sites.tsv     one row per unique (file, line, col, class) site
  <out>/layout_diff.tsv    one row per unique record whose i686 and x64
                           layouts differ (dedup by name + i686 field list)
  <out>/summary.txt        counts by class x area (what X64-PLAN.md quotes)
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import json
import os
import re
import shlex
import subprocess
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BS = chr(92)
X64_TRIPLE = "x86_64-pc-windows-msvc"
X64_WARN = ["-Wpointer-to-int-cast", "-Wint-to-pointer-cast", "-Wshorten-64-to-32",
            "-Wint-conversion", "-Wno-error=int-conversion"]
DIAG_FMT = ["-fno-caret-diagnostics", "-fno-color-diagnostics", "-fdiagnostics-show-option",
            "-ferror-limit=0"]
# -complete: EVERY complete record (plain -fdump-record-layouts under -fsyntax-only dumps only
# the records Sema needed a layout for: sizeof / constants, not member access)
LAYOUT = ["-Xclang", "-fdump-record-layouts-complete"]
SKIP_RECORDS = ("struct __NSConstantString_tag", "struct __va_list_tag")


def norm(p: str) -> str:
    return p.replace(BS, "/")


def rel(p: str) -> str:
    p = norm(p)
    r = norm(str(ROOT)) + "/"
    if p.lower().startswith(r.lower()):
        return p[len(r):]
    return p


def area(path: str) -> str:
    """Coarse bucket for a (repo-relative) path."""
    p = rel(path)
    parts = p.split("/")
    if p.startswith("game/src/main_data/") or p.startswith("overrides/src/main_data/"):
        return "data2c"
    if p.startswith("game/src/overlays/"):
        return "game-ovl-" + parts[3]
    if p.startswith("game/src/main/"):
        return "game-main"
    if p.startswith("game/include/"):
        return "game-include"
    if p.startswith("overrides/"):
        return "overrides"
    if p.startswith("missing/"):
        return "missing"
    if p.startswith("include/"):
        return "include/" + (parts[1] if len(parts) > 2 else "")
    if p.startswith("src/"):
        return "src/" + parts[1]
    if p.startswith("tests/") or p.startswith("tools/"):
        return parts[0]
    return "other"


def is_game(path: str) -> bool:
    p = rel(path)
    return p.startswith(("game/", "overrides/", "missing/"))


# ------------------------------------------------------------------ commands
def x64_cmd(args: list[str], obj: str | None) -> list[str]:
    out, skip = [], False
    for a in args:
        if skip:
            skip = False
            continue
        if a == "-o":
            skip = True
            continue
        if a == "-c" or a.startswith("-o") and len(a) > 2 and not a.startswith("-O"):
            continue
        if a.startswith("--target="):
            a = "--target=" + X64_TRIPLE
        if a in ("-m32", "-w", "-Wno-int-conversion"):
            continue
        out.append(a)
    out += X64_WARN + DIAG_FMT
    if obj:
        out += ["-c", "-o", obj]
    else:
        out += ["-fsyntax-only"]
    return out


def i686_cmd(args: list[str]) -> list[str]:
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
        out.append(a)
    return out + ["-fsyntax-only", "-w"] + DIAG_FMT


# ------------------------------------------------------------------ parsing
DIAG_RE = re.compile(r"^(.*?):(\d+):(\d+): (warning|error|fatal error): (.*?)(?: \[([^\]]+)\])?$")


def err_class(msg: str) -> str:
    m = re.sub(r"'[^']*'", "Q", msg)
    m = re.sub(r"\b0x[0-9A-Fa-f]+\b|\b\d+\b", "N", m)
    return m[:120]


def parse_diags(stderr: str) -> list[list]:
    """[file, line, col, kind, class] for each warning/error (notes dropped)."""
    out = []
    for ln in stderr.splitlines():
        m = DIAG_RE.match(ln)
        if not m:
            continue
        f, l, c, kind, msg, opt = m.groups()
        if kind == "warning":
            cls = "W:" + (opt.split(",")[0] if opt else err_class(msg))
        else:
            cls = "E:" + err_class(msg)
        out.append([rel(f), int(l), int(c), "error" if "error" in kind else "warning", cls])
    return out


def parse_layouts(stdout: str) -> list[dict]:
    """AST record layouts from -fdump-record-layouts (C and C++)."""
    recs = []
    for blk in stdout.split("*** Dumping AST Record Layout")[1:]:
        lines = blk.strip("\n").splitlines()
        name, fields, size, align = None, [], None, None
        for ln in lines:
            if "|" not in ln:
                continue
            left, _, right = ln.partition("|")
            if right.lstrip().startswith("[sizeof="):
                m = re.search(r"sizeof=(\d+), (?:dsize=\d+, )?align=(\d+)", right)
                if m and size is None:
                    size, align = int(m.group(1)), int(m.group(2))
                continue
            sp = len(right) - len(right.lstrip(" "))
            txt = right.strip()
            if name is None:
                name = txt
                base = sp
                continue
            depth = (sp - base) // 2
            if depth == 1:
                fields.append((left.strip(), txt))
        if name is not None and not name.startswith(SKIP_RECORDS):
            # "(unnamed at <path>:L:C)" -> "(unnamed L:C)": stable across copies of a file
            name = re.sub(r"\(unnamed at [^)]*?:(\d+):(\d+)\)", r"(unnamed \1:\2)", name)
            name = re.sub(r"\(anonymous at [^)]*?:(\d+):(\d+)\)", r"(anonymous \1:\2)", name)
            recs.append({"name": name, "size": size, "align": align, "fields": fields})
    return recs


def summarize_layouts(a: list[dict], b: list[dict]) -> list[dict]:
    """Pair i686 (a) and x64 (b) records by name + occurrence; keep the differing ones."""
    def keyed(rs):
        seen = Counter()
        d = {}
        for r in rs:
            k = (r["name"], seen[r["name"]])
            seen[r["name"]] += 1
            d[k] = r
        return d
    da, db = keyed(a), keyed(b)
    diffs = []
    for k, ra in da.items():
        rb = db.get(k)
        if not rb:
            continue
        offs_a = [f[0] for f in ra["fields"]]
        offs_b = [f[0] for f in rb["fields"]]
        if ra["size"] == rb["size"] and offs_a == offs_b:
            continue
        diffs.append({"name": ra["name"], "size32": ra["size"], "size64": rb["size"],
                      "fields32": ra["fields"], "fields64": rb["fields"]})
    return diffs


# ------------------------------------------------------------------ worker
def run_tu(entry: dict, out: str, layout: bool) -> dict:
    f = norm(entry["file"])
    args = shlex.split(norm(entry["command"]), posix=True)
    game = is_game(f)
    obj = None
    if not game:
        h = hashlib.sha1(f.encode()).hexdigest()[:16]
        obj = norm(os.path.join(out, "obj", h + ".obj"))
    cx = x64_cmd(args, obj) + (LAYOUT if layout else [])
    t0 = time.time()
    r = subprocess.run(cx, cwd=entry["directory"], capture_output=True, text=True,
                       encoding="utf-8", errors="replace")
    res = {"file": rel(f), "rc": r.returncode, "diags": parse_diags(r.stderr),
           "t": round(time.time() - t0, 2)}
    if layout:
        l64 = parse_layouts(r.stdout)
        r2 = subprocess.run(i686_cmd(args) + LAYOUT, cwd=entry["directory"], capture_output=True,
                            text=True, encoding="utf-8", errors="replace")
        l32 = parse_layouts(r2.stdout)
        res["nrec"] = len(l32)
        res["ldiff"] = summarize_layouts(l32, l64)
    return res


def cmd_hash(e: dict, layout: bool) -> str:
    return hashlib.sha1((e["command"] + str(layout) + " ".join(LAYOUT)).encode()).hexdigest()[:12]


def do_run(a) -> int:
    db = Path(a.db)
    if not db.is_absolute():
        db = ROOT / db
    out = Path(a.out)
    if not out.is_absolute():
        out = ROOT / out
    (out / "obj").mkdir(parents=True, exist_ok=True)
    entries = json.loads((db / "compile_commands.json").read_text(encoding="utf-8"))
    sel, seenf = [], set()
    for e in entries:
        f = norm(e["file"])
        if "/_deps/" in f:
            continue
        if a.only and not re.search(a.only, f):
            continue
        if f in seenf:          # a TU built for several targets: probe it once
            continue
        seenf.add(f)
        sel.append(e)
    if a.limit:
        sel = sel[: a.limit]
    resf = out / "results.jsonl"
    done = {}
    if resf.exists():
        for ln in resf.read_text(encoding="utf-8").splitlines():
            try:
                d = json.loads(ln)
                done[d["file"]] = d.get("h")
            except Exception:
                pass
    todo = [e for e in sel if done.get(rel(e["file"])) != cmd_hash(e, not a.no_layout)]
    print(f"{len(sel)} TUs selected, {len(sel) - len(todo)} cached, {len(todo)} to run (-j {a.jobs})",
          flush=True)
    t0 = time.time()
    n = 0
    with open(resf, "a", encoding="utf-8") as fo, cf.ThreadPoolExecutor(a.jobs) as ex:
        futs = {ex.submit(run_tu, e, str(out), not a.no_layout): e for e in todo}
        for fu in cf.as_completed(futs):
            e = futs[fu]
            try:
                r = fu.result()
            except Exception as exc:  # keep going; record the failure
                r = {"file": rel(e["file"]), "rc": -1, "diags": [], "exc": repr(exc)}
            r["h"] = cmd_hash(e, not a.no_layout)
            fo.write(json.dumps(r) + "\n")
            n += 1
            if n % 500 == 0:
                fo.flush()
                el = time.time() - t0
                print(f"  {n}/{len(todo)}  {el:.0f}s  eta {el / n * (len(todo) - n):.0f}s", flush=True)
    print(f"done {n} in {time.time() - t0:.0f}s", flush=True)
    return 0


# ------------------------------------------------------------------ report
def ptr_type(t: str) -> bool:
    # field text is "<type> <name>"; a pointer member has '*' in the type part
    return "*" in t.rsplit(" ", 1)[0] if " " in t else "*" in t


def classify_record(d: dict) -> str:
    f32 = d["fields32"]
    types = [t for _, t in f32]
    if any("vftable pointer" in t or "vbtable pointer" in t for t in types):
        return "cxx-vptr"
    if any(ptr_type(t) for t in types):
        return "ptr-member"
    if any(re.search(r"\b(size_t|intptr_t|uintptr_t|ptrdiff_t|SIZE_T|ULONG_PTR|LONG_PTR|"
                     r"UINT_PTR|INT_PTR|HANDLE|WPARAM|LPARAM|va_list)\b", t) for t in types):
        return "ptr-sized-int"
    return "nested-only"


def is_offset_coded(d: dict) -> bool:
    return any(re.search(r"\b(pad|unk|_pad|filler)\w*\b", t) for _, t in d["fields32"])


def do_report(a) -> int:
    out = Path(a.out)
    if not out.is_absolute():
        out = ROOT / out
    rows = {}
    for ln in (out / "results.jsonl").read_text(encoding="utf-8").splitlines():
        try:
            d = json.loads(ln)
        except Exception:
            continue
        rows[d["file"]] = d          # last result per TU wins
    tus = list(rows.values())
    # ---- diagnostics: unique sites
    sites = {}
    tu_err = Counter()
    tu_with = defaultdict(set)
    for r in tus:
        tarea = area(r["file"])
        if r.get("rc", 0) != 0:
            tu_err[tarea] += 1
        for f, l, c, kind, cls in r["diags"]:
            k = (f, l, c, cls)
            sites.setdefault(k, kind)
            tu_with[cls].add(r["file"])
    by_cls = Counter()
    by_cls_area = Counter()
    for (f, l, c, cls), kind in sites.items():
        by_cls[cls] += 1
        by_cls_area[(cls, area(f))] += 1
    with open(out / "diag_sites.tsv", "w", encoding="utf-8") as fo:
        fo.write("file\tline\tcol\tkind\tclass\tarea\n")
        for (f, l, c, cls), kind in sorted(sites.items()):
            fo.write(f"{f}\t{l}\t{c}\t{kind}\t{cls}\t{area(f)}\n")
    # ---- layouts: unique records
    urec = {}
    inst = Counter()
    for r in tus:
        for d in r.get("ldiff", []):
            k = (d["name"], json.dumps(d["fields32"]))
            inst[k] += 1
            if k not in urec:
                d = dict(d)
                d["tu"] = r["file"]
                urec[k] = d
    lcls = Counter()
    lcls_area = Counter()
    with open(out / "layout_diff.tsv", "w", encoding="utf-8") as fo:
        fo.write("record\tclass\toffset_coded\tsize32\tsize64\tnfields\tnptr\tTUs\tfirst_tu\tarea\n")
        for k, d in sorted(urec.items(), key=lambda kv: -inst[kv[0]]):
            c = classify_record(d)
            oc = is_offset_coded(d)
            ar = area(d["tu"])
            lcls[(c, oc)] += 1
            lcls_area[(ar, c)] += 1
            nptr = sum(1 for _, t in d["fields32"] if ptr_type(t))
            fo.write(f"{d['name']}\t{c}\t{int(oc)}\t{d['size32']}\t{d['size64']}\t{len(d['fields32'])}"
                     f"\t{nptr}\t{inst[k]}\t{d['tu']}\t{ar}\n")
    nrec = sum(r.get("nrec", 0) for r in tus)
    # ---- summary
    L = []
    w = L.append
    ntu = len(tus)
    nerr = sum(1 for r in tus if r.get("rc", 0) != 0)
    w(f"x64 probe: {ntu} TUs, {nerr} with errors (rc != 0); "
      f"{sum(1 for r in tus if is_game(r['file']))} game TUs")
    w("TUs with errors by area: " + ", ".join(f"{k}={v}" for k, v in tu_err.most_common()))
    w("")
    w("Unique diagnostic sites by class (sites / TUs reporting):")
    for cls, n in by_cls.most_common(60):
        w(f"  {n:8d}  {len(tu_with[cls]):6d}  {cls}")
    w("")
    w("Top classes by area:")
    areas = sorted({ar for (_, ar) in by_cls_area})
    for cls, _ in by_cls.most_common(15):
        parts = [f"{ar}={by_cls_area[(cls, ar)]}" for ar in areas if by_cls_area[(cls, ar)]]
        w(f"  {cls}: " + ", ".join(parts))
    w("")
    w(f"Record layouts compared (i686 vs x64, TU-instances): {nrec}; "
      f"unique differing records: {len(urec)}, TU-instances {sum(inst.values())}")
    for (c, oc), n in sorted(lcls.items(), key=lambda kv: -kv[1]):
        w(f"  {n:7d}  {c}{'  (offset-coded: pad/unk fields)' if oc else ''}")
    w("  by area: " + ", ".join(f"{ar}/{c}={n}" for (ar, c), n in sorted(lcls_area.items(),
                                                                          key=lambda kv: -kv[1])[:30]))
    tt = sum(r.get("t", 0) for r in tus)
    w(f"\nx64 compile CPU time: {tt:.0f}s")
    (out / "summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(L))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    r.add_argument("--db", default="build/soak2-i686")
    r.add_argument("--out", default="build/x64-probe")
    r.add_argument("-j", "--jobs", type=int, default=4)
    r.add_argument("--limit", type=int, default=0)
    r.add_argument("--only", default="")
    r.add_argument("--no-layout", action="store_true")
    p = sub.add_parser("report")
    p.add_argument("--out", default="build/x64-probe")
    a = ap.parse_args()
    return do_run(a) if a.cmd == "run" else do_report(a)


if __name__ == "__main__":
    sys.exit(main())
