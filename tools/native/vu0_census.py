#!/usr/bin/env python3
"""Census of the VU0 register model in the compiled game (docs/NATIVE-CPU.md).

    python tools/native/vu0_census.py static [--out census/native_vu0_static.tsv]
                                             [--fn census/native_vu0_livein.tsv]
                                             [--jobs 4] [--only SUBSTR]

Finds every compiled source (game/ MANIFEST unit/data with overrides/ in place,
missing/ stand-ins, the libvu0 provider src/sce/vu0/libvu0.c) that touches the
VU0 model: the `vu0bind` bound registers (RG_VU0_BIND_VF/ACC/Q + the mwcc
intrinsics _vmul...), the `vu0asm` calls (rg_vu0_*), the libvu0.h /
vu0inline.h macros, `vcallms`, and the sceVu0* SDK calls.  Each such file is
run through `clang -E` with the game's include order, and the main-file text
of every function is reduced to a sequence of register events (read / write
with a lane mask) on vf0-31, ACC, Q, I, P, R, clip, vi1-15 and the EE GPR temps
(g<n>).

Per function it reports the LIVE-IN registers (lanes read before any write in
the function, textual order; vf0 excluded, it is a constant).  A live-in is the
only way a value can travel between functions through the VU0 register file,
so an empty live-in set for every function proves the global register file can
become function-local values.  Partial-lane cases are reported separately
(`lanein`: a lane kept by a masked write and then stored/read, i.e. a value that
on the EE is whatever the previous code left).

Approximation: textual order, not control flow.  `if (c) v = a; use(v);`
counts v as defined (a false negative is possible when the only write is
conditional), a read at the top of a loop body of a value written later in the
body counts as live-in (conservative).  `&reg` (address taken) is reported as
`addr`.  Verify dynamically (docs/NATIVE-CPU.md, RG_VU0 golden runs).

Outputs:
  --out  one row per file: path, kind (game/override/missing/provider), counts
         per form (bind_vf, bind_acc, bind_q, intrin, asmcall, libvu0, vu0inline,
         vcallms, scevu0) and the number of functions with a live-in.
  --fn   one row per function with VU events: file, function, regs written,
         live-in lanes, lanein lanes, addr-taken regs, callees (direct calls in
         the body), the first live-in statement.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
from syntaxcheck import C_FLAGS, CXX_FLAGS, D2, LLVM, msvc_env  # noqa: E402

TOKENS = re.compile(r"RG_VU0_BIND|rg_vu0|\b_v[a-z0-9]+\s*\(|\bVu0[A-Z]\w*|vcallms|"
                    r"sceVu0\w+|vu0inline\.h|libvu0\.h")

# --------------------------------------------------------------- compile set


def compile_set() -> list[tuple[str, Path]]:
    rows = [ln.split("\t") for ln in
            (PORT / "game" / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    provided = set()
    pp = PORT / "overrides" / "PORT_PROVIDED.tsv"
    for ln in pp.read_text(encoding="utf-8").splitlines():
        if ln.strip() and not ln.startswith("#"):
            provided.add(ln.split("\t")[0])
    out = []
    for r in rows:
        rel, kind = r[0], r[3]
        ovr = PORT / "overrides" / rel
        if kind == "excluded" and ovr.is_file():
            kind = "unit"
        if kind not in ("unit", "data") or not rel.endswith((".c", ".cpp")) or rel in provided:
            continue
        out.append(("override", ovr) if ovr.is_file() else ("game", PORT / "game" / rel))
    miss = PORT / "missing"
    for f in sorted(miss.rglob("*")):
        if f.suffix in (".c", ".cpp"):
            out.append(("missing", f))
    out.append(("provider", PORT / "src" / "sce" / "vu0" / "libvu0.c"))
    return out


# ------------------------------------------------------------ preprocessing


def preprocess(path: Path, env: dict) -> str:
    cxx = path.suffix == ".cpp"
    exe = str(LLVM / "bin" / ("clang++.exe" if cxx else "clang.exe"))
    std = ["-std=gnu++17", *CXX_FLAGS] if cxx else ["-std=gnu99", *C_FLAGS]
    cmd = [exe, "-E", "-w", *D2, *std, "-include", "port/prelude.h",
           "-I", str(PORT / "include"), "-I", str(PORT / "game" / "include"),
           "-I", str(PORT / "src" / "sce" / "vu0"), str(path)]
    r = subprocess.run(cmd, capture_output=True, text=True, env=env,
                       encoding="utf-8", errors="replace", cwd=str(PORT / "game"))
    # keep only text that belongs to the main file
    main = path.name
    keep, cur = [], True
    for ln in r.stdout.splitlines():
        m = re.match(r'#\s*(?:line\s+)?\d+\s+"([^"]*)"', ln)
        if m:
            cur = m.group(1).replace("\\\\", "/").replace("\\", "/").endswith(main)
            continue
        if cur:
            keep.append(ln)
    return "\n".join(keep)


# ------------------------------------------------------------------- events

FULL = 15
MASKS = {"RG_X": 1, "RG_Y": 2, "RG_Z": 4, "RG_W": 8, "RG_XY": 3, "RG_XZ": 5, "RG_YZ": 6,
         "RG_XYZ": 7, "RG_XW": 9, "RG_YW": 10, "RG_XYW": 11, "RG_ZW": 12, "RG_XZW": 13,
         "RG_YZW": 14, "RG_XYZW": 15}
BCS = {"RG_BC_NONE": -1, "RG_BC_X": 0, "RG_BC_Y": 1, "RG_BC_Z": 2, "RG_BC_W": 3}
OPS = ["RG_VADD", "RG_VSUB", "RG_VMUL", "RG_VMAX", "RG_VMINI", "RG_VMADD", "RG_VMSUB",
       "RG_VADDA", "RG_VSUBA", "RG_VMULA", "RG_VMADDA", "RG_VMSUBA"]
CTL = {18: "clip", 20: "r", 21: "i", 22: "q", 23: "p"}


def ival(s: str):
    s = s.strip()
    while s.startswith("(") and s.endswith(")"):
        s = s[1:-1].strip()
    if s in MASKS:
        return MASKS[s]
    if s in BCS:
        return BCS[s]
    if s in ("RG_FT_Q",):
        return 32
    if s in ("RG_FT_I",):
        return 33
    if s in OPS:
        return OPS.index(s)
    try:
        return int(s, 0)
    except ValueError:
        return None


def split_args(text: str, i: int) -> tuple[list[tuple[int, int]], int]:
    """text[i] == '(' -> list of (start, end) arg spans, index after ')'."""
    depth, start, spans = 0, i + 1, []
    j = i
    while j < len(text):
        c = text[j]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
            if depth == 0:
                if text[start:j].strip():
                    spans.append((start, j))
                return spans, j + 1
        elif c == "," and depth == 1:
            spans.append((start, j))
            start = j + 1
        j += 1
    return spans, j


def lane(bc: int | None) -> int:
    return FULL if bc is None or bc < 0 else 1 << bc


def mw_lane(f: int | None) -> int:
    """mwcc field selector 8=x 4=y 2=z 1=w -> lane mask"""
    return {8: 1, 4: 2, 2: 4, 1: 8}.get(f or 0, FULL)


def mw_mask(m: int | None) -> int:
    if m is None:
        return FULL
    return ((m >> 3) & 1) | ((m >> 1) & 2) | ((m << 1) & 4) | ((m << 3) & 8)


REF = re.compile(r"rg_vu0\s*\.\s*(vf)\s*\[\s*(\d+)\s*\]|rg_vu0\s*\.\s*(acc|q|i|p|r|clip)\b")


def ref_reg(text: str) -> str | None:
    m = REF.search(text)
    if not m:
        return None
    return f"vf{m.group(2)}" if m.group(1) else m.group(3)


def asm_call(name: str, a: list[str]):
    """rg_vu0_* call -> (reads, writes) lists of (reg, lanes)"""
    R, W = [], []
    v = [ival(x) for x in a]

    def vf(n):
        return f"vf{n}" if n is not None else "vf?"
    if name == "fmac":
        op, m, fd, fs, ft, bc = (v + [None] * 6)[:6]
        m = FULL if m is None else m
        if op == 1 and fs == ft and bc in (None, -1):
            W.append((vf(fd), m))      # vsub d, a, a: the zero idiom reads nothing
            return R, W
        if fs is not None:
            R.append((vf(fs), m))
        if ft in (32, 33):
            R.append(("q" if ft == 32 else "i", 1))
        else:
            R.append((vf(ft), m if bc in (None, -1) else lane(bc)))
        if op is not None and op in (5, 6, 10, 11):
            R.append(("acc", m))
        if op is not None and op >= 7:
            W.append(("acc", m))
        else:
            W.append((vf(fd), m))
    elif name == "opmula":
        R += [(vf(v[0]), 7), (vf(v[1]), 7)]
        W.append(("acc", 7))
    elif name == "opmsub":
        R += [("acc", 7), (vf(v[1]), 7), (vf(v[2]), 7)]
        W.append((vf(v[0]), 7))   # w lane: the model writes 0 then masks xyz
    elif name in ("abs", "move", "mr32"):
        m, ft, fs = v[:3]
        rl = m if name != "mr32" else FULL
        R.append((vf(fs), rl if rl is not None else FULL))
        W.append((vf(ft), m if m is not None else FULL))
    elif name in ("ftoi", "itof"):
        n, m, ft, fs = v[:4]
        R.append((vf(fs), m or FULL))
        W.append((vf(ft), m or FULL))
    elif name == "clip":
        R += [(vf(v[0]), 7), (vf(v[1]), 8), ("clip", 1)]
        W.append(("clip", 1))
    elif name in ("div", "rsqrt"):
        R += [(vf(v[0]), lane(v[1])), (vf(v[2]), lane(v[3]))]
        W.append(("q", 1))
    elif name == "sqrt":
        R.append((vf(v[0]), lane(v[1])))
        W.append(("q", 1))
    elif name == "lqc2":
        W.append((vf(v[0]), FULL))
    elif name == "sqc2":
        R.append((vf(v[0]), FULL))
    elif name in ("gpr_w64", "mfc1", "gpr_setp"):
        W.append((f"g{v[0]}", 3))
    elif name in ("gpr_r32", "mtc1", "gptr"):
        R.append((f"g{v[0]}", 1))
    elif name == "qmtc2":
        R.append((f"g{v[0]}", FULL))
        W.append((vf(v[1]), FULL))
    elif name == "qmfc2":
        R.append((vf(v[1]), FULL))
        W.append((f"g{v[0]}", FULL))
    elif name == "lq":
        W.append((f"g{v[0]}", FULL))
    elif name == "sq":
        R.append((f"g{v[0]}", FULL))
    elif name in ("cfc2", "ctc2"):
        rt, cid = v[:2]
        reg = CTL.get(cid, f"vi{cid}") if cid is not None else "ctl?"
        if name == "cfc2":
            R.append((reg, 1))
            W.append((f"g{rt}", 3))
        else:
            R.append((f"g{rt}", 1))
            W.append((reg, 1))
    elif name == "getf":
        R.append((vf(v[0]), lane(v[1])))
    elif name == "getq":
        R.append(("q", 1))
    elif name == "vcallms":
        # the SRT program at 0: reads vf1-3, writes vf4-7 (docs/NATIVE-CPU.md)
        R += [("vf1", 7), ("vf2", 7), ("vf3", FULL)]
        W += [(f"vf{k}", FULL) for k in range(4, 8)]
    elif name in ("setvf", "scalar", "ctl_read", "ctl_write", "waitq", "micro_bind",
                  "micro_bound"):
        pass
    return R, W


def vbi_call(name: str, args: list[str]):
    """rg_vbi_* (mwcc intrinsic) -> reads (reg, lanes); the destination arg
    is read only for lanes outside the mask."""
    regs = [ref_reg(x) for x in args]
    v = [ival(x) for x in args]
    R = []
    if name in ("vdiv", "vrsqrt"):
        R += [(regs[1], mw_lane(v[2])), (regs[3], mw_lane(v[4]))]
    elif name == "vsqrt":
        R.append((regs[1], mw_lane(v[2])))
    elif name in ("vwaitq", "vnop"):
        pass
    elif name in ("vopmsub", "vopmula"):
        if regs[0]:
            R.append(("=partial", (regs[0], 7)))   # w is kept
        R += [(r, 7) for r in regs[1:]]
    else:
        m = mw_mask(v[1]) if len(v) > 1 else FULL
        if m != FULL and regs[0]:
            R.append(("=partial", (regs[0], m)))
        rest = regs[2:]
        if name == "vsub" and len(rest) == 2 and rest[0] == rest[1]:
            rest = []                  # zero idiom
        bc = None
        if name.endswith("bc") and len(v) >= 1:
            bc = v[-1]
            rest = regs[2:-1]
        if name in ("vmadd", "vmsub", "vmaddbc", "vmsubbc"):
            R.append((rest[0], m))       # explicit ACC operand
            rest = rest[1:]
        for k, r in enumerate(rest):
            if bc is not None and k == len(rest) - 1:
                R.append((r, mw_lane(bc)))
            else:
                R.append((r, m))
    return [(r, l) for r, l in R if r]


CALL = re.compile(r"\b(rg_vu0s?_|rg_vbi_)(\w+)\s*\(|\b([A-Za-z_]\w*)\s*\(")
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case"}


def func_events(body: str):
    """-> list of statements, each a (reads, writes, addr, text) tuple"""
    stmts = []
    callees = set()
    # statement boundaries
    pieces, depth, start = [], 0, 0
    for k, c in enumerate(body):
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif depth == 0 and c in ";{}":
            pieces.append(body[start:k])
            start = k + 1
    pieces.append(body[start:])
    have_vu = False
    for st in pieces:
        if "rg_vu0" not in st and "rg_vbi" not in st:
            sc = [m.group(3) for m in CALL.finditer(st)
                  if m.group(3) and m.group(3) not in KEYWORDS]
            callees.update(sc)
            if sc:
                stmts.append(([], [], [], " ".join(st.split())[:160], sc))
            continue
        have_vu = True
        sc = []
        R, W, A = [], [], []
        consumed = []
        dest_partial: dict[str, int] = {}
        for m in CALL.finditer(st):
            if m.group(3):
                if m.group(3) not in KEYWORDS:
                    callees.add(m.group(3))
                    sc.append(m.group(3))
                continue
            spans, end = split_args(st, m.end() - 1)
            args = [st[a:b] for a, b in spans]
            if m.group(1) == "rg_vu0s_":
                args = args[1:]   # port/vu0.h call-site form: rg_vu0s_op(&state, ...)
            if m.group(1) in ("rg_vu0_", "rg_vu0s_"):
                r, w = asm_call(m.group(2), args)
                R += r
                W += w
                consumed.append((m.start(), end))
            else:
                for r, l in vbi_call(m.group(2), args):
                    if r == "=partial":
                        dest_partial[l[0]] = l[1]
                    else:
                        R.append((r, l))
                consumed.append((m.start(), end))
        for m in REF.finditer(st):
            if any(a <= m.start() < b for a, b in consumed):
                continue
            reg = f"vf{m.group(2)}" if m.group(1) else m.group(3)
            pre = st[max(0, m.start() - 40):m.start()]
            post = st[m.end():]
            # (*(T *)(void *)&rg_vu0.vf[n]) -> skip to the closing paren
            pm = re.match(r"\s*\]?[\s)]*(.)(.)?", post)
            amp_in_bind = re.search(r"\(\s*\*\s*\([^()]*\)\s*\(\s*void\s*\*\s*\)\s*&\s*$", pre)
            if not amp_in_bind and re.search(r"&\s*$", pre):
                A.append(reg)
                continue
            if amp_in_bind:
                pre2 = pre[:amp_in_bind.start()]
                if re.search(r"&\s*\(*\s*$", pre2):
                    A.append(reg)
                    continue
            if pm and pm.group(1) == "=" and pm.group(2) != "=":
                W.append((reg, FULL if reg.startswith("vf") or reg == "acc" else 1))
            elif pm and pm.group(1) in "+-*/|&^" and pm.group(2) == "=":
                R.append((reg, FULL))
                W.append((reg, FULL))
            else:
                R.append((reg, FULL if reg.startswith("vf") or reg == "acc" else 1))
        W = [(r, dest_partial.get(r, l)) for r, l in W]
        stmts.append((R, W, A, " ".join(st.split())[:160], sc))
    return (stmts if have_vu else []), callees


FUNC = re.compile(r"([A-Za-z_]\w*)\s*\(([^;{}()]|\([^;{}]*?\))*\)\s*(?:const\s*)?\{")


def functions(text: str):
    """top-level function bodies: (name, body)"""
    i, n = 0, len(text)
    depth = 0
    out = []
    while i < n:
        c = text[i]
        if c == "{" and depth == 0:
            # find the header before it
            head = text[max(0, i - 600):i + 1]
            m = None
            for m2 in FUNC.finditer(head):
                m = m2
            j, d = i, 0
            while j < n:
                if text[j] == "{":
                    d += 1
                elif text[j] == "}":
                    d -= 1
                    if d == 0:
                        break
                j += 1
            if m and m.end() == len(head) and m.group(1) not in KEYWORDS:
                out.append((m.group(1), text[i + 1:j]))
            elif m is None or m.end() != len(head):
                # namespace / extern "C" / struct: descend
                body = text[i + 1:j]
                if re.search(r'(extern\s*"C"|namespace\s*\w*)\s*$', text[max(0, i - 40):i]):
                    out += functions(body)
            i = j + 1
            continue
        i += 1
    return out


def lanes_str(d: dict) -> str:
    def ls(m):
        return "".join("xyzw"[k] for k in range(4) if m & (1 << k))
    return ",".join(f"{r}.{ls(m)}" if r.startswith(("vf", "acc", "g")) else r
                    for r, m in sorted(d.items()) if m)


def analyse(stmts, helpers=None):
    """helpers: same-file function name -> (livein, written): a call applies
    the helper's reads then its writes (intra-TU flows are not live-ins)"""
    helpers = helpers or {}
    defined: dict[str, int] = defaultdict(int)
    partial: dict[str, int] = defaultdict(int)   # lanes kept by a masked write
    livein: dict[str, int] = defaultdict(int)
    lanein: dict[str, int] = defaultdict(int)
    written: dict[str, int] = defaultdict(int)
    addr = set()
    first = ""
    for R, W, A, txt, sc in stmts:
        hr, hw = [], []
        for cal in sc:
            if cal in helpers:
                hr += list(helpers[cal][0].items())
                hw += list(helpers[cal][1].items())
        R = list(R) + hr
        W = list(W) + hw
        for reg, m in R:
            if reg == "vf0":
                continue
            if not reg.startswith(("vf", "acc", "g")):
                m = 1
            miss = m & ~defined[reg]
            if miss:
                kept = miss & partial[reg]
                if kept:
                    lanein[reg] |= kept
                if miss & ~kept:
                    livein[reg] |= miss & ~kept
                    first = first or txt
        for reg, m in W:
            if reg == "vf0":
                continue
            if not reg.startswith(("vf", "acc", "g")):
                m = 1
            if defined[reg] == 0 and m != FULL and reg.startswith(("vf", "acc", "g")):
                partial[reg] |= FULL & ~m
            defined[reg] |= m
            written[reg] |= m
        addr.update(A)
    return written, livein, lanein, addr, first


