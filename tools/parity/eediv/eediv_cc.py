#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compiler launcher for game objects with EE float semantics (docs/BRINGUP.md "Retail
parity"; opt-in, see cmake/game.cmake RG_EE_FLOAT).

    eediv_cc.py CLANG ARGS... -o OBJ -c SRC         (CMake C/CXX_COMPILER_LAUNCHER)

1. the same command with `-ffp-contract=off -S -emit-llvm -Xclang -disable-llvm-passes
   -o OBJ.ll` (dependency flags stay; IR before any optimisation, so the VU0 helpers of
   include/port/vu0.h are still separate functions);
2. text rewrite of the IR: `fadd` / `fsub` / `fdiv` on float (scalar and vector lanes) ->
   calls to rg_ee_addf / rg_ee_subf / rg_ee_divf (tools/parity/eediv/rg_ee_ops.cpp), except
   inside functions matching EXCLUDE (VU0 macro-op models: the VU, not the EE FPU);
3. `llvm-link` with the helpers' IR (linkonce_odr, always_inline; built once per build dir);
4. `CLANG --target.. -O2 -c` of the linked module (the full optimisation pipeline, which
   inlines the helpers).
The result runs under the game's MXCSR (round toward zero + FTZ + DAZ with RG_EE_FPU=chop);
with round to nearest the helpers are plain IEEE operations.
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
FOPS = {"fdiv": "rg_ee_divf", "fadd": "rg_ee_addf", "fsub": "rg_ee_subf"}
SCALAR = re.compile(r"^(\s*)(%[\w.\-]+) = (fdiv|fadd|fsub)(?: [a-z ]+?)? float (\S+), (\S+?)(, !.*)?$")
VECTOR = re.compile(r"^(\s*)(%[\w.\-]+) = (fdiv|fadd|fsub)(?: [a-z ]+?)? <(\d+) x float> (.+?), (<.+?>|%[\w.\-]+|zeroinitializer|poison|undef)(, !.*)?$")
DEFINE = re.compile(r"^define .*?@\"?([^\"(]+)\"?\(")
EXCLUDE = re.compile(r"^(rg_vu|rg_vu0|vu0_|rg_vf|rg_vi)")


def rewrite(ir: str, ops=("fadd", "fsub", "fdiv"), exclude=EXCLUDE) -> tuple[str, int]:
    out, n, tmp, used = [], 0, [0], set()
    fn = None

    def t():
        tmp[0] += 1
        return f"%eef.{tmp[0]}"
    for line in ir.splitlines():
        d = DEFINE.match(line)
        if d:
            fn = d.group(1)
        elif line.startswith("}"):
            fn = None
        if fn is not None and not exclude.match(fn) and " float" in line:
            m = SCALAR.match(line)
            if m and m.group(3) in ops:
                ind, dst, op, a, b, md = m.groups()
                out.append(f"{ind}{dst} = call float @{FOPS[op]}(float {a}, float {b})")
                used.add(op)
                n += 1
                continue
            m = VECTOR.match(line)
            if m and m.group(3) in ops:
                ind, dst, op, lanes, a, b, md = m.groups()
                lanes = int(lanes)
                ty = f"<{lanes} x float>"
                acc = "poison"
                for k in range(lanes):
                    ea, eb, q = t(), t(), t()
                    nv = dst if k == lanes - 1 else t()
                    out.append(f"{ind}{ea} = extractelement {ty} {a}, i32 {k}")
                    out.append(f"{ind}{eb} = extractelement {ty} {b}, i32 {k}")
                    out.append(f"{ind}{q} = call float @{FOPS[op]}(float {ea}, float {eb})")
                    out.append(f"{ind}{nv} = insertelement {ty} {acc}, float {q}, i32 {k}")
                    acc = nv
                used.add(op)
                n += 1
                continue
        out.append(line)
    for op in sorted(used):
        out.append(f"declare float @{FOPS[op]}(float, float)")
    return "\n".join(out) + "\n", n


def tool(clang, name):
    return os.path.join(os.path.dirname(clang), name + (".exe" if clang.lower().endswith(".exe") else ""))


def ops_module(clang, target, cache_dir):
    path = os.path.join(cache_dir, "rg_ee_ops.ll")
    src = os.path.join(HERE, "rg_ee_ops.cpp")
    if not os.path.exists(path) or os.path.getmtime(path) < os.path.getmtime(src):
        tmp = path + f".{os.getpid()}.tmp"
        r = subprocess.call([clang] + target + ["-m32", "-msse2", "-mfpmath=sse", "-O2", "-w", "-S", "-emit-llvm",
                                                src, "-o", tmp])
        if r:
            raise SystemExit("eediv_cc: rg_ee_ops.cpp failed")
        os.replace(tmp, path)
    return path


def main(argv):
    cmd = argv[1:]
    if "-c" not in cmd or "-o" not in cmd:
        return subprocess.call(cmd)
    clang = cmd[0]
    o = cmd.index("-o")
    obj = cmd[o + 1]
    ll, ll2, bc = obj + ".ll", obj + ".ee.ll", obj + ".ee.bc"
    first = cmd[:o] + ["-o", ll] + cmd[o + 2:]
    first = [x for x in first if x != "-c"] + ["-ffp-contract=off", "-S", "-emit-llvm", "-Xclang",
                                              "-disable-llvm-passes"]
    r = subprocess.call(first)
    if r:
        return r
    with open(ll, encoding="utf-8") as f:
        ir = f.read()
    ir2, n = rewrite(ir)
    target = [x for x in cmd if x.startswith("--target")]
    opt = [x for x in cmd if re.fullmatch(r"-O[0-3s]", x)][-1:] or ["-O2"]
    link_in = ll
    if n:
        with open(ll2, "w", encoding="utf-8") as f:
            f.write(ir2)
        cache = os.environ.get("EEDIV_CACHE") or os.path.dirname(os.path.abspath(obj))
        ops = ops_module(clang, target, cache)
        r = subprocess.call([tool(clang, "llvm-link"), ll2, ops, "-o", bc])
        if r:
            return r
        link_in = bc
    r = subprocess.call([clang] + target + ["-m32", "-msse2", "-mfpmath=sse", "-w", "-ffp-contract=off"] + opt +
                        ["-c", "-x", "ir", link_in, "-o", obj])
    if not os.environ.get("EEDIV_KEEP"):
        for p in (ll, ll2, bc):
            if os.path.exists(p):
                os.remove(p)
    return r


if __name__ == "__main__":
    sys.exit(main(sys.argv))
