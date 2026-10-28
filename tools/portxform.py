#!/usr/bin/env python3
"""Ingest transform stages for the clang/i686 port (PLAN.md transforms 4 and 6,
the u128 hazard, and the gcc-island varargs).  Imported by tools/ingest.py.

Stages, in the order ingest runs them (each is pure and idempotent):

  int128      `unsigned __int128` / `__int128` -> rg_u128 / rg_s128
              (unsigned/signed _BitInt(128), aligned(16): include/port/u128.h,
              force-included through include/port/prelude.h)
  gccvarargs  gcc 2.9 EE varargs idiom (typedef char *va_list,
              __builtin_next_arg/__builtin_args_info, 8-byte slot walking)
              -> <stdarg.h> va_start/va_arg
  vu0asm      mwcc `asm volatile { ... }` blocks and GNU `__asm__("...")`
              statements made only of VU0 macro-mode / qword-move
              instructions on C operands -> calls into the VU0 model
              (include/port/vu0.h)
  asmexclude  whole-asm functions (`asm T f(...) {...}`) and C functions
              whose remaining asm cannot be translated are cut out: the
              definition becomes a prototype, the symbol goes to
              game/EXCLUDED.tsv; a file left with no C definition is
              excluded from compilation (MANIFEST kind `excluded`, body kept
              verbatim for reference)

Every stage works on a lexed view where comments and string contents are
blanked, so text inside comments is never rewritten.
"""
from __future__ import annotations

import re
from dataclasses import dataclass, field

# ======================================================================= lexing


_LEX1 = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|' + r"'(?:\\.|[^'\\\n])*'?", re.S)
_LEXM = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\])*"?|' + r"'(?:\\.|[^'\\\n])*'?", re.S)
_NONL = re.compile(r"[^\n]")


def _blank_tok(m: "re.Match") -> str:
    t = m.group(0)
    if t[0] == "/":
        return _NONL.sub(" ", t)
    q = t[0]
    closed = len(t) >= 2 and t[-1] == q
    inner = t[1:-1] if closed else t[1:]
    return q + _NONL.sub(" ", inner) + (q if closed else "")


def blank(text: str, multiline_strings: bool = False) -> str:
    """Comments -> spaces, string/char literal CONTENTS -> spaces.  Same
    length, newlines kept, so offsets map 1:1 onto the original text.
    A string ends at a raw newline unless multiline_strings (mwcc accepts
    raw newlines inside the GNU asm template strings)."""
    return (_LEXM if multiline_strings else _LEX1).sub(_blank_tok, text)


_PP = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)


def blank_pp(code: str) -> str:
    return _PP.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), code)


def match_close(s: str, open_i: int, o: str = "{", c: str = "}") -> int:
    depth = 0
    for k in range(open_i, len(s)):
        ch = s[k]
        if ch == o:
            depth += 1
        elif ch == c:
            depth -= 1
            if depth == 0:
                return k
    return len(s) - 1


def _match_paren_back(s: str, close: int) -> int:
    depth = 0
    for k in range(close, -1, -1):
        if s[k] == ")":
            depth += 1
        elif s[k] == "(":
            depth -= 1
            if depth == 0:
                return k
    return -1


@dataclass
class Func:
    name: str
    start: int            # header start (after previous top-level ; or })
    body_open: int
    body_close: int
    header: str
    is_asm: bool          # `asm T f(...)` whole-asm function
    in_class: bool = False


_NOT_FUNC = re.compile(r"(^|[^\w])(class|struct|union|enum|namespace)\b")
_ASM_KW = re.compile(r"(?:^|[\s;}])(?:asm|__asm)\s+(?!volatile\b|__volatile__\b)[A-Za-z_]")


def find_funcs(code: str) -> list[Func]:
    """Top-level function definitions (and C++ inline member bodies) in a
    blanked text.  `extern "C" {` / `namespace x {` are transparent."""
    s = blank_pp(code)
    res: list[Func] = []
    stack: list[tuple[str, Func | None]] = []
    last = 0
    for mm in re.finditer(r"[{};]", s):
        i = mm.start()
        ch = s[i]
        in_func = any(k in ("func", "init") for k, _ in stack)
        if ch == "{":
            if in_func:
                stack.append(("block", None))
                continue
            hdr = s[last:i]
            h = hdr.strip()
            if re.search(r'extern\s+"[^"]*"\s*$|\bnamespace\s+\w*\s*$', hdr):
                stack.append(("transparent", None))
                last = i + 1
                continue
            pre = h.split("(")[0]
            if "=" in pre or h.endswith("="):
                stack.append(("init", None))
            elif _NOT_FUNC.search(pre) and not h.endswith(")"):
                stack.append(("class", None))
                last = i + 1
            else:
                hh = re.sub(r"\s+(const|throw\s*\(\s*\))\s*$", "", h)
                ci = re.search(r"\)\s*:(?!:)", hh)
                if ci:
                    hh = hh[:ci.start() + 1]
                hh = re.sub(r"(\s*__attribute__\s*\(\(.*\)\))+\s*$", "", hh)
                name = "<anon>"
                if hh.endswith(")"):
                    o = _match_paren_back(hh, len(hh) - 1)
                    m = re.search(r"([\w:~]+)\s*$", hh[:o]) if o > 0 else None
                    if m:
                        name = m.group(1)
                is_asm = bool(re.match(r"(?:(?:static|inline|extern|__inline)\s+)*(?:asm|__asm)\b", h))
                f = Func(name, last, i, -1, hdr, is_asm,
                         any(k == "class" for k, _ in stack))
                res.append(f)
                stack.append(("func", f))
        elif ch == "}":
            if stack:
                k, f = stack.pop()
                if f is not None:
                    f.body_close = i
                if k in ("func", "class", "transparent", "init") and \
                        not any(kk in ("func", "init") for kk, _ in stack):
                    last = i + 1
            else:
                last = i + 1
        else:  # ;
            if not any(k in ("func", "init", "block") for k, _ in stack):
                last = i + 1
    for f in res:
        if f.body_close < 0:
            f.body_close = len(s) - 1
    return res


ASM_BLOCK = re.compile(r"\b(?:asm|__asm|__asm__)\s*(?:volatile\b|__volatile__\b)?\s*\{")
GNU_ASM = re.compile(r"\b(?:asm|__asm|__asm__)\s*(?:volatile\b|__volatile__\b)?\s*\(")


def asm_blocks(code: str, lo: int = 0, hi: int | None = None) -> list[tuple[int, int, int]]:
    """(start, brace_open, brace_close) of every `asm [volatile] {...}` block."""
    hi = len(code) if hi is None else hi
    out = []
    for m in ASM_BLOCK.finditer(code, lo, hi):
        o = m.end() - 1
        out.append((m.start(), o, match_close(code, o)))
    return out


# ============================================================== stage: int128

_I128 = re.compile(r"\b(?:(unsigned)\s+|signed\s+)?__int128\b|\b__(u)?int128_t\b")
_MODE_TI = re.compile(
    r"\btypedef\s+(unsigned\s+)?(?:signed\s+)?(?:int|long(?:\s+long)?)\s+(\w+)\s*"
    r"__attribute__\s*\(\(\s*(?:__)?mode(?:__)?\s*\(\s*(?:__)?TI(?:__)?\s*\)\s*\)\)\s*;")


def stage_int128(path: str, data: bytes) -> tuple[bytes, int]:
    """`unsigned __int128` / `__uint128_t` -> rg_u128; `[signed] __int128` /
    `__int128_t` -> rg_s128 (include/port/u128.h)."""
    text = data.decode("utf-8", "surrogateescape")
    if "int128" not in text and "TI" not in text:
        return data, 0
    code = blank(text)
    out, pos, sites = [], 0, 0
    hits = [(m.start(), m.end(), "rg_u128" if (m.group(1) or m.group(2)) else "rg_s128")
            for m in _I128.finditer(code)]
    # gcc spelling: typedef unsigned int u128 __attribute__((mode(TI)));
    hits += [(m.start(), m.end(),
              f"typedef {'rg_u128' if m.group(1) else 'rg_s128'} {m.group(2)};")
             for m in _MODE_TI.finditer(code)]
    for a, b, r in sorted(hits):
        if a < pos:
            continue
        out.append(text[pos:a])
        out.append(r)
        pos = b
        sites += 1
    out.append(text[pos:])
    return "".join(out).encode("utf-8", "surrogateescape"), sites