def scan_file(kind: str, path: Path, env: dict):
    src = path.read_text(encoding="utf-8", errors="replace")
    counts = Counter()
    counts["bind_vf"] = len(re.findall(r"RG_VU0_BIND_VF\s*\(", src))
    counts["bind_acc"] = len(re.findall(r"RG_VU0_BIND_ACC\s*\(", src))
    counts["bind_q"] = len(re.findall(r"RG_VU0_BIND_Q\s*\(", src))
    counts["intrin"] = len(re.findall(r"\b_v(add|sub|mul|max|mini|madd|msub|opm\w+|move|mr32|abs|"
                                      r"ftoi\d+|itof\d+|div|sqrt|rsqrt|waitq|nop)\w*\s*\(", src))
    counts["asmcall"] = len(re.findall(r"\brg_vu0_\w+\s*\(", src))
    counts["libvu0"] = len(re.findall(r"\bVu0[A-Z]\w*\s*\(", src))
    counts["vu0inline"] = int("vu0inline.h" in src)
    counts["vcallms"] = len(re.findall(r"rg_vu0_vcallms\s*\(", src))
    counts["scevu0"] = len(re.findall(r"\bsceVu0\w+\s*\(", src))
    fns = []
    if any(counts[k] for k in ("bind_vf", "bind_acc", "bind_q", "asmcall", "libvu0",
                               "vu0inline")) or kind == "provider":
        text = preprocess(path, env)
        evs = []
        for name, body in functions(text):
            stmts, callees = func_events(body)
            if stmts:
                evs.append((name, stmts, callees))
        helpers: dict = {}
        for _ in range(4):   # fixpoint over same-file helper calls
            nh = {}
            for name, stmts, callees in evs:
                written, livein, lanein, addr, first = analyse(stmts, helpers)
                nh[name] = (dict(livein), dict(written))
            if nh == helpers:
                break
            helpers = nh
        for name, stmts, callees in evs:
            written, livein, lanein, addr, first = analyse(stmts, helpers)
            fns.append((name, written, livein, lanein, addr, sorted(callees), first, stmts))
    return kind, path, counts, fns


