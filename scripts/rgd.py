#!/usr/bin/env python3
"""The matching-decomp harness for SCUS_974.90.

    rgd.py ref      <symbol>          assemble the retail reference into an object
    rgd.py decomp   <symbol> [flags]  run m2c over the reference and print C
    rgd.py build    <symbol>          compile src/<unit>.c with mwcc 2.4
    rgd.py diff     <symbol> [flags]  ref + build + objdiff, side by side
    rgd.py units                      what is registered in config/units.txt

A unit here is ONE FUNCTION, not a translation unit. The retail ELF is stripped
and has no file boundaries to recover, so there is nothing to group functions
by; objdiff is happy to pair a single-function object against a single-function
reference, and that is the whole comparison this project needs. If file
boundaries are ever recovered for a subsystem, units can be widened then.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

import os
# ---- local configuration --------------------------------------------------
# Everything machine-specific comes from the environment (see README.md):
#   RGD_RETAIL_DIR  holds SCUS_974.90 and BIN/<OVERLAY>.BIN copied from your disc
#   RGD_HOST        user@host of the Linux build host (mwcc/mwld run under wibo)
#   RGD_SSH_KEY     private key for RGD_HOST
#   RGD_REMOTE_DIR  work directory on the host; must contain `wibo` and
#                   `mwcps2-3.0.1b210-060308/` (mwccps2.exe, mwldps2.exe)
#   RGD_EEGCC       Sony ee-gcc 2.9-ee-991111-01 install on the host
#   RGD_BASH        (Windows, optional) bash.exe used to run ssh/scp
RETAIL_DIR = Path(os.environ.get("RGD_RETAIL_DIR", ROOT / "retail"))
BUILD_HOST = os.environ.get("RGD_HOST", "")
SSH_KEY = Path(os.environ.get("RGD_SSH_KEY", ROOT / ".ssh" / "id_build"))
REMOTE_ROOT = os.environ.get("RGD_REMOTE_DIR", "~/rgd")
EEGCC = os.environ.get("RGD_EEGCC", "$HOME/eegcc")
# RGD_HOST=local builds on this machine (Linux or WSL): scripts/localhost/
# holds `ssh`/`scp` stand-ins that run the host commands here instead.
if BUILD_HOST == "local":
    _shim = str(ROOT / "scripts" / "localhost")
    if not os.environ.get("PATH", "").startswith(_shim):
        os.environ["PATH"] = _shim + os.pathsep + os.environ.get("PATH", "")


def binutil(tool: str) -> Path:
    """tools/binutils/mips-ps2-decompals-<tool>[.exe] (decompals binutils)."""
    exe = ROOT / "tools" / "binutils" / f"mips-ps2-decompals-{tool}"
    return exe.with_name(exe.name + ".exe") if os.name == "nt" else exe
TOOLS = ROOT / "tools"
AS = binutil("as")
OBJDIFF = TOOLS / "objdiff-cli.exe"
# The compiler is mwcps2-3.0.1b210-060308, settled by a 100% match. It cannot run
# on Windows -- it links LMGR8C.DLL (FLEXlm 8) statically and no licence for it
# exists here -- so builds go to the Linux host under wibo; see build_host().
# 3.0b52 is the best LOCAL stand-in, picked by scoring every installed build
# against all six written functions -- it is top or tied-top on all of them.
# ⚠ AGREEMENT WITH THE STAND-IN IS NOT A MATCH. On EventPlayerIsIdle_250ba0, the one
# function b210 is known to score 100% on, b52 reads 95% (the likely branch)
# while b210's own nominal siblings b44..b119 read 52.9% -- they invert the
# branch structure outright. So the 3.0.x line tracks b210 better than the
# b-series does, but nothing local proves anything about b210.
MWCC = TOOLS / "compilers" / "mwcps2-3.0b52-030722" / "mwccps2.exe"
MWCC_REAL = TOOLS / "compilers" / "mwcps2-3.0.1b210-060308" / "mwccps2.exe"
M2C = TOOLS / "m2c" / "m2c.py"
PYTHON = ROOT / ".venv" / "Scripts" / "python.exe"

ASM_DIR = ROOT / "asm" / "matchings" / "main"
SRC_DIR = ROOT / "src"
REF_DIR = ROOT / "build" / "ref"
OBJ_DIR = ROOT / "build" / "obj"
UNITS = ROOT / "config" / "units.txt"

AS_FLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-g", "-mno-pdr",
            "-non_shared", "-G0", "-I", "include"]
# -O4 is SETTLED: EventPlayerIsIdle_250ba0 matches 100% under b210 at -O4 and nothing else.
# The `no_branch_likely` pragma turned out to be irrelevant -- b210 emits likely
# branches by default -- so no source in this tree carries a pragma. The rest is
# still Dark Cloud's set, unconfirmed until a function needs one of them.
CC_FLAGS = ["-O4", "-c", "-Cpp_exceptions", "off", "-RTTI", "off",
            "-strings", "readonly", "-pragma", "divbyzerocheck on",
            "-nostdinc", "-stderr", "-i", "include"]

# spimdisasm writes every cvt.w.s as a .word with the mnemonic in a comment --
# the R5900's is non-IEEE, so rabbitizer declines to name it. It assembles
# bit-exactly either way, so the build does not care, but m2c reads the .word
# as an unset register and gives up on the function. 1013 functions carry one,
# including the animation clock, so the decompile path puts the mnemonic back.
WORD_WITH_MNEMONIC = re.compile(
    r"^(\s*)/\*.*?\*/\s+\.word\s+0x[0-9A-Fa-f]{8}\s+#\s+([a-z0-9.]+)\s+(\$\S+,\s*\$\S+)")


def die(msg: str) -> "NoReturn":
    print(f"rgd: {msg}", file=sys.stderr)
    raise SystemExit(1)


def asm_path(symbol: str) -> Path:
    p = ASM_DIR / f"{symbol}.s"
    if not p.exists():
        die(f"no reference assembly for {symbol}\n"
            f"     look it up with: grep -i {symbol} config/main.symbols.txt")
    return p


# ★★★★ `src_path` IS TWO FULL rglob()s OF src/, AND A CALLER THAT LOOPS OVER
# EVERY REGISTERED SYMBOL IS THEREFORE O(units x files).  At 5,507 units and
# ~6,300 sources that is ~69 million directory entries per pass, and it grows
# QUADRATICALLY as the project succeeds -- it is why a full `hostbuild.py`
# spends longer walking the tree than compiling it.
#
# ⚠ The fix is OPT-IN and must stay opt-in.  `w1_score.resolve()` deliberately
# retries `src_path()` because a file written moments ago is not reliably
# visible to the next enumeration on this box; a cache that is always on would
# turn that retry into a permanent miss.  So the default path is unchanged and
# a bulk caller says so explicitly:  rgd.prime_src_index()  ...  rgd.drop_src_index()
_SRC_INDEX = None


def prime_src_index() -> int:
    """Walk src/ ONCE and answer every later src_path() from the result."""
    global _SRC_INDEX
    idx = {}
    for suffix in (".c", ".cpp"):
        for p in SRC_DIR.rglob(f"*{suffix}"):
            idx.setdefault(p.stem, {}).setdefault(suffix, []).append(p)
    _SRC_INDEX = idx
    return len(idx)


def drop_src_index() -> None:
    global _SRC_INDEX
    _SRC_INDEX = None


def src_path(symbol: str) -> Path | None:
    if _SRC_INDEX is not None:
        by = _SRC_INDEX.get(symbol)
        if not by:
            return None
        # same order as the uncached form: every .c sorted, then every .cpp
        hits = sorted(by.get(".c", [])) + sorted(by.get(".cpp", []))
        return hits[0] if hits else None
    hits = sorted(SRC_DIR.rglob(f"{symbol}.c")) + sorted(SRC_DIR.rglob(f"{symbol}.cpp"))
    return hits[0] if hits else None


def run(cmd: list, **kw) -> subprocess.CompletedProcess:
    return subprocess.run([str(c) for c in cmd], cwd=ROOT, **kw)


def cmd_ref(symbol: str) -> Path:
    """Assemble the retail disassembly into the object objdiff compares against."""
    REF_DIR.mkdir(parents=True, exist_ok=True)
    out = REF_DIR / f"{symbol}.o"
    r = run([AS] + AS_FLAGS + ["-o", out, asm_path(symbol).relative_to(ROOT)])
    if r.returncode != 0:
        die(f"assembling the reference for {symbol} failed")
    return out


def cmd_build(symbol: str) -> Path:
    src = src_path(symbol)
    if src is None:
        die(f"no source for {symbol}; write src/<subsystem>/{symbol}.c first\n"
            f"     start it from: rgd.py decomp {symbol}")
    OBJ_DIR.mkdir(parents=True, exist_ok=True)
    out = OBJ_DIR / f"{symbol}.o"
    if not MWCC.exists():
        die(f"{MWCC} is missing")
    r = run([MWCC] + CC_FLAGS + [src.relative_to(ROOT), "-o", out])
    if r.returncode != 0:
        die(f"compiling {src.relative_to(ROOT)} failed")
    return out


def cmd_decomp(symbol: str, extra: list) -> int:
    """m2c over the reference assembly, with the cvt.w.s words spelled back out."""
    fixed = ROOT / "build" / "m2c" / f"{symbol}.s"
    fixed.parent.mkdir(parents=True, exist_ok=True)
    lines = []
    for line in asm_path(symbol).read_text().splitlines():
        m = WORD_WITH_MNEMONIC.match(line)
        lines.append(f"{m.group(1)}{m.group(2)} {m.group(3)}" if m else line)
    fixed.write_text("\n".join(lines) + "\n")

    ctx = ROOT / "build" / "ctx.c"
    args = [PYTHON, M2C, "-t", "mipsee-mwcc-c++"]
    if ctx.exists():
        args += ["--context", ctx]
    args += extra + [fixed]
    return run(args).returncode


def write_objdiff_json(symbols: list) -> Path:
    """objdiff pairs objects by unit; each unit here is one function."""
    cfg = {
        "min_version": "2.0.0",
        "custom_make": None,
        "units": [
            {
                "name": f"main/{s}",
                "target_path": f"build/ref/{s}.o",
                "base_path": f"build/obj/{s}.o",
                "metadata": {"auto_generated": False},
            }
            for s in symbols
        ],
    }
    out = ROOT / "objdiff.json"
    out.write_text(json.dumps(cfg, indent=2) + "\n")
    return out


def registered() -> list:
    if not UNITS.exists():
        return []
    return [ln.split("#")[0].strip() for ln in UNITS.read_text().splitlines()
            if ln.split("#")[0].strip()]


def cmd_diff(symbol: str, extra: list) -> int:
    cmd_ref(symbol)
    cmd_build(symbol)
    syms = registered()
    if symbol not in syms:
        syms.append(symbol)
    write_objdiff_json(syms)
    return run([OBJDIFF, "diff", "-p", ".", "-u", f"main/{symbol}", symbol] + extra).returncode


def main() -> int:
    ap = argparse.ArgumentParser(prog="rgd.py", add_help=True)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("ref", "build"):
        sub.add_parser(name).add_argument("symbol")
    for name in ("decomp", "diff"):
        p = sub.add_parser(name)
        p.add_argument("symbol")
        p.add_argument("extra", nargs=argparse.REMAINDER)
    sub.add_parser("units")

    a = ap.parse_args()
    if a.cmd == "ref":
        print(cmd_ref(a.symbol))
    elif a.cmd == "build":
        print(cmd_build(a.symbol))
    elif a.cmd == "decomp":
        return cmd_decomp(a.symbol, a.extra)
    elif a.cmd == "diff":
        return cmd_diff(a.symbol, a.extra)
    elif a.cmd == "units":
        for s in registered():
            state = "src" if src_path(s) else "asm only"
            print(f"{s:<24} {state}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
