#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""make_release.py: the publishable branch tree + player zip of one build (docs/RELEASE.md).

    python tools/release/make_release.py --tag 1028a --exe EXE --map MAP --setup SETUP_EXE
                                         [--data data] [--out out/release/publish]

Steps:
  1. blankexe.py: EXE minus every byte that matches the retail files -> rg-game.blank
     + rg-game.fill (positions only), round trip checked.
  2. OUT/ = the branch tree: README.md, QUICKSTART.md, LICENSE, THIRD_PARTY_NOTICES.md,
     THIRD_PARTY_LICENSES.txt, release/RogueGalaxyPC-TAG-win32.zip, release/SHA256SUMS.txt.
     The zip holds one folder RogueGalaxyPC/ with Setup.exe (rg-setup), the blank + fill,
     the docs and licenses.
  3. Leak gate (fails the run): every file, and every zip member, is scanned for
       - retail bytes: any 16-byte window with >= 8 distinct byte values that equals one of
         SCUS_974.90, an overlay BIN or an IOP module (padding and small-int runs ignored);
       - identifying text: this machine's user name, profile path, the port's absolute
         path and drive, and git user.name / user.email (read at run time, never stored).
"""
import argparse
import datetime
import hashlib
import io
import os
import re
import shutil
import subprocess
import sys
import tarfile
import zipfile
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
PKG = "RogueGalaxyPC"


def sha256(b):
    return hashlib.sha256(b).hexdigest()


def personal_needles():
    """Identifying strings of this machine and user, from the environment (not stored)."""
    vals = set()
    for k in ("USERNAME", "USER", "COMPUTERNAME", "USERDOMAIN"):
        if os.environ.get(k):
            vals.add(os.environ[k])
    home = os.environ.get("USERPROFILE") or os.environ.get("HOME") or ""
    if home:
        vals.add(home)
        vals.add(Path(home).name)
    for key in ("user.name", "user.email"):
        try:
            v = subprocess.run(["git", "config", "--global", key], capture_output=True, text=True).stdout.strip()
        except OSError:
            v = ""
        if v:
            vals.add(v)
            vals.add(v.split("@")[0])
    for v in list(vals):
        vals.update(p for p in re.split(r"[\s._@\\/-]+", v) if len(p) >= 4)
    port = str(PORT)
    vals.update({port, port.replace("\\", "/"), str(PORT.parent), str(PORT.parent).replace("\\", "/")})
    drive = PORT.drive  # e.g. "B:"
    if drive:
        vals.update({drive + "\\", drive + "/"})
    generic = {"user", "users", "home", "admin", "windows", "desktop"}
    out = sorted({v for v in vals if v and v.lower() not in generic and len(v) >= 3}, key=len, reverse=True)
    return [v.encode() for v in out] + [v.encode("utf-16-le") for v in out]


def retail_index(data, w=16):
    files = [data / "SCUS_974.90"] + sorted((data / "BIN").glob("*.BIN")) + sorted((data / "MODULES").glob("*"))
    idx = set()
    for p in files:
        b = p.read_bytes()
        for f in range(0, len(b) - w + 1, 4):
            s = b[f:f + w]
            if len(set(s)) >= 8:  # real content, not padding / small-int runs
                idx.add(s)
    return idx, w


def scan_retail(b, idx_w):
    idx, w = idx_w
    hits = []
    e = 0
    while e <= len(b) - w:
        if b[e:e + w] in idx:
            hits.append(e)
            e += w
        else:
            e += 1
    return hits


def leak_gate(files, data, crtref, personal=True):
    """files: list of (label, bytes).  Returns (problems, allowed hits).  A retail-matching
    window that also occurs in CRTREF (an exe built from no game code, only the same C/C++
    runtime: build/release-tools/crtref) is library text, not game content."""
    needles = personal_needles()
    idx = retail_index(data)
    probs, allowed = [], 0
    for label, b in files:
        low = b.lower()
        for n in (needles if personal else []):
            if n.lower() in low:
                probs.append(f"{label}: identifying text ({len(n)} bytes, '{n.decode('utf-8', 'replace')[:3]}...')")
        for e in scan_retail(b, idx):
            if b[e:e + 16] in crtref:
                allowed += 1
            else:
                probs.append(f"{label}: retail bytes at {e:#x}: {b[e:e + 16]!r}")
    return probs, allowed


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tag", required=True)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--setup", required=True, help="rg-setup.exe (src/extract, static CRT)")
    ap.add_argument("--crtref", default=str(PORT / "build/release-tools/crtref/out/crtref.exe"),
                    help="CRT-only reference exe (no game code): its text counts as generic")
    ap.add_argument("--data", default=str(PORT / "data"))
    ap.add_argument("--out", default=str(PORT / "out" / "release" / "publish"))
    ap.add_argument("--date", default=datetime.date.today().isoformat())
    a = ap.parse_args()
    data = Path(a.data)
    out = Path(a.out)
    work = out.parent / "work"
    if out.exists():
        shutil.rmtree(out)
    if work.exists():
        shutil.rmtree(work)
    (out / "release").mkdir(parents=True)
    work.mkdir(parents=True)

    # 1. blank + fill
    r = subprocess.run([sys.executable, str(HERE / "blankexe.py"), a.exe, a.map, str(data), str(work),
                        "--min-run", "8"], capture_output=True, text=True)
    print(r.stdout.strip(), r.stderr.strip())
    if r.returncode:
        sys.exit("make_release: blankexe failed")

    # 2. docs
    def tpl(name):
        return (HERE / "template" / name).read_text(encoding="utf-8").replace("@TAG@", a.tag).replace("@DATE@", a.date)

    readme, quick = tpl("README.md"), tpl("QUICKSTART.md")
    notices = tpl("THIRD_PARTY_NOTICES.md")
    lic = (PORT / "LICENSE").read_text(encoding="utf-8")
    parts = []
    with tarfile.open(PORT.parent / "tools" / "dl" / "SDL3-3.4.18.tar.gz") as t:
        m = next(x for x in t.getmembers() if x.name.endswith("/LICENSE.txt") and x.name.count("/") == 1)
        parts.append(("SDL3 3.4.18 (zlib)", t.extractfile(m).read().decode("utf-8")))
    for title, p in (("volk (MIT)", "third_party/volk/LICENSE.md"),
                     ("Vulkan Memory Allocator (MIT)", "third_party/vma/LICENSE.txt"),
                     ("Vulkan-Headers (Apache-2.0 OR MIT)", "third_party/vulkan/LICENSE.md")):
        parts.append((title, (PORT / p).read_text(encoding="utf-8")))
    tpl_lic = "".join(f"{'=' * 72}\n{t}\n{'=' * 72}\n\n{x.strip()}\n\n" for t, x in parts)

    tree = {"README.md": readme, "QUICKSTART.md": quick, "LICENSE": lic,
            "THIRD_PARTY_NOTICES.md": notices, "THIRD_PARTY_LICENSES.txt": tpl_lic}
    for name, text in tree.items():
        (out / name).write_text(text, encoding="utf-8", newline="\n")

    def crlf(s):
        return s.replace("\r\n", "\n").replace("\n", "\r\n").encode("utf-8")

    members = {
        "Setup.exe": Path(a.setup).read_bytes(),
        "rg-game.blank": (work / "rg-game.blank").read_bytes(),
        "rg-game.fill": (work / "rg-game.fill").read_bytes(),
        "QUICKSTART.txt": crlf(quick),
        "README.md": crlf(readme),
        "LICENSE.txt": crlf(lic),
        "THIRD_PARTY_NOTICES.md": crlf(notices),
        "THIRD_PARTY_LICENSES.txt": crlf(tpl_lic),
    }
    zname = f"RogueGalaxyPC-{a.tag}-win32.zip"
    zpath = out / "release" / zname
    fixed = (1980, 1, 1, 0, 0, 0)  # no build-machine timestamps
    with zipfile.ZipFile(zpath, "w", zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        for n, b in members.items():
            zi = zipfile.ZipInfo(f"{PKG}/{n}", date_time=fixed)
            zi.compress_type = zipfile.ZIP_DEFLATED
            zi.external_attr = 0o644 << 16
            z.writestr(zi, b)
    zb = zpath.read_bytes()
    (out / "release" / "SHA256SUMS.txt").write_text(f"{sha256(zb)}  {zname}\n", encoding="ascii", newline="\n")

    # 3. leak gate over the tree and the zip members
    files = []
    for p in sorted(out.rglob("*")):
        if p.is_file():
            files.append((p.relative_to(out).as_posix(), p.read_bytes()))
    with zipfile.ZipFile(zpath) as z:
        for n in z.namelist():
            files.append((f"{zname}:{n}", z.read(n)))
            files.append((f"{zname}:{n} (name)", n.encode()))
    probs, allowed = leak_gate(files, data, Path(a.crtref).read_bytes())
    print(f"make_release: {allowed} windows allowed as C-runtime text (also in --crtref)")
    if probs:
        print("make_release: LEAK GATE FAILED")
        for p in probs[:40]:
            print("  " + p)
        sys.exit(1)
    print(f"make_release: {out} ({len(files)} files incl. zip members), zip {len(zb)} bytes, leak gate PASS")


if __name__ == "__main__":
    main()
