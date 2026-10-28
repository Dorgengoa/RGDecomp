#!/usr/bin/env python3
"""Rehash STALE overrides after a re-ingest (docs/UB-AUDIT.md "Overrides rehashed"):
rewrite the `rg-override: replaces game/<path> sha256 <hex>` header of each named
override to game/MANIFEST.tsv's current hash.  Content is not touched.

    python tools/ubaudit/rehash.py overrides/src/main/x/F.c ...
"""
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
man = {r.split("\t")[0]: r.split("\t")[1]
       for r in (PORT / "game" / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]}
rx = re.compile(rb"(rg-override: replaces game/(\S+) sha256 )([0-9a-fA-F]{64})")
for a in sys.argv[1:]:
    p = Path(a)
    b = p.read_bytes()
    m = rx.search(b[:4096])
    if not m:
        print(f"{a}: no header"); continue
    new = man[m.group(2).decode()]
    if m.group(3).decode().lower() == new:
        print(f"{a}: current"); continue
    p.write_bytes(b[:m.start(3)] + new.encode() + b[m.end(3):])
    print(f"{a}: {m.group(3).decode()[:12]} -> {new[:12]}")
