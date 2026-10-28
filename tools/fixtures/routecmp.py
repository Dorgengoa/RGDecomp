#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Run one input route on two rg-game builds and compare them: run hash, STATUS rows,
milestones (timing record), the sym: state trace and screenshots (docs/TEST-FIXTURES.md
"Factory and Insectron drivers").  For build A/B checks that should be identical: the
native-only rg-game vs its oracle twin rg-game-oracle (same tree, emulated paths), or
RG_NATIVE_OVL=ON vs OFF.

    python tools/fixtures/routecmp.py run ROUTE --exe EXE --out D [--card CARD] [--fields N]
                                     [--no-trace] [--every 50] [--shots F,F..]
    python tools/fixtures/routecmp.py compare DA DB [--limit 20]
    python tools/fixtures/routecmp.py pair ROUTE --exe-a A --exe-b B --out D [run options]

ROUTE: a golden name (tools/trace/goldens/NAME.input.txt: newgame_save2, boot_save2_battle2,
..) or an input file.  --card CARD: power-on with out/fixtures/cards/CARD as the memory card
(boot routes: boot_save2_battle2 -> --card save2; factory.py / insectron boot_route.txt ->
factory_plans / insectron_play); the card dir is copied, never written.  --fields: default
the route's "# boot-end:" + 50 (boot scripts) or its last input line + 300.

run: one headless rg-game (RG_GPU=hw) with RG_STATUS_EVERY, RG_TIMING (D/port.jsonl ->
timing.py build --map -> D/port.milestones.tsv) and, unless --no-trace, the state trace of
tools/trace/regions_symbols.cfg (RG_TRACE_OUT=D/trace.tsv, every --every-th game VBlank;
port_regions.cfg excludes / pending as in port_trace.py) -> D/route.json (rc, run hash,
STATUS rows + hash, shots' hashes, crash report, "ovl:" reports).

compare: run hash, STATUS rows (first differing field), screenshot hashes, `timing.py align
--nowrap` (milestone segments that differ), `port_trace.py compare` of the two traces (sym:
regions; port_regions.cfg's ignore list).  Classification (printed + D_A/compare_<B>.json):
  identical       run hash equal (pad reads with their game vbl, the audio output, the kernel
                  trace and clock; NOT the frames: rg-game leaves display_hash_every 0, so
                  pixels are judged by the --shots hashes, reported separately) and the sym:
                  trace agrees
  presentation    run hash differs but STATUS, milestones and the sym: trace agree (audio /
                  timing-only difference, not game state)
  timing          milestones or STATUS shift but the trace agrees where both have vbls
  state           the sym: trace differs (game state diverged; first region / vbl named)
  crash           either run crashed / hung
One rg-game at a time (the machine-wide slot limit applies on top).
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "trace"))
import fxlib  # noqa: E402
import factory  # noqa: E402  (run_game: hang timeout after the slot wait)

TRACE_DIR = fxlib.PORT / "tools" / "trace"
GOLDENS = TRACE_DIR / "goldens"


def route_path(route: str) -> Path:
    p = Path(route)
    if p.exists():
        return p.resolve()
    g = GOLDENS / f"{route}.input.txt"
    if g.exists():
        return g
    raise SystemExit(f"routecmp: no route {route} (file or tools/trace/goldens/NAME.input.txt)")


def default_fields(p: Path) -> int:
    """'# fields: N' in the route, else its last input field + 300."""
    last = 0
    for ln in p.read_text(encoding="utf-8").splitlines():
        m = re.match(r"#\s*fields:\s*(\d+)", ln)
        if m:
            return int(m.group(1))
        t = ln.split()
        if ln.startswith("#!stick") and len(t) >= 3 and t[1].isdigit() and t[2].isdigit():
            last = max(last, int(t[2]))
        elif len(t) >= 2 and t[0].isdigit() and t[1].isdigit():
            last = max(last, int(t[1]))
    return last + 300


ARENA_BASE = 0x004E9E80


