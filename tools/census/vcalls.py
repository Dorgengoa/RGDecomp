#!/usr/bin/env python3
"""Census 2: virtual-call sites through the dummy-class pattern.

Classes are parsed per file (each unit declares its own views).  For every
class with virtual members the census computes:

  slots      vtable order: the first polymorphic base's slots, then this
             class's virtuals in declaration order; a virtual whose name
             matches a base slot overrides it (same slot).  Overloads by
             signature are NOT distinguished (name match only).
  vptr_off   bytes of data members declared BEFORE the first virtual in the
             class that introduces the vptr (or inherited from the
             polymorphic base).  This is the mwcc-matching intent of the
             `u8 pad[0xNN]; virtual ...` idiom; where data members ALSO follow
             the first virtual, `layout` says `data-after-virtual` and the
             real mwcc placement must be confirmed by the P0 vtable probe.

Call sites: `recv->m(` / `recv.m(` where m is a virtual of a class declared
in the same file.  The receiver's class comes from, in order: a cast
`((Cls *)expr)` at the head of the receiver, a declaration `Cls *name` in the
file, `this` inside a member body, or a unique class owning that virtual
(`class_how` = inferred).  obj_off is the constant byte offset when the
receiver is `(Cls *)((u8 *)p + 0xNN)`.

category: dummy_vcall (every virtual of the class is a placeholder name
v<N>/d<N>/f/f<N>/g...) or named_vcall; `dot` in `access` marks a call on an
object (not a pointer) -- clang may devirtualise it.
"""
from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

SIZES = {"u8": 1, "s8": 1, "char": 1, "bool": 1, "u16": 2, "s16": 2, "short": 2,
         "u32": 4, "s32": 4, "int": 4, "f32": 4, "float": 4, "long": 4,
         "unsigned": 4, "signed": 4, "s64": 8, "u64": 8, "f64": 8, "double": 8,
         "u128": 16, "s128": 16}
PLACEHOLDER = re.compile(r"^(v|d|f|g|m|s|vf|slot|fn|vt|virt)_?[0-9A-Fa-f]*$")
HEXNAME = re.compile(r"^(?:v|f|s|slot|vt|vf|fn)_?([0-9A-Fa-f]{1,3})$")


def eval_int(s: str):
    s = s.strip()
    if not re.fullmatch(r"[0-9a-fA-FxX+\-*/() ]+", s):
        return None
    try:
        return int(eval(re.sub(r"\b0+(\d)", r"\1", s), {"__builtins__": {}}))
    except Exception:
        return None


def members(body: str) -> list[str]:
    """Split a class body into top-level member declarations."""
    out, cur, depth, par = [], [], 0, 0
    i = 0
    while i < len(body):
        c = body[i]
        cur.append(c)
        if c == "(":
            par += 1
        elif c == ")":
            par -= 1
        elif c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and par == 0:
                out.append("".join(cur)); cur = []
                # swallow a following ';'
                j = i + 1
                while j < len(body) and body[j] in " \t\r\n":
                    j += 1
                if j < len(body) and body[j] == ";":
                    i = j
        elif c == ";" and depth == 0 and par == 0:
            out.append("".join(cur)); cur = []
        i += 1
    if "".join(cur).strip():
        out.append("".join(cur))
    res = []
    for m in out:
        m = re.sub(r"\b(public|private|protected)\s*:", " ", m).strip()
        if m:
            res.append(m)
    return res


def data_size(decl: str):
    """Size of a data-member declaration, or None if unknown."""
    d = re.sub(r"\b(const|volatile|mutable|unsigned|signed|struct|class|union|enum)\b",
               lambda m: "" if m.group(1) in ("const", "volatile", "mutable", "struct", "class", "union", "enum") else m.group(1), decl)
    d = d.rstrip(";").strip()
    if ":" in d and not "::" in d:
        return None  # bitfield
    m = re.match(r"(\w+)\s*(.*)$", d, re.S)
    if not m:
        return None
    typ, rest = m.group(1), m.group(2)
    total = 0
    for dec in re.split(r",(?![^\[]*\])", rest):
        dec = dec.strip()
        if not dec:
            continue
        ptr = dec.startswith("*") or dec.startswith("(*") or "(*" in dec
        size = 4 if ptr else SIZES.get(typ)
        if size is None:
            return None
        for dim in re.findall(r"\[([^\]]*)\]", dec):
            v = eval_int(dim)
            if v is None:
                return None
            size *= v
        total += size
    return total


