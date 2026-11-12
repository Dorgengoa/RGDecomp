#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""How does each fixed battle start?  Scans trigger_param6 (rc/param/param_2_en.pac, 1081 triggers:
#4 header, #100 / #101 conditions, #102 action stream; all LSB-first base64 op streams,
condexpr.b64_lsb) and the map scripts (SB2 .stb, evscan.py) (lane scenario3 2026-11-11, start
decoding lane scenario4 2026-11-12).

    python tools/fixtures/trigscan.py [--ids 1029,1035,...]          # constants naming each battle
    python tools/fixtures/trigscan.py starts [--ids ..] [--all]      # how each battle is started

Fixed-battle constants come in two spellings: a typed constant (0x03 s16 / 0x05 s32) and the
query `23 05 98 99|9A <s16> 0B` (ScriptEvalQueryOpMaybe_3daaf0 selector 0x98 / 0x99: a named
fixed-battle id constant).  `23 03 98 02 0B` is the CURRENT battle id
(CharaSysGetEncounterIdMaybe_3a36d0), so a #101 `battle == B` condition is a battle-end trigger.
Action commands (`31 CMD 50 01 <arg> [60 02 <arg>].. 50 02 70 01`):
  0x0E (B, L)   arm fixed battle B for the event whose map-script label is L (the label routine
                runs BattleEncounterSetup, native 1534: the event ends in battle B)
  0x05 (N)      play event N (event_param5 #4: [N, 'EVcc-nnnn', '', group, _, label])
  0x1B (B)      start fixed battle B now (area masters, Mother Type 1-3 debug rows)
Start kinds printed by `starts`:
  field event   a trigger arms B and plays event N in the field (`scenario.py run event:EVcc-nnnn`)
  direct        a trigger starts B by 0x1B
  chained       a battle-end trigger (battle == A) plays event N whose map-script label routine
                calls BattleRebindEncounterMaybe (native 1603, PUSHIMM B): B starts from inside
                battle A's end (game mode 0xB over 7), never from the field -- no event: start
"""
from __future__ import annotations

import argparse
import functools
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import condexpr  # noqa: E402
import rgdata  # noqa: E402

REBIND = 1603    # EvCmdBattleRebindEncounterMaybe_25b890 (system-VM native id, data2c_0044D6F0)
_B = rb"(?:\x03(..)|\x23\x05\x98[\x99\x9a](..)\x0b)"            # battle-id expression
_N = rb"(?:\x03(..)|\x25\x07\x01\x03(..)\x00\x00\x05)"              # number (label / event)
RX_ARM = re.compile(rb"\x31\x0e\x50\x01" + _B + rb"\x60\x02" + _N + rb"\x50\x02\x70\x01", re.S)
RX_EVENT = re.compile(rb"\x31\x05\x50\x01" + _N + rb"\x50\x02\x70\x01", re.S)
RX_START = re.compile(rb"\x31\x1b\x50\x01" + _B + rb"\x50\x02\x70\x01", re.S)
RX_END = re.compile(rb"\x23\x03\x98\x02\x0b" + _B + rb"\x80\x01", re.S)   # battle == B


def _s16(*gs):
    g = next(x for x in gs if x is not None)
    return struct.unpack("<h", g)[0]


@functools.lru_cache(None)
def triggers():
    out, cur = [], None
    for k, r in rgdata.table("trigger_param6.cfg.bin"):
        if k == 4:
            cur = {"head": r, 100: "", 101: "", 102: ""}
            out.append(cur)
        elif cur is not None and k in (100, 101, 102):
            cur[k] = r[0] if r else ""
    return out


def stream(t, k):
    return condexpr.b64_lsb(t[k]) if t[k] else b""


def consts(b: bytes):
    for j in range(len(b)):
        if b[j] == 3 and j + 3 <= len(b):
            yield j, struct.unpack_from("<h", b, j + 1)[0]
        elif b[j] == 5 and j + 5 <= len(b):
            yield j, struct.unpack_from("<i", b, j + 1)[0]
        elif b[j:j + 3] == b"\x23\x05\x98" and j + 7 <= len(b) and b[j + 3] in (0x99, 0x9A):
            yield j, struct.unpack_from("<h", b, j + 4)[0]   # named fixed-battle constant (query 0x98)


def scan(ids):
    hits = {i: [] for i in ids}
    for n, t in enumerate(triggers()):
        for k in (100, 101, 102):
            b = stream(t, k)
            for j, v in consts(b):
                if v in hits:
                    hits[v].append((n, k, j, b.hex()))
    return hits


@functools.lru_cache(None)
def events():
    """{event number: (name, label)} from event_param5 #4."""
    return {r[0]: (r[1], r[5]) for k, r in rgdata.table("event_param5.cfg.bin") if k == 4 and len(r) > 5}


@functools.lru_cache(None)
def event_planets():
    """{event name: planet} from event_param5 #100 [0] (the planet the event plays on; > 0 only)."""
    out, cur = {}, None
    for k, r in rgdata.table("event_param5.cfg.bin"):
        if k == 4:
            cur = r[1]
        elif k == 100 and cur and r and isinstance(r[0], int) and r[0] > 0:
            out.setdefault(cur, r[0])
    return out


@functools.lru_cache(None)
def func_boxes():
    """{event func id: [(map cfg, x, y, z, rot_y, sx, sy, sz)]}: the `FUNC_DATA "event"` boxes of the
    map definitions (map/**/<map>.cfg: FUNC_EVENT_DATA id, FUNC_POS x y z rx ry rz sx sy sz).  A
    trigger's #101 `Q[1a 0d] == Q[1a 1b <id>]` is "the party is in event box <id>"
    (ActionPacketInitAreaTriggerMaybe_3e36b0 m14; the box test is MapAreaTriggerEventsMaybe_200950,
    run on an investigate press (CROSS) in field control, FieldExploreModeUpdate_2833a0)."""
    import gamedata
    a = gamedata.Archive()
    rx = re.compile(r'FUNC_DATA\s+"event";(.*?)FUNC_DATA_END', re.S)
    out = {}
    for n in sorted(a.files):
        low = n.lower().replace("\\", "/")
        if not (low.startswith("map/") and low.endswith(".cfg")):
            continue
        for m in rx.finditer(a.get(n).decode("latin1")):
            body = re.sub(r"//[^\n]*", "", m.group(1))
            ev = re.search(r"FUNC_EVENT_DATA\s+(-?\d+)", body)
            pos = re.search(r"FUNC_POS\s+([^;]+);", body)
            if ev and pos:
                try:
                    v = [float(x) for x in pos.group(1).replace(",", " ").split()]
                except ValueError:   # a typo in the source ('6702.48.85'): the game's parser differs
                    continue
                if len(v) >= 9:
                    out.setdefault(int(ev.group(1)), []).append((n, v[0], v[1], v[2], v[4], v[6], v[7], v[8]))
    return out


RX_BOX = re.compile(rb"[\x20-\x2f]\x03\x1a\x0d\x0b[\x20-\x2f]\x05\x1a[\x1b\x1c](..)\x0b\x80\x01", re.S)   # box == id


def event_box(ev):
    """Where does the field event `ev` ('EV10-0090') start?  -> {trigger, box, zone, planet, map,
    x, y, z, yaw} for the first trigger that plays it with a `party in event box` condition, else
    None.  zone = trigger #4 [5] (planet_zone_param #403 id, e.g. 280 RZ08 Johannasburg)."""
    num = {v[0].upper(): k for k, v in events().items()}.get(ev.upper())
    if num is None:
        return None
    boxes = func_boxes()
    for n, t in enumerate(triggers()):
        act = stream(t, 102)
        if not any(_s16(m.group(1), m.group(2)) == num for m in RX_EVENT.finditer(act)):
            continue
        m = RX_BOX.search(stream(t, 101))
        if not m:
            continue
        fid = _s16(m.group(1))
        for (mp, x, y, z, ry, sx, sy, sz) in boxes.get(fid, []):
            return {"trigger": n, "box": fid, "zone": t["head"][5], "planet": event_planets().get(ev.upper()),
                    "map": mp, "x": x, "y": y, "z": z, "yaw": ry, "size": (sx, sy, sz)}
    return None


@functools.lru_cache(None)
def label_rebinds():
    """{map-script label: [(script, rebind target)]}: label routines of the map scripts (map/**.stb,
    loose or in a .pac) that call BattleRebindEncounterMaybe with an immediate (INVT / none = -1)."""
    import evscan
    out = {}
    for name, mem, b in evscan.scripts(r"^map[\\/]"):
        _, code, _labs = evscan.header(b)
        sites = evscan.native_sites(b, [REBIND])
        if not sites:
            continue
        ents = evscan.entries(b)
        for _i, o in sites:
            st, _en = evscan.routine_of(b, o)
            op, x, y = struct.unpack_from("<iii", b, code + o + 12)
            nop = struct.unpack_from("<i", b, code + o + 24)[0]
            tgt = y if op == 3 and x == 1 and nop == 21 else -1
            for lid in (ents[st][3] if st in ents else []):
                out.setdefault(lid, []).append((name + (" :: " + mem if mem else ""), tgt))
    return out


def starts():
    """{fixed id: [start dict]}: kind field / direct / chained (module docstring)."""
    ev = events()
    reb = label_rebinds()
    out = {}
    for n, t in enumerate(triggers()):
        act = stream(t, 102)
        if not act:
            continue
        plays = [_s16(m.group(1), m.group(2)) for m in RX_EVENT.finditer(act)]
        for m in RX_ARM.finditer(act):
            fid, lab = _s16(m.group(1), m.group(2)), _s16(m.group(3), m.group(4))
            # the event played next to it; else the event whose label is L (EV01-0070 for 1003)
            for e in plays or [k for k, v in sorted(ev.items()) if v[1] == lab][:1] or [None]:
                out.setdefault(fid, []).append({"kind": "field event", "trigger": n, "event": e,
                                                "event_name": ev.get(e, ("", ""))[0], "label": lab})
        for m in RX_START.finditer(act):
            out.setdefault(_s16(m.group(1), m.group(2)), []).append({"kind": "direct", "trigger": n})
        ends = [_s16(m.group(1), m.group(2)) for m in RX_END.finditer(stream(t, 101))]
        for a in ends:
            for e in plays:
                name, lab = ev.get(e, ("", None))
                for scr, b in reb.get(lab, []):
                    if b >= 0:
                        out.setdefault(b, []).append({"kind": "chained", "trigger": n, "after": a, "event": e,
                                                      "event_name": name, "label": lab, "script": scr})
    return out


@functools.lru_cache(None)
def dev_sections():
    """{fixed id: [initial_status5 section]}: developer start states that queue the battle directly
    (WorldData command 117 SetPendingEncounter; debug sections 20010.. 'ボス戦【..】').  Not a story
    start: lane scenario5 found 1024 / 1025 Libra King ('角王' A / B) ONLY here (sections 20230 /
    20240) -- no trigger_param6 stream, map / event / NPC script immediate, zone or map table on
    either disc names them."""
    out = {}
    for sid, v in sorted(rgdata.sections().items()):
        if v.get("encounter") is not None:
            out.setdefault(v["encounter"], []).append(sid)
    return out


def describe(s):
    if s["kind"] == "field event":
        b = event_box(s["event_name"]) if s.get("event_name") else None
        where = f", event box {b['box']} zone {b['zone']} planet {b['planet']}" if b else ""
        return f"field event {s['event_name'] or '?'} (#{s['event']}, label {s['label']}) from trigger #{s['trigger']}{where}"
    if s["kind"] == "direct":
        return f"direct start (0x1B) in trigger #{s['trigger']}"
    return (f"chained: end of battle {s['after']} -> trigger #{s['trigger']} plays {s['event_name']} "
            f"(#{s['event']}, label {s['label']} in {s['script']}) -> BattleRebindEncounter")


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    mode = argv.pop(0) if argv and argv[0] == "starts" else "consts"
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ids", help="comma list of fixed battle ids")
    ap.add_argument("--all", action="store_true", help="starts: every fixed battle, not just bosses")
    a = ap.parse_args(argv)
    import progression
    rows = {int(r["id"]): r for r in progression.read() if r["kind"] in ("boss", "fixed")}
    if a.ids:
        ids = [int(x) for x in a.ids.split(",")]
    else:
        ids = sorted(i for i, r in rows.items() if a.all or mode == "consts" or r["kind"] == "boss")
    if mode == "starts":
        st = starts()
        for i in ids:
            r = rows.get(i, {})
            ss = st.get(i, [])
            # one line per distinct start (a chain event can be in several map scripts)
            seen, lines = set(), []
            for s in ss:
                key = (s["kind"], s.get("event"), s.get("after"), s.get("trigger"))
                if key in seen:
                    continue
                seen.add(key)
                scr = sorted({x["script"] for x in ss if x["kind"] == "chained" and x.get("event") == s.get("event")})
                if s["kind"] == "chained":
                    s = dict(s, script=", ".join(scr))
                lines.append(describe(s))
            dev = dev_sections().get(i)
            none = "no start found" + (f" (developer start state only: section {', '.join(map(str, dev))})" if dev else "")
            print(f"{i} {r.get('name', '')} [census event {r.get('event') or '-'}]: " + ("; ".join(lines) or none))
        n = sum(1 for i in ids if st.get(i))
        print(f"trigscan starts: {n}/{len(ids)} battles with a start found")
        return 0
    hits = scan(ids)
    for i in ids:
        nm = rows.get(i, {}).get("name", "")
        h = hits[i]
        print(f"{i} {nm}: " + ("; ".join(f"trigger #{n} key {k} at byte {j}" for n, k, j, _ in h) if h else "no trigger_param6 constant"))
    print(f"trigscan: {sum(bool(v) for v in hits.values())}/{len(ids)} fixed battles named by a trigger_param6 constant")
    return 0


if __name__ == "__main__":
    sys.exit(main())