def ovl_windows(build: Path):
    """[(name, data start, end)] of the five overlays: retail data start = arena base +
    0x40 (MWo3 header) + text_size, end = + data + bss, read from the build's generated module table
    (overlay-gen/ovl_native_gen.c; the arena registry ovl_registry_gen.c as a fallback)."""
    out = []
    for f in ("ovl_native_gen.c", "ovl_registry_gen.c"):
        src = build / "overlay-gen" / f
        if not src.exists():
            continue
        for m in re.finditer(r'\{"(\w+)", "\w+\.BIN", \d+, \d+u,\s*(0x[0-9A-F]+u|0u), (0x[0-9A-F]+)u, (0x[0-9A-F]+)u, '
                             r'(0x[0-9A-F]+)u', src.read_text(encoding="utf-8")):
            text, data, bss = (int(x, 16) for x in m.group(3, 4, 5))
            if text:   # data start = arena base + 0x40 header + text_size (ovl.c data_vram())
                out.append((m.group(1), ARENA_BASE + 0x40 + text, ARENA_BASE + 0x40 + text + data + bss))
        if out:
            break
    return out


def write_ovl_regions(build: Path, path: Path):
    """regions_symbols.cfg + one `ovl:<name>` region per overlay data+bss window (the
    trace recorder maps it through the arena, or the active native module: trace_map.c)."""
    w = ovl_windows(build)
    if not w:
        raise SystemExit(f"routecmp: no overlay table in {build / 'overlay-gen'}")
    # inlined: the recorder resolves `include` relative to the including file
    lines = (TRACE_DIR / "regions_symbols.cfg").read_text(encoding="utf-8").splitlines()
    lines += [f"ee  ovl:{n:8s} 0x{a:08X}  0x{b:08X}" for n, a, b in w]
    path.write_text(chr(10).join(lines) + chr(10), encoding="utf-8")
    return path


def status_rows(log):
    rows = []
    for ln in log.splitlines():
        m = re.match(r"STATUS field=(\d+) vbl=(\d+) ovl=(-?\d+) .*?gamemode=(\S+)", ln)
        if m:
            rows.append((int(m.group(1)), int(m.group(2)), int(m.group(3)), m.group(4)))
    return rows


