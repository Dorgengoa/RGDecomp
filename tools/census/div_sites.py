#!/usr/bin/env python3
"""Census 5: integer `/` and `%` (and `/=`, `%=`) with a NON-constant divisor.

x86 `idiv`/`div` traps on a zero divisor and on INT_MIN / -1; the EE's `div`
does neither (mwcc's `-pragma divbyzerocheck on`, which the matching build
uses, adds a `break 7` after a zero test -- see README for what that means).

Method (comment- and string-stripped C, asm bodies skipped):
  * the divisor operand is parsed as one unary/postfix expression after the
    operator; it is CONSTANT if it is a numeric/char literal, sizeof(...),
    an ALL_CAPS macro name, or a parenthesised expression of those
  * FLOAT divisions are dropped: either operand has a float literal, a cast
    to f32/f64/float/double, or an identifier/field declared f32/f64/float/
    double anywhere in the same file (`%` is never float)
  * `type` column: int  = an operand is cast to / declared as an integer type
                    unknown = no float evidence and no int evidence
"""
from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

FLOAT_T = r"(?:f32|f64|float|double)"
INT_T = r"(?:s8|u8|s16|u16|s32|u32|s64|u64|int|short|char|long|unsigned|signed|size_t)"
OP = re.compile(r"(?<![/*])([/%])(=?)(?![/*])")
FLOAT_LIT = re.compile(r"(?<![\w.])(\d+\.\d*|\.\d+|\d+\.?\d*[eE][+-]?\d+)[fF]?|(?<![\w.])\d+[fF](?!\w)")
NUM = re.compile(r"\s*(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*")


def parse_operand(s: str, i: int) -> int:
    """end offset of the unary/postfix expression starting at s[i]."""
    n = len(s)
    while i < n and s[i] in " \t\r\n":
        i += 1
    # unary prefixes
    while i < n and s[i] in "-+~!*&":
        i += 1
        while i < n and s[i] in " \t\r\n":
            i += 1
    if i < n and s[i] == "(":
        j = match(s, i, "(", ")")
        inner = s[i + 1:j].strip()
        # a cast: (type) operand
        if re.fullmatch(r"(?:const\s+|volatile\s+|struct\s+|unsigned\s+|signed\s+)*\w+(?:\s+\w+)?\s*\**", inner) \
                and not re.fullmatch(r"\w+", inner) or re.fullmatch(INT_T + "|" + FLOAT_T, inner):
            return parse_operand(s, j + 1)
        i = j + 1
    elif s.startswith("sizeof", i):
        k = i + 6
        while k < n and s[k] in " \t":
            k += 1
        if k < n and s[k] == "(":
            return match(s, k, "(", ")") + 1
        i = k
    else:
        m = re.compile(r"[\w.']+").match(s, i)
        if not m:
            return i
        i = m.end()
    # postfix
    while i < n:
        k = i
        while k < n and s[k] in " \t":
            k += 1
        if k < n and s[k] == "(":
            i = match(s, k, "(", ")") + 1
        elif k < n and s[k] == "[":
            i = match(s, k, "[", "]") + 1
        elif s.startswith("->", k) or (k < n and s[k] == "." and not s[k + 1:k + 2].isdigit()):
            k += 2 if s[k] == "-" else 1
            m = re.compile(r"\s*\w+").match(s, k)
            i = m.end() if m else k
        else:
            break
    return i


def match(s, i, o, c):
    d = 0
    for k in range(i, len(s)):
        if s[k] == o:
            d += 1
        elif s[k] == c:
            d -= 1
            if d == 0:
                return k
    return len(s) - 1


def lhs_operand(s: str, i: int) -> str:
    """rough left operand text: back to the previous operator/paren at depth 0"""
    k = i - 1
    depth = 0
    while k >= 0:
        c = s[k]
        if c in ")]":
            depth += 1
        elif c in "([":
            if depth == 0:
                break
            depth -= 1
        elif depth == 0 and (c in ",;{}=?:+|&^<>!" or (c == "-" and s[k + 1:k + 2] != ">")):
            break
        k -= 1
    return s[k + 1:i]


