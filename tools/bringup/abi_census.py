#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""ABI bug-class census of game/PROTOS.tsv against the retail listings
(docs/PROTOS.md "Rules added 2026-10-18").  Run from the port root:

    python tools/bringup/abi_census.py [--game game] [--out out/abi_census] [vvz] [args] [sret]

vvz   every `void-value-zero` row (the stage replaced a used call value by 0
      because the callee's C definition is void): the caller's listing --
      does it read $v0 after the paired jal ('read' / 'returned' = forwards
      it to its own caller / 'dead')? -- and the callee's listing -- what is
      $v0 at its exits (asmflow.exit_class: 'pass' = a call's result passes
      through, a tail jump; 'set'; 'mixed'; 'undef')?  Verdicts:
        BUG-pass     caller reads $v0, the callee forwards the value of a
                     callee whose C definition returns a value (the
                     transporter class: MenuTransIsReady_203870)
        pass-void    ... forwards a callee that is itself void in C (chains)
        scratch      caller reads $v0, the callee leaves a value it computed
                     for something else (mwcc uses $v0 as a temporary): retail
                     read that incidental value
        undef        the callee returns a register nobody set
        dead         retail's caller never reads $v0 (the C use is dead)
        returned     retail's caller forwards $v0 to ITS caller (C `return F()`)
        noasm        no listing / jal not found
args  `manual-call` / `manual-decl` / `missing-zero` / `manual-missing` rows: for
      each call the stage left alone, the argument registers the callee reads
      beyond the ones the C passes, and what retail's caller holds in them at
      the jal (ENTRY = its own incoming value: the HatenaMark class).
sret  local declarations returning u128/struct by value whose definition does
      not (on i686 a u128/struct return is a hidden pointer argument: the
      ActionPacketInitBattleDefeat class).
Writes <out>/<kind>.tsv and prints the verdict counts.
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "bringup"))
sys.path.insert(0, str(PORT / "tools" / "stages"))
import listings  # noqa: E402
import asmflow  # noqa: E402

OVL_BASE = 0x4E9E80
_VRAM = re.compile(r"/\*\s*\w+\s+([0-9A-Fa-f]{8})\s+\w+\s*\*/")


class Listings:
    def __init__(self):
        t = listings.table()
        self.text = {"main": t.get("asm_text") or {}}
        self.text.update(t.get("ovl_text") or {})
        self.by_name = t.get("by_name") or {}
        self.addr = {}
        for img, d in self.text.items():
            idx = {}
            for fn, tx in d.items():
                a = self.by_name.get(fn) if img == "main" else None
                if a is None:
                    m = _VRAM.search(tx)
                    a = int(m.group(1), 16) if m else None
                if a is not None:
                    idx.setdefault(a, fn)
            self.addr[img] = idx
        self._cfg = {}

    def name_addr(self, name, img="main"):
        if img == "main" and name in self.by_name:
            return self.by_name[name]
        m = re.fullmatch(r"(?:\w+_)?(?:func|FUN)_([0-9A-Fa-f]{6,8})", name)
        if m:
            return int(m.group(1), 16)
        if name in self.text.get(img, {}):
            m = _VRAM.search(self.text[img][name])
            if m:
                return int(m.group(1), 16)
        m = re.search(r"_([0-9a-f]{6})$", name)
        if m:
            return int(m.group(1), 16)
        return self.by_name.get(name)

    def at(self, addr, img="main"):
        """[(img, fn)] listings at addr seen from img (an overlay address
        from MAIN: every overlay that has a function there)."""
        if addr is None:
            return []
        if addr < OVL_BASE:
            fn = self.addr["main"].get(addr)
            return [("main", fn)] if fn else []
        imgs = [img] if img != "main" else [i for i in self.text if i != "main"]
        return [(i, self.addr[i][addr]) for i in imgs if addr in self.addr.get(i, {})]

    def cfg(self, img, fn):
        k = (img, fn)
        if k not in self._cfg:
            tx = self.text.get(img, {}).get(fn)
            self._cfg[k] = asmflow.CFG(asmflow.parse_listing(tx)[0]) if tx else None
        return self._cfg[k]


def image_of(rel):
    m = re.match(r"src/overlays/(\w+)/", rel)
    return m.group(1) if m else "main"


_FNHDR = re.compile(r"^(?![ \t#}{/])(?!(?:if|else|while|for|switch|return|typedef|struct|union|enum|"
                    r"case|do|goto|extern|static\s+const|const)\b)[^;=]*?\b(\w+)\s*\(")


