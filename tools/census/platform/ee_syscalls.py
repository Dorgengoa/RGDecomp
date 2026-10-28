#!/usr/bin/env python3
"""platform_ee_syscalls.tsv -- EE kernel surface.

Sections (column `kind`):
  syscall   every `syscall` instruction in the retail images, with the number
            loaded into $v1 (`addiu $3,$0,N`) and the stub symbol.  Negative
            numbers are the interrupt-context (i*) variants.  `game_direct` =
            distinct game functions that jal the stub; `reached` = reachable
            from game code through library call/tail/addr edges; `via` = up to
            3 boundary functions the game calls that lead to it.
  thread    CreateThread call sites: entry/stack/stack size/gp/priority read
            from the ThreadParam the caller fills (linear const-prop over the
            retail code; '?' = not a straight-line constant)
  start     StartThread sites (tid source, arg)
  prio      ChangeThreadPriority / RotateThreadReadyQueue sites
  sema      CreateSema sites: init_count / max_count from SemaParam
  intc      AddIntcHandler / AddDmacHandler (+_2 variants) sites: cause or
            channel, handler, next
  alarm     SetAlarm/iSetAlarm/SetTimerAlarm/iSetTimerAlarm sites
Value columns: a0..a2 = argument registers; p_* = struct fields.
"""
from __future__ import annotations

import sys
from collections import Counter, defaultdict, deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

COLS = ["kind", "num", "symbol", "addr", "family_sub", "site_image", "caller",
        "caller_is_game", "site", "game_direct", "reached", "via",
        "a0", "a1", "a2", "p_entry", "p_stack", "p_stack_size", "p_gp",
        "p_priority", "note", "src"]


def via_names(m, vk):
    """boundary API names, nearest first."""
    return [m.by_addr[a].name for (_, a), d in
            sorted(vk.items(), key=lambda kv: (kv[1], m.by_addr[kv[0][1]].name))]


def boundary_closure(imgs, edges):
    """lib fn key -> list of boundary lib fns (game-called) that reach it."""
    out = defaultdict(set)
    for e in edges:
        if e.kind != "data" and not e.src.is_game and e.dst.lib and \
                e.src.key != e.dst.key:
            out[e.src.key].add(e.dst.key)
    roots = defaultdict(set)
    for e in edges:
        if e.kind != "data" and e.src.is_game and e.dst.lib:
            roots[e.dst.key].add(e.src.key)
    via = defaultdict(dict)   # lib fn key -> {root key: depth}
    for r in roots:
        dep = {r: 0}
        q = deque([r])
        while q:
            k = q.popleft()
            via[k][r] = dep[k]
            for d in out[k]:
                if d not in dep:
                    dep[d] = dep[k] + 1
                    q.append(d)
    return via, roots


