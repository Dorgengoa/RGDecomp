#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""sspeek.py STATE [STATE2] SECTION OFFSET [WORDS]: print 32-bit words of a save-state
section (e.g. ram) at OFFSET (hex), side by side for two states (docs/X64-PLAN.md 0.7)."""
import struct, sys
sys.path.insert(0, __import__("os").path.dirname(__file__))
from ssdiff import read_state
a = sys.argv[1:]
states = [x for x in a if x.endswith(".rgstate")]
rest = [x for x in a if not x.endswith(".rgstate")]
sec, off = rest[0], int(rest[1], 16)
n = int(rest[2], 0) if len(rest) > 2 else 32
secs = [{nm: b for nm, ad, b in read_state(s)["secs"]}[sec] for s in states]
for i in range(n):
    o = off + 4 * i
    ws = [struct.unpack_from("<I", b, o)[0] for b in secs]
    fl = [struct.unpack("<f", struct.pack("<I", w))[0] for w in ws]
    mark = "" if len(set(ws)) == 1 else "  <--"
    print(f"+{o:07X}  " + "  ".join(f"{w:08x} ({f:.6g})" for w, f in zip(ws, fl)) + mark)
