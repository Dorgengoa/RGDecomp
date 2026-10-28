# SPDX-License-Identifier: CC0-1.0
"""protos_irabi.py: i686 ABI of a call vs its callee's definition, read from clang's own IR.

The protos stage decides ABI identity from its C parser (`_abi_diff`); a row it cannot decide
(`manual-call`, `manual-decl`: struct / union / macro / unknown types, duplicate definitions)
is left to a human.  This tool decides those rows mechanically: it compiles the caller file
and the definition's file with the build's exact command (`compile_commands.json`, override
file when one replaces the unit) to LLVM IR (`-S -emit-llvm`) and compares, per call site,
the lowered i686-windows-msvc signature of the call instruction (the caller's view) with the
`define` of the callee:

    stack slots     offset / size / kind (i = integer or pointer, f = float, d = double,
                    q = 8-byte integer, b<N> = byval aggregate) of every argument
    return          void / i<N> (with zeroext/signext) / float / double / sret

Verdicts per call (`verdict` column):
    OK              same slots (int vs pointer, int of any width in a 4-byte slot are one
                    slot) and a compatible return
    OK-extra        the view passes MORE slots (cdecl: the caller pops them, harmless)
    OK-retunused    return differs but the call's value is never used in the IR
    BUG-missing     the view passes fewer slots than the definition reads (the callee reads
                    a stale stack word on i686); `reads` says whether the callee's retail
                    listing reads that EE register (asmflow) -- not read = harmless
    BUG-kind        a slot differs in kind (float vs int bits) or size
    BUG-retwidth    the definition returns a 1/2-byte integer (AL/AX only on i686) and the
                    view reads a wider integer: the upper EAX bytes are garbage
    BUG-retclass    float/double vs integer return (x87 ST0 vs EAX)
    BUG-sret        hidden struct-return pointer on one side only
    nodef / nocall  the definition / the call was not found in the IR

    python tools/bringup/protos_irabi.py [--game game] [--build build/sweep-i686]
        [--rules manual-call,manual-decl] [--out out/protos2/irabi.tsv] [--jobs 4]

IR files are cached under out/protos2/ir/ (keyed by command + source hash).  Used for the
2026-10-25 protos manual-row close-out (docs/PROTOS.md "Manual rows closed").
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import json
import re
import shlex
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
N = lambda s: s.replace(chr(92), "/")  # noqa: E731

_DECL = re.compile(r'^declare\s+(?P<pre>[^@]*?)@(?P<name>"[^"]+"|[\w.$]+)\((?P<params>.*)\)', re.M)
_DEF = re.compile(r'^define\s+(?P<pre>[^@]*?)@(?P<name>"[^"]+"|[\w.$]+)\((?P<params>.*)\)\s*(?P<post>[^{]*)\{', re.M)
_CALL = re.compile(r'(?:(?P<lhs>%[\w.]+)\s*=\s*)?(?:tail\s+|musttail\s+|notail\s+)?(?:call|invoke)\s+'
                   r'(?P<pre>[^@(]*?)@(?P<name>"[^"]+"|[\w.$]+)\((?P<args>.*?)\)(?=\s*(?:#\d+|$|to\s|,\s*!))')
_TYPEDEF = re.compile(r'^(%[\w."$:<>,\- ]+?|%"[^"]+")\s*=\s*type\s+(.*)$', re.M)


def base_name(sym):
    s = sym.strip('"')
    if s.startswith("?"):
        m = re.match(r"\?([\w$]+)@", s)
        return m.group(1) if m else s
    return s.lstrip("_") if False else s


def split_top(s):
    out, d, cur = [], 0, []
    for ch in s:
        if ch in "([{<":
            d += 1
        elif ch in ")]}>":
            d -= 1
        if ch == "," and d == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur).strip())
    return out


class Types:
    """Sizes / alignments of IR types under the i686-pc-windows-msvc datalayout."""

    def __init__(self, ir):
        self.defs = {}
        for m in _TYPEDEF.finditer(ir):
            self.defs[m.group(1).strip()] = m.group(2).strip()
        self._c = {}

    def sa(self, t):
        t = t.strip()
        if t in self._c:
            return self._c[t]
        r = self._sa(t)
        self._c[t] = r
        return r

    def _sa(self, t):
        if t in ("i1", "i8"):
            return 1, 1
        if t == "i16":
            return 2, 2
        if t in ("i32", "ptr", "float") or t.endswith("*"):
            return 4, 4
        if t in ("i64", "double"):
            return 8, 8
        if t == "x86_fp80":
            return 10, 4
        if t == "i128" or t == "fp128":
            return 16, 16
        m = re.fullmatch(r"<(\d+) x (.+)>", t)
        if m:
            s, a = self.sa(m.group(2))
            return s * int(m.group(1)), max(a, min(16, s * int(m.group(1))))
        m = re.fullmatch(r"\[(\d+) x (.+)\]", t)
        if m:
            s, a = self.sa(m.group(2))
            return s * int(m.group(1)), a
        if t.startswith("%"):
            body = self.defs.get(t)
            if body is None or body == "opaque":
                return None, None
            return self.sa(body)
        packed = t.startswith("<{")
        if t.startswith("{") or packed:
            inner = t[2:-2] if packed else t[1:-1]
            off, al = 0, 1
            for f in split_top(inner):
                s, a = self.sa(f)
                if s is None:
                    return None, None
                a = 1 if packed else a
                off = (off + a - 1) // a * a + s
                al = max(al, a)
            return (off + al - 1) // al * al, al
        return None, None


def _attr_type(s, attr):
    m = re.search(attr + r"\(", s)
    if not m:
        return None
    k, d = m.end(), 1
    while d:
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
        k += 1
    return s[m.end():k - 1]


def param_slots(items, types):
    """[(offset, size, kind)] of an IR parameter/argument list; plus sret flag."""
    slots, off, sret = [], 0, False
    for it in items:
        if it == "...":
            slots.append((off, 0, "..."))
            continue
        ty = it.split()[0]
        if "sret(" in it:
            sret = True
            continue        # hidden pointer: compared through the return
        if "byval(" in it:
            bt = _attr_type(it, "byval")
            s, _a = types.sa(bt)
            s = s if s is not None else -1
            slots.append((off, s, f"b{s}"))
            off += (max(s, 4) + 3) // 4 * 4
            continue
        if "inalloca" in it:
            slots.append((off, -1, "inalloca"))
            continue
        if ty in ("float",):
            k, s = "f", 4
        elif ty == "double":
            k, s = "d", 8
        elif ty == "i64":
            k, s = ("q" if "noundef" in it else "b8"), 8     # no noundef: a coerced aggregate
        elif ty == "ptr" and "dead_on_return" in it:
            k, s = "ind", 4     # MSVC x86: an over-aligned aggregate passed by address
        elif ty in ("i1", "i8", "i16", "i32", "ptr") or ty.endswith("*"):
            k, s = ("i" if "noundef" in it or ty == "ptr" else "b4"), 4
        else:
            s, _a = types.sa(ty)
            k = "a" + str(s)
            s = s if s is not None else -1
        slots.append((off, s, k))
        off += (max(s, 4) + 3) // 4 * 4
    return slots, sret


def ret_of(pre):
    """Return descriptor of the text before `@name(` in a define/call."""
    toks = pre.split()
    zext = "zeroext" in toks
    sext = "signext" in toks
    ty = None
    for t in toks:
        if re.fullmatch(r"(void|i\d+|float|double|ptr|x86_fp80|%[\w.\"]+|\{.*|<.*|\[.*)", t):
            ty = t
    if ty is None:
        # struct literal returns: take the brace group
        m = re.search(r"(\{[^}]*\}|<\{[^}]*\}>)", pre)
        ty = m.group(1) if m else "?"
    return ty, ("z" if zext else "s" if sext else "")


def ret_desc(ty, ext, sret, types):
    if sret:
        return "sret"
    if ty == "void":
        return "void"
    if ty in ("float", "double"):
        return ty
    if ty == "ptr":
        return "i32"
    m = re.fullmatch(r"i(\d+)", ty)
    if m:
        w = int(m.group(1))
        if w < 32:
            return f"i{max(w, 8)}{ext}"
        return f"i{w}"
    s, _a = types.sa(ty)
    return f"agg{s}"


class IRCache:
    def __init__(self, build, game, cache, ignore_overrides=False):
        self.ignore_overrides = ignore_overrides
        self.cmds = {}
        for c in json.load(open(Path(build) / "compile_commands.json")):
            self.cmds[N(c["file"]).lower()] = (c["command"], c["directory"])
        self.game = Path(game).resolve()
        self.cache = Path(cache).resolve()
        self.cache.mkdir(parents=True, exist_ok=True)

    def source_for(self, rel):
        """The file the build compiles for game rel (override if it replaces the unit)."""
        o = PORT / "overrides" / rel
        g = self.game / rel
        if self.ignore_overrides:
            return g
        if o.exists():
            return o
        for p in (o, g):
            if N(str(p.resolve())).lower() in self.cmds:
                return p
        return o if o.exists() else g

    def ir(self, rel, keep=True):
        src = rel if isinstance(rel, Path) else self.source_for(rel)
        key = N(str(src.resolve())).lower()
        if key not in self.cmds:
            # fall back to a sibling's command with the file swapped
            twin = key.replace("/port/overrides/", "/port/game/")   # an override made after
            sib = twin if twin in self.cmds else next(                # the build's configure
                (k for k in self.cmds if k.endswith(src.suffix) and "/port/game/src/" in k), None)
            if sib is None:
                return None
            cmd, cwd = self.cmds[sib]
            cmd = cmd.replace(self.cmds[sib][0].split()[-1], str(src))
        else:
            cmd, cwd = self.cmds[key]
        data = src.read_bytes()
        h = hashlib.sha1(cmd.encode() + data).hexdigest()[:16]
        out = self.cache / f"{h}.ll"
        if keep is False:
            summ = self.cache / "sum" / f"{h}.json"
            if summ.exists():
                return json.loads(summ.read_text())
        if not out.exists():
            argv = shlex.split(cmd, posix=False)
            argv = [a.strip('"') for a in argv]
            # drop -o X and -c, emit IR
            res, skip = [], False
            for a in argv:
                if skip:
                    skip = False
                    continue
                if a == "-o":
                    skip = True
                    continue
                if a == "-c" or a.startswith("-flto"):
                    continue
                res.append(a)
            res = [r for r in res if not re.match(r"-O\d", r)] + ["-O0", "-Xclang", "-disable-O0-optnone",
                                                                   "-S", "-emit-llvm", "-o", str(out)]
            if N(str(src)).lower() not in [N(r).lower() for r in res]:
                res.append(str(src))
            p = subprocess.run(res, cwd=cwd, capture_output=True, text=True)
            if p.returncode != 0:
                (self.cache / f"{h}.err").write_text(p.stderr[-4000:])
                return None
        ir = out.read_text(encoding="utf-8", errors="replace")
        if keep is False:
            sm = summarize(ir)
            summ.parent.mkdir(parents=True, exist_ok=True)
            summ.write_text(json.dumps(sm))
            out.unlink()
            return sm
        return ir


def parse_ir(ir):
    types = Types(ir)
    defs = {}
    for m in _DEF.finditer(ir):
        nm = base_name(m.group("name"))
        ty, ext = ret_of(m.group("pre"))
        slots, sret = param_slots(split_top(m.group("params")), types)
        defs.setdefault(nm, (ret_desc(ty, ext, sret, types), slots))
    return types, defs


_GLOBAL_CXX = re.compile(r'^"?\?([A-Za-z_]\w*)@@Y')


def strict_name(sym):
    """C name, or the name of a global (non-member) C++ function; else None."""
    s = sym.strip('"')
    if not s.startswith("?"):
        return s
    m = _GLOBAL_CXX.match(sym)
    return m.group(1) if m else None


def summarize(ir):
    """Per file: defs {name: [ret, slots, internal]} and calls [[name, ret, slots, used]]."""
    types = Types(ir)
    defs = {}
    for m in _DEF.finditer(ir):
        nm = strict_name(m.group("name"))
        if nm is None:
            continue
        ty, ext = ret_of(m.group("pre"))
        slots, sret = param_slots(split_top(m.group("params")), types)
        internal = bool(re.search(r"\b(internal|private|linkonce_odr|weak_odr)\b", m.group("pre")))
        defs.setdefault(nm, [ret_desc(ty, ext, sret, types), slots, internal])
    calls = []
    for body in function_bodies(ir):
        for ln in body.splitlines():
            if "call" not in ln or "@" not in ln:
                continue
            m = _CALL.search(ln)
            if not m or m.group("name").startswith("llvm."):
                continue
            nm = strict_name(m.group("name"))
            if nm is None:
                continue
            ty, ext = ret_of(m.group("pre"))
            slots, sret = param_slots(split_top(m.group("args")), types)
            calls.append([nm, ret_desc(ty, ext, sret, types), slots, used(body, m.group("lhs")),
                          narrowed(body, m.group("lhs"))])
    return {"defs": defs, "calls": calls}


def parse_decls(ir):
    types = Types(ir)
    out = {}
    for m in _DECL.finditer(ir):
        ty, ext = ret_of(m.group("pre"))
        slots, sret = param_slots(split_top(m.group("params")), types)
        out.setdefault(base_name(m.group("name")), (ret_desc(ty, ext, sret, types), slots))
    return out


PROVIDER_HEADERS = ("src/crt/crt.h", "src/sce/vu0/sce_vu0.h")


def provider_decls(irc, names, cache):
    """IR declarations of names from the port's provider headers (protos PROVIDER_HEADERS)."""
    hdr = [h for h in PROVIDER_HEADERS if (PORT / h).exists()]
    have = set()
    for h in hdr:
        tx = (PORT / h).read_text(encoding="utf-8", errors="replace")
        have |= {n for n in names if re.search(r"\b%s\s*\(" % re.escape(n), tx)}
    if not have:
        return {}
    src = Path(cache) / "provider_probe.c"
    nl = chr(10)
    body = "".join(f'#include "{(PORT / h).as_posix()}"' + nl for h in hdr)
    body += "void *rgp_irabi_probe[] = {" + nl + "".join(f"  (void *)&{n}," + nl for n in sorted(have)) + "};" + nl
    if not src.exists() or src.read_text() != body:
        src.write_text(body)
    ir = irc.ir(src)
    return parse_decls(ir) if ir else {}


