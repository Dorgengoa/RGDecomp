#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Insert RG_IOP_HLE("fn") census counters at the top of the named functions
(docs/NATIVE-IOP.md).  Idempotent: a body that already counts is left alone.

    python tools/native/iop_instrument.py [--api] FILE FN [FN ...]

--api inserts RG_IOP_API (SDK entry the game reaches) instead of RG_IOP_HLE.
"""
import re
import sys
from pathlib import Path


def main() -> int:
    args = sys.argv[1:]
    macro = "RG_IOP_HLE"
    if args and args[0] == "--api":
        macro = "RG_IOP_API"
        args = args[1:]
    path = Path(args[0])
    names = args[1:]
    lines = path.read_text(encoding="utf-8").split("\n")
    done = set()
    for i, ln in enumerate(lines):
        for n in names:
            if n in done:
                continue
            if not re.match(r"^[A-Za-z_][\w\s\*]*\b%s\s*\(" % re.escape(n), ln) or ln.rstrip().endswith(";"):
                continue
            tag = '%s("%s");' % (macro, n)
            if "{" in ln and ln.rstrip().endswith("}"):        # one-liner
                if tag not in ln:
                    lines[i] = ln.replace("{", "{ " + tag, 1)
                done.add(n)
            else:
                j = i
                while j < len(lines) and lines[j].strip() != "{":
                    j += 1
                if j < len(lines) and tag not in lines[j + 1]:
                    lines.insert(j + 1, "    " + tag)
                done.add(n)
    miss = [n for n in names if n not in done]
    if miss:
        print("not found:", " ".join(miss), file=sys.stderr)
    path.write_text("\n".join(lines), encoding="utf-8")
    print(f"{path}: {len(done)} instrumented")
    return 1 if miss else 0


if __name__ == "__main__":
    sys.exit(main())