def cmd_static(a) -> int:
    env = msvc_env()
    files = []
    for kind, p in compile_set():
        if a.only and a.only not in p.as_posix():
            continue
        try:
            s = p.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if TOKENS.search(s):
            files.append((kind, p))
    print(f"vu0_census: {len(files)} candidate files", file=sys.stderr)
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda f: scan_file(f[0], f[1], env), files))
    keys = ["bind_vf", "bind_acc", "bind_q", "intrin", "asmcall", "libvu0", "vu0inline",
            "vcallms", "scevu0"]
    tot = Counter()
    rows, frows = [], []
    nlive = nlane = nfn = ncross = 0
    live_regs = Counter()
    # function -> (file, regs written incl. VU callees, transitively)
    # (file, name) -> regs written; a callee resolves to the caller's own file
    # first (static helpers share names across files), else to the one other
    # definition (extern)
    wmap: dict[tuple[str, str], dict] = {}
    calls: dict[tuple[str, str], list[str]] = {}
    byname: dict[str, list[str]] = defaultdict(list)
    for kind, p, c, fns in res:
        for f in fns:
            key = (p.as_posix(), f[0])
            wmap.setdefault(key, dict(f[1]))
            calls.setdefault(key, f[5])
            byname[f[0]].append(p.as_posix())

    def resolve(fp: str, cal: str):
        fs = byname.get(cal, [])
        if fp in fs:
            return (fp, cal)
        return (fs[0], cal) if len(fs) == 1 else None
    for _ in range(6):   # transitive closure over the VU functions
        for key, w in wmap.items():
            for cal in calls.get(key, []):
                k2 = resolve(key[0], cal)
                if k2 and k2 != key:
                    for r, m in wmap[k2].items():
                        w[r] = w.get(r, 0) | m
    clob_rows = []
    for kind, p, c, fns in res:
        for f in fns:
            name, stmts = f[0], f[7]
            pend: dict[str, set] = defaultdict(set)   # reg -> cross-TU callees since its def
            for R, W, A, txt, sc in stmts:
                for reg, m in R:
                    for k2 in sorted(pend.get(reg, ())):
                        cw = wmap[k2].get(reg, 0)
                        if cw & (m if reg.startswith(("vf", "acc", "g")) else 1):
                            clob_rows.append([p.relative_to(PORT).as_posix(), name, reg, k2[1],
                                              Path(k2[0]).name, txt])
                for cal in sc:
                    k2 = resolve(p.as_posix(), cal)
                    if k2 and k2[0] != p.as_posix():
                        for reg in wmap[k2]:
                            pend[reg].add(k2)
                    elif k2:
                        for reg in wmap[k2]:
                            pend.pop(reg, None)
                for reg, m in W:
                    pend.pop(reg, None)
    for kind, p, c, fns in res:
        if not any(c.values()):
            continue
        rel = p.relative_to(PORT).as_posix()
        nl = sum(1 for f in fns if f[2])
        tot.update(c)
        tot["files_" + kind] += 1
        rows.append([rel, kind] + [str(c[k]) for k in keys] + [str(len(fns)), str(nl)])
        local_called = {cal for f in fns for cal in f[5] if cal != f[0]}
        mctx = re.search(r"#define\s+RG_VU0_CTX_NAME\s+(\w+)", p.read_text(encoding="utf-8", errors="replace"))
        for name, written, livein, lanein, addr, callees, first, _st in fns:
            nfn += 1
            if not livein:
                scope = ""
            elif "vf?" in written or any(r.endswith("?") for r in written):
                scope = "param-reg"      # writes a register named by a parameter
            elif name in local_called:
                scope = "tu-helper"      # supplied by its callers in the same file
            elif mctx:
                scope = "ctx:" + mctx.group(1)   # a named shared context (port/vu0_ctx.h)
            elif kind == "provider":
                scope = "provider"       # src/sce/vu0: static helper chains (reviewed)
            else:
                scope = "cross"
                ncross += 1
            nlive += bool(livein)
            nlane += bool(lanein)
            for r in livein:
                live_regs[r] += 1
            frows.append([rel, name, scope, lanes_str(written), lanes_str(livein), lanes_str(lanein),
                          ",".join(sorted(addr)), ",".join(callees)[:300], first])
    a.out.parent.mkdir(parents=True, exist_ok=True)
    with a.out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("\t".join(["path", "kind"] + keys + ["vu_functions", "livein_functions"]) + "\n")
        for r in sorted(rows):
            f.write("\t".join(r) + "\n")
    with a.fn.open("w", encoding="utf-8", newline="\n") as f:
        f.write("path\tfunction\tscope\twritten\tlivein\tlanein\taddr\tcallees\tfirst_livein_stmt\n")
        for r in sorted(frows):
            f.write("\t".join(r) + "\n")
    print("files: " + ", ".join(f"{k[6:]}={v}" for k, v in sorted(tot.items()) if k.startswith("files_")))
    print("sites: " + ", ".join(f"{k}={tot[k]}" for k in keys))
    print(f"functions with VU events: {nfn}; with live-in: {nlive} (cross-function, not a same-file helper: {ncross}); with kept-lane reads: {nlane}")
    clob = a.fn.with_name(a.fn.stem.replace("livein", "clobber") + ".tsv")
    with clob.open("w", encoding="utf-8", newline="\n") as f:
        f.write("path\tfunction\treg\tcallee\tcallee_file\tread_stmt\n")
        for r in sorted(set(map(tuple, clob_rows))):
            f.write("\t".join(r) + "\n")
    print(f"reads after a cross-TU callee that writes the register: {len(set(map(tuple, clob_rows)))} (-> {clob})")
    print("live-in registers (functions): " + ", ".join(f"{r}={n}" for r, n in live_regs.most_common()))
    print(f"wrote {a.out} and {a.fn}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("static")
    s.add_argument("--out", type=Path, default=PORT / "census" / "native_vu0_static.tsv")
    s.add_argument("--fn", type=Path, default=PORT / "census" / "native_vu0_livein.tsv")
    s.add_argument("--jobs", type=int, default=4)
    s.add_argument("--only", default="")
    a = ap.parse_args()
    return cmd_static(a)


if __name__ == "__main__":
    sys.exit(main())