def calls_in(ir, callee, types):
    out = []
    for ln in ir.splitlines():
        if "@" not in ln or callee not in ln:
            continue
        m = _CALL.search(ln)
        if not m or base_name(m.group("name")) != callee:
            continue
        ty, ext = ret_of(m.group("pre"))
        slots, sret = param_slots(split_top(m.group("args")), types)
        out.append((m.group("lhs"), ret_desc(ty, ext, sret, types), slots))
    return out, ir


def function_bodies(ir):
    """The text of each `define .. { .. }` (SSA value names are per function)."""
    out, cur = [], None
    for ln in ir.splitlines():
        if ln.startswith("define "):
            cur = [ln]
        elif cur is not None:
            cur.append(ln)
            if ln.startswith("}"):
                out.append(chr(10).join(cur))
                cur = None
    return out


def narrowed(ir, lhs):
    """Width N when every use of the call result lhs is `trunc .. lhs to iN` (the C
    casts the value back to the definition's narrow type: protos `ret-narrow`), else None."""
    if not lhs:
        return None
    pat = re.compile(re.escape(lhs) + r"(?![\w.])")
    ws = []
    for ln in ir.splitlines():
        if not pat.search(ln) or ln.lstrip().startswith(lhs + " ="):
            continue
        m = re.search(r"=\s*trunc i32 " + re.escape(lhs) + r" to i(\d+)", ln)
        if not m:
            return None
        ws.append(int(m.group(1)))
    return max(ws) if ws else None