# ========================================================== stage: gccvarargs
# gcc 2.9 (Sony EE) varargs: every slot is 8 bytes and the code walks them by
# hand.  i686 cdecl slots are 4 bytes, so the walk itself is rewritten:
#   typedef char *va_list;                 -> #include <stdarg.h>
#   ap = (T)__builtin_next_arg(L) - (...); -> va_start(ap, L);
#   #define VS(ap,l) (ap = ... __builtin_next_arg(l) ...)  -> va_start(ap, l)
#   ap += 8; ... ((T *)ap)[-2] ...         -> ... va_arg(ap, T) ...
#   ap += 8; ... *(T *)(ap - 8) ...        -> ... va_arg(ap, T) ...
# (va_end is a no-op on i686 and is not added.)

_VA_TYPEDEF = re.compile(r"typedef\s+char\s*\*\s*va_list\s*;")
_VA_START = re.compile(
    r"(\w+)\s*=\s*\(\s*(?:char\s*\*|va_list)\s*\)\s*__builtin_next_arg\s*\(\s*(\w+)\s*\)\s*-\s*\(")
_VA_ADV = re.compile(r"(\w+)\s*\+=\s*8\s*;")


def stage_gccvarargs(path: str, data: bytes) -> tuple[bytes, int]:
    text = data.decode("utf-8", "surrogateescape")
    if "__builtin_next_arg" not in text:
        return data, 0
    sites = 0
    code = blank(text)
    edits: list[tuple[int, int, str]] = []
    for m in _VA_TYPEDEF.finditer(code):
        edits.append((m.start(), m.end(), "#include <stdarg.h>\n"))
        sites += 1
    for m in _VA_START.finditer(code):
        o = m.end() - 1
        c = match_close(code, o, "(", ")")
        end = c + 1
        tail = re.match(r"\s*\)?", code[end:])  # macro form: closing paren of (ap = ...)
        rep = f"va_start({m.group(1)}, {m.group(2)})"
        # macro body `(ap = ... )`: drop the opening paren we are inside of
        k = m.start() - 1
        while k >= 0 and code[k] in " \t":
            k -= 1
        if k >= 0 and code[k] == "(" and tail and tail.group(0).strip() == ")":
            edits.append((k, end + tail.end(), rep))
        else:
            edits.append((m.start(), end, rep))
        sites += 1
    for m in _VA_ADV.finditer(code):
        ap = m.group(1)
        rx = re.compile(r"\(\s*\(\s*([\w\s]+?\*?)\s*\*\s*\)\s*" + ap + r"\s*\)\s*\[\s*-\s*2\s*\]"
                        r"|\*\s*\(\s*([\w\s]+?)\s*\*\s*\)\s*\(\s*" + ap + r"\s*-\s*8\s*\)")
        u = rx.search(code, m.end())
        if not u:
            continue
        typ = (u.group(1) or u.group(2)).strip()
        edits.append((m.start(), m.end(), ""))
        edits.append((u.start(), u.end(), f"va_arg({ap}, {typ})"))
        sites += 1
    edits.sort()
    out, pos = [], 0
    for a, b, r in edits:
        if a < pos:
            continue
        out.append(text[pos:a])
        out.append(r)
        pos = b
    out.append(text[pos:])
    return "".join(out).encode("utf-8", "surrogateescape"), sites


# ============================================================== stage: vu0asm

GPR_NAMES = {n: i for i, n in enumerate(
    "zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
    "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra".split())}
GPR_NAMES["s8"] = 30
BC = {"x": "RG_BC_X", "y": "RG_BC_Y", "z": "RG_BC_Z", "w": "RG_BC_W"}
FMAC = re.compile(r"^v(add|sub|mul|max|mini|madd|msub)(a?)([xyzwqi]?)\.([xyzw]+)$")
NOPS = {"nop", "vnop", "vwaitq", "sync", "sync.l", "sync.p", "ssnop"}
C_KEYWORDS = {"if", "else", "while", "for", "return", "sizeof"}


class Untranslatable(Exception):
    pass


def _mask(m: str) -> str:
    if not m or not re.fullmatch(r"x?y?z?w?", m):
        raise Untranslatable(f"bad field mask .{m}")
    return "RG_" + m.upper()


def _bare(tok: str) -> str:
    return tok[1:] if tok.startswith("$") else tok


