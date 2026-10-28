#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""datafix_packed.py: put retail's NUMBER back in data words the data layer turned into
pointers although they are packed small integers (s16 pairs / byte groups).  On the host
such a word holds a HOST address, so what the game reads there changes with every relink
(BRINGUP-HISTORY 2026-10-24 "Revelation flashing slot": sprite 12's w/h pair 0x00400040 in
D_004539F0 was `(u32)&DataTableCompareThunk_400040`, so the Revelation board's slot icon UVs
differed between any two links).

Writes/updates overrides/src/main_data/data2c_*.c (the class's existing home: the 2026-10-13
`main-bss` row fix, out/render-bringup/tools/mk_datafix_overrides.py).  An existing override
is edited in place (its header hash is kept); a new one gets the header with the sha256 of
the game/ file.  Idempotent.  Candidates come from tools/parity/pairptr_census.py; every
address below was checked by hand against its neighbours in the retail ELF (the table is
plainly packed: coordinate quads, (id, offset) pairs, ASCII groups).

    python tools/parity/datafix_packed.py [--dry-run]
Re-configure the build after a NEW override file (configure lists overrides/).
"""
from __future__ import annotations

import argparse
import hashlib
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from pairptr_census import elf_reader, split_top  # noqa: E402

# address -> evidence (retail words around it; all packed data)
PACKED = {
    0x00453A54: "Revelation sprite table D_004539F0 entry 12 w/h (64, 64); was &DataTableCompareThunk_400040",
    0x0044E720: "s16 pairs (.. 00FF0010 00BCFD2C [00440014] 00FF000C ..)",
    0x00450884: "s16 pairs (00030024 [00480000] 004C0005 00040012 ..)",
    0x00450D94: "s16 pairs, copy of D_00450870",
    0x004538A4: "s16 pairs, copy of D_00450870",
    0x00453CE4: "s16 pairs, copy of D_00450870",
    0x0045381C: "(index, offset) s16 pairs (00180001 00000002 00300003 [00480004] 00600005 ..)",
    0x00450CC4: "s16 offsets 0,0x18,0x30,0x48,.. (00180000 [00480030] 00780060 ..)",
    0x00453934: "s16 offsets 0,0x18,0x30,0x48,.. (00180000 [00480030] 00780060 ..)",
    0x00462BA4: "s16 offsets 0,0x18,0x30,0x48,.. (00180000 [00480030] 00780060 ..)",
    0x00464144: "s16 offsets 0,0x18,0x30,0x48,.. (00180000 [00480030] 00780000 ..)",
    0x00454500: "ASCII letter groups A..Z (.. 46000045 [00470000] 00004800 ..)",
    0x00462790: "s16 rects (-6, 69, 14, 14) / (128, 82, 14, 14)",
    0x004627A0: "s16 rects (-6, 69, 14, 14) / (128, 82, 14, 14)",
    0x004627C0: "s16 rects (52, 69, 14, 14) / (142, 82, 14, 14)",
    0x00468FB4: "s16 pairs (.. 02BC0046 001C0016 [00460007] 001602BD ..)",
    0x00446740: "packed GS-style words (00440017 00440415 0001E000 12000000 [00480017] 00480415 ..)",
    0x00451060: "s16 coordinate pairs ((0xD4,0x44) (0xF0,0x28) ..)",
    0x0045106C: "s16 coordinate pairs",
    0x0045107C: "s16 coordinate pairs",
    0x00451084: "s16 coordinate pairs",
    0x00451090: "s16 coordinate pairs",
}
DEF = re.compile(r'^((?:static )?(?:const )?u32 (\w+)\[(\d+)\] __attribute__\(\(section\("\.data\$rg([0-9A-F]{8})"\)[^;]*?=\s*\{)(.*?)(\};)',
                 re.S | re.M)
TOOL = "tools/parity/datafix_packed.py"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--elf", default="../work/SCUS_974.90")
    a = ap.parse_args()
    word = elf_reader(a.elf)
    left = dict(PACKED)
    for gf in sorted((PORT / "game" / "src" / "main_data").glob("data2c_*.c")):
        rel = gf.relative_to(PORT / "game").as_posix()
        of = PORT / "overrides" / rel
        src = (of if of.exists() else gf).read_text(encoding="utf-8")
        hits = []

        def fix(m):
            head, name, n, base, body, tail = m.groups()
            base, n = int(base, 16), int(n)
            if not any(base <= t < base + 4 * n for t in left):
                return m.group(0)
            # split on top-level commas, comments kept attached to their element
            parts, depth, cur, i = [], 0, [], 0
            while i < len(body):
                if body.startswith("/*", i):
                    j = body.index("*/", i) + 2
                    cur.append(body[i:j]); i = j; continue
                ch = body[i]
                depth += ch in "([{"
                depth -= ch in ")]}"
                if ch == "," and depth == 0:
                    parts.append("".join(cur)); cur = []
                else:
                    cur.append(ch)
                i += 1
            parts.append("".join(cur))
            k = -1
            for pi, p in enumerate(parts):
                code = re.sub(r"/\*.*?\*/", "", p, flags=re.S).strip()
                if not code:
                    continue
                k += 1
                ad = base + 4 * k
                if ad in left and not re.fullmatch(r"0x[0-9A-Fa-f]+u?|\d+u?", code):
                    lead = p[:len(p) - len(p.lstrip())]
                    parts[pi] = f"{lead}0x{word(ad):08X}u /* rg-override: packed numbers, not a pointer (was {code}; {TOOL}) */"
                    hits.append(ad)
            return head + ",".join(parts) + tail

        new = DEF.sub(fix, src)
        if not hits:
            continue
        for h in hits:
            left.pop(h, None)
        if of.exists():
            new = re.sub(r"(\* why: [^\n]*)", lambda m: m.group(1) + f"; packed words {', '.join('0x%08X' % x for x in hits)} ({TOOL})", new, count=1)
        else:
            sha = hashlib.sha256(gf.read_bytes()).hexdigest()
            new = (f"/* rg-override: replaces game/{rel} sha256 {sha}\n"
                   f" * why: packed numbers symbolised as pointers at {', '.join('0x%08X' % x for x in hits)}\n"
                   f" * (generated by {TOOL}; BRINGUP-HISTORY 2026-10-24 Revelation flashing slot) */\n") + new
        print(f"{'would write' if a.dry_run else 'wrote'} overrides/{rel}: {', '.join('0x%08X' % x for x in hits)}"
              f"{' (existing override)' if of.exists() else ' (NEW)'}")
        if not a.dry_run:
            of.parent.mkdir(parents=True, exist_ok=True)
            of.write_text(new, encoding="utf-8", newline="\n")
    for ad, why in sorted(left.items()):
        print(f"not found / already numeric: 0x{ad:08X} ({why})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