class Files:
    """Presumed-line (#line) mapping and enclosing function of a PROTOS.tsv row."""

    def __init__(self, game):
        self.game = game
        self._c = {}

    def lines(self, rel):
        if rel not in self._c:
            p = self.game / rel
            ls = p.read_text(encoding="utf-8", errors="replace").splitlines() if p.exists() else []
            pres, cur = {}, 1
            for i, ln in enumerate(ls):
                m = re.match(r"\s*#\s*line\s+(\d+)", ln)
                if m:
                    cur = int(m.group(1))
                    continue
                pres[cur] = i
                cur += 1
            self._c[rel] = (ls, pres)
        return self._c[rel]

    def nargs(self, rel, line, callee):
        """Argument count of the call of callee nearest the row's line (PROTOS.tsv
        lines are the stage's input lines; later stages may shift them)."""
        ls, pres = self.lines(rel)
        i = pres.get(int(line))
        if i is None:
            return None
        call = re.compile(r"\b%s\s*\(" % re.escape(callee))
        decl = re.compile(r"\s*(extern\s|[\w\s\*]+\b%s\s*\([^)]*\)\s*;)" % re.escape(callee))
        best = None
        for k in range(max(0, i - 12), min(len(ls), i + 12)):
            if call.search(ls[k]) and not decl.match(ls[k]):
                if best is None or abs(k - i) < abs(best - i):
                    best = k
        if best is None:
            return None
        tx = "\n".join(ls[best:best + 30])
        m = call.search(tx)
        k, d, n, any_ = m.end(), 1, 0, False
        while k < len(tx) and d:
            ch = tx[k]
            if ch in "([{":
                d += 1
            elif ch in ")]}":
                d -= 1
            elif ch == "," and d == 1:
                n += 1
            elif not ch.isspace() and d >= 1:
                any_ = True
            k += 1
        return n + 1 if any_ else 0

    def encl(self, rel, line):
        ls, pres = self.lines(rel)
        i = pres.get(int(line))
        if i is None:
            return None
        depth = 0
        for k in range(i, -1, -1):
            s = ls[k]
            depth += s.count("}") - s.count("{")
            m = _FNHDR.match(s)
            if m and depth < 0 and not s.rstrip().endswith(";"):
                return m.group(1)
        return None


def load_defs(game):
    """name -> return type text of every C/C++ definition in game/src (rough)."""
    rx = re.compile(r'^(?:extern\s+"C"\s+)?(?:static\s+|inline\s+)*([A-Za-z_][\w\s\*]*?)\s*\**\s*\b(\w+)\s*\(([^;{}]*)\)\s*(?:\{|$)', re.M)
    defs = {}
    for p in (game / "src").rglob("*"):
        if p.suffix not in (".c", ".cpp"):
            continue
        tx = p.read_text(encoding="utf-8", errors="replace")
        for m in rx.finditer(tx):
            ret, nm = m.group(1).strip(), m.group(2)
            if ret in ("return", "else", "if", "while", "for", "switch", "case", "do", "goto", "sizeof"):
                continue
            k = m.end()
            while k < len(tx) and tx[k] in " \t\r\n":
                k += 1
            if m.group(0).rstrip().endswith("{") or (k < len(tx) and tx[k] == "{"):
                star = "*" if "*" in m.group(0)[:m.start(2) - m.start(0)] else ""
                defs.setdefault(nm, ret + star)
    return defs


