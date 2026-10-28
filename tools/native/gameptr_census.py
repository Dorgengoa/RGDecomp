#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of the native renderer's reads of game-owned memory (docs/NATIVE-RENDER.md
"Remembered packets"; history 2026-10-26 (rpkt)).

    python tools/native/gameptr_census.py [--check] [--files GLOB ...]

Lists, per source file of src/native/render (C / C++):
  host     the walkers' host() address translators: each must route through nr_game_ptr
           (nr_mem.h: unreadable memory refused, poison checked), else FAIL under --check;
  deref    every cast of a 32-bit game address to a host pointer ((...)(uintptr_t)x), with the
           enclosing function and whether it is on the allowlist below (reads at build time
           of memory the game has just written, writes of the port's own packets,
           diagnostics); an unlisted one FAILS under --check: decide whether it can outlive
           the memory, then copy at build time or add it here with the reason;
  apply    nr_const_apply(...) calls (an in-place walk of a packet address) with the argument,
           to review which addresses are applied in place rather than from a copy.
Exit 0, or 1 with --check when something fails.  ~0.1 s.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "src/native/render"

# (file, function): why the raw dereference cannot read dead memory
ALLOW = {
    ("nr_scene.c", "note_put"): "build time: copies the packet its builder has just written",
    ("nr_scene.c", "ptab_put"): "build time: copies the packet its builder has just written",
    ("nr_scene.c", "note_apply"): "RG_NR_STALE diagnostic only (compares the copy with memory)",
    ("nr_scene.c", "nr_chain_packet"): "writes the copy into the caller's live packet stack",
    ("nr_scene.c", "census_note"): "RG_NR_CENSUS: the caller's microcode tuple (live during the call)",
    ("nr_scene.c", "game_constants"): "the caller's microcode tuple (live during the call)",
    ("nr_scene.c", "nr_model_record2"): "the caller's microcode tuple (live during the call)",
    ("nr_scene.c", "clip_note"): "the draw context struct (lives as long as the game)",
    ("nr_im.c", "nr_im_end_prim"): "writes the marker over the packet just finished (build time)",
    ("nr_fx.c", "words"): "RG_NR_FXCENSUS: records an address, no read",
    ("nr_mem.c", "nr_game_ptr"): "the checked translation itself",
    ("nr_mem.c", "nr_poison_stack"): "writes the poison after nr_game_ptr accepted the range",
}

FUNC_RE = re.compile(r"^(?:static\s+|inline\s+|extern\s+)*[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*\([^;]*$")
CAST_RE = re.compile(r"\(\s*(?:const\s+)?(?:u?int\d+_t|u8|void|char)\s*\*\s*\)\s*\(\s*uintptr_t\s*\)")
APPLY_RE = re.compile(r"\bnr_const_apply\s*\(([^;]*)\)")


def functions(lines):
    """the enclosing top-level function name for every line (brace depth tracking)"""
    out, cur, depth, pending = [], "", 0, ""
    for ln in lines:
        s = ln.split("//")[0]
        if depth == 0:
            m = FUNC_RE.match(s)
            if m and m.group(1) not in ("if", "for", "while", "switch", "return", "sizeof"):
                pending = m.group(1)
            if "{" in s and pending:
                cur = pending
        out.append(cur if depth > 0 or "{" in s else pending or cur)
        depth += s.count("{") - s.count("}")
        if depth <= 0:
            depth = 0
            if "}" in s:
                cur, pending = "", ""
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--files", nargs="*", default=["*.c", "*.cpp"])
    a = ap.parse_args(argv)
    files = sorted({p for g in a.files for p in SRC.glob(g)})
    bad = 0
    rows = []
    for p in files:
        lines = p.read_text(encoding="utf-8", errors="replace").splitlines()
        fn = functions(lines)
        text = "\n".join(lines)
        # host() translators
        for m in re.finditer(r"static\s+const\s+uint8_t\s*\*\s*host\s*\(([^)]*)\)\s*\{(.*?)\n\}", text, re.S):
            ok = "nr_game_ptr" in m.group(2)
            ln = text[:m.start()].count("\n") + 1
            rows.append(("host", p.name, ln, "host", "routes through nr_game_ptr" if ok else "RAW (no nr_game_ptr)", ok))
            bad += not ok
        for i, ln in enumerate(lines):
            if CAST_RE.search(ln) and "host(" not in fn[i]:
                f = fn[i]
                why = ALLOW.get((p.name, f))
                if f == "host":
                    continue
                rows.append(("deref", p.name, i + 1, f, why or "NOT ON THE ALLOWLIST: " + ln.strip()[:90], bool(why)))
                bad += not why
            for m in APPLY_RE.finditer(ln):
                if "nr_cblock *b" in m.group(1):
                    continue   # the definition
                rows.append(("apply", p.name, i + 1, fn[i], "in place: " + m.group(1).strip()[:70], True))
    w = max((len(f"{r[1]}:{r[2]}") for r in rows), default=10)
    for kind, f, ln, func, what, ok in rows:
        print(f"{kind:5s} {f + ':' + str(ln):{w}s} {func:22s} {'ok  ' if ok else 'FAIL'} {what}")
    n = {k: sum(r[0] == k for r in rows) for k in ("host", "deref", "apply")}
    print(f"gameptr_census: {len(files)} files, {n['host']} host(), {n['deref']} raw dereferences, "
          f"{n['apply']} in-place applies; {bad} failing: {'FAIL' if bad else 'PASS'}")
    return 1 if (a.check and bad) else 0


if __name__ == "__main__":
    sys.exit(main())