def used(ir, lhs):
    if not lhs:
        return False
    return re.search(re.escape(lhs) + r"\b(?!\s*=)", ir.split(lhs + " =", 1)[1]) is not None \
        if (lhs + " =") in ir else False


def _words(slots):
    """Stack words of a slot list: what the callee reads at each 4-byte offset.
    Integer / pointer / byval aggregate bytes are plain bits ('w'); a float is 'f',
    a double 'd' (two words); an aggregate passed by address 'ind'."""
    out = []
    for off, sz, k in slots:
        if k == "...":
            out.append("...")
        elif k == "f":
            out.append("f")
        elif k == "d":
            out += ["d", "d"]
        elif k == "ind":
            out.append("ind")
        elif k in ("i",):
            out.append("w")
        elif k == "q":
            out += ["q", "q"]
        elif sz is not None and sz > 0:
            out += ["a"] * ((sz + 3) // 4)     # aggregate bytes: bits, any integer word
        else:
            out.append("?" + k)
    return out


def compare(dret, dslots, cret, cslots, val_used):
    v = []
    va = "..." in [s[2] for s in dslots]
    dw = [w for w in _words(dslots) if w != "..."]
    cw = [w for w in _words(cslots) if w != "..."]
    for i, w in enumerate(dw):
        if i >= len(cw):
            v.append(("BUG-missing", f"word {i} ({w}) not passed"))
            break
        if cw[i] != w and not ("a" in (cw[i], w) and {cw[i], w} <= {"a", "w", "q"}):
            v.append(("BUG-kind", f"word {i}: view {cw[i]} vs def {w}"))
            break
    if not v and [s[2] for s in dslots] != [s[2] for s in cslots][:len(dslots)]:
        v.append(("OK-bits", "same stack words, different spelling ("
                  + ",".join(s[2] for s in cslots) + " vs " + ",".join(s[2] for s in dslots) + ")"))
    extra = len(cw) > len(dw) and not va
    # return
    if dret != cret:
        if cret == "void":
            if dret in ("float", "double"):
                v.append(("BUG-retclass", f"view void, def {dret}: x87 ST0 left"))
        elif dret == "sret" and cret == "i32" and len(cslots) == len(dslots) + 1:
            v.append(("OK-sretptr", "view reads the out pointer: MSVC returns the sret pointer in EAX"))
        elif dret == "sret" or cret == "sret":
            v.append(("BUG-sret", f"view {cret}, def {dret}"))
        elif not val_used:
            v.append(("OK-retunused", f"view {cret}, def {dret}"))
        elif dret == "void":
            v.append(("BUG-retvoid", f"view {cret}, def void"))
        elif ("float" in (dret, cret) or "double" in (dret, cret)):
            v.append(("BUG-retclass", f"view {cret}, def {dret}"))
        else:
            dwid = int(re.match(r"i(\d+)", dret).group(1)) if dret.startswith("i") else 32
            cwid = int(re.match(r"i(\d+)", cret).group(1)) if cret.startswith("i") else 32
            if dwid < cwid:
                v.append(("BUG-retwidth", f"view {cret}, def {dret}"))
            elif dwid > cwid:
                v.append(("OK-retnarrow", f"view {cret}, def {dret}"))
            elif dret.startswith("agg") or cret.startswith("agg"):
                v.append(("BUG-retagg", f"view {cret}, def {dret}"))
    if not v:
        return ("OK-extra" if extra else "OK"), ""
    bugs = [x for x in v if x[0].startswith("BUG")]
    if bugs:
        return bugs[0][0], "; ".join(d for _, d in v)
    return v[0][0], "; ".join(d for _, d in v)


def callee_in(ir, name):
    return name in parse_ir(ir)[1]


def find_def_files(game, names):
    """name -> [rel] of files whose text defines name (regex; C or C++)."""
    want = set(names)
    out = {}
    # port providers first (overrides/ and missing/ definitions: the C port of an
    # excluded asm unit), then the corpus by file stem
    for root in (PORT / "overrides" / "src", PORT / "missing" / "src"):
        if root.exists():
            for p in root.rglob("*"):
                if p.suffix in (".c", ".cpp") and p.stem in want:
                    out.setdefault(p.stem, []).append(p)
    for p in (game / "src").rglob("*"):
        if p.suffix in (".c", ".cpp") and p.stem in want:
            out.setdefault(p.stem, []).append(p.relative_to(game).as_posix())
    rx = re.compile(r"\b(\w+)\s*\([^;{}]*\)\s*(?:const\s*)?\{")
    for p in (game / "src").rglob("*"):
        if p.suffix not in (".c", ".cpp"):
            continue
        tx = p.read_text(encoding="utf-8", errors="replace")
        hit = [n for n in want if n in tx]
        if not hit:
            continue
        for m in rx.finditer(tx):
            if m.group(1) in want and p.relative_to(game).as_posix() not in out.get(m.group(1), []):
                out.setdefault(m.group(1), []).append(p.relative_to(game).as_posix())
    return out


def image_of(path):
    m = re.search(r"/src/overlays/(\w+)/", N(str(path)))
    return m.group(1) if m else "main"


def audit_all(a):
    """Every direct call in every compiled unit vs its callee's definition."""
    irc = IRCache(a.build, a.game, a.cache)
    srcs = sorted({k for k in irc.cmds if any(t in k for t in ("/port/game/src/", "/port/overrides/src/",
                                                                 "/port/missing/src/"))})
    print(f"protos_irabi --all: {len(srcs)} units", flush=True)
    done = [0]

    def one(k):
        r = irc.ir(Path(k), keep=False)
        done[0] += 1
        if done[0] % 1000 == 0:
            print(f"  {done[0]} / {len(srcs)}", flush=True)
        return k, r
    with cf.ThreadPoolExecutor(a.jobs) as ex:
        sums = dict(ex.map(one, srcs))
    glob = {}
    for k, sm in sums.items():
        if not sm:
            continue
        for nm, (ret, slots, internal) in sm["defs"].items():
            if not internal:
                glob.setdefault(nm, []).append((image_of(k), k, ret, slots))
    rows, tally = [], {}
    for k, sm in sums.items():
        if not sm:
            rows.append((k, "", "noir", "", "", ""))
            continue
        img = image_of(k)
        seen = {}
        for call in sm["calls"]:
            nm, cret, cslots, val = call[:4]
            nw = call[4] if len(call) > 4 else None
            if nm in sm["defs"]:
                ret, slots, _i = sm["defs"][nm]
                dk = k
            else:
                cand = glob.get(nm)
                if not cand:
                    continue
                pick = [c for c in cand if c[0] == img] or [c for c in cand if c[0] == "main"] or cand
                _img, dk, ret, slots = pick[0]
            v, why = compare(ret, slots, cret, cslots, val)
            if v == "BUG-retwidth" and nw is not None and ret.startswith("i") and                     nw <= int(re.match(r"i(\d+)", ret).group(1)):
                v, why = "OK-retnarrowed", why + f"; every use truncates to i{nw}"
            tally[v] = tally.get(v, 0) + 1
            if v.startswith("BUG") or v.startswith("OK-ret") or v == "OK-sretptr":
                key = (nm, v, why)
                if key in seen:
                    continue
                seen[key] = 1
                rows.append((k, nm, v, dk, why, f"def {ret} {[x[2] for x in slots]} view {cret} "
                                                f"{[x[2] for x in cslots]}"))
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as fo:
        fo.write("file\tcallee\tverdict\tdef_file\twhy\tshapes\n")
        for r in sorted(rows):
            fo.write("\t".join(str(x) for x in r) + "\n")
    print("calls: " + ", ".join(f"{n} {v}" for v, n in sorted(tally.items(), key=lambda x: -x[1])))
    return 0


def analyse(game, build, cache, jobs=4, rules=("manual-call", "manual-decl"),
            ignore_overrides=False):
    """[(file, callee, verdict, def_file, calls, why, shapes)] for every (file, callee) pair
    of the given PROTOS.tsv rules.  ignore_overrides: compile the game file even where an
    override replaces it (the ctest control)."""
    game = Path(game)
    rows = [l.rstrip("\n").split("\t") for l in open(game / "PROTOS.tsv", encoding="utf-8")][1:]
    rows = [r for r in rows if len(r) >= 5 and r[3] in set(rules)]
    pairs = sorted({(r[0], r[2]) for r in rows})
    callees = sorted({c for _, c in pairs})
    deff = find_def_files(game, callees)
    irc = IRCache(build, game, cache, ignore_overrides)
    files = sorted({f for f, _ in pairs} | {f for c in callees for f in deff.get(c, [])}, key=str)
    with cf.ThreadPoolExecutor(jobs) as ex:
        irs = dict(zip(files, ex.map(irc.ir, files)))
    pdecl = provider_decls(irc, [c for c in callees if not any(
        irs.get(df) and callee_in(irs[df], c) for df in deff.get(c, []))], cache)
    res = []
    for f, callee in pairs:
        ir = irs.get(f)
        dd = None
        for df in deff.get(callee, []):
            if irs.get(df):
                _t, defs = parse_ir(irs[df])
                if callee in defs:
                    dd = (df, defs[callee])
                    break
        if dd is None and callee in pdecl:
            dd = ("provider header", pdecl[callee])
        if ir is None:
            res.append((f, callee, "noir", "", "", "", ""))
            continue
        cs = [c for c in summarize(ir)["calls"] if c[0] == callee]
        if dd is None:
            res.append((f, callee, "nodef", "", f"{len(cs)} calls", "", ""))
            continue
        df, (dret, dslots) = dd
        if not cs:
            res.append((f, callee, "nocall", str(df), "", "", f"def {dret} {dslots}"))
            continue
        vs = []
        for _nm, cret, cslots, val, nw in cs:
            v = compare(dret, dslots, cret, cslots, val)
            if v[0] == "BUG-retwidth" and nw is not None and dret.startswith("i") and \
                    nw <= int(re.match(r"i(\d+)", dret).group(1)):
                v = ("OK-retnarrowed", v[1] + f"; every use truncates to i{nw}")
            vs.append(v)
        worst = sorted(vs, key=lambda x: (not x[0].startswith("BUG"), x[0]))[0]
        res.append((f, callee, worst[0], str(df), f"{len(cs)} calls", worst[1],
                    f"def {dret} {[x[2] for x in dslots]} view {cs[0][1]} {[x[2] for x in cs[0][2]]}"))
    return res


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--build", default=str(PORT / "build" / "sweep-i686"))
    ap.add_argument("--rules", default="manual-call,manual-decl")
    ap.add_argument("--out", default=str(PORT / "out" / "protos2" / "irabi.tsv"))
    ap.add_argument("--cache", default=str(PORT / "out" / "protos2" / "ir"))
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--ignore-overrides", action="store_true",
                    help="compile the game file even where an override replaces it")
    ap.add_argument("--all", action="store_true",
                    help="every direct call of every compiled unit (game/overrides/missing)")
    a = ap.parse_args(argv)
    if a.all:
        return audit_all(a)
    res = analyse(Path(a.game), a.build, a.cache, a.jobs, set(a.rules.split(",")),
                  a.ignore_overrides)
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    with open(a.out, "w", encoding="utf-8", newline="\n") as fo:
        fo.write("file\tcallee\tverdict\tdef_file\tcalls\twhy\tshapes\n")
        for r in res:
            fo.write("\t".join(str(x) for x in r) + "\n")
    import collections
    c = collections.Counter(r[2] for r in res)
    print(f"protos_irabi: {len(res)} (file, callee) pairs: " + ", ".join(f"{n} {v}" for v, n in c.most_common()))
    return 0


if __name__ == "__main__":
    sys.exit(main())
