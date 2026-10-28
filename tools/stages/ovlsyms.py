#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `ovlsyms`: give each overlay's own data/bss names an overlay
prefix (PLAN.md transform 7, docs/OVERLAY.md).

All five MWo3 overlays load at 0x004E9E80, and the decomp names their .data and
.bss objects by address (`D_00524D08`), so two overlays can carry the SAME name
for different objects: NORMAL and INSECT share 8 (D_00524D08 ... D_005251B0).
On the PS2 each overlay is linked on its own; on the port all five are linked
into one executable, so the names must differ.  Functions are already
prefixed (`title_...`) by the decomp.

Rule, for files of image <ov> (src/overlays/<ov>/...) only:

    D_XXXXXXXX / jtbl_XXXXXXXX  with  OVERLAY_DATA[ov][0] <= X < OVERLAY_DATA[ov][1]
        ->  <ov>_D_XXXXXXXX / <ov>_jtbl_XXXXXXXX

Everything else is untouched: MAIN names (D_0047xxxx ...), MAIN files (MAIN's
own uses of NORMAL's D_00527020 / D_005273B8 stay unprefixed: the generated
arena defines them as aliases, see tools/gen_overlay_registry.py), comments and
strings are renamed too (harmless; keeps grep consistent).  A name in the
overlay's TEXT range or past its bss end is an error (none at 2efa6b43).
Idempotent: `<ov>_D_x` has no word boundary before `D_`, so it never rematches.

OVERLAY_DATA is a reviewed table (like hwaccess.OVERLAY_DATA):
[data vram, bss end) = 0x004E9E80 + the yaml `data` subsegment start, + data +
bss sizes (naming 2efa6b43 config/<ov>.yaml; the generator cross-checks it
against the snapshot and errors on a mismatch).

Registration (tools/ingest.py is owned elsewhere; not wired in here):

    import ovlsyms
    os_ = ovlsyms.OvlSymsStage()
    ... Stage("ovlsyms", os_.apply, ("unit", "data"), os_)   # any position after
                                                             # asmexclude; before protos
                                                             # is best (protos then sees
                                                             # the final names)

Standalone on one file:  python tools/stages/ovlsyms.py <relpath> IN OUT
"""
from __future__ import annotations

import re
import sys

OVERLAY_DATA = {
    "title":   (0x004F1400, 0x004F1B80),
    "insmenu": (0x004F9780, 0x004FA300),
    "normal":  (0x00524D00, 0x00528200),
    "factory": (0x0050B480, 0x00510C00),
    "insect":  (0x00523B00, 0x00526080),
}
TEXT_START = 0x004E9EC0
NAME = re.compile(r"\b(D|jtbl)_([0-9A-Fa-f]{8})\b")


def image_of(relpath: str) -> str | None:
    m = re.match(r"src/overlays/(\w+)/", relpath.replace("\\", "/"))
    if m and m.group(1) in OVERLAY_DATA:
        return m.group(1)
    m = re.match(r"src/(\w+)_data/", relpath.replace("\\", "/"))
    if m and m.group(1) in OVERLAY_DATA:
        return m.group(1)
    return None


class OvlSymsStage:
    def __init__(self):
        self.errors: list[tuple[str, str]] = []
        self.stats: dict[str, int] = {}
        self.files = 0

    def apply(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        ov = image_of(relpath)
        if ov is None:
            return data, 0
        lo, hi = OVERLAY_DATA[ov]
        text = data.decode("utf-8", errors="surrogateescape")
        n = 0

        def sub(m):
            nonlocal n
            a = int(m.group(2), 16)
            if lo <= a < hi:
                n += 1
                return f"{ov}_{m.group(0)}"
            if TEXT_START <= a < lo or hi <= a < 0x00600000:
                # comments may cite neighbours; only report real code uses
                self.errors.append((relpath, f"{m.group(0)} outside {ov}'s data/bss"))
            return m.group(0)

        new = NAME.sub(sub, text)
        if n:
            self.files += 1
            self.stats[ov] = self.stats.get(ov, 0) + n
        return new.encode("utf-8", errors="surrogateescape"), n

    __call__ = apply

    def report(self) -> str:
        out = [f"ovlsyms: {sum(self.stats.values())} renames in {self.files} files "
               f"({', '.join(f'{k}={v}' for k, v in sorted(self.stats.items()))}), "
               f"{len(self.errors)} errors"]
        out += [f"  ERROR {f}: {why}" for f, why in self.errors]
        return "\n".join(out)


def main(argv: list[str]) -> int:
    if len(argv) != 4:
        print(__doc__)
        return 2
    st = OvlSymsStage()
    with open(argv[2], "rb") as fh:
        new, n = st.apply(argv[1], fh.read())
    with open(argv[3], "wb") as fh:
        fh.write(new)
    print(st.report())
    return 1 if st.errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
