#!/usr/bin/env python3
"""Ingest stage `vu0frame`: the VU0 register file as function locals
(docs/NATIVE-CPU.md section 4, docs/PROTOS.md "vu0frame").

The `vu0asm` / `vu0bind` output and the port's libvu0.h / vu0inline.h macros
name the VU0 register file `rg_vu0` at the use (`&rg_vu0`, `rg_vu0.vf[n]`).
port/vu0.h used to make that ONE per-file static under RG_VU0_LOCAL.  This
stage gives every function that touches the model its own register file:

  * `RG_VU0_FRAME;` is inserted right after the opening brace of every
    function body that names the model (rg_vu0*, RG_VU0_*, a vu0bind-bound
    name, an mwcc intrinsic `_v*(`, a libvu0.h / vu0inline.h `Vu0*` macro) or
    calls a frame helper (below).  Under RG_VU0_LOCAL it declares the local
    `rg_vu0_state rg_vu0` (vf0 = (0,0,0,1)), which shadows the file-scope
    fallback in port/vu0.h; under `model` it is a no-op (the global file).
  * FRAME HELPERS: a `static` function of the file that touches the model and
    is called by another function of the same file runs on its CALLER's
    register file (the census's `tu-helper` rows read what the caller left,
    `FrameCalc*` ScaleMul / InvScaleMul / StoreMatrix; and the caller may read
    what the helper left, census/vu0frame_callfed.tsv).  The stage adds a first
    parameter `rg_vu0_state *rg_vu0_p_`, passes `&rg_vu0` at every same-file
    call and brackets the body with
        #pragma push_macro("rg_vu0") / #define rg_vu0 (*rg_vu0_p_) / ... /
        #undef rg_vu0 / #pragma pop_macro("rg_vu0")
    so the body's own spellings name the caller's file.  A helper whose name
    is used other than as a direct call (address taken) is NOT converted: it
    gets its own frame and an `info-helper-addr` row (review item).

Non-static same-file callees get their own frame; the census proves no caller
reads what such a callee left (`tools/stages/vu0frame_census.py`: callfed rows
name only static helpers in game/).  A function that names the model but gets
no frame would silently use the file-scope fallback: `--strict-check` in
tools/ubaudit (RG_VU0_STRICT, port/vu0.h) compiles game/ without the fallback.

    python tools/stages/vu0frame.py --one IN OUT      # the stage on one file
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "census"))
import snapshot as S  # noqa: E402  (read-only reuse: strip_comments, find_funcs)

HINT = re.compile(r"rg_vu0|RG_VU0_|\b_v[a-z][a-z0-9]*\s*\(|\bVu0[A-Z]\w*")
MODEL = r"\brg_vu0\w*|\bRG_VU0_\w+|\b_v[a-z][a-z0-9]*\s*\(|\bVu0[A-Z]\w*"
BOUND = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)[ \t]+RG_VU0_BIND_", re.M)
_PP = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
FRAME = " RG_VU0_FRAME;"
# KEPT-LANE functions (tools/stages/vu0frame_census.py `lanein` rows): they read
# or store lanes a masked write keeps (the upper words of an mfc1+qmtc2 GPR temp,
# MtxInverseAffine's vf9.w), i.e. whatever the previous code left.  A function
# listed here gets a `static` frame (persists across calls, the per-file
# behaviour for a one-function file).  EMPTY: the A/B check (frames on vs
# RG_VU0_NO_FRAMES, docs/UB-AUDIT.md "vu0frame") shows the kept lanes are not
# observable with plain locals.  The 22 functions the census lists:
#   InterVector_155bf0/1559e0/154a10/155180, DynClothSolveSpring_16a480,
#   VecScalePoint_1cbc60, VecSolveDistanceConstraint_364740, MatFromPosScale_1cb2b0,
#   MtxInverseAffine_1cb640, ClothSolveDistance_185450, VecDivScalarPoint_1cbbc0,
#   VecDivScalar_1cbbf0, VecLength_13d4a0, VecLerpDir_1cbaf0, VecLerpPoint_1cbac0,
#   VecLerp_1cbb20, VecLinearCombine_1cb8b0, VecScaleDir_1cbc80,
#   VecScaleToLength_1cb510, VecScale_13be00, VecScale_1cbca0, VecWeightedSum3_1cb860
KEEP_FUNCS: set = set()
FRAME_KEEP = ("\n#if RG_VU0_IS_LOCAL && !defined(RG_VU0_NO_FRAMES)\n"
              "static rg_vu0_state rg_vu0 = RG_VU0_RESET_INIT; /* rg:vu0frame keep */\n"
              "#endif\n")
H_OPEN = '\n#pragma push_macro("rg_vu0")\n#define rg_vu0 (*rg_vu0_p_)\n'
H_CLOSE = '\n#undef rg_vu0\n#pragma pop_macro("rg_vu0")\n'
H_PARAM = "rg_vu0_state *rg_vu0_p_"
DECL_HEAD = re.compile(r"\s*(?:extern\s+|static\s+|inline\s+)*(?:const\s+)?"
                       r"(?:void|int|char|short|long|float|double|unsigned|signed|f32|f64|"
                       r"[su](?:8|16|32|64)|struct\s+\w+|union\s+\w+)\s*\**\s*")


def _blank(s: str) -> str:
    return re.sub(r"[^\n]", " ", s)


def _blank_if0(code: str) -> str:
    out, stack, dead = [], [], False
    for ln in code.split("\n"):
        m = re.match(r"\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)", ln)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ("if", "ifdef", "ifndef"):
                stack.append((dead, d == "if" and rest == "0"))
                if d == "if" and rest == "0":
                    dead = True
            elif d in ("else", "elif") and stack and stack[-1][1]:
                dead = stack[-1][0]
            elif d == "endif" and stack:
                dead = stack.pop()[0]
            out.append(ln)
            continue
        out.append(_blank(ln) if dead else ln)
    return "\n".join(out)


def _match_paren_back(s: str, i: int) -> int:
    d = 0
    for j in range(i, -1, -1):
        if s[j] == ")":
            d += 1
        elif s[j] == "(":
            d -= 1
            if d == 0:
                return j
    return -1


def _match_paren(s: str, i: int) -> int:
    d = 0
    for j in range(i, len(s)):
        if s[j] == "(":
            d += 1
        elif s[j] == ")":
            d -= 1
            if d == 0:
                return j
    return -1


class Vu0FrameStage:
    def __init__(self):
        self.errors: list = []
        self.rows: list = []           # (rel, function, rule, detail)
        self.nfiles = 0

    def report(self) -> str:
        from collections import Counter
        c = Counter(r[2] for r in self.rows)
        return "vu0frame: " + ", ".join(f"{k}={v}" for k, v in sorted(c.items())) + \
            f" in {self.nfiles} files"

    def extra_outputs(self) -> dict:
        body = "path\tfunction\trule\tdetail\n" + "".join(
            "\t".join(r) + "\n" for r in sorted(self.rows))
        return {"VU0FRAME.tsv": body.encode()}

    def apply(self, rel: str, data: bytes) -> tuple[bytes, int]:
        text = data.decode("latin-1")
        if not HINT.search(text) or "RG_VU0_FRAME" in text or "rg:vu0frame" in text:
            return data, 0
        _c, nostr = S.strip_comments(text)
        code = _PP.sub(lambda m: _blank(m.group(0)), _blank_if0(nostr))
        funcs = [f for f in S.find_funcs(code)
                 if f.kind in ("func", "member") and f.body_close > f.body_open >= 0
                 and not f.is_asm]
        if not funcs:
            return data, 0
        bound = BOUND.findall(text)
        model_rx = re.compile(MODEL + "".join(rf"|\b{re.escape(b)}\b" for b in bound))
        uses = {id(f): bool(model_rx.search(code, f.body_open, f.body_close)) for f in funcs}
        if not any(uses.values()):
            return data, 0

        # header pieces: name offset, param parens, static
        info = {}
        for f in funcs:
            hdr = code[f.start:f.body_open].rstrip()
            hdr2 = re.sub(r"(\s*(__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)|const))+\s*$", "", hdr)
            if not hdr2.endswith(")"):
                continue
            rp = f.start + len(hdr2) - 1
            lp = _match_paren_back(code, rp)
            m = re.search(r"([A-Za-z_]\w*)\s*$", code[f.start:lp]) if lp > 0 else None
            if not m:
                continue
            pre = code[f.start:f.start + m.start()]
            cut = max(pre.rfind(";"), pre.rfind("}"))
            pre = pre[cut + 1:] if cut >= 0 else pre
            info[id(f)] = (m.group(1), lp, rp, bool(re.search(r"\bstatic\b", pre)))

        names = {}
        for f in funcs:
            if id(f) in info:
                names.setdefault(info[id(f)][0], []).append(f)

        def calls_in(f, name):
            return [m for m in re.finditer(rf"(?<![\w.>:]){re.escape(name)}\s*\(", code[f.body_open:f.body_close])]

        # frame helpers
        helpers = {}
        for f in funcs:
            if id(f) not in info or not uses[id(f)]:
                continue
            name, lp, rp, static = info[id(f)]
            if not static or len(names.get(name, [])) != 1 or f.kind != "func":
                continue
            callers = [g for g in funcs if g is not f and calls_in(g, name)]
            if not callers:
                continue
            # every other mention must be a direct call or a declaration
            ok = True
            for m in re.finditer(rf"\b{re.escape(name)}\b", code):
                if f.start <= m.start() < f.body_open:
                    continue
                if re.match(r"\s*\(", code[m.end():]):
                    continue
                ok = False
                break
            if not ok:
                self.rows.append((rel, name, "info-helper-addr", "address taken: own frame"))
                continue
            helpers[name] = f
        # frames: functions that use the model or call a helper (fixpoint not
        # needed: a helper caller gets a frame, a helper never does)
        edits: list[tuple[int, int, str]] = []    # (start, end, replacement)
        n = 0
        for f in funcs:
            if id(f) not in info and not uses[id(f)]:
                continue
            name = info[id(f)][0] if id(f) in info else "<anon>"
            if name in helpers and helpers[name] is f:
                continue
            calls_h = [h for h in helpers if calls_in(f, h)]
            if uses[id(f)] or calls_h:
                keep = any(info[id(g)][0] in KEEP_FUNCS for g in funcs if id(g) in info)
                edits.append((f.body_open + 1, f.body_open + 1, FRAME_KEEP if keep else FRAME))
                self.rows.append((rel, name, "frame-keep" if keep else "frame", ",".join(calls_h)))
                n += 1
        for name, f in helpers.items():
            _nm, lp, rp, _st = info[id(f)]
            params = code[lp + 1:rp].strip()
            if params in ("", "void"):
                edits.append((lp + 1, rp, H_PARAM))
            else:
                edits.append((lp + 1, lp + 1, H_PARAM + ", "))
            edits.append((f.body_open + 1, f.body_open + 1, H_OPEN))
            edits.append((f.body_close, f.body_close, H_CLOSE))
            self.rows.append((rel, name, "helper", ""))
            n += 1
            # forward declarations `... name(params);` outside bodies
            for m in re.finditer(rf"(?<![\w.>:]){re.escape(name)}\s*\(", code):
                if any(g.body_open <= m.start() <= g.body_close for g in funcs):
                    continue
                if f.start <= m.start() < f.body_open:
                    continue
                o = m.end() - 1
                c = _match_paren(code, o)
                if c < 0 or not re.match(r"\s*;", code[c + 1:]):
                    continue
                inner = code[o + 1:c].strip()
                if inner in ("", "void"):
                    edits.append((o + 1, c, H_PARAM))
                else:
                    edits.append((o + 1, o + 1, H_PARAM + ", "))
                self.rows.append((rel, name, "helper-decl", ""))
            # calls (any function body, the helper's own for recursion); a
            # block-scope declaration `void ScaleMul(void);` gets the parameter
            for g in funcs:
                for m in calls_in(g, name):
                    st = g.body_open + m.start()
                    o = g.body_open + m.end() - 1
                    c = _match_paren(code, o)
                    inner = code[o + 1:c].strip() if c > 0 else "x"
                    # the statement so far is only a return type: a declaration
                    head = re.split(r"[;{}]", code[max(0, st - 200):st])[-1]
                    if DECL_HEAD.fullmatch(head) and c > 0 and re.match(r"\s*;", code[c + 1:]):
                        edits.append((o + 1, c, H_PARAM) if inner in ("", "void") else
                                     (o + 1, o + 1, H_PARAM + ", "))
                        self.rows.append((rel, name, "helper-decl", info[id(g)][0] if id(g) in info else ""))
                        continue
                    edits.append((o + 1, o + 1, "&rg_vu0" if inner == "" else "&rg_vu0, "))
                    self.rows.append((rel, name, "helper-call", info[id(g)][0] if id(g) in info else ""))
        if not edits:
            return data, 0
        # apply back to front; equal starts keep their list order
        order = sorted(range(len(edits)), key=lambda k: (edits[k][0], k), reverse=True)
        out = text
        for k in order:
            a, b, s = edits[k]
            out = out[:a] + s + out[b:]
        self.nfiles += 1
        return out.encode("latin-1"), n


def main() -> int:
    import argparse
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--one", nargs=2, metavar=("IN", "OUT"), required=True)
    a = ap.parse_args()
    st = Vu0FrameStage()
    src = Path(a.one[0])
    data, n = st.apply(src.name, src.read_bytes())
    Path(a.one[1]).write_bytes(data)
    for r in st.rows:
        print("\t".join(r))
    print(f"{n} edits")
    return 0


if __name__ == "__main__":
    sys.exit(main())
