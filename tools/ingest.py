#!/usr/bin/env python3
"""Generate game/ from a pinned snapshot of the matching decomp (PLAN.md D6).

    python tools/ingest.py --source ../RGDecomp --rev <commit> [--out game] [--check]

Everything is read from the git OBJECT DATABASE at <rev> (`git ls-tree` +
`git cat-file --batch`), never from the source repo's working tree, which may
hold another session's uncommitted edits.  Blobs are copied as raw bytes (the
decomp stores every file `-text`, so there is no EOL conversion to undo).

Unit selection (transform 1) follows the snapshot's own build scripts:

  * a symbol resolves to its source exactly as `scripts/rgd.py src_path()` does:
    the file under src/ whose STEM equals the symbol, every `.c` sorted first,
    then every `.cpp` sorted;
  * MAIN's linked set is `config/cunits.txt` (what `scripts/link.py` links).
    `config/units.txt` is only the compile list; an entry there that is not in
    cunits.txt is compiled-but-not-linked and is NOT ingested (reported);
  * overlay <n>'s linked set is `config/ocunits/<n>.txt` (`scripts/olink.py`);
  * `config/hosted.txt` GUEST HOST: a guest is `static` inside its host's
    source and has no file of its own; it is attributed to the host's file;
  * generated data sources (`src/<image>_data/`, from data2c) are taken whole
    when the snapshot has them, plus all of include/;
  * a few snapshot config files that later transforms read (arity seeds,
    hosted/toolchain tables, the unit lists) are copied to game/config/.

Then the transform stages run in order, stage-major, over every ingested
source file.  Each stage is a `Stage` with a name and `apply(relpath, data)
-> (data, sites)` plus optional prepare/extra_outputs/report hooks; a
per-stage census (files changed, sites) is printed.  The stages live in
tools/portxform.py and tools/stages/ (protos, spin).  Transform 6 (`asmexclude`) also writes game/EXCLUDED.tsv
(every symbol whose asm body was cut, to be bound to src/sce or an override)
and marks wholly-asm files `excluded` in MANIFEST.tsv: they are kept for
reference but are not compiled (the compile set is kind unit + data).

The output is deterministic: files are written only when their bytes differ,
files not in the new set are deleted, and MANIFEST.tsv / SNAPSHOT.txt are
sorted and timestamp-free.  `--check` re-runs nothing and only verifies that
game/ matches its MANIFEST.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable

PORT = Path(__file__).resolve().parent.parent

# The pinned snapshot (docs/TOOLCHAIN.md "Game source").  `ingest.py` with no
# --source/--rev ingests exactly this: the published decomp, commit 675c07fe
# "Rogue Galaxy matching decompilation" (docs/SNAPSHOT-CLEAN.md).  PIN_SOURCE is
# that repo's git dir (its work tree is ../RGDecomp; its HEAD is an
# unborn branch, so the commit is always named explicitly).  PIN_TREE is the
# commit's tree id: `ingest.py --compare-tree REPO@REV` checks any other clone or
# commit (e.g. after a push) against it in one command.  To move the pin: change
# these three lines, re-ingest, then classify STALE overrides (docs/LINK.md
# "Switching the snapshot").  Previous pin: the interim replay b09ccfa1
# (docs/SNAPSHOT-INTERIM.md).
PIN_SOURCE = "../RGDecomp/.git"
PIN_REV = "675c07feec314d493f9cc3d51f511bc7eb6ca07d"
PIN_TREE = "460f59203d957c85b74cb184af1f5b75a49ac0a6"
OVERLAYS = ("title", "insmenu", "normal", "factory", "insect")
CONFIG_COPY = ("config/cunits.txt", "config/units.txt", "config/hosted.txt",
               "config/toolchain.txt", "config/arity.txt",
               "config/arity_inferred.txt", "config/data2c.json") + tuple(
                   f"config/ocunits/{o}.txt" for o in OVERLAYS)
SRC_EXT = (".c", ".cpp")


# ---------------------------------------------------------------- git access
class Snapshot:
    def __init__(self, repo: Path, rev: str):
        self.repo = repo
        self.commit = self._git("rev-parse", "--verify", f"{rev}^{{commit}}").strip()
        out = self._git("ls-tree", "-r", "-z", "--full-tree", self.commit)
        self.blobs: dict[str, str] = {}
        for ent in out.split("\0"):
            if not ent:
                continue
            meta, path = ent.split("\t", 1)
            mode, kind, sha = meta.split()
            if kind == "blob":
                self.blobs[path] = sha
        self._cache: dict[str, bytes] = {}

    def _git(self, *args: str) -> str:
        r = subprocess.run(["git", "-C", str(self.repo), *args],
                           capture_output=True, text=True, encoding="utf-8")
        if r.returncode:
            raise SystemExit(f"ingest: git {' '.join(args)} failed: {r.stderr.strip()}")
        return r.stdout

    def prefetch(self, paths: list[str]) -> None:
        """Read many blobs in ONE `git cat-file --batch` process."""
        want = [p for p in paths if p not in self._cache]
        if not want:
            return
        req = "".join(f"{self.blobs[p]}\n" for p in want).encode()
        r = subprocess.run(["git", "-C", str(self.repo), "cat-file", "--batch"],
                           input=req, capture_output=True)
        if r.returncode:
            raise SystemExit(f"ingest: git cat-file failed: {r.stderr.decode()}")
        buf, pos = r.stdout, 0
        for p in want:
            nl = buf.index(b"\n", pos)
            sha, kind, size = buf[pos:nl].split()
            size = int(size)
            self._cache[p] = buf[nl + 1:nl + 1 + size]
            pos = nl + 1 + size + 1  # trailing LF after each object

    def read(self, path: str) -> bytes:
        self.prefetch([path])
        return self._cache[path]

    def text(self, path: str) -> str:
        return self.read(path).decode("utf-8", errors="replace")

    def has(self, path: str) -> bool:
        return path in self.blobs


def symbol_list(text: str) -> list[str]:
    """One symbol per line, `#` comments, CRLF-tolerant (factory.txt is CRLF)."""
    out = []
    for ln in text.splitlines():
        s = ln.split("#")[0].strip()
        if s:
            out.append(s.split()[0])
    return out


# ---------------------------------------------------------------- transforms
@dataclass
class Stage:
    """One mechanical transform.  apply() must be idempotent and pure.

    Stages run STAGE-MAJOR: stage k sees every file after stage k-1, so a
    whole-corpus stage can `prepare()` on exactly the bytes it will be
    applied to.  Optional hooks on `obj`:
      prepare(files)   -- called once with {relpath: bytes} of ALL ingested
                          files (current state) before the stage's apply()s;
      extra_outputs()  -- {relpath under game/: bytes}, called after; each
                          gets a MANIFEST row of kind `generated`;
      report()         -- a text block printed with the census;
      errors           -- a list; non-empty makes ingest exit 1.
    """
    name: str
    apply: Callable[[str, bytes], tuple[bytes, int]]
    kinds: tuple[str, ...] = ("unit", "data")
    obj: object = None

    def hook(self, name: str):
        return getattr(self.obj, name, None) if self.obj is not None else None


# Transform stages, in run order (tools/portxform.py documents each):
#   int128      u128 hazard          -- also rewrites include/ (vec.h)
#   gccvarargs  gcc-island varargs
#   vu0asm      transform 4 (inline VU0 asm -> VU0 model calls)
#   vu0bind     mwcc VU0 register bindings -> lvalues on the VU0 model +
#               port/vu0intrin.h intrinsics (docs/LINK.md)
#   asmexclude  transform 6 (asm-bodied functions cut, EXCLUDED.tsv)
#   wideret     4-byte definitions whose retail $v0 is 64 bits (chains,
#               accumulators) return long long (tools/stages/wideret.py,
#               docs/PROTOS.md "wideret") -- before protos, so the header follows
#   protos      transform 2 (prototype unification, tools/stages/protos.py,
#               docs/PROTOS.md) -- whole-corpus: prepare() + extra outputs
#               include/port/game_protos.h and PROTOS.tsv
#   dialect     mwcc spellings clang hard-rejects (tools/portxform.py):
#               C++ unnamed-type externs, prototype-scoped struct tags, GNU
#               lvalue casts -- after protos, so protos is measured unchanged
#   fnvoid      C++ only: a function designator passed to a `void *` parameter or
#               assigned to a `void *` lvalue gets `(void *)` (the MSVC target's
#               implicit conversion; other C++ targets reject it: docs/LINUX.md,
#               tools/stages/fnvoid.py) -- after dialect
#   vu0frame    the VU0 register file as function locals: RG_VU0_FRAME in
#               every function that names the model, frame helpers take the
#               caller's file (tools/stages/vu0frame.py, docs/NATIVE-CPU.md
#               section 4) -- after protos/dialect (it adds a parameter to
#               static helpers); extra output VU0FRAME.tsv
#   ovlsyms     `<ov>_` prefix on each overlay's own data/bss names
#               (tools/stages/ovlsyms.py, docs/OVERLAY.md) -- before protos
#   datareloc   MAIN data C for the host: raw PS2 address words -> link-time
#               relocations, f32/s16-typed address words, microcode blobs,
#               MAIN bss as one labelled block, overlay reservations dropped
#               (tools/stages/datareloc.py, docs/LINK.md) -- before protos, so
#               protos fixes the declarations it adds; extra output DATARELOC.tsv
#   devirt      transform 3: dummy virtual classes -> explicit __vptr + VCM
#               slot thunks, C/C++ linkage fixes (tools/stages/devirt.py,
#               docs/DEVIRT.md); extra outputs DEVIRT.tsv, DEVIRT_FLAGS.tsv
#   retwiden    a narrow (1/2-byte) return of an address-taken function is
#               returned extended to 32 bits (tools/stages/retwiden.py,
#               docs/PROTOS.md "retwiden") -- after devirt (slot calls)
#   spin        busy-wait instrumentation (tools/stages/spin.py, docs/SPIN.md)
#               -- after protos, so protos never sees rg_spin_* as a game symbol
#   hwaccess    transform 5: address literals -> HW_R*/HW_W*/PS2_SPR/...
#               (tools/stages/hwaccess.py, docs/HWBUS.md) -- LAST, after spin
#               (spin matches loop headers textually); extra output HWACCESS.tsv
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parent / "stages"))
import portxform  # noqa: E402
import protos  # noqa: E402
import spin  # noqa: E402
import ovlsyms  # noqa: E402
import devirt  # noqa: E402
import hwaccess  # noqa: E402
import datareloc  # noqa: E402
import vu0frame  # noqa: E402
import fnvoid  # noqa: E402
import retwiden  # noqa: E402
import wideret  # noqa: E402

ASM_EXCLUDE = portxform.AsmExclude()


def make_stages() -> list[Stage]:
    """Fresh stage objects (protos/spin keep per-run state)."""
    pr = protos.ProtoStage()
    sp = spin.SpinStage()
    os_ = ovlsyms.OvlSymsStage()
    dv = devirt.DevirtStage()
    hw = hwaccess.HwAccessStage()
    dr = datareloc.DataRelocStage()
    vf = vu0frame.Vu0FrameStage()
    rt = retwiden.RetWidenStage()
    wr = wideret.WideRetStage()
    return [
        Stage("int128", portxform.stage_int128, ("unit", "data", "include")),
        Stage("gccvarargs", portxform.stage_gccvarargs),
        Stage("vu0asm", portxform.stage_vu0asm),
        Stage("vu0bind", portxform.stage_vu0bind),
        Stage("asmexclude", ASM_EXCLUDE),
        Stage("ovlsyms", os_.apply, ("unit", "data"), os_),
        Stage("datareloc", dr.apply, ("data",), dr),
        Stage("wideret", wr.apply, ("unit",), wr),
        Stage("protos", pr.apply, ("unit", "data"), pr),
        Stage("dialect", portxform.stage_dialect),
        Stage("fnvoid", fnvoid.apply, ("unit",)),
        Stage("vu0frame", vf.apply, ("unit",), vf),
        Stage("devirt", dv.apply, ("unit", "include"), dv),
        Stage("retwiden", rt.apply, ("unit",), rt),
        Stage("spin", sp.apply, ("unit",), sp),
        Stage("hwaccess", hw.apply, ("unit",), hw),
    ]


STAGES: list[Stage] = make_stages()


@dataclass
class StageCensus:
    files_changed: int = 0
    sites: int = 0


# ---------------------------------------------------------------- selection
@dataclass
class Entry:
    relpath: str                 # path in the snapshot == path under game/
    image: str                   # main/title/.../include/config
    kind: str                    # unit | data | include | config
    symbols: list[str] = field(default_factory=list)


def select(snap: Snapshot) -> tuple[dict[str, Entry], dict]:
    report: dict = {"missing": [], "duplicate": [], "compiled_not_linked": [],
                    "multi_source": [], "unregistered_src": [], "per_image": {},
                    "hosted": 0, "cross_image": []}

    # rgd.src_path(): stem -> sorted .c hits then sorted .cpp hits
    by_stem: dict[str, dict[str, list[str]]] = {}
    for p in snap.blobs:
        if p.startswith("src/") and p.endswith(SRC_EXT):
            name = p.rsplit("/", 1)[1]
            stem, ext = name.rsplit(".", 1)
            by_stem.setdefault(stem, {}).setdefault("." + ext, []).append(p)

    def src_path(sym: str) -> str | None:
        by = by_stem.get(sym)
        if not by:
            return None
        hits = sorted(by.get(".c", [])) + sorted(by.get(".cpp", []))
        if len(hits) > 1:
            report["multi_source"].append((sym, hits))
        return hits[0] if hits else None

    hosted: dict[str, str] = {}
    if snap.has("config/hosted.txt"):
        for ln in snap.text("config/hosted.txt").splitlines():
            f = ln.split("#")[0].split()
            if len(f) >= 2:
                hosted[f[0]] = f[1]

    images = [("main", "config/cunits.txt")] + [
        (o, f"config/ocunits/{o}.txt") for o in OVERLAYS]
    entries: dict[str, Entry] = {}
    linked: set[str] = set()
    for image, cfg in images:
        if not snap.has(cfg):
            report["missing"].append((image, f"<no {cfg}>"))
            continue
        syms = symbol_list(snap.text(cfg))
        seen: set[str] = set()
        n_units = 0
        for s in syms:
            if s in seen:
                report["duplicate"].append((image, s))
                continue
            seen.add(s)
            linked.add(s)
            path = src_path(s)
            if path is None and s in hosted:
                path = src_path(hosted[s])
                report["hosted"] += 1
            if path is None:
                report["missing"].append((image, s))
                continue
            n_units += 1
            e = entries.get(path)
            if e is None:
                entries[path] = Entry(path, image, "unit", [s])
            else:
                if e.image != image:
                    report["cross_image"].append((s, path, e.image, image))
                e.symbols.append(s)
        report["per_image"][image] = (len(syms), n_units)

    if snap.has("config/units.txt"):
        for s in symbol_list(snap.text("config/units.txt")):
            if s not in linked and s not in report["compiled_not_linked"]:
                report["compiled_not_linked"].append(s)

    # generated data sources: src/<image>_data/** (data2c)
    for p in snap.blobs:
        parts = p.split("/")
        if p.startswith("src/") and len(parts) > 2 and parts[1].endswith("_data"):
            entries[p] = Entry(p, parts[1][:-len("_data")], "data")
    for p in snap.blobs:
        if p.startswith("include/"):
            entries[p] = Entry(p, "include", "include")
    for p in CONFIG_COPY:
        if snap.has(p):
            entries[p] = Entry(p, "config", "config")

    taken = set(entries)
    report["unregistered_src"] = sorted(
        p for p in snap.blobs
        if p.startswith("src/") and p.endswith(SRC_EXT) and p not in taken)
    return entries, report


# ---------------------------------------------------------------- output
def sha256(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


def tree_digest(root: Path) -> tuple[str, int]:
    h = hashlib.sha256()
    n = 0
    for p in sorted(root.rglob("*")):
        if p.is_file():
            rel = p.relative_to(root).as_posix()
            h.update(rel.encode() + b"\0" + p.read_bytes() + b"\0")
            n += 1
    return h.hexdigest(), n


def write_if_changed(path: Path, data: bytes) -> bool:
    if path.exists() and path.read_bytes() == data:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    try:
        path.write_bytes(data)
    except OSError:
        # Windows: a file another process has memory-mapped (a concurrent
        # compile including game_protos.h) cannot be truncated in place
        # (EINVAL); write a sibling and rename it over the old file
        import os
        import time
        tmp = path.with_name(path.name + ".ingest-tmp")
        tmp.write_bytes(data)
        for i in range(50):
            try:
                os.replace(tmp, path)
                break
            except OSError:
                if i == 49:
                    raise
                time.sleep(0.2)
    return True


def ingest(source: Path, rev: str, out: Path) -> int:
    snap = Snapshot(source, rev)
    entries, rep = select(snap)
    paths = sorted(entries)
    snap.prefetch(paths)

    # transform 6 context: image of each file, MAIN/overlay symbol addresses
    ASM_EXCLUDE.__init__()
    ASM_EXCLUDE.image_of = {p: e.image for p, e in entries.items()}
    for img in ("main",) + OVERLAYS:
        cfg = f"config/{img}.symbols.txt"
        if snap.has(cfg):
            for ln in snap.text(cfg).splitlines():
                f = ln.split("//")[0].split("=")
                if len(f) == 2 and f[1].strip().rstrip(";").startswith("0x"):
                    ASM_EXCLUDE.addr_of[(img, f[0].strip())] = int(
                        f[1].strip().rstrip(";"), 16)

    global STAGES
    STAGES = make_stages()
    # protos: MAIN's address table (symbols + interior-entry labels) for the
    # address-style alias renames (docs/PROTOS.md, rule addr-alias)
    addr_table = protos.snapshot_addr_table(source, snap.commit)
    for st in STAGES:
        if st.name in ("protos", "wideret"):
            st.obj.addr_table = addr_table
        if st.name == "datareloc":       # docs/LINK.md "Data layer"
            st.obj.addr_table = addr_table
            st.obj.ovl_funcs = datareloc.ovl_func_table(ASM_EXCLUDE.addr_of)
            st.obj.entries = entries
    census = {st.name: StageCensus() for st in STAGES}
    outputs: dict[str, bytes] = {p: snap.read(p) for p in paths}
    extra: dict[str, bytes] = {}
    for st in STAGES:                      # stage-major (see Stage)
        if st.name == "protos" and os.environ.get("RG_INGEST_PRE_PROTOS"):
            # debug: the protos stage's exact input, for tools/stages/protos_pre.py
            # (re-runs protos alone in ~1/5 of an ingest; docs/PROTOS.md "Stack-block census")
            import pickle
            with open(os.environ["RG_INGEST_PRE_PROTOS"], "wb") as fh:
                pickle.dump({"outputs": dict(outputs),
                             "apply": [p for p in paths if entries[p].kind in st.kinds],
                             "kinds": {p: entries[p].kind for p in paths},
                             "addr_table": addr_table}, fh)
        prep = st.hook("prepare")
        if prep is not None:
            prep(dict(outputs))
        for p in paths:
            if entries[p].kind in st.kinds:
                data = outputs[p]
                new, sites = st.apply(p, data)
                if new != data:
                    census[st.name].files_changed += 1
                census[st.name].sites += sites
                outputs[p] = new
        for p in ASM_EXCLUDE.excluded_files:   # later stages skip them
            entries[p].kind = "excluded"
        more = st.hook("extra_outputs")
        if more is not None:
            extra.update(more())

    for p in ASM_EXCLUDE.excluded_files:
        entries[p].kind = "excluded"
    outputs["EXCLUDED.tsv"] = ASM_EXCLUDE.tsv().encode()
    entries["EXCLUDED.tsv"] = Entry("EXCLUDED.tsv", "-", "generated")
    for p, d in sorted(extra.items()):
        if p in entries:
            raise SystemExit(f"ingest: generated output {p} collides with a snapshot file")
        outputs[p] = d
        entries[p] = Entry(p, "-", "generated")
    paths = sorted(entries)
    manifest = ["relpath\tsha256\timage\tkind\tsymbols"]
    for p in paths:
        e = entries[p]
        manifest.append(f"{p}\t{sha256(outputs[p])}\t{e.image}\t{e.kind}\t"
                        f"{','.join(e.symbols) or '-'}")
    outputs["MANIFEST.tsv"] = ("\n".join(manifest) + "\n").encode()
    outputs["SNAPSHOT.txt"] = (
        "# game/ is GENERATED by tools/ingest.py -- never edit it by hand.\n"
        f"source\t{source.as_posix()}\n"
        f"rev\t{snap.commit}\n"
        f"stages\t{','.join(st.name for st in STAGES) or '-'}\n"
        f"generated\t{','.join(sorted(extra)) or '-'}\n").encode()

    out.mkdir(parents=True, exist_ok=True)
    written = sum(write_if_changed(out / p, d) for p, d in outputs.items())
    removed = 0
    for f in sorted(out.rglob("*"), reverse=True):
        rel = f.relative_to(out).as_posix()
        if f.is_file() and rel not in outputs:
            f.unlink()
            removed += 1
        elif f.is_dir() and not any(f.iterdir()):
            f.rmdir()

    # ---- report
    kinds: dict[str, int] = {}
    for e in entries.values():
        kinds[e.kind] = kinds.get(e.kind, 0) + 1
    print(f"snapshot {snap.commit} ({source.as_posix()})")
    print("units per image (registered symbols / resolved to a source):")
    for img, (n, ok) in rep["per_image"].items():
        files = sum(1 for e in entries.values() if e.kind == "unit" and e.image == img)
        print(f"  {img:8s} {n:6d} registered  {ok:6d} resolved  {files:6d} files")
    data_imgs: dict[str, int] = {}
    for e in entries.values():
        if e.kind == "data":
            data_imgs[e.image] = data_imgs.get(e.image, 0) + 1
    print(f"data sources: {sum(data_imgs.values())} {data_imgs or '(none in this snapshot)'}")
    print("files by kind: " + ", ".join(f"{k}={v}" for k, v in sorted(kinds.items())))
    print(f"hosted guests attributed to host file: {rep['hosted']}")
    print(f"missing source (registered, no file): {len(rep['missing'])}")
    for m in rep["missing"]:
        print(f"    {m}")
    print(f"duplicate registrations: {len(rep['duplicate'])}")
    for d in rep["duplicate"]:
        print(f"    {d}")
    print(f"symbols resolving to >1 file (first taken): {len(rep['multi_source'])}")
    for m in rep["multi_source"]:
        print(f"    {m}")
    print(f"files shared across images: {len(rep['cross_image'])}")
    print(f"compiled-not-linked (units.txt only, excluded): "
          f"{len(rep['compiled_not_linked'])} {rep['compiled_not_linked'][:10]}")
    print(f"unregistered src files (excluded): {len(rep['unregistered_src'])}")
    for u in rep["unregistered_src"]:
        print(f"    {u}")
    print("transform stages:" + ("" if STAGES else " (none)"))
    for name, c in census.items():
        print(f"  {name:24s} files_changed={c.files_changed} sites={c.sites}")
    by: dict[tuple, int] = {}
    for r in ASM_EXCLUDE.rows:
        by[(r.lib, r.scope, r.reason)] = by.get((r.lib, r.scope, r.reason), 0) + 1
    print(f"EXCLUDED.tsv: {len(ASM_EXCLUDE.rows)} symbols, "
          f"{len(ASM_EXCLUDE.excluded_files)} files excluded from compilation")
    for k in sorted(by):
        print(f"    {k[0]:8s} {k[1]:9s} {k[2]:14s} {by[k]}")
    for st in STAGES:
        stats = getattr(st.obj, "stats", None)
        if stats:
            print(f"{st.name} rules: " + ", ".join(f"{k}={v}" for k, v in sorted(stats.items())))
        rep_fn = st.hook("report")
        if rep_fn is not None:
            print(rep_fn())
    print(f"generated: {', '.join(sorted(extra)) or '-'}")
    digest, n = tree_digest(out)
    print(f"game/: {n} files, {written} written, {removed} removed, tree sha256 {digest}")
    bad = check_overrides(out)
    errs = sum(len(getattr(st.obj, "errors", None) or ()) for st in STAGES)
    return 1 if (bad or errs) else 0


# ---------------------------------------------------------------- overrides
OVR_RX = re.compile(rb"rg-override:\s*replaces\s+game/(\S+)\s+sha256\s+([0-9a-fA-F]{64})")


def check_overrides(out: Path, root: Path | None = None) -> int:
    """overrides/<path> replaces game/<path>.  Its first 4 KiB must hold

        /* rg-override: replaces game/<path> sha256 <64 hex> */

    the SHA-256 of the generated game/ file it replaces (overrides/README.md).
    A different hash means the snapshot or a stage moved under the override:
    re-port it, then update the hash."""
    root = root or (PORT / "overrides")
    if not root.is_dir():
        return 0
    rows = (out / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]
    man = {r.split("\t")[0]: r.split("\t")[1] for r in rows}
    bad = n = 0
    for f in sorted(root.rglob("*")):
        rel = f.relative_to(root).as_posix()
        if not f.is_file() or not rel.endswith((".c", ".cpp", ".h")):
            continue
        n += 1
        m = OVR_RX.search(f.read_bytes()[:4096])
        if m is None:
            print(f"OVERRIDE {rel}: no `rg-override: replaces game/<path> sha256 <hex>` header")
            bad += 1
            continue
        target, want = m.group(1).decode(), m.group(2).decode().lower()
        if target != rel:
            print(f"OVERRIDE {rel}: header names game/{target}, expected game/{rel}")
            bad += 1
        elif target not in man:
            print(f"OVERRIDE {rel}: game/{target} is not in MANIFEST.tsv")
            bad += 1
        elif man[target] != want:
            print(f"OVERRIDE {rel}: STALE, recorded {want}, game/{target} is now {man[target]}")
            bad += 1
    print(f"overrides: {n} files, {bad} problems")
    return bad


def check(out: Path) -> int:
    bad = 0
    lines = (out / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]
    for ln in lines:
        rel, digest = ln.split("\t")[:2]
        f = out / rel
        if not f.exists() or sha256(f.read_bytes()) != digest:
            print(f"MISMATCH {rel}")
            bad += 1
    listed = {ln.split("\t")[0] for ln in lines} | {"MANIFEST.tsv", "SNAPSHOT.txt"}
    for f in out.rglob("*"):
        if f.is_file() and f.relative_to(out).as_posix() not in listed:
            print(f"EXTRA {f.relative_to(out).as_posix()}")
            bad += 1
    print(f"check: {len(lines)} manifest rows, {bad} problems")
    bad += check_overrides(out)
    return 1 if bad else 0


def _tree_listing(repo: str, rev: str) -> tuple[str, dict[str, str]]:
    def git(*args):
        r = subprocess.run(["git", "-C", repo, *args], capture_output=True, text=True,
                           encoding="utf-8")
        if r.returncode:
            raise SystemExit(f"ingest: git {' '.join(args)} failed: {r.stderr.strip()}")
        return r.stdout
    tree = git("rev-parse", f"{rev}^{{tree}}").strip()
    blobs = {}
    for ent in git("ls-tree", "-r", "-z", "--full-tree", tree).split(chr(0)):
        if ent:
            meta, path = ent.split(chr(9), 1)
            blobs[path] = meta.split()[2]
    return tree, blobs


def compare_tree(spec: str) -> int:
    """Is REPO@REV the same content as the pin?  Git tree ids are content
    hashes, so the official decomp commit, once it exists, has tree PIN_TREE
    exactly when every file is byte-identical to the scratch copy we pinned
    (docs/SNAPSHOT-CLEAN.md).  Read-only on REPO (rev-parse + ls-tree)."""
    repo, _, rev = spec.partition("@")
    rev = rev or "HEAD"
    tree, theirs = _tree_listing(repo, rev)
    print(f"{repo}@{rev}: tree {tree}")
    print(f"pin  {PIN_SOURCE}@{PIN_REV[:8]}: tree {PIN_TREE}")
    if tree == PIN_TREE:
        print("IDENTICAL: switch PIN_SOURCE/PIN_REV to it; game/ will not change")
        return 0
    _t, ours = _tree_listing(PIN_SOURCE, PIN_REV)
    add = sorted(set(theirs) - set(ours))
    rem = sorted(set(ours) - set(theirs))
    mod = sorted(p for p in set(ours) & set(theirs) if ours[p] != theirs[p])
    for tag, ps in (("A", add), ("D", rem), ("M", mod)):
        for p in ps:
            print(tag + chr(9) + p)
    print(f"DIFFERS: {len(add)} added, {len(rem)} removed, {len(mod)} modified "
          f"(re-ingest with --source {repo} --rev {rev} --out <dir> and review)")
    return 1


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--source", type=Path, default=Path(PIN_SOURCE),
                    help=f"snapshot repo (default: the pin, {PIN_SOURCE})")
    ap.add_argument("--rev", default=PIN_REV,
                    help=f"snapshot commit (default: the pin, {PIN_REV[:8]})")
    ap.add_argument("--out", type=Path, default=PORT / "game")
    ap.add_argument("--check", action="store_true",
                    help="verify game/ against its MANIFEST.tsv only")
    ap.add_argument("--compare-tree", metavar="REPO[@REV]",
                    help="compare REPO's commit REV (default HEAD) with the pinned "
                         "tree PIN_TREE: equal trees mean the pin can switch to it "
                         "(docs/SNAPSHOT-CLEAN.md)")
    a = ap.parse_args()
    if a.check:
        return check(a.out)
    if a.compare_tree:
        return compare_tree(a.compare_tree)
    return ingest(a.source, a.rev, a.out)


if __name__ == "__main__":
    sys.exit(main())
