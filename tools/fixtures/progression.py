#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""The game's order of events, extracted from its own tables (docs/GAME-PROGRESSION.md):
chapters / phases / start-state sections, story bosses and other fixed battles (where, when,
which story section is the last one before them), and the random-encounter tables per planet
area (which enemies, under which story condition).  Writes census/progression.tsv, which
tools/fixtures/scenario.py reads.  Game-derived names only (no code / assets).

    python tools/fixtures/progression.py [--out census/progression.tsv] [--md]   # --md: print the doc tables

Sources (all in data/DATA0_0 through gamedata.py / cfgdump.py / rgdata.py):
- rc/param/phase_param_EN (chapters, phases), rc/param/initial_status5 (sections: the
  developers' start states, with the story flags each one sets),
- param_2_en.pac fixed_encount_param_EN (fixed battles: #4 id, 'Chapter N: Boss Battle/Name',
  party members; #301 party positions; #102 enemies + positions), monster_param_EN (names),
  encount_group_param_EN (random groups: #4 id + name, #102 members),
- rc/param/planet/<pl>_2_en.pac <PL>_encount_param_EN (#4 table id + area name, #200 location,
  #201 condition string -> condexpr.py, #204 group id + weight), planet_zone_param_2_EN (planets),
- dbg/map_jump_en.txt (debug jump points: planet + position + label; labels name the events
  'EV05_0090_0 ...'), bit_flag_param_EN (story flag names: 'EV05-0090' = that event seen).

Boss rows: planet = the planet of the nearest debug jump point to the party's battle position
(PLANET_FIX overrides the few where that is wrong / far); trigger event = the nearest jump
labelled with an event on that planet; section = the last initial_status5 section (in story
order) that does NOT yet set the trigger event's flag, among the boss's chapter (SECTION_FIX
overrides).  These three are derived, so check them against a run (scenario.py run) before
trusting a new one; the rows proven so far are listed in docs/GAME-PROGRESSION.md."""
from __future__ import annotations

import argparse
import math
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import cfgdump  # noqa: E402
import condexpr  # noqa: E402
import gamedata  # noqa: E402
import rgdata  # noqa: E402

ROOT = HERE.parents[1]
OUT = ROOT / "census" / "progression.tsv"
PLANET_PACS = ["da", "rz", "jr", "zl", "bd", "mg", "gs", "ex", "sp", "rs", "ar"]

# planet of a fixed battle where the nearest jump point is on the wrong planet or > 3,000 away
# (Johanna = Rosa's Johannasburg area, Alistia = planet 21 as cardlib's alistia card)
PLANET_FIX = {1035: 2, 1055: 21, 1056: 21, 1057: 21}
# story section where the flag rule picks none / a wrong one (chapter 14 = the ghost ship /
# post-game sections; area masters = the late-game story point, as cardlib's late_game)
SECTION_FIX = {1029: 9010}   # Zegram on the deck: phase 9020 is 'After Zegram Runs Off'
# chapter 8's three sub-chapters run in any order: the boss's planet picks one (8-A Vedan,
# 8-B Juraika, 8-C Zerard; section ids 81xx / 82xx / 83xx)
CH8_SUB = {5: 1, 3: 2, 4: 3}
CHAPTER_SECTIONS = {14: [14010], "Ghost Ship EX": [14030], "Alistia": [28010], "Area Master": [13020],
                    "TGS Area Master": [13020], "Help Event": [13020], "Factory Extra": [13020], "Mimic": [13020]}


def monster_names():
    names = {}
    for kind, r in rgdata.table("monster_param_EN.cfg.bin"):
        if kind == 4 and len(r) > 3 and isinstance(r[3], str) and r[3]:
            names[r[0]] = r[3]
    return names


def planets():
    """{planet id: (code, name)} + {code: id}."""
    by_id, by_code = {}, {}
    for k, a in rgdata.table("planet_zone_param_2_EN.cfg.bin"):
        if k == 401:
            by_id[a[0]] = (a[1], a[2])
            by_code[a[1].lower()] = a[0]
    by_id.setdefault(21, ("AR", "Alistia"))
    return by_id, by_code


def groups():
    out, cur = {}, None
    for k, r in rgdata.table("encount_group_param_EN.cfg.bin"):
        if k == 4:
            cur = out[r[0]] = (r[1], [])
        elif k == 102 and cur:
            cur[1].append(r[0])
    return out


def fixed_battles():
    out, cur = [], None
    for k, a in rgdata.table("fixed_encount_param_EN.cfg.bin"):
        if k == 4:
            cur = {"id": a[0], "label": a[1], "party_ids": [x for x in a[9:12] if x != -1], "pos": [], "enemies": []}
            out.append(cur)
        elif cur is None:
            continue
        elif k == 301:
            cur["pos"].append(a)
        elif k == 102:
            cur["enemies"].append(a)
    return out


def event_of(label):
    m = re.match(r"(?i)\s*ev(\d\d)[-_](\d{4})", label or "")
    return f"EV{m.group(1)}-{m.group(2)}" if m else None


def section_order():
    """Section ids in story order (chapter sections, then chapter-14 / Alistia ones)."""
    return sorted(rgdata.sections())


def chapter_key(label):
    head = label.split("/")[0].split(":")[0].strip()
    m = re.match(r"Chapter (\d+)", head)
    if m:
        return int(m.group(1))
    return head


def section_for(fid, chap, ev_flag, planet=None):
    if fid in SECTION_FIX:
        return SECTION_FIX[fid], "fixed"
    if not isinstance(chap, int) or chap >= 14:
        for k, v in CHAPTER_SECTIONS.items():
            if chap == k or (isinstance(chap, str) and chap.startswith(str(k))):
                return v[0], "chapter"
        return 13020, "default"
    secs = rgdata.sections()
    cands = [s for s in section_order() if s // 1000 == chap]
    if chap == 8 and planet in CH8_SUB:
        cands = [s for s in cands if s // 100 % 10 == CH8_SUB[planet]]
    if not cands:
        return None, "none"
    if ev_flag is None:
        return cands[-1], "chapter-last"
    before = [s for s in cands if not any(n == ev_flag and v for n, v in secs[s]["flags"])]
    if not before:
        return cands[0], "chapter-first"
    return before[-1], "flag"


def boss_rows():
    jumps = rgdata.map_jumps()
    names = monster_names()
    charas = rgdata.charas()
    pl_names, _ = planets()
    flags = {v: k for k, v in rgdata.flag_names().items()}
    rows = []
    for f in fixed_battles():
        pos = next((p for p in f["pos"] if p[1] != -1 and any(p[2:5])), None)
        epos = f["enemies"][0][3:6] if f["enemies"] else [0, 0, 0]
        here = pos[2:5] if pos else epos
        yaw = pos[5] if pos else 0.0
        near = sorted((math.dist(here, j[1:4]), k, j[0], j[5]) for k, j in jumps.items())
        planet = PLANET_FIX.get(f["id"])
        dist = None
        chap = chapter_key(f["label"])
        if planet is None and any(here):
            dist, _, planet, _ = near[0]
            # planets reuse coordinates: a jump within +600 of the nearest that names an event
            # of the battle's own chapter (EVcc) wins (Albioth: Rosa 346 vs Mariglenn EV11 387)
            if isinstance(chap, int):
                own = [n for n in near if n[0] <= near[0][0] + 600 and (event_of(n[3]) or "").startswith(f"EV{chap:02d}")]
                if own:
                    dist, _, planet, _ = own[0]
        evs = [(d, k, lab) for d, k, pl, lab in near if pl == planet and event_of(lab)]
        ev = event_of(evs[0][2]) if evs and evs[0][0] < 1500 else None
        ev_jump = evs[0][1] if evs and evs[0][0] < 1500 else None
        chap = chapter_key(f["label"])
        flag = flags.get(ev) if ev else None
        sec, how = section_for(f["id"], chap, flag, planet)
        label = f["label"]
        kind = "boss" if "Boss Battle" in label or "Area Master" in label else "fixed"
        rows.append({
            "kind": kind, "id": f["id"], "name": label.split("/", 1)[-1], "chapter": chap,
            "label": label, "planet": planet if planet is not None else "",
            "planet_name": pl_names.get(planet, ("", ""))[1] if planet is not None else "",
            "spawn": (f"{here[0]:.2f},{here[1]:.2f},{here[2]:.2f},{yaw:.2f}" if any(here) else ""),
            "jump": near[0][1] if dist is not None else "", "jump_dist": round(dist) if dist is not None else "",
            "event": ev or "", "event_jump": ev_jump or "", "event_flag": flag if flag is not None else "",
            "section": sec or "", "section_rule": how,
            "enemies": ", ".join(names.get(e[1], str(e[1])) for e in f["enemies"]),
            "party": ", ".join(charas.get(x, str(x)) for x in f["party_ids"]),
        })
    return rows


def readable(cond):
    """condexpr output with names: flag / var names, progress codes as chapters."""
    fl, vr = rgdata.flag_names(), rgdata.var_names()

    def prog(m):
        c = int(m.group(1))
        ch, sub = divmod(c, 10)
        return f"progress(ch{ch}{'-' + 'ABC'[sub - 1] if sub else ''})"
    cond = re.sub(r"progress\[(\d+)\]", prog, cond)
    cond = re.sub(r"\bflag\[(\d+)\]", lambda m: f"flag[{m.group(1)} {fl.get(int(m.group(1)), '')}]".replace(" ]", "]"), cond)
    cond = re.sub(r"\bvar\[(\d+)\]", lambda m: f"var[{m.group(1)} {vr.get(int(m.group(1)), '')}]".replace(" ]", "]"), cond)
    return cond


def encounter_rows():
    a = gamedata.Archive()
    by_id, by_code = planets()
    g = groups()
    names = monster_names()
    rows = []
    sep = chr(92)
    for pl in PLANET_PACS:
        try:
            b = a.get(f"rc{sep}param{sep}planet{sep}{pl}_2_en.pac")
        except KeyError:
            continue
        for nm, off, size in gamedata.pac_members(b):
            if not nm.lower().endswith("_encount_param_en.cfg.bin"):
                continue
            cur = None
            for k, r in cfgdump.parse(b[off:off + size]):
                if k == 4:
                    cur = {"kind": "encounter", "planet": by_code.get(pl, ""), "planet_name": by_id.get(by_code.get(pl), ("", pl))[1],
                           "id": r[0], "name": r[1], "location": "", "condition": "always", "groups": []}
                    rows.append(cur)
                elif cur is None:
                    continue
                elif k == 200:
                    cur["location"] = r[0]
                elif k == 201:
                    cur["condition"] = readable(condexpr.decode(r[0]))
                elif k == 204:
                    cur["groups"].append((r[0], r[1]))
    for r in rows:
        mons = []
        for gid, _w in r["groups"]:
            for m in g.get(gid, ("", []))[1]:
                n = names.get(m, str(m))
                if n not in mons:
                    mons.append(n)
        r["enemies"] = ", ".join(mons)
        r["group_ids"] = " ".join(str(x) for x, _ in r["groups"])
    return rows


def phase_rows():
    rows, titles = rgdata.phases()
    secs = rgdata.sections()
    out = []
    for ch, sub, letter, ph in rows:
        for v, title in ph:
            sid = ch * 1000 + sub * 100 + v
            var = [s for s in secs if s // 10 == sid // 10]
            out.append({"kind": "phase", "chapter": f"{ch}{letter}", "id": sid, "name": title,
                        "label": titles.get(ch, ""), "section": " ".join(map(str, sorted(var)))})
    return out


COLS = ["kind", "chapter", "id", "name", "planet", "planet_name", "section", "section_rule", "event", "event_flag",
        "event_jump", "spawn", "jump", "jump_dist", "enemies", "party", "location", "condition", "group_ids", "label"]


def write(path: Path):
    rows = phase_rows() + boss_rows() + encounter_rows()
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# progression census (tools/fixtures/progression.py; docs/GAME-PROGRESSION.md): game-derived\n")
        f.write("# kinds: phase (chapter phase + its initial_status5 sections), boss / fixed (fixed_encount_param_EN),\n")
        f.write("# encounter (per-planet random-encounter tables, condition decoded by condexpr.py)\n")
        f.write("\t".join(COLS) + "\n")
        for r in rows:
            f.write("\t".join(str(r.get(c, "")).replace("\t", " ") for c in COLS) + "\n")
    return rows


def read(path: Path = OUT):
    """[{col: str}] of census/progression.tsv (made on first use)."""
    if not path.exists():
        write(path)
    lines = [ln for ln in path.read_text(encoding="utf-8").splitlines() if ln and not ln.startswith("#")]
    head = lines[0].split("\t")
    return [dict(zip(head, ln.split("\t"))) for ln in lines[1:]]


def story_key(r):
    c = r["chapter"]
    return (int(c) if str(c).isdigit() else 99, int(r["section"] or 0), r["event"] or "~", int(r["id"]))


def markdown(rows):
    """The generated tables of docs/GAME-PROGRESSION.md."""
    L = []
    ph = [r for r in rows if r["kind"] == "phase"]
    L += ["### Chapters, phases and start-state sections", "",
          "Source: phase_param_EN (chapter / phase titles), initial_status5 (section ids: chapter x 1000 + "
          "sub-chapter x 100 + phase; `(2)`.. variants share the phase).", "",
          "| Chapter | Phase id | Phase | Sections |", "| --- | --- | --- | --- |"]
    last = None
    for r in ph:
        ch = f"{r['chapter']} {r['label']}" if r["chapter"] != last else ""
        last = r["chapter"]
        L.append(f"| {ch} | {r['id']} | {r['name']} | {r['section']} |")
    fx = [r for r in rows if r["kind"] in ("boss", "fixed")]
    story = sorted([r for r in fx if str(r["chapter"]).isdigit() and int(r["chapter"]) <= 13], key=story_key)
    L += ["", "### Story battles in story order (chapters 1-13)", "",
          "Source: fixed_encount_param_EN (id, label, enemies, party, party position); planet = nearest debug "
          "jump point (dbg/map_jump_en.txt) to the party position (`jump`, distance in world units); trigger "
          "event = nearest jump labelled with an event (< 1,500 units) and its story flag (bit_flag_param_EN); "
          "section = the last initial_status5 section of the chapter that does not set that flag "
          "(`section_rule`; progression.py SECTION_FIX / PLANET_FIX for the exceptions).  `scenario.py run ID` "
          "starts the battle from that section.", "",
          "| # | Ch | Id | Battle | Kind | Planet | Trigger event (flag) | Section | Enemies | Party |",
          "| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |"]
    for i, r in enumerate(story, 1):
        ev = f"{r['event']} ({r['event_flag']})" if r["event"] else "-"
        L.append(f"| {i} | {r['chapter']} | {r['id']} | {r['name']} | {r['kind']} | {r['planet_name'] or r['planet']} | "
                 f"{ev} | {r['section']} ({r['section_rule']}) | {r['enemies']} | {r['party']} |")
    post = [r for r in fx if r not in story]
    L += ["", "### Post-game and optional fixed battles", "",
          "Chapter 14 = rematches / the ghost ship; Ghost Ship EX floors; Alistia; area masters (bounty "
          "hunter targets: found in the field, story-independent once the area is open); help / factory "
          "battles (tutorial set pieces).  Sections: cardlib's post-game start points (13020 + 14010 / "
          "14030 / 28010) or 13020.", "",
          "| Id | Group | Battle | Planet | Event (flag) | Section | Enemies |", "| --- | --- | --- | --- | --- | --- | --- |"]
    for r in sorted(post, key=lambda r: int(r["id"])):
        grp = r["label"].split("/")[0].split(":")[0]
        ev = f"{r['event']} ({r['event_flag']})" if r["event"] else "-"
        L.append(f"| {r['id']} | {grp} | {r['name']} | {r['planet_name'] or r['planet']} | {ev} | {r['section']} | "
                 f"{r['enemies']} |")
    enc = [r for r in rows if r["kind"] == "encounter"]
    L += ["", "### Random encounters by planet and area", "",
          "Source: rc/param/planet/<pl>_2_en.pac <PL>_encount_param_EN: one table per area and story "
          "condition (#201, decoded by condexpr.py: `progress(chN)` = that chapter's progress slot, "
          "phase value; `chapter` = current chapter); enemies = the members of its encounter groups "
          "(encount_group_param_EN, `scenario.py groups NAME` / `scenario.py run enemy:NAME`).", ""]
    for pl in dict.fromkeys(r["planet_name"] for r in enc):
        L += [f"#### {pl}", "", "| Table | Area | Condition | Enemies |", "| --- | --- | --- | --- |"]
        for r in enc:
            if r["planet_name"] == pl:
                L.append(f"| {r['id']} | {r['name']} | {r['condition']} | {r['enemies']} |")
        L.append("")
    where = {}
    for r in enc:
        for e in r["enemies"].split(", "):
            if e:
                where.setdefault(e, [])
                k = f"{r['planet_name']}: {r['name'].split(':')[0]}"
                if k not in where[e]:
                    where[e].append(k)
    # formations: every encount_group_param group (a formation = one random battle's enemy
    # set), by zone prefix, with the area tables that roll it (an area table rolls one of its
    # groups per encounter; #204 weights)
    g = groups()
    names = monster_names()
    used = {}
    for r in enc:
        for x in r["group_ids"].split():
            used.setdefault(int(x), []).append(r["id"])
    zones = {}
    for gid, (gname, mem) in sorted(g.items()):
        zones.setdefault(gname.split("_")[0].upper(), []).append((gid, gname, mem))
    zarea = {}
    for r in enc:
        for x in r["group_ids"].split():
            z = g.get(int(x), ("?_", []))[0].split("_")[0].upper()
            a = f"{r['planet_name']}: {r['name'].split(':')[0]}"
            if a not in zarea.setdefault(z, []):
                zarea[z].append(a)
    L += ["### Encounter formations by zone", "",
          "Source: encount_group_param_EN (#4 group id + developer name `<ZONE>_<formation>`, #102 members; "
          "`scenario.py groups NAME`).  A group is only loaded on its own zone's maps, so "
          "`scenario.py run enemy:NAME` needs a card in that zone (scenario.py ZONE_CARDS).  `Tables` = the "
          "area tables above that roll the group (one group per random battle, #204 weight).  Planets without "
          "random encounters (no `<PL>_encount_param_EN` table): the Dorgenark (da), space (sp), Rose "
          "Nebula (rs).  TGS / E3 = trade-show demo groups, not met in the retail story.", ""]
    for z, gl in zones.items():
        L += [f"#### {z} ({'; '.join(zarea.get(z, [])[:4]) or 'no area table'})", "",
              "| Group | Formation | Members | Tables |", "| --- | --- | --- | --- |"]
        for gid, gname, mem in gl:
            L.append(f"| {gid} | {gname.split('_', 1)[-1]} | {', '.join(names.get(m, str(m)) for m in mem)} | "
                     f"{' '.join(str(t) for t in used.get(gid, [])) or '-'} |")
        L.append("")
    L += ["### Enemy index (random encounters)", "", "| Enemy | Planet: area (first word group of the area name) |",
          "| --- | --- |"]
    for e in sorted(where, key=str.lower):
        L.append(f"| {e} | {'; '.join(where[e][:6])}{' ..' if len(where[e]) > 6 else ''} |")
    return "\n".join(L) + "\n"


BEGIN, END = "<!-- progression.py --md: generated below, do not edit -->", "<!-- progression.py --md: end -->"


def write_md(path: Path, rows):
    t = path.read_text(encoding="utf-8") if path.exists() else f"{BEGIN}\n{END}\n"
    a, b = t.index(BEGIN), t.index(END)
    path.write_text(t[:a + len(BEGIN)] + "\n\n" + markdown(rows) + "\n" + t[b:], encoding="utf-8")


def check(rows):
    """Completeness of the census / doc (progression.py --check): -> [(what, detail)] gaps."""
    gaps = []
    fx = [r for r in rows if r["kind"] in ("boss", "fixed")]
    import trigscan   # how is the battle started? (lane scenario3 constants, lane scenario4 start decoding)
    starts = trigscan.starts()
    for r in fx:
        miss = [k for k in ("section", "planet", "spawn") if not r[k]]
        if miss:
            gaps.append(("battle without " + "/".join(miss), f"{r['id']} {r['name']}"))
        if r["kind"] == "boss" and str(r["chapter"]).isdigit() and not r["event"]:
            ss = starts.get(int(r["id"]), [])
            fe = [s for s in ss if s["kind"] == "field event"]
            ch = [s for s in ss if s["kind"] == "chained"]
            if fe:
                bx = trigscan.event_box(fe[0]["event_name"]) or {}
                how = f"started by field event {fe[0]['event_name']} (trigger_param6 #{fe[0]['trigger']}, "                       f"event box {bx.get('box', '?')}; target event:{fe[0]['event_name']})"
            elif ch:
                how = f"CHAINED after battle {ch[0]['after']} ({ch[0]['event_name']} in battle, BattleRebind): no field start"
            else:
                how = "no start found in trigger_param6 / map scripts"
            gaps.append(("story boss without census trigger event", f"{r['id']} {r['name']} (ch{r['chapter']}, "
                                                                     f"section {r['section']} {r['section_rule']}; {how})"))
    for r in fx:
        if r["kind"] == "boss" and not starts.get(int(r["id"])):
            dev = trigscan.dev_sections().get(int(r["id"]))
            gaps.append(("boss with no decoded start", f"{r['id']} {r['name']} (census event {r['event'] or '-'}"
                         + (f"; developer start state only: section {', '.join(map(str, dev))}" if dev else "") + ")"))
    enc = [r for r in rows if r["kind"] == "encounter"]
    used = {int(x) for r in enc for x in r["group_ids"].split()}
    for gid, (gname, mem) in sorted(groups().items()):
        if gid not in used:
            gaps.append(("formation in no area table", f"{gid} {gname}"))
    for r in enc:
        if not r["group_ids"]:
            gaps.append(("area table without groups", f"{r['id']} {r['name']}"))
        if not r["location"]:
            gaps.append(("area table without location", f"{r['id']} {r['name']}"))
    a = gamedata.Archive()
    sep = chr(92)
    have = {r["planet_name"] for r in enc}
    by_id, by_code = planets()
    for pl in PLANET_PACS:
        nm = by_id.get(by_code.get(pl), ("", pl))[1]
        if nm not in have:
            try:
                b = a.get(f"rc{sep}param{sep}planet{sep}{pl}_2_en.pac")
            except KeyError:
                gaps.append(("planet pac missing", pl))
                continue
            n = sum(1 for m, off, size in gamedata.pac_members(b) if m.lower().endswith("_encount_param_en.cfg.bin")
                    for k, _r in cfgdump.parse(b[off:off + size]) if k == 4)
            gaps.append(("planet without area tables" if n == 0 else "planet tables not in the doc", f"{pl} {nm} ({n} tables)"))
    return gaps


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=str(OUT))
    ap.add_argument("--md", nargs="?", const=str(ROOT / "docs" / "GAME-PROGRESSION.md"),
                    help="also rewrite the generated tables of docs/GAME-PROGRESSION.md")
    ap.add_argument("--check", action="store_true", help="list completeness gaps (no write)")
    a = ap.parse_args(argv)
    if a.check:
        from collections import Counter
        g = check(read())
        for what, n in Counter(w for w, _ in g).items():
            print(f"{what}: {n}")
        for what, d in g:
            print(f"  {what}: {d}")
        return 0
    rows = write(Path(a.out))
    if a.md:
        write_md(Path(a.md), read(Path(a.out)))
    from collections import Counter
    print(f"progression: {a.out}: " + ", ".join(f"{k} {v}" for k, v in Counter(r['kind'] for r in rows).items()))
    return 0


if __name__ == "__main__":
    sys.exit(main())
