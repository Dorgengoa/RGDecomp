#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Who consumes the RNG, frame by frame, port vs retail (docs/TEST-FIXTURES.md "Retail parity").

    python tools/parity/rngtrace.py SCEN --exe EXE --dir D [--frames N] [--env K=V ..]

Needs a parity run of SCEN in D (port_events.json / the final pass script, retail plan).
Port: the final pass again with RG_BREAK on GfxEndFrame_141c20 and Rand_133710 (ret_rva =
the caller); retail: the scenario again with a probe hook on Rand_133710 (ra = the caller),
ordered against the frame samples by ring sequence.  Callers are named by function (port:
rg-game.map; retail: the snapshot listing names, which carry their address).  Prints, from
the compare anchor, the first frame whose caller sequence differs and both sequences there.
"""
from __future__ import annotations

import argparse
import bisect
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(PORT / "tools" / "bringup"))
import parity  # noqa: E402

RAND = 0x133710


def retail_names():
    import listings
    t = listings.table()
    out = []
    for name in (t.get("asm_text") or {}):
        m = re.search(r"_([0-9a-f]{6})$", name)
        if m:
            out.append((int(m.group(1), 16), name))
    out.sort()
    return out


def name_of(tab, a):
    i = bisect.bisect_right(tab, (a, "~")) - 1
    return tab[i][1] if i >= 0 else hex(a)


def port_trace(exe: Path, d: Path, sc, env_extra, nframes):
    pm = parity.PortMap(exe)
    ev = json.loads((d / "port_events.json").read_text())
    cmp_frame, cmp_vbl = ev["compare"]
    env = {"RG_BREAK": f"0x{pm.syms['GfxEndFrame_141c20']:X},0x{pm.syms['Rand_133710']:X}",
           "RG_BREAK_MAX": "100000000", "RG_BREAK_FROM_VBL": str(max(0, cmp_vbl - 4)),
           "RG_INPUT_KEY": "frames", "RG_SS": "1"}
    env.update(env_extra)
    fields = 2 * (cmp_frame + nframes) + 1200
    log = parity._run_port(exe, ["--boot-save", sc["card"], "--input", str(d / "final.input.txt"),
                                 "--fields", str(fields)], env, d / "rng_port.log")
    syms = sorted((r, n) for n, r in pm.syms.items())
    frames, cur = {}, None
    gfx = pm.syms["GfxEndFrame_141c20"]
    for ln in log.splitlines():
        m = re.match(r"BRK rva=0x([0-9A-F]+) .*ret_rva=0x([0-9A-F]+) hit=(\d+)", ln)
        if not m:
            continue
        rva, ret, hit = int(m.group(1), 16), int(m.group(2), 16), int(m.group(3))
        if rva == gfx:
            cur = hit
            frames.setdefault(cur, [])
        elif cur is not None:
            i = bisect.bisect_right(syms, (ret, "~")) - 1
            frames[cur].append(syms[i][1] if i >= 0 else hex(ret))
    # calls between GfxEndFrame k and k+1 belong to frame k+1 (sampled at its end)
    return {k + 1 - cmp_frame: v for k, v in frames.items()}


def retail_trace(d: Path, name, nframes):
    import probe

    def hooks(h):
        h.entry(RAND, "rand")
    out = d / "rng_retail"
    parity.run_retail_scenario(name, out, 1.0, groups="core", extra_hooks=hooks)
    tab = retail_names()
    hdr, frames = parity.load_frames(out / "retail.jsonl")
    ev = json.loads((out / "retail_hooks.json").read_text())
    cmp_frame = hdr["meta"]["compare_frame"]
    seqs = sorted((f["_seq"], f["frame"]) for f in frames if "_seq" in f)
    res = {}
    for e in ev:
        i = bisect.bisect_right(seqs, (e["seq"], 1 << 40))
        if i >= len(seqs):
            continue
        fr = seqs[i][1]          # the next frame sample after this call
        res.setdefault(fr - cmp_frame, []).append(name_of(tab, e["ra"] & 0xFFFFFFFF))
    return res


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("scenario")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--dir", required=True)
    ap.add_argument("--frames", type=int, default=120)
    ap.add_argument("--env", action="append", default=[])
    a = ap.parse_args(argv)
    sc = parity.scenario(a.scenario)
    d = Path(a.dir)
    env = dict(kv.split("=", 1) for kv in a.env)
    P = port_trace(Path(a.exe).resolve(), d, sc, env, a.frames)
    R = retail_trace(d, a.scenario, a.frames)
    (d / "rngtrace.json").write_text(json.dumps({"port": P, "retail": R}))
    for k in range(0, a.frames):
        p, r = P.get(k, []), R.get(k, [])
        if p != r:
            print(f"first difference at frame {k}:")
            print(f"  port   ({len(p)}): {p}")
            print(f"  retail ({len(r)}): {r}")
            for j in range(max(0, k - 2), k):
                print(f"  frame {j} (same): {P.get(j, [])}")
            return 0
    print(f"rng caller sequences identical for {a.frames} frames")
    return 0


if __name__ == "__main__":
    sys.exit(main())
