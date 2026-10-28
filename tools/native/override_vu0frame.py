#!/usr/bin/env python3
"""Put hand-written VU0 code on function-local register files (docs/UB-AUDIT.md
"vu0frame: overrides and libvu0").

The ingest stage `vu0frame` (tools/stages/vu0frame.py) converts game/ at ingest
time; overrides and port provider files are not ingested, so they kept the
per-file `static rg_vu0_state rg_vu0` fallback of port/vu0.h.  This tool runs
the SAME transform (the stage class is imported read-only, no copy of its
rules) over such files, in place:

  * `RG_VU0_FRAME;` after the `{` of every function that names the model;
  * a `static` same-file helper that touches the model gets the caller's
    register file (`rg_vu0_state *rg_vu0_p_` first parameter, `&rg_vu0` at
    every same-file call, push_macro/#define rg_vu0 (*rg_vu0_p_)/pop_macro).

Skipped: files that select a named cross-file context (`RG_VU0_CTX_NAME`,
port/vu0_ctx.h: the whole file runs on the context, RG_VU0_FRAME is a no-op
there) and files already converted (the stage's own idempotence test).

    python tools/native/override_vu0frame.py [--write] [--out DIR] FILE...
    python tools/native/override_vu0frame.py --scan [--write]   # overrides/ + src/sce/vu0/libvu0.c

Without --write: prints the rows (path, function, rule, detail) and, with
--out, writes the converted copies under DIR (same relative paths).
Then: `python tools/ubaudit/wcensus.py BUILD --strict-vu0` must report 0.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "stages"))
import vu0frame  # noqa: E402  (read-only reuse)
from vu0frame import HINT, Vu0FrameStage  # noqa: E402

# One widening of the stage's model test, for hand-written files only: a
# file-local macro whose body names the model (libvu0.c's LQ / SQ / FMAC
# wrap rg_vu0_lqc2 / rg_vu0_fmac) counts as a model use, exactly like a
# vu0bind-bound name does in the stage (its BOUND list).  Without it a
# function written only with such macros gets no frame (and stays on the
# file-scope fallback) and a static helper written with them is not seen as
# a helper.  Ingested game/ code has no such macros (wcensus --strict-vu0 = 0);
# a stage proposal is in docs/UB-AUDIT.md.
_MACRO = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(?:\([^)\n]*\))?[ \t]+"
    r"(?:RG_VU0_BIND_|(?:[^\n]*?)\brg_vu0)", re.M)


class _Bound:
    """Stands in for vu0frame.BOUND: the macro names above plus `extra`.

    `extra` closes the one gap of the stage's single pass for hand-written
    files: a static function that touches the model ONLY through a frame
    helper (libvu0.c rot_angle -> qmtc2_float / ecossin) and is itself called
    by another function must be a helper too (its callers read what it left).
    convert() reruns the stage with the helpers found so far counted as model
    uses until the helper set is stable."""
    extra: set = set()

    def findall(self, text):
        return _MACRO.findall(text) + sorted(self.extra)


vu0frame.BOUND = _Bound()


def convert(rel: str, data: bytes):
    """The stage on one file, to a fixpoint of the helper set."""
    _Bound.extra = set()
    while True:
        st = Vu0FrameStage()
        new, n = st.apply(rel, data)
        helpers = {r[1] for r in st.rows if r[2] == "helper"}
        if helpers <= _Bound.extra:
            return st, new, n
        _Bound.extra |= helpers


GAME_FN = re.compile(r"\bVu0\w*_[0-9a-f]{5,6}\b")
SCAN_ROOTS = ("overrides", "missing")
SCAN_EXTRA = ("src/sce/vu0/libvu0.c",)


def scan() -> list[Path]:
    out = []
    for root in SCAN_ROOTS:
        for p in sorted((PORT / root).rglob("*")):
            if p.suffix in (".c", ".cpp") and p.is_file():
                out.append(p)
    out += [PORT / e for e in SCAN_EXTRA]
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("files", nargs="*", type=Path)
    ap.add_argument("--scan", action="store_true", help="overrides/, missing/, libvu0.c")
    ap.add_argument("--write", action="store_true", help="rewrite the files in place")
    ap.add_argument("--out", type=Path, help="write converted copies here instead")
    a = ap.parse_args()
    files = (scan() if a.scan else []) + [f.resolve() for f in a.files]
    rows = []
    changed = skipped_ctx = 0
    for p in files:
        data = p.read_bytes()
        text = data.decode("latin-1")
        if not HINT.search(text):
            continue
        rel = p.resolve().relative_to(PORT).as_posix()
        if not HINT.search(GAME_FN.sub("", text)):
            # the only hit is a call of a game function named Vu0*_<addr>
            # (LensFlareDraw -> Vu0InnerProduct_13bd60): no model use
            print(f"{rel}\t-\tskip-nomodel\tonly game Vu0*_<addr> calls")
            continue
        if "RG_VU0_CTX_NAME" in text:
            skipped_ctx += 1
            print(f"{rel}\t-\tskip-ctx\tnamed cross-file context")
            continue
        st, new, n = convert(rel, data)
        rows += st.rows
        if new == data:
            continue
        changed += 1
        if a.write:
            p.write_bytes(new)
        elif a.out:
            q = a.out / rel
            q.parent.mkdir(parents=True, exist_ok=True)
            q.write_bytes(new)
    for r in rows:
        print("\t".join(r))
    c = Counter(r[2] for r in rows)
    print(", ".join(f"{k}={v}" for k, v in sorted(c.items())) + f"; {changed} files {'rewritten' if a.write else 'to convert'}, "
          f"{skipped_ctx} ctx files skipped", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
