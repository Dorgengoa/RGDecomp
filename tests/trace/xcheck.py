# SPDX-License-Identifier: CC0-1.0
"""Cross-checks of the C recorder against tools/trace/trace.py itself.

  xcheck.py hash  --exe rg-trace-tests [--control]
      the C BLAKE2b-8 of fixed buffers == hashlib.blake2b(digest_size=8).
      --control compares against a plausible wrong hash (the first 8 bytes of
      a 64-byte BLAKE2b digest): must FAIL.
  xcheck.py image --exe rg-trace-tests --regions R --tmp DIR [--control]
      the C recorder in PS2-pointer mode over a synthetic EE image writes a
      TSV; trace.py's load_regions/region_bytes/h over the same image must give
      exactly the same rows, and trace.py compare must parse the port TSV and
      call it IDENTICAL.  --control perturbs one expected row: must FAIL.
"""
import argparse
import contextlib
import hashlib
import io
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(PORT, "tools", "trace"))

import trace  # noqa: E402


def buf(n):
    return bytes(((i * 131 + 7 + (i >> 9)) & 0xFF) for i in range(n))


def t_hash(args):
    out = subprocess.run([args.exe, "hash"], capture_output=True, text=True, check=True).stdout
    full = buf(0x100000)
    bad = 0
    n = 0
    for line in out.splitlines():
        k, got = line.split("\t")
        data = k.encode() if k.startswith("ptr:") else full[:int(k)]
        if args.control:
            want = hashlib.blake2b(data).hexdigest()[:16]
        else:
            want = trace.h(data)
        n += 1
        if got != want:
            bad += 1
            print("len %s: C %s, python %s" % (k, got, want))
    print("hash: %d buffers, %d differ" % (n, bad))
    return 1 if bad or n < 10 else 0


class Snap:
    def __init__(self, ee):
        self.ee = ee

    def space(self, s):
        return self.ee if s == "ee" else b""


def t_image(args):
    os.makedirs(args.tmp, exist_ok=True)
    out = os.path.join(args.tmp, "port_image.tsv")
    img = os.path.join(args.tmp, "image.bin")
    exp = os.path.join(args.tmp, "python_image.tsv")
    subprocess.run([args.exe, "image", args.regions, out, img], check=True)
    with open(img, "rb") as f:
        ee = f.read()
    s = Snap(ee)
    frame, cycle = 120, 0x2328FA47
    rows = ["%d\t@cycle\t%08x" % (frame, cycle),
            "%d\t@vbl\t%d" % (frame, int.from_bytes(ee[trace.GAME_VBL:trace.GAME_VBL + 4], "little"))]
    for reg in trace.load_regions(args.regions):
        data = trace.region_bytes(s, reg)
        if data is not None:
            rows.append("%d\t%s\t%s" % (frame, reg[1], trace.h(data)))
    if args.control:
        k = next(i for i, r in enumerate(rows) if "\tsym:Kseg\t" in r)
        rows[k] = rows[k][:-1] + ("0" if rows[k][-1] != "0" else "1")
    with open(exp, "w", encoding="utf-8", newline="\n") as f:
        f.write("# python reference (xcheck.py)\n" + "\n".join(rows) + "\n")
    with open(out, encoding="utf-8") as f:
        got = [l.rstrip("\n") for l in f if not l.startswith("#") and l.strip()]
    bad = 0
    for i in range(max(len(rows), len(got))):
        a = rows[i] if i < len(rows) else "(none)"
        b = got[i] if i < len(got) else "(none)"
        if a != b:
            bad += 1
            print("row %d: python %r, port %r" % (i, a, b))
    print("image: %d python rows, %d port rows, %d differ" % (len(rows), len(got), bad))
    # TSV compatibility: trace.py's own compare reads the port file
    cap = io.StringIO()
    with contextlib.redirect_stdout(cap):
        rc = trace.compare(argparse.Namespace(a=exp, b=out, key="frame", only=None, ignore=None, limit=10))
    print(cap.getvalue().strip())
    if rc != 0 or "IDENTICAL" not in cap.getvalue():
        bad += 1
    return 1 if bad or len(rows) < 10 else 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("what", choices=("hash", "image"))
    ap.add_argument("--exe", required=True)
    ap.add_argument("--regions")
    ap.add_argument("--tmp")
    ap.add_argument("--control", action="store_true")
    args = ap.parse_args()
    args.exe = os.path.abspath(args.exe)
    return t_hash(args) if args.what == "hash" else t_image(args)


if __name__ == "__main__":
    sys.exit(main())