class Cls:
    def __init__(self, name):
        self.name = name
        self.bases = []
        self.slots: list[str] = []
        self.own_virtuals: list[str] = []
        self.vptr_off = None
        self.layout = ""
        self.virtual_dtor = False


def parse_classes(sf: S.SrcFile) -> dict[str, Cls]:
    out: dict[str, Cls] = {}
    for f in sf.funcs:
        if f.kind != "class":
            continue
        hdr = f.header.strip()
        m = re.search(r"\b(class|struct)\s+(\w+)\s*(?::\s*([^{]*))?$", hdr)
        if not m:
            continue
        c = Cls(m.group(2))
        if m.group(3):
            c.bases = [re.sub(r"\b(public|private|protected|virtual)\b", "", b).strip()
                       for b in m.group(3).split(",")]
        body = sf.nostr[f.body_open + 1:f.body_close]
        mems = members(body)
        before = 0
        unknown = False
        seen_virtual = False
        data_after = False
        for mm in mems:
            flat = " ".join(mm.split())
            if flat.startswith("virtual") or re.match(r"(inline\s+)?virtual\b", flat):
                seen_virtual = True
                sig = flat.split("{")[0]
                nm = re.search(r"(~?\w+)\s*\(", sig)
                name = nm.group(1) if nm else "?"
                if name.startswith("~"):
                    c.virtual_dtor = True
                c.own_virtuals.append(name)
                continue
            if "(" in flat.split("=")[0] and not re.search(r"\(\s*\*", flat):
                continue  # non-virtual member function / ctor
            if flat.startswith(("typedef", "static", "friend", "enum", "using")):
                continue
            if re.match(r"(struct|union|class)\b[^;]*\{", flat):
                sz = None
            else:
                sz = data_size(flat)
            if seen_virtual:
                data_after = True
                continue
            if sz is None:
                unknown = True
            else:
                before += sz
        c.layout = ("data-after-virtual" if data_after else "") + \
                   (" unknown-member-size" if unknown else "")
        c.vptr_off = None if unknown else before
        out[c.name] = c
    # resolve slots with single inheritance through polymorphic bases
    def resolve(c: Cls, depth=0):
        if c.slots or depth > 10:
            return
        base = None
        for b in c.bases:
            bc = out.get(b)
            if bc:
                resolve(bc, depth + 1)
                if bc.slots:
                    base = bc
                    break
        slots = list(base.slots) if base else []
        if base:
            c.vptr_off = base.vptr_off
            c.layout = (c.layout + " via-base:" + base.name).strip()
        for v in c.own_virtuals:
            if v in slots:
                continue
            slots.append(v)
        c.slots = slots
        if len([b for b in c.bases if b in out]) > 1:
            c.layout = (c.layout + " multiple-inheritance").strip()
    for c in out.values():
        resolve(c)
    return {k: v for k, v in out.items() if v.slots}


CALL = re.compile(r"(->|\.)\s*(~?\w+)\s*\(")


