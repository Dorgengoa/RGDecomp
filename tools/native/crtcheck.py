#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Wrong-CRT guard for the i686 Windows exes (docs/TOOLCHAIN.md "Wrong CRT / STL", "MSVC toolset").

2026-11-10 (lane menuleft, USER: "use VS 2022 build tools"; VS 2019 was removed): the build
toolset is now VS 2022 Build Tools, MSVC 14.44.  The one CRT difference the game saw (float
sqrtf rounding under the guest MXCSR, below) is taken out of the CRT by port/sqrtf_map.h, so an
exe passes when its CRT objects are ONE consistent known toolset: VS 2022 14.44 (the build
toolset) or VS 2019 14.29 (exes built before 11-10: baselines, the oracle).  A mix (a build dir
rebuilt in another environment) fails.  --toolset 14.44 (the post-link step,
cmake/crtguard.cmake: the build dir's RG_MSVC_TOOLS_VERSION) requires that one.
History (VS 2019 era):

An i686 rg-game built by plain `ninja` OUTSIDE a vcvars x86 shell is compiled and linked
against another MSVC CRT / STL (clang / lld-link autodetect the newest Visual Studio, VS 2022,
instead of the VS 2019 Build Tools 14.29 the baselines use): the CRT's float helpers
(`_sqrtf` & co. from libcpmt:xfprec.obj) are other code, i686 pixels change and the golden
route's run hash differs from field 24,894 (lane rtgi2, 2026-11-07).  This reads the link map
lld-link writes beside the exe (/MAP) and checks which CRT objects were linked:

    python tools/native/crtcheck.py MAP_OR_EXE [...]      # PASS / FAIL per exe, exit 1 on any FAIL
    python tools/native/crtcheck.py EXE --fail-rename     # (post-link) FAIL also renames the exe
                                                          #  to <exe>.wrongcrt so nothing runs it
    python tools/native/crtcheck.py MAP --list            # the CRT lib:object set
    python tools/native/crtcheck.py MAP --ref FILE        # also diff the set vs a reference list

An EXE argument means <exe without .exe>.map; x64 exes (PE machine 0x8664) and Linux maps are
skipped (PASS, "not i686").  Rules (i686): every REQUIRED object present, no FORBIDDEN one.
A missing map is a FAIL (nothing to check) unless --allow-nomap (then a WARNING; bootcheck.py and
render_gate.sh allow it, build_playtest.py does not).
Used by: the rg-game / rg-game-oracle POST_BUILD step (cmake/crtguard.cmake), build_playtest.py
(build step + every gate), bootcheck.py, render_gate.sh.  Control: crtcheck.py --selftest.
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

# known toolsets: name, REQUIRED objects, FORBIDDEN object patterns.
# VS 2019 (14.29) x86: _sqrtf / _ldexpf / the _FXp_* helpers come from libcpmt's xfprec.obj;
# vector_algorithms / ftol3 / locale0 only come with the newer STL / CRT.
# VS 2022 (14.44) x86: the STL's asan_noop.obj (in every 14.44 link: rg-game and the oracle; 14.29 has
# none); never xfprec.  (special_math / ftol3 / the
# UCRT *_sse2_precise kernels came only with the CRT's sqrtf: gone since port/sqrtf_map.h.)
TOOLSETS = {
    "14.44": ("VS 2022 Build Tools 14.44", ["libcpmt:asan_noop.obj"],
              [r"^libcpmt:xfprec\.obj$", r"^libcpmt:xfd[a-z]+\.obj$"]),
    "14.29": ("VS 2019 Build Tools 14.29", ["libcpmt:xfprec.obj"],
              [r"\bvector_algorithms\.obj$", r"\bftol3[a-z_]*\.obj$", r"^libcpmt:locale0?\.obj$"]),
}
BUILD_TOOLSET = "14.44"   # the toolset builds use now (cmake/crtguard.cmake RG_MSVC_TOOLS_DOC)
REQUIRED = TOOLSETS[BUILD_TOOLSET][1]
FORBIDDEN = TOOLSETS[BUILD_TOOLSET][2]
CRT_LIBS = ("libcmt", "libcpmt", "libvcruntime", "libucrt", "msvcrt", "msvcprt", "vcruntime",
            "ucrt", "oldnames", "legacy_stdio_definitions", "libconcrt")
OBJ_RE = re.compile(r"\s((?:%s)[a-z0-9_]*):([A-Za-z0-9_.$-]+\.obj)\s*$" % "|".join(CRT_LIBS), re.I)


def pe_machine(exe: Path):
    try:
        b = exe.read_bytes()[:4096]
        off = struct.unpack_from("<I", b, 0x3C)[0]
        if b[:2] != b"MZ" or b[off:off + 4] != b"PE\0\0":
            return None
        return struct.unpack_from("<H", b, off + 4)[0]
    except (OSError, struct.error):
        return None


def crt_objects(text: str) -> set[str]:
    out = set()
    for line in text.splitlines():
        m = OBJ_RE.search(line)
        if m:
            out.add(f"{m.group(1).lower()}:{m.group(2)}")
    return out


def map_arch(text: str) -> str:
    head = text[:4000]
    if "Preferred load address" not in head:
        return "elf" if ("Memory map" in head or "VMA" in head) else "?"
    # x86 C symbols carry a leading underscore (_main); x64 ones do not
    return "x64" if re.search(r"\smainCRTStartup\s", text) and not re.search(r"\s_mainCRTStartup\s", text) else "i686"


def evaluate(objs: set[str], toolset: str | None = None) -> tuple[list[str], list[str]]:
    """(missing, bad) for one toolset (default the build toolset)"""
    _, req, forb = TOOLSETS[toolset or BUILD_TOOLSET]
    missing = [r for r in req if r not in objs]
    bad = sorted(o for o in objs for f in forb if re.search(f, o))
    return missing, bad


def which_toolset(objs: set[str], only: str | None = None):
    """the known toolset whose markers the CRT set matches (None: none / a mix)"""
    for k in ([only] if only else TOOLSETS):
        if evaluate(objs, k) == ([], []):
            return k
    return None


def check(path: Path, fail_rename=False, allow_nomap=False, ref=None, quiet=False, toolset=None) -> bool:
    path = Path(path)
    exe = path if path.suffix.lower() == ".exe" else path.with_suffix(".exe")
    mp = path.with_suffix(".map")
    mach = pe_machine(exe) if exe.exists() else None
    if mach == 0x8664:
        if not quiet:
            print(f"crtcheck: SKIP {exe} (x64 exe; the guard is i686-only)")
        return True
    if not mp.exists():
        msg = (f"crtcheck: {'WARNING' if allow_nomap else 'FAIL'} {exe}: no link map {mp}: its MSVC CRT cannot be checked"
               " (copy the .map beside the exe)")
        print(msg)
        return allow_nomap
    text = mp.read_text(encoding="utf-8", errors="replace")
    arch = "i686" if mach == 0x14C else map_arch(text)
    if arch != "i686":
        if not quiet:
            print(f"crtcheck: SKIP {mp} ({arch} map; the guard is i686-only)")
        return True
    objs = crt_objects(text)
    tk = which_toolset(objs, toolset)
    ok = tk is not None
    missing, bad = evaluate(objs, toolset)
    if ok:
        print(f"crtcheck: PASS {mp.name if quiet else mp}: {len(objs)} CRT objects, {TOOLSETS[tk][0]} x86 CRT markers present")
    else:
        print(f"crtcheck: FAIL {mp}: the exe's MSVC CRT / STL objects are not one known toolset"
              f" ({'want ' + TOOLSETS[toolset][0] if toolset else 'VS 2022 14.44 or VS 2019 14.29'}; vs"
              f" {TOOLSETS[toolset or BUILD_TOOLSET][0]}: missing {missing or '-'}, other-toolset objects {bad or '-'}).\n"
              "  It was built outside a vcvars x86 shell (plain ninja): its pixels and run hash are NOT\n"
              "  comparable with the gate baselines.  Rebuild inside vcvars x86: python tools/native/lane_build.py\n"
              "  BUILD_DIR [TARGET], python tools/playtest/vcrun.py BUILD_DIR -- ninja TARGET, or tools/build.ps1;\n"
              "  objects compiled outside vcvars are stale too: ninja -t clean first (docs/TOOLCHAIN.md \"Wrong CRT / STL\").")
        if fail_rename and exe.exists():
            dst = exe.with_name(exe.name + ".wrongcrt")
            try:
                dst.unlink(missing_ok=True)
                exe.rename(dst)
                print(f"  renamed {exe.name} -> {dst.name} (so nothing runs it; the next build relinks it)")
            except OSError as e:
                print(f"  could not rename {exe}: {e}")
    if ref:
        want = {l.strip() for l in Path(ref).read_text().splitlines() if l.strip() and not l.startswith("#")}
        extra, gone = sorted(objs - want), sorted(want - objs)
        print(f"  vs {ref}: {len(extra)} extra {extra[:12]}, {len(gone)} missing {gone[:12]}")
    return ok


def selftest() -> int:
    h = " Preferred load address is 00400000"
    v19 = "\n".join([h, " 0001:0 _sqrtf 0 libcpmt:xfprec.obj", " 0001:0 _mainCRTStartup 0 libcmt:exe_main.obj"])
    v22 = "\n".join([h, " 0001:0 _x 0 libcpmt:asan_noop.obj", " 0001:0 __ftol3 0 libcmt:ftol3.obj",
                      " 0001:0 _mainCRTStartup 0 libcmt:exe_main.obj"])
    mix = "\n".join([h, " 0001:0 _sqrtf 0 libcpmt:xfprec.obj", " 0001:0 __ftol3 0 libcmt:ftol3.obj",
                      " 0001:0 _mainCRTStartup 0 libcmt:exe_main.obj"])
    r = [which_toolset(crt_objects(t)) for t in (v19, v22, mix)]
    r.append(which_toolset(crt_objects(v19), "14.44"))
    ok = r == ["14.29", "14.44", None, None] and map_arch(v19) == "i686"
    print(f"crtcheck selftest: 2019 / 2022 / mix / 2019-as-2022 -> {r} -> {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("paths", nargs="*")
    ap.add_argument("--fail-rename", action="store_true")
    ap.add_argument("--allow-nomap", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--ref")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--toolset", choices=sorted(TOOLSETS), help="require this toolset (default: any known one)")
    a = ap.parse_args(argv)
    if a.selftest:
        return selftest()
    if a.list:
        for p in a.paths:
            for o in sorted(crt_objects(Path(p).with_suffix(".map").read_text(encoding="utf-8", errors="replace"))):
                print(o)
        return 0
    ok = True
    for p in a.paths:
        ok &= check(Path(p), a.fail_rename, a.allow_nomap, a.ref, a.quiet, a.toolset)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