class VuXlat:
    """Translate the statements of one asm text into rg_vu0_* C calls.

    Operands: vfN[f] / ACC / Q / I / viN are VU registers; $N and the MIPS
    ABI names are EE GPRs, usable only as temps WRITTEN inside the block (a
    read of a GPR the block did not write would read a C argument through the
    MIPS calling convention -> Untranslatable); $fN (hardware FPRs) are
    Untranslatable; any other identifier is a C variable, as in mwcc asm."""

    def __init__(self, cvars: dict[str, str] | None = None):
        self.cvars = cvars or {}         # GNU operand placeholder -> C expression
        self.written: set[int] = set()   # GPRs written inside this block
        self.rets: set[int] = set()      # v0/v1 written

    # ---- operands
    def vf(self, tok: str) -> tuple[int, str | None]:
        m = re.fullmatch(r"\$?vf(\d+)([xyzw]?)", tok)
        if not m or int(m.group(1)) > 31:
            raise Untranslatable(f"expected vf register, got {tok!r}")
        return int(m.group(1)), (m.group(2) or None)

    def gpr(self, tok: str) -> int | None:
        m = re.fullmatch(r"\$(\d+)", tok)
        if m:
            return int(m.group(1))
        m = re.fullmatch(r"\$?([a-z]\w*)", tok)
        if m and m.group(1) in GPR_NAMES and m.group(1) not in self.cvars:
            return GPR_NAMES[m.group(1)]
        return None

    def cexpr(self, tok: str) -> str:
        if tok in self.cvars:
            return self.cvars[tok]
        if re.fullmatch(r"\$f\d+", tok):
            raise Untranslatable(f"hardware FPR {tok}")
        if not re.fullmatch(r"[A-Za-z_]\w*", tok) or tok in C_KEYWORDS:
            raise Untranslatable(f"operand {tok!r}")
        return f"({tok})"

    def rd_gpr(self, n: int) -> None:
        if n != 0 and n not in self.written:
            raise Untranslatable(f"reads live EE register ${n}")

    def wr_gpr(self, n: int) -> None:
        if n in (2, 3):
            self.rets.add(n)
        self.written.add(n)

    def addr(self, tok: str) -> str:
        m = re.fullmatch(r"(-?(?:0x[0-9a-fA-F]+|\d+))?\s*\(\s*([^()]+?)\s*\)", tok)
        if not m:
            raise Untranslatable(f"memory operand {tok!r}")
        off = m.group(1) or "0"
        base = m.group(2)
        g = self.gpr(base)
        if g is not None:
            self.rd_gpr(g)
            b = f"rg_vu0_gptr({g})"
        else:
            b = f"(char *){self.cexpr(base)}"
        return b if re.fullmatch(r"0(x0+)?", off) else f"{b} + {off}"

    # ---- one statement
    def stmt(self, s: str) -> str | None:
        s = s.strip()
        if not s:
            return None
        if re.match(r"^[\w$@.]+\s*:", s):
            raise Untranslatable("label (EE control flow)")
        if s.startswith("."):
            if re.match(r"\.set\s+(no)?(reorder|at|macro|volatile)\b", s):
                return None
            raise Untranslatable(f"directive {s.split()[0]}")
        parts = s.split(None, 1)
        mn = parts[0].lower()
        ops = [o.strip() for o in re.split(r",(?![^()]*\))", parts[1])] if len(parts) > 1 else []
        if mn in NOPS:
            return None
        try:
            return self._insn(mn, ops)
        except IndexError:
            raise Untranslatable(f"operand count: {s}")

    def _insn(self, mn: str, ops: list[str]) -> str:
        base = re.sub(r"\.(ni|i)$", "", mn)
        if base in ("lqc2", "sqc2"):
            n, _ = self.vf(ops[0])
            return f"rg_vu0_{base}({n}, {self.addr(ops[1])});"
        if base in ("lq", "sq"):
            g = self.gpr(ops[0])
            a = self.addr(ops[1])
            if g is None:
                v = self.cexpr(ops[0])
                if base == "lq":
                    return f"__builtin_memcpy(&{v}, {a}, 16);"
                return f"__builtin_memcpy({a}, &{v}, 16);"
            if base == "lq":
                self.wr_gpr(g)
                return f"rg_vu0_lq({g}, {a});"
            self.rd_gpr(g)
            return f"rg_vu0_sq({g}, {a});"
        if base in ("qmtc2", "qmfc2"):
            g = self.gpr(ops[0])
            n, _ = self.vf(ops[1])
            if g is None:
                raise Untranslatable(f"{base} with C operand {ops[0]}")
            if base == "qmtc2":
                self.rd_gpr(g)
                return f"rg_vu0_qmtc2({g}, {n});"
            self.wr_gpr(g)
            return f"rg_vu0_qmfc2({g}, {n});"
        if base in ("cfc2", "ctc2"):
            m = re.fullmatch(r"\$?vi(\d+)", ops[1])
            if not m:
                raise Untranslatable(f"{base} operand {ops[1]}")
            vi = int(m.group(1))
            g = self.gpr(ops[0])
            if base == "cfc2":
                if g is None:
                    return f"{self.cexpr(ops[0])} = (rg_vu_s32)rg_vu0_ctl_read({vi});"
                self.wr_gpr(g)
                return f"rg_vu0_cfc2({g}, {vi});"
            if g is None:
                return f"rg_vu0_ctl_write({vi}, (rg_vu_u32)({self.cexpr(ops[0])}));"
            self.rd_gpr(g)
            return f"rg_vu0_ctc2({g}, {vi});"
        if mn == "mfc1":
            g = self.gpr(ops[0])
            f = self.cexpr(ops[1])
            if g is None:
                return f"{self.cexpr(ops[0])} = (rg_vu_s32)rg_f2u({f});"
            self.wr_gpr(g)
            return f"rg_vu0_mfc1({g}, {f});"
        if mn == "mtc1":
            g = self.gpr(ops[0])
            f = self.cexpr(ops[1])
            if g is None:
                return f"{f} = rg_u2f((rg_vu_u32)({self.cexpr(ops[0])}));"
            self.rd_gpr(g)
            return f"{f} = rg_vu0_mtc1({g});"
        if mn in ("addiu", "daddiu", "addi", "daddi"):
            g = self.gpr(ops[0])
            if g is None:
                raise Untranslatable(f"{mn} into C operand")
            src = self.gpr(ops[1])
            imm = ops[2]
            if src is None:
                e = f"rg_vu0_gpr_setp({g}, (char *){self.cexpr(ops[1])} + {imm});"
            else:
                self.rd_gpr(src)
                e = (f"rg_vu0_gpr_w64({g}, (rg_vu_u64)(rg_vu_s64)(rg_vu_s32)"
                     f"(rg_vu0_gpr_r32({src}) + {imm}));")
            self.wr_gpr(g)
            return e
        if mn == "move" or (mn in ("daddu", "addu", "or") and _bare(ops[2]) in ("0", "zero")):
            g = self.gpr(ops[0])
            if g is None:
                raise Untranslatable(f"{mn} into C operand")
            src = self.gpr(ops[1])
            if src is None:
                e = f"rg_vu0_gpr_setp({g}, (char *){self.cexpr(ops[1])});"
            else:
                self.rd_gpr(src)
                e = f"__builtin_memcpy(rg_vu0.gpr[{g}], rg_vu0.gpr[{src}], 8);"
            self.wr_gpr(g)
            return e
        # ---- VU0 macro ops
        m = FMAC.match(mn)
        if m:
            op, acc, bcq, mask = m.groups()
            if acc and op in ("max", "mini"):
                raise Untranslatable(mn)
            opname = "RG_V" + op.upper() + ("A" if acc else "")
            if acc:
                if _bare(ops[0]).upper() != "ACC":
                    raise Untranslatable(f"{mn} dest {ops[0]}")
                fd = 0
            else:
                fd, _ = self.vf(ops[0])
            fs, _ = self.vf(ops[1])
            if bcq in ("q", "i"):
                if _bare(ops[2]).upper() != bcq.upper():
                    raise Untranslatable(f"{mn} third operand {ops[2]}")
                return f"rg_vu0_fmac({opname}, {_mask(mask)}, {fd}, {fs}, RG_FT_{bcq.upper()}, RG_BC_NONE);"
            ft, tbc = self.vf(ops[2])
            if bcq and tbc and tbc != bcq:
                raise Untranslatable(f"{mn} bc field mismatch {ops[2]}")
            if not bcq and tbc:
                raise Untranslatable(f"{mn} unexpected field on {ops[2]}")
            bc = BC[bcq] if bcq else "RG_BC_NONE"
            return f"rg_vu0_fmac({opname}, {_mask(mask)}, {fd}, {fs}, {ft}, {bc});"
        m = re.match(r"^vop(mula|msub)\.xyz$", mn)
        if m:
            fs, _ = self.vf(ops[1])
            ft, _ = self.vf(ops[2])
            if m.group(1) == "mula":
                if _bare(ops[0]).upper() != "ACC":
                    raise Untranslatable(f"{mn} dest {ops[0]}")
                return f"rg_vu0_opmula({fs}, {ft});"
            fd, _ = self.vf(ops[0])
            return f"rg_vu0_opmsub({fd}, {fs}, {ft});"
        m = re.match(r"^v(abs|move|mr32)\.([xyzw]+)$", mn)
        if m:
            ft, _ = self.vf(ops[0])
            fs, _ = self.vf(ops[1])
            return f"rg_vu0_{m.group(1)}({_mask(m.group(2))}, {ft}, {fs});"
        m = re.match(r"^v(ftoi|itof)(0|4|12|15)\.([xyzw]+)$", mn)
        if m:
            ft, _ = self.vf(ops[0])
            fs, _ = self.vf(ops[1])
            return f"rg_vu0_{m.group(1)}({m.group(2)}, {_mask(m.group(3))}, {ft}, {fs});"
        if re.match(r"^vclipw?\.xyz$", mn):
            fs, _ = self.vf(ops[0])
            ft, f = self.vf(ops[1])
            if f not in (None, "w"):
                raise Untranslatable(f"{mn} {ops[1]}")
            return f"rg_vu0_clip({fs}, {ft});"
        if mn in ("vdiv", "vrsqrt", "vsqrt"):
            if _bare(ops[0]).upper() != "Q":
                raise Untranslatable(f"{mn} dest {ops[0]}")
            regs = []
            for o in ops[1:]:
                n, f = self.vf(o)
                if not f:
                    raise Untranslatable(f"{mn} needs a field: {o}")
                regs += [str(n), BC[f]]
            if len(regs) != (2 if mn == "vsqrt" else 4):
                raise Untranslatable(f"{mn} operand count")
            fn = {"vdiv": "div", "vrsqrt": "rsqrt", "vsqrt": "sqrt"}[mn]
            return f"rg_vu0_{fn}({', '.join(regs)});"
        raise Untranslatable(f"instruction {mn}")

    def block(self, body: str) -> list[tuple[str, str]]:
        """[(C statements or '', original line)] for every source line."""
        res = []
        for line in body.split("\n"):
            outs = [c for c in (self.stmt(st) for st in line.split(";")) if c]
            res.append((" ".join(outs), line.strip()))
        return res


def _render(rows: list[tuple[str, str]]) -> str:
    out = []
    for c, orig in rows:
        o = orig.replace("*/", "* /")
        if c and o:
            out.append(f"{c} /* {o} */")
        elif c:
            out.append(c)
        elif o:
            out.append(f"/* {o} */")
        else:
            out.append("")
    return "\n".join(out)


def _ret_type(f: Func) -> str:
    h = re.sub(r"\s+", " ", f.header).strip()
    k = h.find(f.name + "(") if f.name + "(" in h else h.find(f.name)
    rt = h[:k] if k >= 0 else h
    return re.sub(r"\b(static|inline|extern|__inline|asm|__asm)\b", "", rt).strip()


def _needs_asm_return(f: Func, code: str) -> bool:
    """Non-void function with no C `return <value>` -- the asm supplies v0/f0."""
    if _ret_type(f) in ("void", ""):
        return False
    return not re.search(r"\breturn\b\s*[^;\s]", code[f.body_open:f.body_close + 1])


def translate(body_code: str, cvars: dict[str, str] | None = None
              ) -> tuple[list[tuple[str, str]], set[int]]:
    x = VuXlat(cvars)
    rows = x.block(body_code)
    return rows, x.rets


