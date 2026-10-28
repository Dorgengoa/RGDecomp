# SPDX-License-Identifier: CC0-1.0
"""Generate the timing-record site table from probe.py's `timing` hook set.

    python tools/trace/gen_timing_sites.py [--src game/src] [--tsv tools/trace/timing_sites.tsv]
                                           [--h build/.../rg_timing_sites.h] [--check]

probe.py's build_timing_hooks() is the one definition of the timing contract
(docs/TIMING-REFERENCE.md). This script runs it against a recording stand-in
for probe.Hooks (no ELF, no PCSX2) and writes:

  --tsv  one row per site: id, PCSX2 site name, hook kind, PS2 address, the
         game function at that address, entry/return dump specs, flags. The
         future `probe_wrap` ingest stage reads it (docs/TIMING-LOCKSTEP.md).
  --h    a C header for src/trace/timing.c: RG_TIMING_<Site> ids (the same
         numbers probe.py writes in its meta `sites`) and the dump specs as
         data, so rg_timing_enter/leave log the same six words PCSX2 logs.
  --check  compare the --tsv file with a fresh generation; exit 1 on drift.

Site ids are probe.py's: 1-based, in build_timing_hooks call order. The word
specs are probe.py's dump items (W_abs/W_ptr/W_reg/W_stk/W_fpr), normalised:
  abs:ADDR[+o..]   start at the PS2 address ADDR
  arg:N[+o..]      start at argument N (W_reg(a0..a3) at entry; W_stk(slot) at
                   return, slot 1 = a0: the trampoline's saved arguments)
  fpr:N            the bits of $fN (float argument)
followed by the dereference chain: no offsets = the start value itself;
otherwise p = start, p = *(p + o) for every offset but the last (null -> 0),
word = *(p + last).

Function names come from the definitions under --src (default game/src) and
src/ (the port's own SDK names, e.g. sceCdRead_12a728). Original CC0 code.
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)

import probe  # noqa: E402
from mips import A0, A3  # noqa: E402

COLS = ["id", "site", "kind", "addr", "func", "entry", "ret", "flags"]


class Recorder:
    """Stands in for probe.Hooks: records each hook call instead of
    assembling a trampoline. Site ids follow probe.Hooks._site."""

    def __init__(self):
        self.sites = []

    def _add(self, kind, addr, name, dump=None, dump_ret=None, flags=()):
        self.sites.append({"id": len(self.sites) + 1, "site": name, "kind": kind, "addr": addr,
                           "entry": words(dump, "entry"), "ret": words(dump_ret, "ret"),
                           "flags": list(flags)})
        return len(self.sites)

    def entry(self, addr, name, dump=None, pre=None):
        if pre:
            raise SystemExit("%s: `pre` code has no port equivalent" % name)
        return self._add("entry", addr, name, dump)

    def leaf(self, addr, name, dump=None, skip_zero=None):
        fl = []
        if skip_zero is not None:
            if not A0 <= skip_zero <= A3:
                raise SystemExit("%s: skip_zero on a non-argument register" % name)
            fl.append("skipzero=a%d" % (skip_zero - A0))
        return self._add("leaf", addr, name, dump, flags=fl)

    def entry_ret(self, addr, name, dump=None, dump_ret=None, log_entry=True):
        return self._add("entry_ret" if log_entry else "ret", addr, name, dump, dump_ret)

    def syscall_stub(self, addr, name, dump=None):
        raise SystemExit("%s: syscall stubs are not timing sites" % name)


def _item(spec, where):
    """One probe words-dump item -> 'abs:ADDR+o+o' / 'arg:N+o' / 'fpr:N'."""
    if spec[0] == "fpr":
        return "fpr:%d" % spec[1]
    _, base, *offs = spec
    if base[0] == "abs":
        head = "abs:%08x" % base[1]
    elif base[0] == "reg":
        if not A0 <= base[1] <= A3:
            raise SystemExit("W_reg on register %d: only a0..a3 have a port equivalent" % base[1])
        if where != "entry":
            raise SystemExit("W_reg in a return dump: use W_stk")
        head = "arg:%d" % (base[1] - A0)
    elif base[0] == "stk":
        if where != "ret" or not 1 <= base[1] <= 3:
            raise SystemExit("W_stk slot %d (%s): only return dumps, slots 1..3 (a0..a2)" % (base[1], where))
        head = "arg:%d" % (base[1] - 1)
    else:
        raise SystemExit("unknown dump base %r" % (base,))
    return head + "".join("+%x" % o for o in offs)


def words(dump, where):
    """A probe dump spec -> list of six (or fewer) normalised word specs."""
    if dump is None:
        return []
    if dump[0] == "words":
        return [_item(s, where) for s in dump[1]]
    # legacy six-consecutive-words forms
    kind = dump[0]
    if kind == "reg":
        base = probe.W_reg(dump[1], 0)[:2]
        off = dump[2]
    elif kind == "stk":
        base = ("m", ("stk", dump[1]))
        off = dump[2]
    elif kind == "abs":
        return [_item(probe.W_abs(dump[1] + 4 * i), where) for i in range(6)]
    elif kind == "ptr":
        return [_item(probe.W_ptr(dump[1], dump[2] + 4 * i), where) for i in range(6)]
    else:
        raise SystemExit("unknown dump %r" % (dump,))
    return [_item(base + (off + 4 * i,), where) for i in range(6)]


def scan_names(dirs, addrs):
    """{addr: function name} from definitions `name_<addr>(` in C sources."""
    want = {"%x" % a: a for a in addrs}
    rx = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*?_([0-9a-f]{5,6}))\s*\(")
    found = {}
    for d in dirs:
        if not os.path.isdir(d):
            continue
        for root, _, files in os.walk(d):
            for f in files:
                if not f.endswith((".c", ".cpp")):
                    continue
                stem = os.path.splitext(f)[0]
                m = re.match(r".*_([0-9a-f]{5,6})$", stem)
                if m and m.group(1) in want and want[m.group(1)] not in found:
                    found[want[m.group(1)]] = stem
                    continue
                if not f.startswith(("libcdvd", "libpad")):
                    continue
                for m in rx.finditer(open(os.path.join(root, f), encoding="utf-8", errors="replace").read()):
                    if m.group(2) in want:
                        found.setdefault(want[m.group(2)], m.group(1))
    return found


def generate(src_dirs):
    rec = Recorder()
    probe.build_timing_hooks(rec)
    names = scan_names(src_dirs, [s["addr"] for s in rec.sites])
    for s in rec.sites:
        s["func"] = names.get(s["addr"], "")
    return rec.sites


def tsv_text(sites):
    out = ["# GENERATED by tools/trace/gen_timing_sites.py from probe.py build_timing_hooks -- do not edit.",
           "# docs/TIMING-LOCKSTEP.md: the timing record's sites (ids = probe.py meta `sites`).",
           "\t".join(COLS)]
    for s in sites:
        out.append("\t".join([str(s["id"]), s["site"], s["kind"], "%08x" % s["addr"], s["func"] or "-",
                              ",".join(s["entry"]) or "-", ",".join(s["ret"]) or "-",
                              ",".join(s["flags"]) or "-"]))
    return "\n".join(out) + "\n"


def _c_word(spec):
    kind, rest = spec.split(":", 1)
    parts = rest.split("+")
    head, offs = parts[0], [int(o, 16) for o in parts[1:]]
    if len(offs) > 4:
        raise SystemExit("word %s: more than 4 offsets" % spec)
    k = {"abs": "RG_TW_ABS", "arg": "RG_TW_ARG", "fpr": "RG_TW_FPR"}[kind]
    base = int(head, 16) if kind == "abs" else int(head)
    o = offs + [0] * (4 - len(offs))
    return "{%s, %d, 0x%08Xu, {0x%X, 0x%X, 0x%X, 0x%X}}" % (k, len(offs), base, *o)


def h_text(sites):
    kinds = {"entry": "RG_TS_ENTRY", "leaf": "RG_TS_ENTRY", "entry_ret": "RG_TS_ENTRY | RG_TS_RET",
             "ret": "RG_TS_RET"}
    L = ["/* GENERATED by tools/trace/gen_timing_sites.py from tools/trace/probe.py",
         " * build_timing_hooks -- do not edit.  docs/TIMING-LOCKSTEP.md. */",
         "#ifndef RG_TIMING_SITES_H", "#define RG_TIMING_SITES_H", "",
         "enum {"]
    for s in sites:
        L.append("    RG_TIMING_%s = %d,   /* %s %08x %s */" % (s["site"], s["id"], s["kind"], s["addr"], s["func"]))
    L += ["    RG_TIMING_NSITES = %d" % (len(sites) + 1), "};", "",
          "#ifdef RG_TIMING_SITE_TABLE",
          "static const rg_timing_site k_rg_timing_sites[RG_TIMING_NSITES] = {",
          "    {0, 0, 0, 0, -1, 0, 0, {{0}}, {{0}}},"]
    for s in sites:
        skip = -1
        for f in s["flags"]:
            if f.startswith("skipzero=a"):
                skip = int(f[len("skipzero=a"):])
        ent = ", ".join(_c_word(w) for w in s["entry"]) or "{0}"
        ret = ", ".join(_c_word(w) for w in s["ret"]) or "{0}"
        L.append('    {"%s", "%s", 0x%08Xu, %s, %d, %d, %d,\n     {%s},\n     {%s}},'
                 % (s["site"], s["func"], s["addr"], kinds[s["kind"]], skip, len(s["entry"]), len(s["ret"]),
                    ent, ret))
    L += ["};", "#endif", "", "#endif", ""]
    return "\n".join(L)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", action="append", default=None,
                    help="source tree(s) for function names (default game/src and src)")
    ap.add_argument("--tsv", default=None)
    ap.add_argument("--h", default=None)
    ap.add_argument("--check", action="store_true", help="--tsv must equal a fresh generation")
    args = ap.parse_args()
    src = args.src or [os.path.join(PORT, "game", "src"), os.path.join(PORT, "src")]
    sites = generate(src)
    if args.check:
        path = args.tsv or os.path.join(HERE, "timing_sites.tsv")
        old = open(path, encoding="utf-8").read()
        new = tsv_text(sites)
        if old != new:
            sys.stderr.write("%s is stale: regenerate with gen_timing_sites.py --tsv %s\n" % (path, path))
            import difflib
            sys.stderr.writelines(difflib.unified_diff(old.splitlines(True), new.splitlines(True), path, "generated"))
            sys.exit(1)
        print("%s: %d sites, in sync with probe.py" % (path, len(sites)))
        return
    if args.tsv:
        with open(args.tsv, "w", encoding="utf-8", newline="\n") as f:
            f.write(tsv_text(sites))
    if args.h:
        os.makedirs(os.path.dirname(os.path.abspath(args.h)), exist_ok=True)
        text = h_text(sites)
        if not os.path.exists(args.h) or open(args.h, encoding="utf-8").read() != text:
            with open(args.h, "w", encoding="utf-8", newline="\n") as f:
                f.write(text)
    print("%d timing sites%s%s" % (len(sites), " -> " + args.tsv if args.tsv else "",
                                     " -> " + args.h if args.h else ""))


if __name__ == "__main__":
    main()
