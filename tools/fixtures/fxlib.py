# SPDX-License-Identifier: CC0-1.0
"""Shared helpers for the save-state test fixtures (docs/TEST-FIXTURES.md).

A fixture set lives in out/fixtures/<exe-id>/ (game-derived data: never
committed), where <exe-id> is the first 16 hex digits of the SHA-256 of the
rg-game.exe that wrote it:

    bin/rg-game.exe, bin/rg-game.map   a copy of that build (states load only into it)
    <milestone>.rgstate                one save state per milestone
    manifest.json                      what was saved, how, and when
    regen.log                          the generating run's stderr

Save states only load into the exact build that wrote them (rg-game refuses
any other), so a rebuilt exe needs a regenerated set (regen.py, ~8 min).
"""
from __future__ import annotations

import hashlib
import json
import os
import struct
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
DEFAULT_EXE = PORT / "build" / "fixtures-i686" / "rg-game.exe"
FIXTURES = PORT / "out" / "fixtures"
# The route the fixture sets are generated with: power-on -> first battle won ->
# Salgin -> save at the first transporter (docs/TEST-FIXTURES.md "Route").  It
# is newgame_battle.input.txt (unchanged, to field 24,695) plus a continuation,
# so the title/field/battle states are the same as with the old golden.
# newgame_save2 (2026-10-18) re-timed the continuation after the AngleWrap fix;
# newgame_save1 is kept for history (it no longer wins the battle).
GOLDEN = PORT / "tools" / "trace" / "goldens" / "newgame_save2.input.txt"
GOLDEN_SAVE1 = PORT / "tools" / "trace" / "goldens" / "newgame_save1.input.txt"
GOLDEN_BATTLE = PORT / "tools" / "trace" / "goldens" / "newgame_battle.input.txt"
# Game-save fixtures (memory-card folders written by the game itself; survive
# rebuilds, unlike states): out/fixtures/cards/<name>/ (game-derived, never
# committed), each with a boot input in tools/trace/goldens/boot_<name>.input.txt.
# regen.py refreshes ROUTE_CARD (the card GOLDEN writes); save1 = the card of the
# old route (exe4), left as it was.
CARDS = FIXTURES / "cards"
ROUTE_CARD = "save2"

# name, field (kernel VBlanks completed; the game's own vbl counter runs ~33
# behind), description.  Fields are on the route (GOLDEN, RG_GPU=hw).
MILESTONES = [
    ("title", 1500, "title menu over the attract movie (TITLE overlay, before NEW GAME)"),
    ("field", 8000, "first 3D field after the opening FMV (NORMAL overlay)"),
    ("battle", 23000, "first battle (game mode 7), just after its intro unlocks"),
    ("battle_won", 26780, "first battle won: results screen -> Hooded Man scene (game mode 11)"),
    ("town", 28840, "first field control in Salgin, walking (game mode 6)"),
    ("save_point", 30220, "beside the first transporter (save point) after its tutorial"),
    ("trans_menu", 30780, "transporter menu open (game mode 20), before Save"),
    ("saved", 31700, "saved to MEMORY CARD slot 1 / FILE 01, back in the field (card in cards/)"),
]
MILESTONE_FIELDS = {n: f for n, f, _ in MILESTONES}
# milestones whose runs need the memory card as the generating run left it
# (the card is host state, not in the save state): run_from.py seeds the run's
# saves dir with the set's cards/ snapshot
CARD_MILESTONES = {"saved"}


# Game-save boot fixtures (run_from.py --boot-save NAME, bootcheck.py): card
# out/fixtures/cards/NAME/ (save2 is written by regen.py, the others are manufactured from
# it by `saveedit.py make`), script tools/trace/goldens/boot_NAME.input.txt, and the
# milestones a run must pass: (name, field, overlay loader index, game mode or None).
# Overlay indices: 2 TITLE, 3 NORMAL, 4 FACTORY, 5 INSECT, 6 INSMENU (docs/OVERLAY.md).
BOOT_FIXTURES = {
    "save2": [("control", 3750, 3, "6/100")],
    "factory": [("factory", 4400, 4, "16/100"), ("factory_exit", 6400, 3, "6/100")],
    "insectron": [("insmenu", 2300, 6, None), ("insect", 10300, 5, None),
                  ("insect_battle", 11500, 5, "15/101")],
    # the save2 card with a longer script: steered walk east, random encounter = battle 2
    "save2_battle2": [("battle2", 4500, 3, "11/0"), ("battle2_fight", 5000, 3, "7/201"),
                      ("battle2_won", 7250, 3, "7/504"), ("battle2_field", 7700, 3, "6/100")],
}
# boot fixtures that reuse another fixture's card (script boot_<name>.input.txt as usual)
BOOT_CARD = {"save2_battle2": "save2"}