def gnu_asm_parts(raw: str, open_paren: int) -> tuple[int, str, list, list]:
    """Parse `asm(...)` from its '(' (string pieces may hold raw newlines, as
    in AnimKeyBlendMaterial_1559e0.c).  Returns (close_index, template,
    outputs, inputs); operands are (constraint, expr)."""
    code = blank(raw[open_paren:], multiline_strings=True)
    close = match_close(code, 0, "(", ")")
    inner_raw = raw[open_paren + 1:open_paren + close]
    inner = code[1:close]
    secs, depth, start = [], 0, 0
    for k, ch in enumerate(inner):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == ":" and depth == 0:
            secs.append((start, k))
            start = k + 1
    secs.append((start, len(inner)))
    tmpl = "".join(re.findall(r'"((?:[^"\\]|\\.)*)"', inner_raw[secs[0][0]:secs[0][1]], re.S))
    tmpl = tmpl.replace("\\n", "\n").replace("\\t", " ")

    def operands(i: int) -> list:
        if i >= len(secs):
            return []
        a, b = secs[i]
        return [(c, e.strip()) for c, e in
                re.findall(r'"([^"]*)"\s*\(((?:[^()]|\([^()]*\))*)\)', inner_raw[a:b])]
    return open_paren + close, tmpl, operands(1), operands(2)


def gnu_template_to_block(tmpl: str, ops: list) -> tuple[str, dict[str, str]]:
    """Substitute %N operands with placeholders the translator resolves."""
    cvars: dict[str, str] = {}
    t = tmpl
    for idx in range(len(ops) - 1, -1, -1):
        con, ex = ops[idx]
        ph = f"RGOP{idx}"
        if "m" in con:
            cvars[ph] = f"&({ex})"
            t = re.sub(rf"(?<![\w(])%{idx}(?!\d)", f"0({ph})", t)
        else:
            cvars[ph] = f"({ex})"
            t = re.sub(rf"%{idx}(?!\d)", ph, t)
    # `0(&(x))` would cast `(char *)&(x)`: cexpr already yields the address
    return t, cvars


def stage_vu0asm(path: str, data: bytes) -> tuple[bytes, int]:
    text = data.decode("utf-8", "surrogateescape")
    if "asm" not in text:
        return data, 0
    code = blank(text)
    edits: list[tuple[int, int, str]] = []
    for f in find_funcs(code):
        if f.is_asm:
            continue
        lo, hi = f.body_open, f.body_close
        for s, o, e in asm_blocks(code, lo, hi):
            try:
                rows, rets = translate(code[o + 1:e])
            except Untranslatable:
                continue
            if rets and _needs_asm_return(f, code):
                continue
            edits.append((s, e + 1, "{ /* [port] vu0asm: asm block -> VU0 model */"
                          + _render(rows) + "}"))
        for m in GNU_ASM.finditer(code, lo, hi):
            try:
                close, tmpl, outs, ins = gnu_asm_parts(text, m.end() - 1)
                t, cvars = gnu_template_to_block(tmpl, outs + ins)
                rows, rets = translate(t, cvars)
            except (Untranslatable, ValueError):
                continue
            if rets and _needs_asm_return(f, code):
                continue
            end = close + 1
            sm = re.match(r"\s*;", text[end:])
            if sm:
                end += sm.end()
            nl = text[m.start():end].count("\n")
            body = " ".join(f"{c} /* {o.replace('*/', '* /')} */" for c, o in rows if c)
            edits.append((m.start(), end, "{ /* [port] vu0asm: GNU asm -> VU0 model */ "
                          + body + " }" + "\n" * nl))
    if not edits:
        return data, 0
    edits.sort()
    out, pos = [], 0
    for a, b, r in edits:
        out.append(text[pos:a])
        out.append(r)
        pos = b
    out.append(text[pos:])
    return "".join(out).encode("utf-8", "surrogateescape"), len(edits)


# ========================================================== stage: asmexclude

# MAIN address bands that are SDK / library code (same table as
# tools/census/snapshot.py LIB_BANDS -- memory: sdk-library-track).
LIB_BANDS = [
    (0x00100000, 0x00108000, "library", "band:crt0+MSL-runtime"),
    (0x00108000, 0x00140000, "sdk", "band:sce-sdk"),
    (0x00165608, 0x001660D4, "sdk", "band:sdremote-gcc-island"),
    (0x00446000, 0x00448000, "sdk", "band:libkernl"),
]


def classify_lib(path: str, image: str, addr: int | None) -> tuple[str, str]:
    for p in path.split("/")[1:-1]:
        if p == "sdk":
            return "sdk", "path:sdk"
        if p == "libc":
            return "library", "path:libc"
        if p == "gcc" or p.startswith("lib"):
            return "library", f"path:{p}"
    if image == "main" and addr is not None:
        for lo, hi, cls, why in LIB_BANDS:
            if lo <= addr < hi:
                return cls, why
    return "game", ""


COP2_RX = re.compile(r"^(?:v[a-z]|lqc2|sqc2|qmfc2|qmtc2|cfc2|ctc2|bc2)", re.I)
MMI_RX = re.compile(r"^(?:lq|sq|p[a-z]|qfsrv|mtsa|mfsa)", re.I)


def body_class(asm_text: str) -> str:
    """cop2 / cop2+ee / mmi / ee / nops by mnemonic (census asm_bodies.py)."""
    mns = []
    for st in re.split(r"[;\n]", asm_text):
        st = re.sub(r"^\s*(?:[\w$@.]+\s*:\s*)*", "", st).strip()
        if not st or st.startswith(".") or st.startswith("#"):
            continue
        m = re.match(r"[A-Za-z][\w.]*", st)
        if m:
            mns.append(m.group(0).lower())
    if not mns:
        return "empty"
    rest = [m for m in mns if m not in NOPS and m not in ("jr", "mfc1", "mtc1")]
    if not rest:
        return "nops"
    c2 = [m for m in rest if COP2_RX.match(m)]
    mmi = [m for m in rest if MMI_RX.match(m) and not COP2_RX.match(m)]
    ee = [m for m in rest if m not in c2 and m not in mmi]
    if c2:
        return "cop2" if not ee else "cop2+ee"
    if mmi:
        return "mmi" if not ee else "mmi+ee"
    return "ee"


def _first_reason(asm_text: str) -> str:
    try:
        translate(asm_text)
    except Untranslatable as u:
        return str(u)
    return "asm supplies the return value"


def _has_data_defs(code: str) -> bool:
    """Any top-level object DEFINITION left (heuristic; keeps a file compiled
    when its asm functions are cut but it still owns data)."""
    s = blank_pp(code)
    depth, start = 0, 0
    for k, ch in enumerate(s):
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        elif ch == ";" and depth == 0:
            st = s[start:k].strip()
            start = k + 1
            if not st:
                continue
            st = re.sub(r"^(?:\s*__attribute__\s*\(\(.*?\)\))+", "", st).strip()
            if re.match(r"(extern|typedef)\b", st):
                continue
            if re.fullmatch(r"(?:struct|union|enum|class)\b[^=]*\}", st, re.S):
                continue
            pre = st.split("=")[0]
            if "=" not in st and "(" in pre:
                continue  # prototype
            return True
    return False


@dataclass
class ExRow:
    symbol: str
    file: str
    image: str
    reason: str
    lib: str
    lib_reason: str
    scope: str
    detail: str