def is_const(expr: str) -> bool:
    e = expr.strip()
    while e.startswith("(") and match(e, 0, "(", ")") == len(e) - 1:
        e = e[1:-1].strip()
    e = re.sub(r"^\(\s*(?:" + INT_T + r")\s*\)\s*", "", e)
    if not e:
        return True
    if re.fullmatch(r"[-+~]?\s*(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*", e):
        return True
    if re.fullmatch(r"'(\\.|[^'])+'", e) or e.startswith("sizeof"):
        return True
    if re.fullmatch(r"[A-Z][A-Z0-9_]+", e):
        return True
    toks = re.findall(r"[A-Za-z_]\w*", e)
    if not toks and re.fullmatch(r"[\s0-9a-fA-FxXuUlL()+\-*/%<>|&~]+", e):
        return True
    return False


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    rows = []
    dropped = Counter()
    for sf in snap.all():
        s = sf.nostr
        if "/" not in s and "%" not in s:
            continue
        # blank asm bodies and preprocessor include lines
        spans = [(f.body_open, f.body_close) for f in sf.funcs if f.is_asm]
        spans += [(m.start(), match(s, m.end() - 1, "{", "}")) for m in
                  re.finditer(r"\basm\s*(?:volatile\s*)?\{", s)]
        spans += [(m.start(), m.end()) for m in re.finditer(r"^\s*#\s*(include|pragma)[^\n]*", s, re.M)]
        floats = set(re.findall(r"\b" + FLOAT_T + r"\b\s*(?:\*\s*)*(\w+)", s))
        floats |= set(re.findall(r"\b" + FLOAT_T + r"\b[^;(){}]*?,\s*\**\s*(\w+)", s))
        ints = set(re.findall(r"\b" + INT_T + r"\b\s+(\w+)\s*[;,=)\[]", s))
        for m in OP.finditer(s):
            o = m.start()
            if any(x <= o <= y for x, y in spans):
                continue
            # skip `*/`-like leftovers and division inside #define? keep #define
            end = parse_operand(s, m.end())
            div = s[m.end():end].strip()
            if not div:
                continue
            if is_const(div):
                continue
            lhs = lhs_operand(s, o)
            both = lhs + " " + div
            idents = {t for t in re.findall(r"[A-Za-z_]\w*", both)}
            if m.group(1) == "/":
                if FLOAT_LIT.search(both) or re.search(r"\(\s*" + FLOAT_T + r"\s*\)", both) \
                        or re.search(r"\*\s*\(\s*" + FLOAT_T + r"\s*\*\s*\)", both) \
                        or re.search(r"\b" + FLOAT_T + r"\s*\*", both):
                    dropped["float(literal/cast)"] += 1
                    continue
                if idents & floats:
                    dropped["float(declared-name)"] += 1
                    continue
            if re.search(r"\(\s*" + INT_T + r"(\s+" + INT_T + r")?\s*\)", both) or \
                    re.search(r"\*\s*\(\s*" + INT_T + r"\s*\*\s*\)", both) or (idents & ints):
                typ = "int"
            else:
                typ = "unknown"
            cat = ("mod" if m.group(1) == "%" else "div") + ("_assign" if m.group(2) else "")
            ln = sf.line(o)
            rows.append(dict(file=sf.path, line=ln, symbol=sf.symbol_at(o), image=sf.image,
                             lib=sf.lib, category=cat, type=typ,
                             divisor=S.snippet(div, 80), dividend=S.snippet(lhs, 80),
                             context=S.snippet(sf.line_text(ln, "code"))))
    rows.sort(key=lambda r: (r["image"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["type", "divisor", "dividend", "context"]
    out = Path(a.out) / "div_sites.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "div_sites", {
        "dropped": " ".join(f"{k}={v}" for k, v in dropped.items())}))
    print(Counter((r["category"], r["type"], r["lib"]) for r in rows))
    print(f"dropped {dict(dropped)}; wrote {out} ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