# The card library (cardlib.LIBRARY, docs/TEST-FIXTURES.md "Card library"): every card boots
# with tools/trace/goldens/boot_lib.input.txt and has the same milestones.  A milestone field
# may be a (first, last) range: it passes when any STATUS line in the range matches; mode
# "7/*" matches any phase of game mode 7; optional milestones are reported, never fail.
# (name, field or (first, last), overlay, game mode or None[, "optional"])
LIB_MS = [("control", 4600, 3, "6/100"), ("menu", 5000, 3, "17/*"), ("field", 5250, 3, "6/*"),
          ("encounter", (5250, 8000), 3, "7/*", "optional")]
BOOT_SCRIPT = {}


def lib_milestones(control):
    """Card-library milestones relative to the field where control starts (bootcheck.py
    finds it in a first pass and places the smoke actions relative to it, see
    bootcheck.lib_script): control, main menu open (17), back in the field after CIRCLE (both
    before any walking), then a forward walk and a box walk with
    and an optional random encounter (game mode 7) during the box walk."""
    c = control
    return [("control", c + 40, 3, "6/100"), ("menu", c + 160, 3, "17/*"), ("field", c + 340, 3, "6/*"),
            ("encounter", (c + 700, c + 3500), 3, "7/*", "optional")]
try:
    import cardlib as _cardlib
    for _n in _cardlib.LIBRARY:
        BOOT_FIXTURES[_n] = LIB_MS
        BOOT_SCRIPT[_n] = "lib"
except ImportError:  # pragma: no cover
    _cardlib = None


def exe_path(arg: str | None = None) -> Path:
    p = arg or os.environ.get("RG_FIXTURES_EXE")
    return Path(p).resolve() if p else DEFAULT_EXE


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def exe_id(exe: Path) -> str:
    return sha256(exe)[:16]


def fixture_dir(exe: Path) -> Path:
    return FIXTURES / exe_id(exe)


def load_manifest(d: Path) -> dict | None:
    m = d / "manifest.json"
    if not m.exists():
        return None
    return json.loads(m.read_text(encoding="utf-8"))


def game_env(extra: dict | None = None) -> dict:
    """The environment the fixtures are saved and loaded with (the init
    fingerprint must match: same GPU kind, GS worker setting, data dir)."""
    env = dict(os.environ)
    env.setdefault("RG_DATA", str(PORT / "data"))
    env.setdefault("RG_GPU", "hw")
    for k in [k for k in env if k.startswith("RG_TRACE_") or k in ("RG_TIMING", "RG_SS_AUDIT")]:
        if not (extra and k in extra):
            env.pop(k)
    if extra:
        env.update(extra)
    return env


# ---- the state file header (src/savestate/ss_core.c ss_fhdr, i686 layout) ----
HDR_BYTES = 560
M64 = (1 << 64) - 1


def ss_hash64(b: bytes, seed: int) -> int:
    """src/savestate/ss_heap.c ss_hash64."""
    h = 0xCBF29CE484222325 ^ ((seed * 0x9E3779B97F4A7C15) & M64)
    n = len(b) // 8 * 8
    for (v,) in struct.iter_unpack("<Q", b[:n]):
        h ^= v
        h = (h * 0x100000001B3) & M64
        h ^= h >> 29
    for c in b[n:]:
        h ^= c
        h = (h * 0x100000001B3) & M64
    h ^= h >> 33
    h = (h * 0xFF51AFD7ED558CCD) & M64
    h ^= h >> 33
    return h