class AsmExclude:
    """Transform 6.  Context (filled by ingest before the stages run):
    image_of[path], addr_of[(image, symbol)].  Results: rows (EXCLUDED.tsv)
    and excluded_files (MANIFEST kind `excluded`)."""

    name = "asmexclude"

    def __init__(self) -> None:
        self.image_of: dict[str, str] = {}
        self.addr_of: dict[tuple[str, str], int] = {}
        self.rows: list[ExRow] = []
        self.excluded_files: set[str] = set()

    def _row(self, path: str, sym: str, reason: str, scope: str, detail: str) -> None:
        image = self.image_of.get(path, "?")
        addr = self.addr_of.get((image, sym))
        if addr is None:
            m = re.search(r"_([0-9a-fA-F]{6})$", sym)
            addr = int(m.group(1), 16) if m else None
        lib, why = classify_lib(path, image, addr)
        self.rows.append(ExRow(sym, path, image, reason, lib, why, scope,
                               re.sub(r"\s+", " ", detail).strip()))

    def __call__(self, path: str, data: bytes) -> tuple[bytes, int]:
        text = data.decode("utf-8", "surrogateescape")
        if "asm" not in text:
            return data, 0
        code = blank(text)
        funcs = find_funcs(code)
        targets: list[tuple[Func, str, str]] = []
        for f in funcs:
            if f.is_asm:
                body = code[f.body_open + 1:f.body_close]
                targets.append((f, "asm-function", body_class(body)))
                continue
            blocks = asm_blocks(code, f.body_open, f.body_close)
            if blocks:
                s, o, e = blocks[0]
                body = code[o + 1:e]
                targets.append((f, "asm-block", f"{body_class(body)}; {_first_reason(body)}"))
                continue
            g = GNU_ASM.search(code, f.body_open, f.body_close)
            if g:
                close, tmpl, outs, ins = gnu_asm_parts(text, g.end() - 1)
                t, cv = gnu_template_to_block(tmpl, outs + ins)
                try:
                    translate(t, cv)
                    why = "asm supplies the return value"
                except Untranslatable as u:
                    why = str(u)
                targets.append((f, "gnu-asm", f"{body_class(t)}; {why}"))
        if not targets:
            return data, 0

        sp = blank_pp(code)
        whole: str | None = None
        cuts: list[tuple[int, int, str]] = []
        for f, reason, detail in targets:
            if f.in_class:
                whole = f"asm in class member {f.name}"
                break
            hdr = sp[f.start:f.body_open]
            lead = len(hdr) - len(hdr.lstrip())
            dstart = f.start + lead
            hdr_text = text[dstart:f.body_open]
            static = bool(re.search(r"\b(static|inline|__inline)\b", code[dstart:f.body_open]))
            if static:
                rest = code[:dstart] + code[f.body_close + 1:]
                if re.search(rf"\b{re.escape(f.name)}\b", rest):
                    whole = f"static asm helper {f.name} is used by C in the same file"
                    break
                rep = ""
            else:
                proto = re.sub(r"\b(?:asm|__asm)\b\s*", "", hdr_text).rstrip()
                rep = (f"{proto}; /* [port] asmexclude: {reason} body cut -- "
                       f"bound later, see EXCLUDED.tsv */")
            nl = text[dstart:f.body_close + 1].count("\n") - rep.count("\n")
            cuts.append((dstart, f.body_close + 1, rep + "\n" * max(nl, 0)))

        if whole is None:
            out, pos = [], 0
            for a, b, r in sorted(cuts):
                out.append(text[pos:a])
                out.append(r)
                pos = b
            out.append(text[pos:])
            new = "".join(out)
            ncode = blank(new)
            left = [g for g in find_funcs(ncode)]
            if not left and not _has_data_defs(ncode):
                whole = "no C definition left"
        if whole is not None:
            self.excluded_files.add(path)
            tnames = {f.name for f, _, _ in targets}
            for f, reason, detail in targets:
                self._row(path, f.name, reason, "file", detail)
            for f in funcs:
                if f.name not in tnames and not f.in_class:
                    self._row(path, f.name, "collateral", "file", whole)
            return data, len(targets)
        for f, reason, detail in targets:
            self._row(path, f.name, reason, "function", detail)
        return new.encode("utf-8", "surrogateescape"), len(targets)

    def tsv(self) -> str:
        cols = ["symbol", "file", "image", "reason", "lib", "lib_reason", "scope", "detail"]
        lines = ["\t".join(cols)]
        for r in sorted(self.rows, key=lambda r: (r.file, r.symbol)):
            lines.append("\t".join(str(getattr(r, c)) for c in cols))
        return "\n".join(lines) + "\n"


# ---------------------------------------------------------------- dialect
# Stage `dialect`: mwcc-accepted spellings clang rejects outright (no flag
# downgrades them).  Each rule is local, keeps line numbers, and is a no-op
# on its own output.
#
#  cxx-anon-extern  C++: `extern struct { ... } D_x;` -- a variable of an
#                   unnamed type has no linkage in C++, so it can never bind
#                   to the C definition.  The type gets a tag
#                   (`struct rgp_anon_D_x { ... } D_x;`).
#  proto-tag        C: `extern void F(.., struct T a);` before any file-scope
#                   `struct T`: the tag is scoped to the prototype, so every
#                   call passes an incomplete type.  `struct T; ` is inserted
#                   on the same line, ahead of the declaration.
#  lvalue-cast      `((T *)p)++` / `--` (GNU lvalue cast) ->
#                   `(*(T **)&(p))++`, the same pointer increment.
#  wide-shift       a 32-bit call result shifted left by >= 32 (see _WIDE_SHIFT)
#  arg-order        a nested call writing &x before a later argument reads x
#                   (see _arg_order_edits)
#  (these two are semantic, not syntax: clang compiles the original but
#  traps / reads a stale value; docs/BRINGUP.md)
_ANON_EXT = re.compile(
    r"\bextern\s+((?:const\s+|volatile\s+)*)(struct|union)(\s*)\{([^{}]*)\}\s*([A-Za-z_]\w*)\s*;")
_LV_CAST = re.compile(
    r"\(\(\s*([A-Za-z_][\w ]*?\s*\*+)\s*\)\s*([A-Za-z_]\w*)\s*\)\s*(\+\+|--)")
_TAG_USE = re.compile(r"\b(struct|union)\s+([A-Za-z_]\w*)")


# ---------------------------------------------------------------- vu0bind
# mwcc VU0 register bindings (`#pragma vu0_mmi_reg_binding on` +
# `extern u128 v asm("vf4")`, the s88m de-asm spelling, d784320c+): each bound
# variable becomes an lvalue on the VU0 model's register file, and the file
# includes port/vu0intrin.h, which implements the mwcc intrinsics (_vmul,
# _vaddbc, _vdiv, ...) on values (docs/LINK.md "VU0 register bindings").
# Only vf0..vf31 / ACC / Q are rewritten; GPR bindings (asm("r4")) are unused
# externs that clang reads as asm labels.
_VB_DECL = re.compile(
    r'\bextern\s+((?:const\s+)?[A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s+(?:asm|__asm__)\s*'
    r'\(\s*"(vf(\d+)|ACC|Q)"\s*\)\s*;')
_VB_INC = '#include "port/vu0intrin.h" /* rg:vu0bind */'


def stage_vu0bind(path: str, data: bytes) -> tuple[bytes, int]:
    text = data.decode("utf-8", "surrogateescape")
    if "vu0_mmi_reg_binding" not in text and not _VB_DECL.search(text):
        return data, 0
    n = 0

    def sub(m):
        nonlocal n
        n += 1
        ty, name, reg, num = m.group(1), m.group(2), m.group(3), m.group(4)
        td = f"rgvb_{name}_t"
        if reg == "Q":
            lv = f"RG_VU0_BIND_Q({td})"
        elif reg == "ACC":
            lv = f"RG_VU0_BIND_ACC({td})"
        else:
            lv = f"RG_VU0_BIND_VF({int(num)}, {td})"
        return (f"typedef {ty} __attribute__((aligned(4))) {td}; "
                f"/* rg:vu0bind {reg} */\n#define {name} {lv}\n")

    new = _VB_DECL.sub(sub, text)
    if n == 0:
        return data, 0
    if _VB_INC not in new:
        new = _VB_INC + "\n" + new
    return new.encode("utf-8", "surrogateescape"), n


# block-scope scalar arrays (`u8 sp20[0x190];`): the EE stack frame is
# 16-aligned and mwcc puts such buffers at 16-aligned offsets, so the game
# passes them to code that moves qwords (u128 / lq / sq -> movaps on i686,
# CameraObjSetDefaults_161d50 -> CameraBaseInit_15fc80).  i686 gives a u8
# array alignment 1: add aligned(16) to every block-scope scalar array of
# >= 16 bytes (a declaration at a line start or right after `{` / `;`:
# PointInOrientedBox_1c8430's one-line `{f32 inv[16];` reaches
# MtxInverseAffine_1cb640's movaps stores; clang realigns the frame).
_LOCAL_ARR = re.compile(
    r"(?:^|(?<=[{;]))([ \t]*(?:static\s+)?(?:volatile\s+)?(?:const\s+)?"
    r"(?:u8|s8|u16|s16|u32|s32|u64|s64|f32|f64|char|short|int|long|float|double|"
    r"unsigned\s+char|unsigned\s+short|unsigned\s+int|unsigned|signed\s+char)"
    r"[ \t]+[A-Za-z_]\w*[ \t]*\[[ \t]*(0x[0-9A-Fa-f]+|\d+)[ \t]*\]((?:[ \t]*\[[ \t]*(?:0x[0-9A-Fa-f]+|\d+)[ \t]*\])*))"
    r"([ \t]*[;=])", re.M)