def rows_of(game, rules):
    out = []
    for ln in (game / "PROTOS.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        if len(f) >= 5 and f[3] in rules:
            out.append(f)
    return out


def sites(L, F, rel, caller, callee):
    """(cfg, [jal insn indices to callee]) in the caller's listing."""
    img = image_of(rel)
    cand = [(img, caller)] if caller in L.text.get(img, {}) else L.at(L.name_addr(caller, img), img)
    ca = L.name_addr(callee, img)
    for ci, cn in cand:
        cfg = L.cfg(ci, cn)
        if cfg is None:
            continue
        js = [i for i, op, tgt in cfg.calls()
              if tgt == callee or (ca is not None and L.name_addr(tgt, ci) == ca)]
        return cfg, js, ci
    return None, [], img


def callee_class(L, callee, img, defs, depth=0):
    """(cls, passed callees, passed-ret) of the callee's listings."""
    a = L.name_addr(callee, img)
    lst = L.at(a, img) if a is not None else []
    if callee in L.text.get("main", {}) and not lst:
        lst = [("main", callee)]
    if not lst:
        return "nolisting", [], ""
    res = set()
    passed = set()
    for ci, cn in lst:
        cfg = L.cfg(ci, cn)
        cls, calls = asmflow.exit_class(cfg)
        res.add(cls)
        passed |= {(ci, c) for c in calls}
    cls = res.pop() if len(res) == 1 else "mixed-ovl"
    rets = []
    for ci, c in sorted(passed):
        nm = L.at(L.name_addr(c, ci), ci)
        nm = nm[0][1] if nm else c
        rt = defs.get(nm) or defs.get(c)
        if rt is None and depth < 3 and c != "<indirect>":
            sub, _, _ = callee_class(L, c, ci, defs, depth + 1)
            rt = "?" + sub
        rets.append(f"{nm}:{rt}")
    return cls, sorted({c for _, c in passed}), ";".join(rets)


def census_vvz(game, out, L, F, defs):
    rows = rows_of(game, {"void-value-zero"})
    res = []
    for f in rows:
        rel, line, callee = f[0], f[1], f[2]
        caller = F.encl(rel, line)
        cfg, js, img = sites(L, F, rel, caller, callee) if caller else (None, [], image_of(rel))
        uses = sorted({asmflow.reg_after_call(cfg, j) for j in js}) if cfg and js else []
        ccls, passed, prets = callee_class(L, callee, image_of(rel), defs)
        use = "read" if "read" in uses else ("returned" if "returned" in uses else
                                             ("dead" if uses else "noasm"))
        if use == "read":
            if ccls == "pass":
                void = all(re.search(r":(void|\?)", x) and not re.search(r":void\s*\*", x)
                           for x in prets.split(";")) if prets else True
                verdict = "pass-void" if void else "BUG-pass"
            elif ccls in ("set",):
                verdict = "scratch"
            elif ccls == "mixed":
                verdict = "mixed"
            elif ccls == "undef":
                verdict = "undef"
            else:
                verdict = "noasm-callee"
        else:
            verdict = use
        res.append((rel, line, callee, caller or "?", use, ccls, prets, verdict))
    write(out / "vvz.tsv", ("file", "line", "callee", "caller", "caller_v0", "callee_exit",
                            "passed", "verdict"), res)
    return res


def census_args(game, out, L, F, defs):
    rows = rows_of(game, {"manual-call", "manual-decl", "missing-zero", "manual-missing"})
    flow = asmflow.Flow(lambda k: (asmflow.parse_listing(L.text[k.split(":")[0]][k.split(":", 1)[1]])[0]
                                   if k.split(":", 1)[1] in L.text.get(k.split(":")[0], {}) else None),
                        lambda tgt, frm: (lambda r: f"{r[0][0]}:{r[0][1]}" if r else None)(
                            L.at(L.name_addr(tgt, frm.split(":")[0]), frm.split(":")[0])))
    res = []
    seen = set()
    for f in rows:
        rel, line, callee, rule, det = f[:5]
        if rule == "manual-decl":
            # a declaration row: classify every call of the callee in the file
            continue
        caller = F.encl(rel, line)
        key = (rel, caller, callee)
        if key in seen and rule == "manual-call":
            continue
        seen.add(key)
        cfg, js, img = sites(L, F, rel, caller, callee) if caller else (None, [], image_of(rel))
        a = L.name_addr(callee, image_of(rel))
        cl = L.at(a, image_of(rel)) if a is not None else []
        if not cfg or not js or not cl:
            res.append((rel, line, callee, rule, caller or "?", "noasm", "", "", ""))
            continue
        ci, cn = cl[0]
        nargs = F.nargs(rel, line, callee)
        reads, missing = [], []
        for k in range(4):
            reg = "$%d" % (4 + k)
            r = flow.reads(f"{ci}:{cn}", reg)
            if r.startswith("yes"):
                vals = sorted({str(asmflow.value_at_call(cfg, j, reg)) for j in js})
                reads.append(f"a{k}={'|'.join(vals)}")
                if nargs is not None and k >= nargs:
                    missing.append(f"a{k}={'|'.join(vals)}")
        if nargs is None:
            v = "nargs?"
        elif not missing:
            v = "ok"
        elif all("ENTRY" in m for m in missing):
            v = "MISSING-entry"
        else:
            v = "MISSING"
        res.append((rel, line, callee, rule, caller, v, f"C passes {nargs}; " + " ".join(reads),
                    " ".join(missing), det[:120]))
    write(out / "args.tsv", ("file", "line", "callee", "rule", "caller", "verdict", "callee_reads",
                             "missing", "detail"), res)
    return res


def census_sret(game, out, L, F, defs):
    rx = re.compile(r"^\s*(?:extern\s+(?:\"C\"\s+)?)?(u128|s128|qword|__int128[\w\s]*|struct\s+\w+|"
                    r"[A-Z]\w*)\s+(\w+)\s*\([^;{}]*\)\s*;", re.M)
    res = []
    for p in (game / "src").rglob("*"):
        if p.suffix not in (".c", ".cpp"):
            continue
        tx = p.read_text(encoding="utf-8", errors="replace")
        for m in rx.finditer(tx):
            t, nm = m.group(1), m.group(2)
            if not re.match(r"u128|s128|qword|__int128", t):
                continue
            d = defs.get(nm)
            if d is not None and re.match(r"u128|s128|qword|__int128", d):
                continue
            rel = p.relative_to(game).as_posix()
            res.append((rel, nm, t, d or "?"))
    write(out / "sret.tsv", ("file", "callee", "view_ret", "def_ret"), res)
    return res


def write(path, hdr, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\t".join(hdr) + "\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--out", type=Path, default=PORT / "out" / "abi_census")
    ap.add_argument("kinds", nargs="*", default=["vvz", "args", "sret"])
    a = ap.parse_args()
    L = Listings()
    F = Files(a.game)
    defs = load_defs(a.game)
    for k in a.kinds:
        res = {"vvz": census_vvz, "args": census_args, "sret": census_sret}[k](a.game, a.out, L, F, defs)
        col = {"vvz": 7, "args": 5, "sret": 3}[k]
        c = collections.Counter(r[col] if k != "args" else r[5] for r in res)
        print(f"{k}: {len(res)} rows: " + ", ".join(f"{v} {n}" for v, n in c.most_common()))


if __name__ == "__main__":
    main()