def main():
    facts, imgs, edges, files = C.cached()
    m = imgs["main"]
    via, roots = boundary_closure(imgs, edges)
    rows = []
    # ---- syscalls
    for name, im in imgs.items():
        for f in im.fns:
            prev = []
            for pc, w in C.insns(im, f):
                if (w >> 26) == 0 and (w & 63) == 0x0C:
                    num = None
                    for ppc, pw in reversed(prev[-6:]):
                        if (pw >> 26) == 0x09 and ((pw >> 16) & 31) == 3 and \
                                ((pw >> 21) & 31) == 0:
                            num = C.sx16(pw & 0xFFFF)
                            break
                        if (pw >> 26) == 0x0D and ((pw >> 16) & 31) == 3 and \
                                ((pw >> 21) & 31) == 0:
                            num = pw & 0xFFFF
                            break
                    vk = via.get(f.key, {})
                    vn = via_names(m, vk)
                    rows.append({
                        "kind": "syscall",
                        "num": ("?" if num is None else
                                (f"-0x{-num:02X}" if num < 0 else f"0x{num:02X}")),
                        "symbol": f.name, "addr": f"0x{f.addr:06X}",
                        "family_sub": "/".join(f.lib) if f.lib else "GAME",
                        "site_image": name, "site": f"0x{pc:06X}",
                        "game_direct": len(roots.get(f.key, ())),
                        "reached": "yes" if vk else "no",
                        "via": " ".join(vn[:3]) + (f" (+{len(vn) - 3})" if len(vn) > 3 else "")})
                prev.append((pc, w))
    nsys = len(rows)
    # ---- call-site argument recovery
    wanted = {
        "CreateThread": "thread", "StartThread_1176e0": "start",
        "ChangeThreadPriority": "prio", "RotateThreadReadyQueue": "prio",
        "CreateSema": "sema", "AddIntcHandler": "intc", "AddIntcHandler_2": "intc",
        "AddDmacHandler": "intc", "AddDmacHandler_2": "intc",
        "SetAlarm_116320": "alarm", "iSetAlarm_116380": "alarm",
        "iSetAlarm": "alarm", "SetTimerAlarm_1222f0": "alarm",
        "iSetTimerAlarm_122420": "alarm"}
    tmap = {m.by_name[n].addr: (n, k) for n, k in wanted.items() if n in m.by_name}
    missing = [n for n in wanted if n not in m.by_name]
    for iname, im in imgs.items():
        for f in im.fns:
            for site, tgt, (r, stk, mem) in C.callsites(im, f, set(tmap), imgs):
                tn, kind = tmap[tgt]
                row = {"kind": kind, "symbol": tn, "addr": f"0x{tgt:06X}",
                       "site_image": iname, "caller": f.name,
                       "caller_is_game": "yes" if f.is_game else "no",
                       "site": f"0x{site:06X}",
                       "family_sub": "/".join(f.lib) if f.lib else "GAME",
                       "a0": C.fmt(r.get(4), imgs, iname),
                       "a1": C.fmt(r.get(5), imgs, iname),
                       "a2": C.fmt(r.get(6), imgs, iname)}
                p = r.get(4)

                def fld(off):
                    if isinstance(p, tuple) and p[0] == "sp":
                        return stk.get(p[1] + off, None), True
                    if isinstance(p, int):
                        return mem.get(p + off, None), (p + off) in mem
                    return None, False
                if kind == "thread":
                    for col, off in (("p_entry", 4), ("p_stack", 8),
                                     ("p_stack_size", 0xC), ("p_gp", 0x10),
                                     ("p_priority", 0x14)):
                        v, _ = fld(off)
                        row[col] = C.fmt(v, imgs, iname)
                    row["note"] = "ThreadParam{func@4,stack@8,size@C,gp@10,initPriority@14}"
                    row["src"] = C.src_lines(facts, files, iname, f.name,
                                             r"\.\s*\w*(stack|prio|func|entry|size)\w*\s*=[^=]")
                elif kind == "sema":
                    v1, _ = fld(4)
                    v2, _ = fld(8)
                    row["note"] = f"max_count={C.fmt(v1)} init_count={C.fmt(v2)}"
                    row["src"] = C.src_lines(facts, files, iname, f.name,
                                             r"\.\s*\w*(count|cnt)\w*\s*=[^=]")
                elif kind == "intc":
                    cause = r.get(4)
                    names = {"AddIntcHandler": {2: "VBLANK_START(2)", 3: "VBLANK_END(3)",
                                                0: "GS(0)", 1: "SBUS(1)", 4: "VIF0(4)",
                                                5: "VIF1(5)", 6: "VU0(6)", 7: "VU1(7)",
                                                8: "IPU(8)", 9: "TIMER0(9)", 10: "TIMER1(10)",
                                                11: "TIMER2(11)", 12: "TIMER3(12)",
                                                13: "SFIFO(13)", 14: "VU0WD(14)"},
                             "AddDmacHandler": {0: "VIF0(0)", 1: "VIF1(1)", 2: "GIF(2)",
                                                3: "fromIPU(3)", 4: "toIPU(4)", 5: "SIF0(5)",
                                                6: "SIF1(6)", 7: "SIF2(7)", 8: "fromSPR(8)",
                                                9: "toSPR(9)"}}
                    base = tn.replace("_2", "")
                    if isinstance(cause, int):
                        row["note"] = names.get(base, {}).get(cause, str(cause))
                rows.append(row)
    rows_k = Counter(r["kind"] for r in rows)
    C.write_tsv(C.OUT / "platform_ee_syscalls.tsv", COLS, rows, C.meta(
        "ee_syscalls", {"rows": len(rows),
                        "kinds": ", ".join(f"{k}={v}" for k, v in sorted(rows_k.items())),
                        "missing_symbols": " ".join(missing) or "none",
                        "note": "values recovered by straight-line const-prop "
                                "of retail code; '?' = not a constant on the "
                                "straight-line path"}))
    print(rows_k, "missing:", missing)


if __name__ == "__main__":
    main()