# block-scope aggregate locals (`DBuff db;` in GfxSetVideoMode_1451f0, handed
# to sceGsSetDefDBuff, whose port provider stores qwords): 16-aligned like the
# EE frame slot they had
_LOCAL_AGG = re.compile(
    r"^([ \t]+(?:static[ \t]+)?(?:volatile[ \t]+)?(?:struct[ \t]+|union[ \t]+)?([A-Za-z_]\w*)[ \t]+[A-Za-z_]\w*"
    r"((?:[ \t]*\[[ \t]*(?:0x[0-9A-Fa-f]+|\d+)[ \t]*\])*))([ \t]*[;=])", re.M)
_NOT_AGG = {"u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64", "int", "char",
            "bool", "float", "double", "long", "short", "unsigned", "signed", "void", "return",
            "goto", "delete", "else", "do", "case", "typedef", "throw", "new", "sizeof",
            "extern", "const", "register", "auto", "using", "namespace", "BOOL", "size_t",
            "u128", "s128", "rg_u128", "rg_s128", "qword", "uint", "ushort", "uchar"}
_ELEM = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2, "short": 2, "u64": 8, "s64": 8,
         "f64": 8, "double": 8}


def _local_arr_bytes(decl: str, n: str, more: str) -> int:
    t = decl.split()
    base = next((x for x in t if x in _ELEM), None)
    size = _ELEM.get(base, 4) * int(n, 0)
    for d in re.findall(r"(0x[0-9A-Fa-f]+|\d+)", more or ""):
        size *= int(d, 0)
    return size


_BLOCK_STATIC_FN = re.compile(r"(static\s+)(?=[A-Za-z_][\w\s\*]*\(\s*[^();{}]*\)\s*;)")
# wide-shift: m2c's `(F(..) << 0x30) >> 0x30` is the EE's dsll32/dsra32 on
# the 64-bit register holding F's 32-bit result (a sign-extension of the low
# bits).  In C a 32-bit `x << 48` is undefined and clang (TrapUnreachable on
# the MSVC target) emits int3 (LoaderReleaseById_1cd340).  A call result
# shifted left by >= 32 is widened first:
# `F(..) << K` -> `(__typeof__((F(..)) + 0LL))(F(..)) << K` (unevaluated
# __typeof__: 32-bit ints become long long, 64-bit types keep theirs, so a
# u64 still shifts logically).  Census: build/boot/ubscan.py
# (-Wshift-count-overflow over the whole corpus, docs/BRINGUP.md).
# an extern declaration of a data2c object (D_xxxxxxxx, overlay-prefixed
# title_D_..., data2c_..): group 1 = every `const` before the name, the first
# one only (one edit per match; a second `const` is pointer-level)
_CONST_DATA_DECL = re.compile(
    r"\bextern\s+(?:\"[^\"]*\"\s+)?(const\s+)(?:volatile\s+)?(?:struct\s+|union\s+|unsigned\s+|signed\s+)?"
    r"\w+\s*(?:\*\s*)*\b(?:\w+_)?(?:D_[0-9A-Fa-f]{8}|data2c_\w+)\b\s*(?:\[[^\]]*\]\s*)*"
    r"(?:__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)\s*)?;")
_WIDE_SHIFT = re.compile(
    r"(?<![\w.>])([A-Za-z_]\w*\s*\((?:[^()]|\([^()]*\))*\))(\s*<<\s*"
    r"(?:0x[23][0-9A-Fa-f]|3[2-9]|[45][0-9]|6[0-3])\b)")


# arg-order: `F(.., G(.., &x, ..), .., x, ..)` -- the nested call writes x
# and a LATER argument reads it.  mwcc evaluated G first (retail:
# title_TitleStateLoadRes_4ec030 passes ArchiveGetFileByPath's size out
# parameter to SaveMenuMsgTableParse_376b40); clang on i686 evaluates
# arguments right to left and reads the stale x.  The nested call is hoisted
# into a GNU statement expression: `({ __typeof__(G(..)) rgp_ao0 = G(..);
# F(.., rgp_ao0, .., x, ..); })`.  Census: build/boot/argorder.py.
_AO_CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
_AO_KW = {"if", "while", "for", "switch", "return", "sizeof", "__typeof__", "typeof",
          "__attribute__", "defined"}


def _ao_close(s: str, i: int) -> int:
    d = 0
    for j in range(i, len(s)):
        if s[j] == "(":
            d += 1
        elif s[j] == ")":
            d -= 1
            if d == 0:
                return j
    return -1


def _ao_args(s: str, a: int, b: int):
    out, d, st = [], 0, a
    for j in range(a, b):
        c = s[j]
        if c in "([{":
            d += 1
        elif c in ")]}":
            d -= 1
        elif c == "," and d == 0:
            out.append((st, j))
            st = j + 1
    out.append((st, b))
    return out


def _arg_order_edits(code: str, text: str):
    edits = []
    taken = []          # spans already rewritten (outer calls): no nesting
    for m in _AO_CALL.finditer(code):
        if m.group(1) in _AO_KW:
            continue
        lp = m.end() - 1
        rp = _ao_close(code, lp)
        if rp < 0 or any(a <= m.start() < b for a, b in taken):
            continue
        args = _ao_args(code, lp + 1, rp)
        if len(args) < 2:
            continue
        texts = [code[a:b] for a, b in args]
        hoist = None
        for i, at in enumerate(texts):
            if not _AO_CALL.search(at):
                continue
            for x in re.findall(r"&\s*([A-Za-z_]\w*)\b(?!\s*(?:\.|->|\[))", at):
                if any(re.search(rf"(?<![\w&.>])\s*{x}\b(?!\s*\()", bt)
                       and not re.search(rf"&\s*{x}\b", bt) for bt in texts[i + 1:]):
                    hoist = i
                    break
            if hoist is not None:
                break
        if hoist is None:
            continue
        a, b = args[hoist]
        inner = text[a:b].strip()
        tmp = f"rgp_ao{len(edits)}"
        outer = text[m.start():a] + (" " if text[a] == " " else "") + tmp + text[b:rp + 1]
        edits.append((m.start(), rp + 1,
                      f"({{ __typeof__({inner}) {tmp} = {inner}; {outer}; }})"))
        taken.append((m.start(), rp + 1))
    return edits


_BF_SIZE = {"u8": 1, "s8": 1, "char": 1, "signed char": 1, "unsigned char": 1, "bool": 1,
            "u16": 2, "s16": 2, "short": 2, "unsigned short": 2, "signed short": 2,
            "u32": 4, "s32": 4, "int": 4, "unsigned": 4, "unsigned int": 4, "signed": 4,
            "signed int": 4, "long": 4, "unsigned long": 4, "vc_u32": 4,
            "u64": 8, "s64": 8, "long long": 8, "unsigned long long": 8}
_BF_UNSIGNED = {"u8", "unsigned char", "u16", "unsigned short", "u32", "unsigned",
                "unsigned int", "unsigned long", "vc_u32", "u64", "unsigned long long"}
_BF_DECL = re.compile(
    r"^\s*(?:(?:public|private|protected)\s*:\s*)*(?:__extension__\s+)?"
    r"((?:const\s+|volatile\s+)*(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*(?:\s+(?:int|long|short|char))*)"
    r"\s+([A-Za-z_]\w*\s*:\s*\w+(?:\s*,\s*[A-Za-z_]\w*\s*:\s*\w+)*)\s*$", re.S)
BITFIELD_CENSUS: dict = {}


_GCC_PRIM = dict(_BF_SIZE)
_GCC_PRIM.update({"f32": 4, "float": 4, "f64": 8, "double": 8, "VC_VPTR_MEMBER": 4,
                  "vc_u32": 4, "u128": 16, "s128": 16, "rg_u128": 16, "qword": 16})