def receiver(s: str, end: int) -> str:
    """Text of the postfix expression ending just before `end`."""
    k = end - 1
    while k >= 0 and s[k] in " \t\r\n":
        k -= 1
    start = k + 1
    while k >= 0:
        if s[k] in ")]":
            op, cl = ("(", ")") if s[k] == ")" else ("[", "]")
            depth = 0
            while k >= 0:
                if s[k] == cl:
                    depth += 1
                elif s[k] == op:
                    depth -= 1
                    if depth == 0:
                        break
                k -= 1
            k -= 1
            start = k + 1
            # identifier before '(' / '[' (call or index)
            while k >= 0 and (s[k].isalnum() or s[k] == "_"):
                k -= 1
            start = k + 1
        elif s[k].isalnum() or s[k] == "_":
            while k >= 0 and (s[k].isalnum() or s[k] == "_"):
                k -= 1
            start = k + 1
        else:
            break
        j = k
        while j >= 0 and s[j] in " \t\r\n":
            j -= 1
        if j >= 1 and s[j - 1:j + 1] == "->":
            k = j - 2
            continue
        if j >= 0 and s[j] == "." and not (j >= 1 and s[j - 1].isdigit()):
            k = j - 1
            continue
        break
    return s[start:end].strip()


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    rows = []
    for sf in snap.all():
        if "virtual" not in sf.nostr:
            continue
        classes = parse_classes(sf)
        if not classes:
            continue
        owners: dict[str, list[str]] = {}
        for c in classes.values():
            for v in c.slots:
                owners.setdefault(v, []).append(c.name)
        decl_rx = re.compile(r"\b(" + "|".join(map(re.escape, classes)) + r")\s*\*\s*(?:const\s+)?(\w+)")
        decls = {}
        for m in decl_rx.finditer(sf.nostr):
            decls.setdefault(m.group(2), []).append((m.start(), m.group(1)))
        for m in CALL.finditer(sf.nostr):
            meth = m.group(2)
            if meth not in owners:
                continue
            enc = sf.enclosing(m.start())
            if enc is None or m.start() < enc.body_open or enc.kind == "class":
                continue  # inside a declaration, not a body
            recv = receiver(sf.nostr, m.start())
            cls, how = None, ""
            cm = re.match(r"\(*\s*(?:struct\s+|class\s+)?(\w+)\s*\*\s*\)", recv.lstrip("("))
            if cm and cm.group(1) in classes:
                cls, how = cm.group(1), "cast"
            elif re.fullmatch(r"\w+", recv) and recv in decls:
                prior = [d for d in decls[recv] if d[0] < m.start()] or decls[recv]
                cand = prior[-1][1]
                if cand in classes:
                    cls, how = cand, "decl"
            elif recv == "this" and enc.kind == "member":
                pass
            if cls is None or meth not in classes[cls].slots:
                own = owners[meth]
                if len(set(own)) == 1:
                    cls, how = own[0], (how + "+" if how else "") + "inferred"
                else:
                    cls, how = own[-1], "ambiguous:" + ",".join(sorted(set(own)))
            c = classes[cls]
            slot = c.slots.index(meth) if meth in c.slots else -1
            off = re.search(r"\(\s*u8\s*\*\s*\)\s*\(?\s*([\w>.\-\[\]]+)\s*\)?\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)*\s*$", recv)
            dummy = all(PLACEHOLDER.match(v) or v.startswith("~") for v in c.slots)
            hn = HEXNAME.match(meth)
            name_check = ""
            if hn and slot >= 0:
                t = hn.group(1)
                if t.isdigit() and int(t) == slot:
                    name_check = "name=slot"
                elif int(t, 16) == 8 + 4 * slot:
                    name_check = "name=byte(8+4*slot)"
                elif int(t, 16) == 4 * slot:
                    name_check = "name=byte(4*slot)"
                else:
                    name_check = "differs"
            rows.append(dict(
                file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                image=sf.image, lib=sf.lib,
                category="dummy_vcall" if dummy else "named_vcall",
                cls=cls, method=meth, slot=slot, slot_byte=f"0x{8 + slot * 4:X}" if slot >= 0 else "", name_check=name_check,
                nslots=len(c.slots),
                vptr_off=("" if c.vptr_off is None else f"0x{c.vptr_off:X}"),
                obj_off=(off.group(2) if off else ""),
                access="dot" if m.group(1) == "." else "arrow",
                class_how=how, layout=(c.layout + (" virtual-dtor" if c.virtual_dtor else "")).strip(),
                receiver=S.snippet(recv, 120)))
    rows.sort(key=lambda r: (r["image"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["cls", "method", "slot", "slot_byte", "name_check", "nslots", "vptr_off",
                          "obj_off", "access", "class_how", "layout", "receiver"]
    out = Path(a.out) / "vcalls.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "vcalls", {
        "slot_byte": "8 + 4*slot (mwcc vtable: 8-byte header before slot 0; see name_check)"}))
    print(Counter((r["category"], r["image"]) for r in rows))
    print(Counter(r["class_how"].split(":")[0] for r in rows))
    print("name_check", Counter(r["name_check"] for r in rows))
    print(f"wrote {out} ({len(rows)} rows, {len({r['file'] for r in rows})} files)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
