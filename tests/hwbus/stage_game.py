#!/usr/bin/env python3
"""Run the hwaccess stage over a copy of game/ and syntax-check every file it
changed with clang (D2 flags, PORT-HEADERS.md include order; same flags as
tools/syntaxcheck.py), before and after (ctest -L hwbus).

    python tests/hwbus/stage_game.py [OUT]            # default out/hw-test/game
    python tests/hwbus/stage_game.py OUT control      # must FAIL (see below)

Pass criteria:
  - the stage reports 0 errors and every game row of census/addr_literals.tsv
    is accounted for (rewritten / asm / left with a reason);
  - every changed file is idempotent (checked by the stage CLI);
  - no changed file has a clang error the original did not have;
  - no hardware dereference `*(volatile T *)0x10xxxxxx / 0x1200xxxx` is left
    outside asm in a compiled game file, and no MAIN overlay literal.
Control: the `#define NAME (*(volatile T *)A)` alias handling is disabled,
so `GS_PMODE = ...` stores in GsDbufPutEnv become assignments to an rvalue
-> new clang errors -> FAIL (proves the syntax check is armed).
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
sys.path.insert(0, str(PORT / "tools" / "stages"))
import hwaccess as H  # noqa: E402
import portxform as X  # noqa: E402
import syntaxcheck as S  # noqa: E402


def clang(root: Path, rel: str, env) -> list[str]:
    cxx = rel.endswith(".cpp")
    exe = str(S.LLVM / "bin" / ("clang++.exe" if cxx else "clang.exe"))
    std = ["-std=gnu++17", *S.CXX_FLAGS] if cxx else ["-std=gnu99", *S.C_FLAGS]
    cmd = [exe, "-fsyntax-only", "-w", "-ferror-limit=0", "-fno-color-diagnostics", *S.D2, *std,
           "-include", "port/prelude.h", "-I", str(PORT / "include"), "-I", str(root / "include"),
           rel]
    r = subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=str(root),
                       encoding="utf-8", errors="replace")
    errs = []
    for ln in r.stderr.splitlines():
        m = S.DIAG.match(ln)
        if m:
            errs.append(re.sub(r":\d+:\d+:", ":", ln.replace("\\", "/")))
    return errs


def staged_main(control: bool) -> int:
    """game/ is already hwaccess-staged (ingest runs the stage, docs/LINK.md):
    re-running it changes nothing, so check the stage's OWN accounting instead
    -- game/HWACCESS.tsv (what ingest rewrote) reconciled against
    census/addr_literals.tsv (same rule as at ingest: 0 UNACCOUNTED), every
    rewritten file compiles with 0 clang errors, nothing left behind.
    Control: the mask-* rows (the reviewed PS2_PHYS/PS2_UNCACHED/PS2_UCAB
    sites) are dropped -> their census rows are UNACCOUNTED -> FAIL."""
    game = PORT / "game"
    st = H.HwAccessStage(H.CENSUS)
    lines = (game / "HWACCESS.tsv").read_text(encoding="utf-8").splitlines()[1:]
    for ln in lines:
        f = ln.split("\t")
        if len(f) < 7 or (control and f[3].startswith("mask-")):
            continue
        st.rows.append(H.Rewrite(f[0], int(f[1]), f[2], f[3], f[4], f[5], f[6]))
    units = [r.split("\t")[0] for r in (game / "MANIFEST.tsv").read_text(
        encoding="utf-8").splitlines()[1:] if r.split("\t")[3] == "unit"]
    for rel in units:
        if H.file_lib(rel) == "game" and st.QUICK.search(
                (game / rel).read_text(encoding="utf-8", errors="replace")):
            st.seen.add(rel)
    rec = st.reconcile()
    unacc = [(row, d) for row, d in rec if d == "UNACCOUNTED"]
    for row, _ in unacc:
        print(f"    UNACCOUNTED {row['file']}:{row['line']} {row['value']} {row['category']}")
    bad = 0
    if unacc:
        print(f"FAIL: {len(unacc)} unaccounted census rows")
        bad += 1
    changed = sorted({r.file for r in st.rows})
    env = S.msvc_env()
    errs = 0
    for rel in changed:
        e = clang(game, rel, env)
        if e:
            errs += len(e)
            print(f"ERRORS {rel}:")
            for x in e[:10]:
                print("    " + x)
    print(f"syntax: {len(changed)} rewritten files, {errs} clang errors")
    bad += errs > 0
    left = 0
    for rel in changed:
        text = (game / rel).read_text(encoding="utf-8", errors="replace")
        code = X.blank(text)
        spans = [(a, b) for a, b, _ in X.asm_blocks(code)]
        spans += [(f.start, f.body_close) for f in X.find_funcs(code) if f.is_asm]
        for m in H.DEREF_RX.finditer(code):
            a = H.lit(m.group("A"))
            if any(lo <= m.start() <= hi for lo, hi in spans):
                continue
            if H.is_hw(a) or (H.is_ovl(a) and H.file_image(rel) == "main"):
                left += 1
                print(f"LEFT {rel}: {text[m.start():m.end()]}")
    bad += left > 0
    if len(changed) < 25:
        print(f"FAIL: only {len(changed)} files rewritten (expected the ~31 census files)")
        bad += 1
    print("stage_game (staged game/): " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


def main() -> int:
    args = [a for a in sys.argv[1:] if a != "control"]
    control = "control" in sys.argv[1:]
    snap = (PORT / "game" / "SNAPSHOT.txt")
    if snap.exists() and re.search(r"^stages\t.*\bhwaccess\b", snap.read_text(), re.M):
        return staged_main(control)
    out = (Path(args[0]) if args else PORT / "out" / "hw-test" / "game").resolve()
    if control:
        H.DEFINE_RX = re.compile(r"(?!)")
    changed_list = out.parent / (out.name + ".changed.txt")
    sys.argv = ["hwaccess", "--game", str(PORT / "game"), "--out", str(out),
                "--changed", str(changed_list)]
    rc = H.main()
    bad = 0
    if rc != 0:
        print("FAIL: stage reported errors or unaccounted census rows")
        bad += 1
    changed = [ln for ln in changed_list.read_text().split() if ln]
    env = S.msvc_env()
    new_errs = 0
    for rel in changed:
        before = clang(PORT / "game", rel, env)
        after = clang(out, rel, env)
        extra = [e for e in after if e not in before]
        if extra:
            new_errs += len(extra)
            print(f"NEW ERRORS {rel}:")
            for e in extra[:10]:
                print("    " + e)
    print(f"syntax: {len(changed)} changed files, {new_errs} new clang errors")
    bad += new_errs > 0
    # nothing left behind: hardware derefs / MAIN overlay literals outside asm
    left = 0
    for rel in changed:
        text = (out / rel).read_text(encoding="utf-8", errors="replace")
        code = X.blank(text)
        spans = [(a, b) for a, b, _ in X.asm_blocks(code)]
        spans += [(f.start, f.body_close) for f in X.find_funcs(code) if f.is_asm]
        for m in H.DEREF_RX.finditer(code):
            a = H.lit(m.group("A"))
            if any(lo <= m.start() <= hi for lo, hi in spans):
                continue
            if H.is_hw(a) or (H.is_ovl(a) and H.file_image(rel) == "main"):
                left += 1
                print(f"LEFT {rel}: {text[m.start():m.end()]}")
    bad += left > 0
    if len(changed) < 25:
        print(f"FAIL: only {len(changed)} files changed (expected the ~31 census files)")
        bad += 1
    print("stage_game: " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
