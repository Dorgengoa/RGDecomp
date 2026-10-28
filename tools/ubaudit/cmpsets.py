#!/usr/bin/env python3
"""Compare two fixture sets (tools/fixtures/regen.py manifests) of two builds of
the same tree: per milestone the vbl and run hash, and with --check sets the
check run hash and the frame hash at milestone + K (docs/UB-AUDIT.md).

    python tools/ubaudit/cmpsets.py SET_A SET_B      (out/fixtures/<exe-id> dirs or exes)

Exit 0 when every common milestone matches.  The run hash folds the kernel
trace, audio, pad words and virtual time every field, so equal hashes at the
last milestone mean the two runs were identical field by field up to there.
"""
import hashlib
import json
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]


def load(p: str) -> dict:
    q = Path(p)
    if q.suffix.lower() == ".exe":
        h = hashlib.sha256(q.read_bytes()).hexdigest()[:16]
        q = PORT / "out" / "fixtures" / h
    return json.loads((q / "manifest.json").read_text(encoding="utf-8")) | {"_dir": str(q)}


def flat(m: dict) -> dict:
    out = {}
    for n, r in m.get("milestones", {}).items():
        out[n] = {"vbl": r.get("vbl"), "run_hash": r.get("run_hash")}
    for n, r in (m.get("checks") or {}).items():
        d = out.setdefault(n, {})
        if isinstance(r, dict):
            for k, v in r.items():
                if k in ("run_hash", "frame_hash", "vbl", "shot_hash", "hash"):
                    d["check_" + k] = v
    return out


def main() -> int:
    a, b = load(sys.argv[1]), load(sys.argv[2])
    fa, fb = flat(a), flat(b)
    print(f"A {a['_dir']}  ({a.get('exe_source')})")
    print(f"B {b['_dir']}  ({b.get('exe_source')})")
    bad = 0
    for n in fa:
        if n not in fb:
            print(f"  {n:12s} only in A")
            continue
        keys = sorted(set(fa[n]) | set(fb[n]))
        diff = [k for k in keys if fa[n].get(k) != fb[n].get(k)]
        bad += bool(diff)
        tag = "OK  " if not diff else "DIFF"
        print(f"  {tag} {n:12s} " + "  ".join(
            f"{k}={fa[n].get(k)}" + ("" if k not in diff else f"|{fb[n].get(k)}") for k in keys))
    print("IDENTICAL" if not bad else f"{bad} milestones differ")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
