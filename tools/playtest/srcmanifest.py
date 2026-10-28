#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Snapshot the source state a play-test exe is built from (shared tree, other lanes editing).

    python tools/playtest/srcmanifest.py write out/playtest/1026a-manifest.txt [--note "..."]
    python tools/playtest/srcmanifest.py compare out/playtest/1026a-manifest.txt

`write`: HEAD, `git diff --stat`, and the sha256 / size / mtime of every modified or untracked
file (git status -uall; ignored dirs such as build/ out/ game/ and unignored stray build dirs
at the root, e.g. buildrender-i686/, are not listed). `compare`: hashes
the tree again and lists files changed / added / removed since the manifest -- run it after the
build (and after the gates) to prove no other lane's edit slipped in mid-build.
"""
import argparse
import hashlib
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def git(*a):
    return subprocess.run(["git", *a], cwd=ROOT, capture_output=True, text=True,
                          errors="replace").stdout


def changed_files():
    out = []
    for line in git("status", "--porcelain", "-uall").splitlines():
        st, p = line[:2], line[3:].strip().strip('"')
        if " -> " in p:
            p = p.split(" -> ", 1)[1]
        top = p.split("/", 1)[0]
        if top.startswith("build") or (ROOT / top / "CMakeCache.txt").exists():
            continue   # stray build dirs at the root (e.g. buildrender-i686): not source
        out.append((st.strip() or "?", p))
    return sorted(out, key=lambda x: x[1])


def file_rows():
    rows = {}
    for st, p in changed_files():
        f = ROOT / p
        if f.is_file():
            b = f.read_bytes()
            rows[p] = (st, hashlib.sha256(b).hexdigest()[:16], len(b),
                       time.strftime("%m-%d %H:%M:%S", time.localtime(f.stat().st_mtime)))
        else:
            rows[p] = (st, "-", 0, "-")
    return rows


def write(path, note):
    rows = file_rows()
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(f"# play-test source manifest, written {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        if note:
            f.write(f"# {note}\n")
        f.write(f"# HEAD {git('rev-parse', 'HEAD').strip()}\n")
        f.write("\n## git diff --stat (tracked files vs HEAD)\n")
        f.write(git("diff", "--stat=200"))
        f.write(f"\n## files (status, sha256[:16], bytes, mtime, path): {len(rows)}\n")
        for p, (st, h, n, mt) in rows.items():
            f.write(f"{st}\t{h}\t{n}\t{mt}\t{p}\n")
    print(f"srcmanifest: {len(rows)} files -> {path}")


def read_rows(path):
    rows, on = {}, False
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        if line.startswith("## files"):
            on = True
            continue
        if on and line.count("\t") == 4:
            st, h, n, mt, p = line.split("\t")
            rows[p] = h
    return rows


def compare(path):
    old, new = read_rows(path), {p: r[1] for p, r in file_rows().items()}
    ch = [p for p in old if p in new and old[p] != new[p]]
    add = [p for p in new if p not in old]
    gone = [p for p in old if p not in new]
    for tag, lst in (("changed", ch), ("added", add), ("removed", gone)):
        for p in lst:
            print(f"{tag}\t{p}")
    print(f"srcmanifest compare: {len(ch)} changed, {len(add)} added, {len(gone)} removed "
          f"since {path}")
    return 1 if ch or add or gone else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("mode", choices=["write", "compare"])
    ap.add_argument("manifest")
    ap.add_argument("--note")
    a = ap.parse_args()
    if a.mode == "write":
        write(a.manifest, a.note)
        return 0
    return compare(a.manifest)


if __name__ == "__main__":
    sys.exit(main())
