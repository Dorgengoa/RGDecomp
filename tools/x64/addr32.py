#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""datareloc x64 mode `addr32` (P7 strategy A, docs/X64-PLAN.md step 3).

The data layer (tools/stages/datareloc.py) writes MAIN's .data as C objects
`u32 D_x[N] __attribute__((section(".data$rgXXXXXXXX"), aligned(A))) = {..}`
whose pointer words are `(u32)&SYM`, `(u32)((u8 *)&SYM + OFF)` or
`(u32)(SYM + OFF)`.  On x64 a pointer truncated to 32 bits is not a C
constant (clang: "initializer element is not a compile-time constant"), and a
`__ptr32` initializer is rejected by LLVM ("unsupported expression in static
initializer: addrspacecast").  The x64 build therefore emits each object that
holds a pointer word as top-level assembly in the SAME section with the SAME
alignment and size: `.long SYM+OFF` is an IMAGE_REL_AMD64_ADDR32 relocation,
correct because the exe's image lies below 2 GB (tools/x64/pecheck.py gates
the link flags).  The C declaration becomes `extern TYPE NAME[N];` so the
rest of the file (sizecheck typedef, interior-name aliases) is unchanged.

Objects without pointer words stay C.  i686 never runs this (the x64 source
tree is derived by tools/x64/derive.py).

    python tools/x64/addr32.py FILE.c            # rewritten file to stdout (debug)
"""
from __future__ import annotations

import re
import sys

DEF = re.compile(
    r"(?m)^(?P<const>const\s+)?(?P<type>u32|s32|u16|s16|u8|s8|f32|char)\s+(?P<name>\w+)"
    r"\s*\[(?P<n>[^\]]*)\]\s*__attribute__\(\((?P<attrs>.*?)\)\)\s*=\s*\{(?P<body>.*?)\};",
    re.S)
SIZE = {"u32": 4, "s32": 4, "f32": 4, "u16": 2, "s16": 2, "u8": 1, "s8": 1, "char": 1}
DIR = {4: ".long", 2: ".short", 1: ".byte"}
INT = re.compile(r"^\(?\s*-?(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)?$")
SYM = r"[A-Za-z_]\w*"
PTR_FORMS = [
    re.compile(r"^\(\s*(?:u32|s32)\s*\)\s*&\s*(?P<s>" + SYM + r")$"),
    re.compile(r"^\(\s*(?:u32|s32)\s*\)\s*\(\s*\(\s*(?:u8|s8|char)\s*\*\s*\)\s*&\s*(?P<s>" + SYM
               + r")\s*(?P<op>[+-])\s*(?P<o>0[xX][0-9A-Fa-f]+|\d+)[uU]?\s*\)$"),
    re.compile(r"^\(\s*(?:u32|s32)\s*\)\s*\(\s*(?P<s>" + SYM
               + r")\s*(?P<op>[+-])\s*(?P<o>0[xX][0-9A-Fa-f]+|\d+)[uU]?\s*\)$"),
    re.compile(r"^\(\s*(?:u32|s32)\s*\)\s*(?P<s>" + SYM + r")$"),
]


def split_top(s: str) -> list[str]:
    out, depth, st = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append(s[st:i])
            st = i + 1
    out.append(s[st:])
    return [x.strip() for x in out if x.strip()]


def word(e: str) -> str | None:
    """An element -> assembler operand, or None if it is not understood."""
    if INT.match(e):
        v = e.strip("()").rstrip("uUlL")
        return v
    for rx in PTR_FORMS:
        m = rx.match(e)
        if m:
            s = m.group("s")
            if "o" in m.groupdict() and m.group("o"):
                return f"{s}{m.group('op')}{m.group('o')}"
            return s
    return None


def section_of(attrs: str) -> tuple[str | None, int | None]:
    sec = re.search(r'section\(\s*"([^"]+)"\s*\)', attrs)
    al = re.search(r"aligned\(\s*(\d+)\s*\)", attrs)
    return (sec.group(1) if sec else None), (int(al.group(1)) if al else None)


def convert(text: str) -> tuple[str, int, list[str]]:
    """-> (new text, objects converted, problems)."""
    probs: list[str] = []
    n = 0
    out = []
    last = 0
    for m in DEF.finditer(text):
        body = re.sub(r"/\*.*?\*/", " ", m.group("body"), flags=re.S)
        body = re.sub(r"//[^\n]*", " ", body)
        if "&" not in body and not re.search(r"\(\s*(?:u32|s32)\s*\)\s*\(?\s*" + SYM, body):
            continue
        typ = m.group("type")
        esz = SIZE[typ]
        elems = split_top(body)
        ops = []
        bad = None
        for e in elems:
            w = word(e)
            if w is None or (esz != 4 and not INT.match(e)):
                bad = e
                break
            ops.append(w)
        if bad is not None:
            probs.append(f"{m.group('name')}: element not understood: {bad[:80]}")
            continue
        sec, al = section_of(m.group("attrs"))
        if sec is None:
            probs.append(f"{m.group('name')}: no section attribute")
            continue
        try:
            count = int(m.group("n"), 0)
        except ValueError:
            probs.append(f"{m.group('name')}: array bound {m.group('n')!r}")
            continue
        if len(ops) > count:
            probs.append(f"{m.group('name')}: {len(ops)} initializers for [{count}]")
            continue
        flags = "dr" if m.group("const") else "dw"
        name = m.group("name")
        lines = [f'".section {sec},\\"{flags}\\"\\n"']
        if al:
            lines.append(f'".p2align {al.bit_length() - 1}\\n"')
        elif esz > 1:
            lines.append(f'".p2align {esz.bit_length() - 1}\\n"')
        lines.append(f'".globl {name}\\n{name}:\\n"')
        d = DIR[esz]
        for i in range(0, len(ops), 8):
            lines.append(f'"{d} ' + ", ".join(ops[i:i + 8]) + '\\n"')
        if count > len(ops):
            lines.append(f'".zero {(count - len(ops)) * esz}\\n"')
        lines.append('".text\\n"')
        asm = ("/* rg:addr32 (x64): pointer words as ADDR32 relocations (tools/x64/addr32.py) */\n"
               f"{m.group('const') or ''}extern {typ} {name}[{m.group('n')}];\n"
               "__asm__(\n    " + "\n    ".join(lines) + ");")
        out.append(text[last:m.start()])
        out.append(asm)
        last = m.end()
        n += 1
    out.append(text[last:])
    return "".join(out), n, probs


def main(argv: list[str]) -> int:
    t = open(argv[0], encoding="utf-8", errors="surrogateescape").read()
    new, n, probs = convert(t)
    sys.stdout.write(new)
    for p in probs:
        print("addr32: " + p, file=sys.stderr)
    print(f"addr32: {n} objects converted", file=sys.stderr)
    return 1 if probs else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