def _gcc_member(stmt: str):
    """(size, align) of a plain member declaration `T [*]name[N]..` with a
    primitive T (mwcc/GCC on the EE), or None."""
    st = stmt.strip()
    if st == "VC_VPTR_MEMBER":
        return (4, 4)
    st = re.sub(r"^(?:(?:public|private|protected)\s*:\s*)+", "", st)
    st = re.sub(r"__attribute__\s*\(\(.*?\)\)", "", st).strip()
    m = re.fullmatch(r"((?:const\s+|volatile\s+)*(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*(?:\s+(?:int|long|short|char))*)"
                     r"\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[\s*(?:0x[0-9A-Fa-f]+|\d+)\s*\]\s*)*)", st)
    if not m:
        return None
    typ = " ".join(re.sub(r"\b(const|volatile)\b", "", m.group(1)).split())
    if m.group(2):
        size = al = 4
    elif typ in _GCC_PRIM:
        size = _GCC_PRIM[typ]
        al = size
    else:
        return None
    for d in re.findall(r"\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]", m.group(4)):
        size *= int(d, 0)
    return (size, al)


def _bf_advance(bitpos, m):
    """GCC cursor after a bitfield declaration (None when unknown)."""
    if bitpos is None:
        return None
    typ = " ".join(re.sub(r"\b(const|volatile)\b", "", m.group(1)).split())
    sz = _BF_SIZE.get(typ)
    if sz is None:
        return None
    for dm in re.finditer(r"([A-Za-z_]\w*)\s*:\s*(\w+)", m.group(2)):
        try:
            w = int(dm.group(2), 0)
        except ValueError:
            return None
        if w <= 0:
            return None
        if bitpos // (sz * 8) != (bitpos + w - 1) // (sz * 8):
            bitpos = (bitpos // (sz * 8) + 1) * sz * 8
        bitpos += w
    return bitpos


def _bf_unit_rewrite(run, fields, start, stmts, code):
    """A bitfield run with fields crossing bytes, whose GCC start offset is
    known: re-declare every field with one unit type U (the smallest of 1, 2,
    4, 8 bytes that divides the start and holds each field inside one U unit
    at its GCC position), with unnamed padding where GCC skipped bits, so the
    MSVC layout is GCC's.  The member after the run must not start inside
    the last U unit.  -> (edits, alignment to keep) or None."""
    if start is None:
        return None
    pos, place, maxsz = start * 8, [], 1
    for a, b, typ, ws in fields:
        sz = _BF_SIZE[typ]
        maxsz = max(maxsz, sz)
        for nm, w in ws:
            if w <= 0:
                return None
            if pos // (sz * 8) != (pos + w - 1) // (sz * 8):
                pos = (pos // (sz * 8) + 1) * sz * 8
            place.append((nm, w, pos))
            pos += w
    end_bits = pos
    # the member after the run (GCC offset), when the run is not last
    last_b = run[-1][1]
    nxt = None
    for a, b, plain in stmts:
        if a > last_b and code[a:b].strip():
            sa = _gcc_member(code[a:b]) if plain else None
            if sa is None:
                return None
            nxt = ((end_bits + 7) // 8 + sa[1] - 1) // sa[1] * sa[1]
            break
    # one unit size per declaration statement (declarators share the type):
    # search the assignments, simulate MSVC's packing with unnamed padding
    # inserted where GCC left a gap, keep the first that reproduces GCC
    import itertools
    sizes = (1, 2, 4, 8)
    nst = len(fields)
    if nst > 8:
        return None
    for us in itertools.product(sizes, repeat=nst):
        k, ustart, ubits, used = 0, None, 0, 0
        pads, okk = {}, True
        for si, (a_, b_, typ, ws) in enumerate(fields):
            ub = us[si] * 8
            for nm, w in ws:
                p = place[k][2]
                pad = []
                if p // ub != (p + w - 1) // ub:
                    okk = False
                    break
                if ustart is not None and ubits == ub and ustart <= p and p + w <= ustart + ub                         and p >= ustart + used:
                    if p > ustart + used:
                        pad.append(p - (ustart + used))
                else:
                    base = start * 8 if ustart is None else ustart + ubits
                    ns = (base + ub - 1) // ub * ub
                    if not (ns <= p < ns + ub):
                        okk = False
                        break
                    if ustart is not None and ubits == ub:
                        pad.append(0)            # force a new unit
                    if p > ns:
                        pad.append(p - ns)
                    ustart, ubits = ns, ub
                used = p + w - ustart
                pads[k] = pad
                k += 1
            if not okk:
                break
        if not okk:
            continue
        unit_end = ustart + ubits
        if nxt is not None and unit_end > nxt * 8:
            continue
        if nxt is None and ((unit_end // 8) + maxsz - 1) // maxsz != ((end_bits + 7) // 8 + maxsz - 1) // maxsz:
            continue
        tn = {1: "char", 2: "short", 4: "int", 8: "long long"}
        edits, k = [], 0
        for si, (a_, b_, typ, ws) in enumerate(fields):
            sign = "unsigned" if typ in _BF_UNSIGNED else "signed"
            # `__extension__` marks the run as re-declared (idempotence)
            mark = "__extension__ " if si == 0 else ""
            edits.append((a_, b_, f"{mark}{sign} {tn[us[si]]}"))
            body = code[b_:]
            for dm, (nm, w) in zip(re.finditer(r"([A-Za-z_]\w*)\s*:\s*\w+", body), ws):
                if pads.get(k):
                    edits.append((b_ + dm.start(1), b_ + dm.start(1),
                                  "".join(f" : {x}, " for x in pads[k])))
                k += 1
        return edits, maxsz
    return None


def _bitfield_edits(code: str, path: str) -> list[tuple[int, int, str]]:
    """Rule `bitfield-gcc` (BRINGUP.md checkpoint, session 3).  clang's
    i686-windows-msvc target lays bitfields out the MSVC way: a run of
    bitfields uses units of the DECLARED type, aligned to it, a change of type
    size starts a new unit, and the next member comes after the whole unit.
    mwcc (like GCC) packs each field at the current bit offset inside any
    aligned unit of its type and lets the next member follow the last used
    byte.  `G { u8 *unk94; u8 pad98[2]; u64 f0:1, f1:1, f2:1; }` put f2 at
    +0xA0 bit 2 on the port and +0x9A bit 2 on the EE
    (WorldDataCmdSetPartyMember_3b9b00 then skipped every NEW GAME party
    command).  -mno-ms-bitfields is not supported for the MSVC ABI.

    A run of bitfields in a struct/class (not a union) whose fields each stay
    inside one byte at their GCC bit positions (sequential from the run's
    byte-aligned start) is re-declared with 1-byte types (`unsigned char` /
    `signed char` by the declared signedness): MSVC then packs them exactly
    as mwcc did.  The struct keeps mwcc's alignment through
    `__attribute__((aligned(A)))`, A = the widest declared bitfield type.
    Runs with a field crossing a byte, a zero-width field or an unknown type
    are left alone and counted (BITFIELD_CENSUS)."""
    edits = []
    n = len(code)
    for ob in re.finditer(r"\{", code):
        i = ob.start()
        head = code[max(0, i - 200):i]
        km = re.search(r"\b(struct|class|union)\b(?:\s+__attribute__\s*\(\(.*?\)\))?\s*[\w\s:,<>]*$", head, re.S)
        if not km or km.group(1) == "union":
            continue
        # body extent
        d, j = 0, i
        while j < n:
            if code[j] == "{":
                d += 1
            elif code[j] == "}":
                d -= 1
                if d == 0:
                    break
            j += 1
        if j >= n:
            continue
        # top-level statements of the body
        stmts, d, s0 = [], 0, i + 1
        for k in range(i + 1, j):
            ch = code[k]
            if ch in "{(":
                d += 1
            elif ch in "})":
                d -= 1
                if d == 0 and ch == "}":
                    stmts.append((s0, k + 1, False))
                    s0 = k + 1
            elif ch == ";" and d == 0:
                stmts.append((s0, k, True))
                s0 = k + 1
        runs, cur = [], []
        starts = []         # GCC byte offset of each run's start, or None
        bitpos = 0          # GCC layout cursor (bits) while every member is known
        for a, b, plain in stmts:
            m = _BF_DECL.match(code[a:b]) if plain else None
            if m:
                if not cur:
                    starts.append(None if bitpos is None else (bitpos + 7) // 8)
                    if bitpos is not None:
                        bitpos = (bitpos + 7) // 8 * 8
                cur.append((a, b, m))
                bitpos = _bf_advance(bitpos, m)
            else:
                if cur:
                    runs.append(cur)
                cur = []
                sa = _gcc_member(code[a:b]) if plain else None
                if bitpos is not None and sa is not None:
                    sz, al = sa
                    bitpos = ((bitpos + 7) // 8 + al - 1) // al * al * 8 + sz * 8
                elif plain and not code[a:b].strip():
                    pass
                else:
                    bitpos = None
        if cur:
            runs.append(cur)
        align = 1
        for ri, run in enumerate(runs):
            fields = []         # (type span, type, [(name, width)])
            ok, why = True, ""
            for a, b, m in run:
                typ = " ".join(re.sub(r"\b(const|volatile)\b", "", m.group(1)).split())
                if typ not in _BF_SIZE:
                    ok, why = False, "type " + typ
                    break
                ws = []
                for dm in re.finditer(r"([A-Za-z_]\w*)\s*:\s*(\w+)", m.group(2)):
                    try:
                        ws.append((dm.group(1), int(dm.group(2), 0)))
                    except ValueError:
                        ok, why = False, "width " + dm.group(2)
                fields.append((a + m.start(1), a + m.end(1), typ, ws))
            if ok:
                pos = 0
                for _a, _b, typ, ws in fields:
                    for nm, w in ws:
                        if w <= 0 or (pos % 8) + w > 8:
                            ok, why = False, "crosses a byte" if w > 0 else "zero width"
                            break
                        pos += w
                    if not ok:
                        break
            if any("__extension__" in code[a:b] for a, b, _m in run):
                BITFIELD_CENSUS["unit-rewritten"] = BITFIELD_CENSUS.get("unit-rewritten", 0) + 1
                continue        # an earlier pass re-declared this run
            if not ok and why == "crosses a byte":
                uni = _bf_unit_rewrite(run, fields, starts[ri], stmts, code)
                if uni is not None:
                    edits.extend(uni[0])
                    align = max(align, uni[1])
                    BITFIELD_CENSUS["unit-rewrite"] = BITFIELD_CENSUS.get("unit-rewrite", 0) + 1
                    continue
            key = "convertible" if ok else "left:" + why.split()[0]
            if ok and all(_BF_SIZE[t] == 1 for _a, _b, t, _w in fields):
                key = "already-bytes"
            BITFIELD_CENSUS[key] = BITFIELD_CENSUS.get(key, 0) + 1
            if key != "convertible":
                continue
            for a, b, typ, _ws in fields:
                if _BF_SIZE[typ] == 1:
                    continue
                rep = "unsigned char" if typ in _BF_UNSIGNED else "signed char"
                edits.append((a, b, rep))
                align = max(align, _BF_SIZE[typ])
        if align > 1:
            # after the closing brace (`struct G {..} __attribute__((aligned(8))) G;`):
            # a struct head stays parseable for the other dialect rules
            edits.append((j + 1, j + 1, f" __attribute__((aligned({align})))"))
    return edits


def stage_dialect(path: str, data: bytes) -> tuple[bytes, int]:
    text = data.decode("utf-8", "surrogateescape")
    code = blank_pp(blank(text))
    edits: list[tuple[int, int, str]] = []
    edits += _bitfield_edits(code, path)
    if path.endswith(".cpp"):
        for m in _ANON_EXT.finditer(code):
            o = m.start(2) + len(m.group(2))
            edits.append((o, o, f" rgp_anon_{m.group(5)}"))
    for m in _LV_CAST.finditer(code):
        edits.append((m.start(), m.end(),
                      f"(*({m.group(1).strip()} *)&({m.group(2)})){m.group(3)}"))
    if path.endswith(".c"):
        depth, paren, seen = 0, 0, set()
        i, n = 0, len(code)
        tag_at = {mm.start(): mm for mm in _TAG_USE.finditer(code)}
        while i < n:
            ch = code[i]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
            elif ch == "(":
                paren += 1
            elif ch == ")":
                paren -= 1
            elif i in tag_at and depth == 0:
                mm = tag_at[i]
                key = (mm.group(1), mm.group(2))
                if key not in seen:
                    seen.add(key)
                    if paren > 0:     # start of the declaration
                        k = max(code.rfind(";", 0, i), code.rfind("}", 0, i)) + 1
                        while k < i and code[k] in " \t\r\n":
                            k += 1
                        edits.append((k, k, f"{key[0]} {key[1]}; "))
            elif ch == "s" and depth > 0 and paren == 0:
                # block-scope `static void f(void);` (a redeclaration of a
                # file-scope static, d784320c FrameCalcWorldMatrix): clang
                # rejects the storage class there; drop it (linkage is kept
                # from the prior declaration)
                mm = _BLOCK_STATIC_FN.match(code, i)
                if mm and (i == 0 or not (code[i - 1].isalnum() or code[i - 1] == "_")):
                    edits.append((i, mm.end(1), ""))
            i += 1
    # `extern const T D_xxxxxxxx;` (the decomp's spelling to keep mwcc off
    # %gp_rel) written through `*(T *)&D_x = v`: clang deletes stores to a
    # const object (LoadingScreenResetEntriesMaybe_343140 lost
    # `D_004E898C = 1`, so the loading screen never finished).  Every data
    # object is writable on the port (datareloc), so the qualifier goes.
    # Also with a trailing `__attribute__((section(".sdata")))` (the
    # gp-addressed spelling, [[mwcc-const-sdata-load-hoist]]): missed until
    # 2026-10-23, so MenuItemCmdFadeSequenceStep_2adce0 lost its `W = ..`
    # stores and item-menu Use etc. soft-locked (BRINGUP item 7; census
    # tools/census/constwrite_census.py).
    for m in _CONST_DATA_DECL.finditer(code):
        edits.append((m.start(1), m.end(1), ""))
    for m in _WIDE_SHIFT.finditer(code):
        if re.match(r"(?:sizeof|if|while|for|switch|return)\b", m.group(1)):
            continue
        call = text[m.start(1):m.end(1)]
        if code[:m.start(1)].rstrip().endswith(")"):
            continue        # `(u64)F(..) << 32`: already cast (a cast binds tighter)
        edits.append((m.start(1), m.end(1), f"(__typeof__(({call}) + 0LL))({call})"))
    for lo, hi, rep in _arg_order_edits(code, text):
        if not any(lo < e_hi and e_lo < hi for e_lo, e_hi, _ in edits):
            edits.append((lo, hi, rep))
    cands = [m for m in _LOCAL_ARR.finditer(code)
             if _local_arr_bytes(m.group(1), m.group(2), m.group(3)) >= 16]
    cands += [m for m in _LOCAL_AGG.finditer(code) if m.group(2) not in _NOT_AGG]
    for m in cands:
        # innermost open brace: a function body / statement block, not a
        # struct/union/class body or an initializer
        depth, k = 0, m.start() - 1
        while k >= 0:
            ch = code[k]
            if ch == "}":
                depth += 1
            elif ch == "{":
                if depth == 0:
                    break
                depth -= 1
            k -= 1
        if k < 0:
            continue
        before = code[max(0, k - 200):k].rstrip()
        if before.endswith("=") or re.search(
                r"\b(?:struct|union|class|enum|namespace)\b[^;{}()]*$", before) or \
                re.search(r"\bextern\s+\"C\"\s*$", before):
            continue
        edits.append((m.end(1), m.end(1), " __attribute__((aligned(16)))"))
    if not edits:
        return data, 0
    for lo, hi, rep in sorted(edits, key=lambda e: e[0], reverse=True):
        text = text[:lo] + rep + text[hi:]
    return text.encode("utf-8", "surrogateescape"), len(edits)


def make_stages() -> list[tuple[str, object]]:
    """(name, apply) in ingest order; the AsmExclude instance is returned too
    so ingest can fill its context and read its results."""
    return [("int128", stage_int128), ("gccvarargs", stage_gccvarargs),
            ("vu0asm", stage_vu0asm), ("vu0bind", stage_vu0bind),
            ("asmexclude", AsmExclude()),
            ("dialect", stage_dialect)]


def _main() -> int:
    """python tools/portxform.py STAGE[,STAGE...] IN OUT -- run stages on one
    file, checking each is idempotent (CMake uses it on tests/xlat/*.c)."""
    import sys
    if len(sys.argv) != 4:
        print(_main.__doc__)
        return 2
    stages = dict(make_stages())
    path = sys.argv[2].replace(chr(92), "/")
    data = open(sys.argv[2], "rb").read()
    for name in sys.argv[1].split(","):
        fn = stages[name]
        out, sites = fn(path, data)
        again, _ = fn(path, out)
        if again != out:
            print(f"{name}: NOT idempotent on {path}")
            return 1
        print(f"{name}: {sites} sites")
        data = out
    open(sys.argv[3], "wb").write(data)
    return 0


if __name__ == "__main__":
    raise SystemExit(_main())
