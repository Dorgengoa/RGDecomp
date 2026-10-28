"""Struct / union / class layout of a C or C++ definition body, mwcc's (MIPS
EABI, GCC rules): natural alignment, bitfields packed GCC-style (a field
never straddles a unit of its declared type), anonymous nested struct/union
members, `__attribute__((aligned(N)))`, C++ member functions / access
specifiers / static members / typedefs skipped.  Classes with base classes
or virtual functions are not laid out (the vptr position is mwcc's
business: devirt.py).

    layout(body, type_size) -> (size, align, {member: offset}) or None
    type_size(text) -> (size, align) or None   # resolves a member's base type

Used by the protos stack-block rule (local sizes) and its census.
"""
from __future__ import annotations

import re

ALIGNED = re.compile(r"__attribute__\s*\(\(\s*aligned\s*\(\s*(\d+)\s*\)\s*\)\)")
ATTR = re.compile(r"__attribute__\s*\(\((?:[^()]|\((?:[^()]|\([^()]*\))*\))*\)\)")


def _split_top(body: str):
    """Top-level member declarations of a brace body: ('decl', text) and
    ('nested', kind, inner, trailing_declarator_text, attr) items; member
    function bodies are dropped."""
    out, i, n, start = [], 0, len(body), 0
    while i < n:
        ch = body[i]
        if ch == "{":
            head = body[start:i]
            depth, j = 1, i + 1
            while j < n and depth:
                if body[j] == "{":
                    depth += 1
                elif body[j] == "}":
                    depth -= 1
                j += 1
            inner = body[i + 1:j - 1]
            hm = re.fullmatch(r"\s*(?:typedef\s+)?(struct|union|class)\s*(\w+)?\s*(__attribute__.*)?\s*",
                              head, re.S)
            if hm and "(" not in head.replace("__attribute__", "").split("{")[0] \
                    .replace(hm.group(3) or "", ""):
                k = body.find(";", j)
                tail = body[j:k if k >= 0 else n]
                out.append(("nested", hm.group(1), inner, tail, head))
                i = start = (k + 1 if k >= 0 else n)
                continue
            if ")" in head or "(" in head:      # a member function body
                i = start = j
                # `{ .. };` stray semicolon after a body
                while start < n and body[start] in " \t\r\n;":
                    start += 1
                i = start
                continue
            return None                         # enum body or something unknown
        if ch == ";":
            t = body[start:i].strip()
            if t:
                out.append(("decl", t))
            start = i + 1
        i += 1
    if body[start:].strip():
        return None
    return out


def _dim(x: str):
    """An array dimension: an integer literal or +, -, *, / of literals
    (`u8 pad1B4[0x228 - 0x1B4]`), else None."""
    x = x.strip()
    if not re.fullmatch(r"[0-9A-Fa-fxX\s+\-*/()]+", x):
        return None
    toks = re.findall(r"0[xX][0-9A-Fa-f]+|\d+|[+\-*/()]", x)
    if "".join(toks) != re.sub(r"\s", "", x):
        return None
    try:
        v = eval(" ".join(str(int(t, 0)) if t[0].isdigit() else ("//" if t == "/" else t)
                          for t in toks), {"__builtins__": {}})
    except Exception:
        return None
    return v if isinstance(v, int) and v >= 0 else None