def peek(path: Path) -> dict:
    """The header of a state file (no exe needed)."""
    b = Path(path).read_bytes()[:HDR_BYTES]
    if len(b) < HDR_BYTES or b[:8] != b"RGSTATE1":
        raise ValueError(f"{path}: not an rg-game save state")
    cstr = lambda x: x.split(b"\0", 1)[0].decode("utf-8", "replace")
    ver, hb = struct.unpack_from("<II", b, 8)
    field, vbl = struct.unpack_from("<QI", b, 120)
    kvbl, know, run_hash, created = struct.unpack_from("<QQQQ", b, 136)
    want = struct.unpack_from("<Q", b, 552)[0]
    ok = ss_hash64(b[:552] + b"\0" * 8, 0x484452) == want
    return {
        "version": ver, "hdr_bytes": hb, "build_id": cstr(b[16:56]),
        "field": field, "game_vbl": vbl, "kernel_vblank": kvbl, "kernel_now": know,
        "run_hash": "%016x" % run_hash, "created": created,
        "note": cstr(b[168:296]), "input": cstr(b[296:552]), "header_ok": ok,
    }


def rewrite_header(src: Path, dst: Path, build_id: str | None = None) -> None:
    """Copy a state with a changed build id and a VALID header checksum (the
    foreign-build control: the load must refuse it by build, not as corrupt)."""
    b = bytearray(Path(src).read_bytes())
    if build_id is not None:
        bid = build_id.encode()[:39]
        b[16:56] = bid + b"\0" * (40 - len(bid))
    b[552:560] = b"\0" * 8
    struct.pack_into("<Q", b, 552, ss_hash64(bytes(b[:560]), 0x484452))
    Path(dst).write_bytes(bytes(b))


def fresh(d: Path, exe: Path, names=None) -> tuple[bool, str]:
    """Is the fixture set in d usable with exe?  (ok, why-not)"""
    m = load_manifest(d)
    if not m:
        return False, "no manifest"
    if m.get("exe_sha256") != sha256(exe):
        return False, "built by another exe"
    for n in names or [x for x, _, _ in MILESTONES]:
        e = m.get("milestones", {}).get(n)
        if not e or not (d / e["file"]).exists():
            return False, f"milestone {n} missing"
    return True, ""


def say(*a):
    print(*a, flush=True)
    sys.stdout.flush()


# ---- crash reports (rg-game "EXCEPTION ... rva X" + "stack words in the image (rva): ..") ----
def map_symbols(map_path: Path):
    """[(rva, name)] sorted, from an rg-game.map (lld /MAP)."""
    import bisect  # noqa: F401
    import re
    syms = []
    for line in open(map_path, encoding="latin-1"):
        m = re.match(r"\s*000[1-9]:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{16})\s+", line)
        if m:
            syms.append((int(m.group(2), 16) - 0x400000, m.group(1)))
    syms.sort()
    return syms


def symbolize(map_path: Path, rvas):
    import bisect
    syms = map_symbols(map_path)
    keys = [a for a, _ in syms]
    out = []
    for r in rvas:
        i = bisect.bisect_right(keys, r) - 1
        out.append(f"{syms[i][1]}+{r - syms[i][0]:#x}" if i >= 0 else f"?{r:#x}")
    return out


def crash_report(log: str, exe: Path, max_words: int = 12):
    """Symbolized EXCEPTION lines of an rg-game log (empty list if none)."""
    import re
    mp = Path(exe).with_suffix(".map")
    out = []
    for i, ln in enumerate(log.splitlines()):
        m = re.search(r"EXCEPTION (0x[0-9A-F]+) at .*rva (0x[0-9A-F]+)\)?(.*)", ln)
        if not m:
            continue
        rvas = [int(m.group(2), 16)]
        for nxt in log.splitlines()[i + 1:i + 4]:
            if "stack words in the image" in nxt:
                rvas += [int(w, 16) for w in nxt.split(":", 1)[1].split()[:max_words]]
        names = symbolize(mp, rvas) if mp.exists() else [hex(r) for r in rvas]
        out.append(f"EXCEPTION {m.group(1)} at {names[0]}{m.group(3)}; stack: " + " <- ".join(names[1:]))
    return out