def cmd_run(a) -> dict:
    exe = Path(a.exe).resolve()
    out = Path(a.out).resolve()
    if out.exists():
        shutil.rmtree(out)
    (out / "bin").mkdir(parents=True)
    for s in (exe, exe.with_suffix(".map")):          # a private copy: rebuilds can't swap it
        shutil.copy2(s, out / "bin" / s.name)
    bexe = out / "bin" / exe.name
    rp = route_path(a.route)
    fields = a.fields or default_fields(rp)
    saves = out / "saves"
    if a.card:
        card = fxlib.CARDS / a.card
        if not card.is_dir():
            raise SystemExit(f"routecmp: no card {card}")
        shutil.copytree(card, saves)
    else:
        saves.mkdir()
    env = {"RG_STATUS_EVERY": str(a.status), "RG_TIMING": str(out / "port.jsonl")}
    regions = TRACE_DIR / "regions_symbols.cfg"
    if a.ovl_regions:
        regions = write_ovl_regions(Path(a.ovl_regions), out / "regions_ovl.cfg")
    if not a.no_trace:
        env.update(RG_TRACE_OUT=str(out / "trace.tsv"), RG_TRACE_REGIONS=str(regions),
                   RG_TRACE_PORTCFG=str(TRACE_DIR / "port_regions.cfg"), RG_TRACE_EVERY=str(a.every))
    shots = [int(x) for x in a.shots.split(",") if x] if a.shots else []
    cmd = [str(bexe), "--headless", "--fields", str(fields), "--saves", str(saves), "--input", str(rp)]
    for s in shots:
        cmd += ["--shot", f"{s}:{out / f's{s:05d}.png'}"]
    t0 = time.time()
    e = fxlib.game_env(env)
    rc, log = factory.run_game(cmd, e, hang_s=a.hang)
    (out / "port.log").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    subprocess.run([sys.executable, str(TRACE_DIR / "timing.py"), "build", str(out / "port.jsonl"), "--map",
                    str(bexe.with_suffix(".map"))], check=False, capture_output=True)
    rh = None
    for ln in log.splitlines():
        m = re.search(r"run_hash=([0-9a-f]{16})", ln)
        if m and ln.startswith("rg-game:"):
            rh = m.group(1)
    rows = status_rows(log)
    res = {"exe": str(exe), "exe_id": fxlib.exe_id(exe), "route": str(rp), "card": a.card, "fields": fields,
           "rc": rc, "wall_s": round(time.time() - t0), "run_hash": rh, "status_rows": len(rows),
           "status_hash": hashlib.sha256(repr(rows).encode()).hexdigest()[:16],
           "last_status": rows[-1] if rows else None,
           "shots": {str(s): factory.png_hash(out / f"s{s:05d}.png") for s in shots},
           "crash": fxlib.crash_report(log, bexe), "hang": "TIMEOUT" in log,
           "ovl_reports": [ln for ln in log.splitlines() if ln.startswith("ovl:")][:20],
           "trace": str(out / "trace.tsv") if (out / "trace.tsv").exists() else None}
    (out / "route.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    print(json.dumps({k: v for k, v in res.items() if k not in ("shots",)}, indent=1))
    return res


def _status(d: Path):
    return status_rows((d / "port.log").read_text(encoding="utf-8", errors="replace"))


def compare(da: Path, db: Path, limit=20) -> dict:
    ra, rb = (json.loads((d / "route.json").read_text()) for d in (da, db))
    out = {"a": str(da), "b": str(db), "run_hash": [ra["run_hash"], rb["run_hash"]]}
    sa, sb = _status(da), _status(db)
    diff = next(((x, y) for x, y in zip(sa, sb) if x != y), None)
    out["status_equal"] = sa == sb
    out["status_first_diff"] = diff
    out["status_len"] = [len(sa), len(sb)]
    out["shots_differ"] = sorted(k for k in set(ra["shots"]) | set(rb["shots"]) if ra["shots"].get(k) != rb["shots"].get(k))
    # milestones
    ma, mb = da / "port.milestones.tsv", db / "port.milestones.tsv"
    if ma.exists() and mb.exists():
        p = subprocess.run([sys.executable, str(TRACE_DIR / "timing.py"), "align", "--nowrap", str(ma), str(mb)],
                           capture_output=True, text=True, errors="replace")
        txt = p.stdout + p.stderr
        (da / f"align_{db.name}.txt").write_text(txt, encoding="utf-8")
        m = re.search(r"(\d+) segments? differ", txt)
        out["milestones_differ"] = int(m.group(1)) if m else None
        out["milestones"] = [sum(1 for _ in open(ma, encoding="utf-8")) - 1, sum(1 for _ in open(mb, encoding="utf-8")) - 1]
        out["milestones_identical"] = ma.read_bytes() == mb.read_bytes()
    # sym: trace
    if ra.get("trace") and rb.get("trace") and Path(ra["trace"]).exists() and Path(rb["trace"]).exists():
        p = subprocess.run([sys.executable, str(TRACE_DIR / "port_trace.py"), "compare", ra["trace"], rb["trace"],
                            "--limit", str(limit)], capture_output=True, text=True, errors="replace")
        txt = p.stdout + p.stderr
        (da / f"trace_cmp_{db.name}.txt").write_text(txt, encoding="utf-8")
        out["trace_rc"] = p.returncode
        out["trace_summary"] = [ln for ln in txt.splitlines() if ln.strip()][-3:]
        out["traces_identical"] = Path(ra["trace"]).read_bytes() == Path(rb["trace"]).read_bytes()
        out["ovl_rows"] = ovl_rows(Path(ra["trace"]), Path(rb["trace"]))
    bad = ra["crash"] or rb["crash"] or ra.get("hang") or rb.get("hang") or ra["rc"] != 0 or rb["rc"] != 0
    if bad:
        cls = "crash"
    elif out.get("trace_rc", 0) != 0:
        cls = "state"
    elif ra["run_hash"] and ra["run_hash"] == rb["run_hash"]:
        cls = "identical"
    elif not out["status_equal"] or out.get("milestones_differ"):
        cls = "timing"
    else:
        cls = "presentation"
    out["class"] = cls
    (da / f"compare_{db.name}.json").write_text(json.dumps(out, indent=1), encoding="utf-8")
    return out


def ovl_rows(ta: Path, tb: Path) -> dict:
    """Per ovl:<name> region (--ovl-regions): game vbls with a row in A / in B / in both, and
    how many of those agree.  The arena maps a window whatever is resident (other overlays'
    bytes, zeros); the native module table only while that module is active, so 'both' =
    the module's own residency.  Overlay .data holds host pointers (relocated words), so two
    different exes need not agree byte for byte; 'equal' says how often they do."""
    import trace as tr

    def by_vbl(t):
        o = {}
        for fr in sorted(t):
            v = int(t[fr].get("@vbl", "0"))
            if v and v not in o:
                o[v] = t[fr]
        return o
    a, b = by_vbl(tr.read_trace(str(ta))), by_vbl(tr.read_trace(str(tb)))
    regs = sorted({r for rows in list(a.values()) + list(b.values()) for r in rows if r.startswith("ovl:")})
    res = {}
    for r in regs:
        va = {v for v, rows in a.items() if r in rows}
        vb = {v for v, rows in b.items() if r in rows}
        both = va & vb
        eq = sum(1 for v in both if a[v][r] == b[v][r])
        res[r] = {"a": len(va), "b": len(vb), "both": len(both), "equal": eq}
    return res


def cmd_compare(a):
    r = compare(Path(a.a), Path(a.b), a.limit)
    print(json.dumps(r, indent=1))
    return 0 if r["class"] == "identical" else 1


def cmd_pair(a):
    base = Path(a.out)
    for tag, exe in (("a", a.exe_a), ("b", a.exe_b)):
        ns = argparse.Namespace(**vars(a))
        ns.exe, ns.out = exe, str(base / tag)
        cmd_run(ns)
    r = compare(base / "a", base / "b", a.limit)
    print(json.dumps(r, indent=1))
    return 0 if r["class"] == "identical" else 1


def run_args(p):
    p.add_argument("--card")
    p.add_argument("--fields", type=int, default=0)
    p.add_argument("--no-trace", action="store_true")
    p.add_argument("--every", type=int, default=50, help="trace every N game VBlanks")
    p.add_argument("--status", type=int, default=50, help="RG_STATUS_EVERY")
    p.add_argument("--shots", default="", help="comma-separated fields")
    p.add_argument("--hang", type=int, default=3600, help="hang timeout (s) after the slot wait")
    p.add_argument("--limit", type=int, default=20)
    p.add_argument("--ovl-regions", metavar="BUILD_DIR",
                   help="also trace each overlay's data+bss window (ovl:<name>, retail addresses from "
                        "BUILD_DIR/overlay-gen); compare judges sym: only, ovlscan.py reads the ovl: rows")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("run")
    r.add_argument("route")
    r.add_argument("--exe", required=True)
    r.add_argument("--out", required=True)
    run_args(r)
    r.set_defaults(fn=lambda a: 0 if cmd_run(a)["rc"] == 0 else 1)
    c = sp.add_parser("compare")
    c.add_argument("a")
    c.add_argument("b")
    c.add_argument("--limit", type=int, default=20)
    c.set_defaults(fn=cmd_compare)
    p = sp.add_parser("pair")
    p.add_argument("route")
    p.add_argument("--exe-a", required=True)
    p.add_argument("--exe-b", required=True)
    p.add_argument("--out", required=True)
    run_args(p)
    p.set_defaults(fn=cmd_pair)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