def layout(body: str, type_size, is_union=False, attr: str = ""):
    items = _split_top(body)
    if items is None:
        return None
    off_bits, size_bits, al, mem = 0, 0, 1, {}
    am = ALIGNED.search(attr or "")
    if am:
        al = int(am.group(1))

    def place(sz, a, name, nbits=None):
        nonlocal off_bits, size_bits, al
        al = max(al, a)
        if is_union:
            o = 0
        else:
            if nbits is None:
                o = (off_bits + 8 * a - 1) // (8 * a) * (8 * a)
            else:
                unit = 8 * sz
                o = off_bits
                if nbits == 0:
                    o = (o + unit - 1) // unit * unit
                elif o // unit != (o + nbits - 1) // unit:
                    o = (o + unit - 1) // unit * unit
        if name:
            mem[name] = o // 8
        w = 8 * sz if nbits is None else nbits
        if is_union:
            size_bits = max(size_bits, w)
        else:
            off_bits = o + w
            size_bits = off_bits

    for it in items:
        if it[0] == "nested":
            _k, kind, inner, tail, head = it
            sub = layout(inner, type_size, kind == "union", head + " " + tail)
            if sub is None:
                return None
            sz, a, sm = sub
            decls = [d.strip() for d in ATTR.sub("", tail).split(",") if d.strip()]
            if not decls:           # anonymous member: its fields are ours
                o0 = None
                if is_union:
                    o0 = 0
                else:
                    o0 = (off_bits + 8 * a - 1) // (8 * a) * (8 * a) // 8
                place(sz, a, None)
                for k, v in sm.items():
                    mem.setdefault(k, o0 + v)
                continue
            for d in decls:
                dm = re.fullmatch(r"(\**)\s*(\w+)\s*((?:\[\s*\w+\s*\]\s*)*)", d)
                if not dm:
                    return None
                s1, a1 = (4, 4) if dm.group(1) else (sz, a)
                for x in re.findall(r"\[\s*(\w+)\s*\]", dm.group(3)):
                    try:
                        s1 *= int(x, 0)
                    except ValueError:
                        return None
                place(s1, a1, dm.group(2))
            continue
        t = it[1]
        if re.match(r"(public|private|protected)\s*:", t):
            t = re.sub(r"^(public|private|protected)\s*:\s*", "", t)
            if not t:
                continue
        if re.match(r"(typedef|static|friend|using|enum)\b", t) or t.startswith("template"):
            continue
        if re.search(r"\bvirtual\b", t):
            return None
        tt = ATTR.sub(lambda m: m.group(0) if "aligned" in m.group(0) else "", t)
        if "(" in ATTR.sub("", tt):
            if re.search(r"\(\s*\*\s*\w+\s*\)\s*\(", tt):      # function pointer member
                fm = re.search(r"\(\s*\*\s*(\w+)\s*\)", tt)
                place(4, 4, fm.group(1))
                continue
            continue                         # a member function declaration
        maln = ALIGNED.search(tt)
        tt = ATTR.sub("", tt).strip()
        dm = re.fullmatch(r"((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+|"
                          r"class\s+|enum\s+|mutable\s+)*[A-Za-z_][\w:]*(?:\s+(?:int|long|char|short))*)\s*(.*)",
                          tt, re.S)
        if not dm:
            return None
        base = " ".join(dm.group(1).split())
        for dec in dm.group(2).split(","):
            dec = dec.strip()
            bm = re.fullmatch(r"(\w*)\s*:\s*(\w+)", dec)
            if bm:
                r = type_size(base)
                if r is None:
                    return None
                try:
                    nb = int(bm.group(2), 0)
                except ValueError:
                    return None
                place(r[0], r[1], bm.group(1) or None, nb)
                continue
            mm = re.fullmatch(r"([\*&\s]*)\s*([A-Za-z_]\w*)\s*((?:\[\s*[^\]]*\]\s*)*)", dec)
            if not mm:
                return None
            if mm.group(1).strip():
                s1, a1 = 4, 4
            else:
                r = type_size(base)
                if r is None:
                    return None
                s1, a1 = r
            if maln:
                a1 = max(a1, int(maln.group(1)))
            for x in re.findall(r"\[\s*([^\]]*)\]", mm.group(3)):
                v = _dim(x)
                if v is None:
                    return None
                s1 *= v
            place(s1, a1, mm.group(2))
    size = (size_bits + 7) // 8
    size = (size + al - 1) // al * al
    return (size, al, mem)
