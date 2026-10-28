#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of the game's sound path to the IOP (docs/NATIVE-AUDIO.md section 1).

    python tools/native/audio_census.py static  [--out census/native_audio_static.tsv]
    python tools/native/audio_census.py dynamic LOG [LOG ...] [--out census/native_audio_dynamic.tsv]

static   scans game/src (overrides in place of the files they replace):
         - the sound worker's command table D_0044AE10 (thread command id ->
           executor) and what each executor sends (SK group/sub-command, sdremote
           fno);
         - every call site of SoundSendCmd_1b6cc0 / SoundQueueCmd_1b6d60 with its
           literal command id (who asks the driver for what);
         - every caller of the rest of the IOP-facing surface: sceSdRemote, the
           SoundIopSendCmdG*S* block builders, the pcm_mixer RPC SoundRpcCall_1bc5e0,
           SIF DMA (SifDmaSendSync_*), the IOP heap (IopHeap*, sceSifAllocIopHeap);
         - the callers of those functions up to 2 more levels (the game's sound API).
dynamic  reads command logs written by a run with RG_AUDIO_CMDLOG=<path> (one line
         per driver command: frame, thread command, words, result; pcm_mixer calls
         as "pcm" lines; see src/native/audio/ra_host.c) and/or the HLE's
         RG_SND_LOG (sdr_driver fno / SK words), and counts commands per log.

Pure text processing, no build needed.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from fs_census import PORT, game_sources, scan_file, strip_comments  # noqa: E402

# Thread command names (SOUND-PROTOCOL.md "What the game sends", plus the table).
CMD_NAMES = {
    0x01: "AllNotesOff(track)", 0x02: "AllSoundOff(track)", 0x03: "SeqDataUpload",
    0x04: "MsinCreate", 0x05: "BankRegister", 0x06: "SeqAttach", 0x07: "MsinAttach",
    0x08: "BankAttach", 0x09: "SpuTransfer(BD chunk)", 0x0A: "SetOutputMode",
    0x0B: "HsynthQuery71", 0x0C: "SetMasterVolume", 0x0D: "SeqPause", 0x0E: "SeqPlay",
    0x0F: "SeqStop", 0x10: "SeqTempoAbs", 0x11: "SeqTempoRel", 0x12: "SeqSetVolume",
    0x13: "SeqQuery", 0x14: "MsinQuery", 0x15: "SeqDataRelease", 0x16: "MsinRelease",
    0x17: "BankRelease", 0x18: "SeqDetach", 0x19: "MsinDetach", 0x1A: "BankDetach",
    0x1B: "KeyOff", 0x1C: "KeyOnMuted", 0x1D: "SetVolume", 0x1E: "SetPan",
    0x1F: "SetPitchBend", 0x20: "KeyOn", 0x21: "EffectEnable", 0x22: "SetReverbMode",
    0x23: "SetReverbDepth", 0x24: "SetReverbEndAddr", 0x25: "SetInputVolume",
    0x26: "SdRemote(raw)",
}

SURFACE = re.compile(
    r"^(sceSdRemote_1229e8|sceSdRemoteInit_122890|sceSdRemoteCallbackInit_122d70|"
    r"SoundIopSendCmdG[0-3]S[0-9A]_[0-9a-f]+|SdRemoteInitMasterVolume_165608|"
    r"SoundRpcCall_1bc5e0|SifDmaSendSync_1c21e0|SifDmaSendSync_1d2c20|"
    r"IopHeapAlloc\w*|IopHeapFree\w*|sceSifAllocIopHeap|sceSifFreeIopHeap|"
    r"SoundSendCmd_1b6cc0|SoundQueueCmd_1b6d60)$")
SEND = re.compile(r"\b(SoundSendCmd_1b6cc0|SoundQueueCmd_1b6d60)\s*\(\s*(0x[0-9A-Fa-f]+|\d+)")
GCALL = re.compile(r"\b(SoundIopSendCmdG([0-3])S([0-9A])_[0-9a-f]+)\s*\(([^;]*)")
SDR = re.compile(r"\bsceSdRemote_1229e8\s*\(\s*1\s*,\s*(0x[0-9A-Fa-f]+|\d+)")
RPC = re.compile(r"\bSoundRpcCall_1bc5e0\s*\(\s*(0x[0-9A-Fa-f]+|\d+)")


def table() -> dict[int, str]:
    p = PORT / "game" / "src" / "main_data" / "data2c_0044AE10.c"
    txt = p.read_text(encoding="utf-8", errors="replace")
    body = txt[txt.index("{", txt.index("D_0044AE10[")) + 1:]
    body = body[:body.index("}")]
    out = {}
    for i, item in enumerate(x.strip() for x in body.split(",")):
        m = re.search(r"&(\w+)", item)
        if m:
            out[i] = m.group(1)
    return out


def func_bodies(srcs) -> dict[str, tuple[str, str]]:
    """function name -> (relpath, comment-stripped body text) for single-function units."""
    out = {}
    for rel, p in srcs.items():
        stem = p.stem
        out.setdefault(stem, (rel, strip_comments(p.read_text(encoding="utf-8", errors="replace"))))
    return out


def args_of(callargs: str) -> list[str]:
    depth, cur, out = 0, "", []
    for ch in callargs:
        if ch == "(":
            depth += 1
        elif ch == ")":
            if depth == 0:
                break
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def cmd_static(a) -> int:
    srcs = game_sources()
    bodies = func_bodies(srcs)
    calls: dict[str, set[str]] = defaultdict(set)
    where: dict[str, str] = {}
    sends: dict[int, Counter] = defaultdict(Counter)       # cmd id -> sender -> sites
    other: dict[tuple[str, str], int] = Counter()          # (caller, surface) -> sites
    rpcs: dict[int, set[str]] = defaultdict(set)
    sdrs: dict[int, set[str]] = defaultdict(set)
    for rel, p in sorted(srcs.items()):
        for fn, callee, ln, text in scan_file(p):
            calls[fn].add(callee)
            where.setdefault(fn, rel)
            if SURFACE.match(callee):
                m = SEND.search(text)
                if m and callee == m.group(1):
                    sends[int(m.group(2), 0)][fn] += 1
                else:
                    other[(fn, callee)] += 1
                m = RPC.search(text)
                if m and callee == "SoundRpcCall_1bc5e0":
                    rpcs[int(m.group(1), 0)].add(fn)
                m = SDR.search(text)
                if m and callee == "sceSdRemote_1229e8":
                    sdrs[int(m.group(1), 0)].add(fn)
    tab = table()
    # what each executor sends
    exe_sends: dict[str, list[str]] = {}
    for i, fn in tab.items():
        rel, body = bodies.get(fn, ("?", ""))
        out = []
        for m in GCALL.finditer(body):
            ar = args_of(m.group(4))
            sub = ""
            if m.group(3) in ("0", "1") and ar:
                sub = f" form {ar[0]}"
            elif m.group(3) == "2" and len(ar) > 1:
                sub = f" cmd {ar[1]}"
            out.append(f"G{m.group(2)}/S{m.group(3)}{sub}")
        for m in SDR.finditer(body):
            out.append(f"sdremote {m.group(1)}")
        if "sceSdRemote_1229e8" in body and not SDR.search(body):
            out.append("sdremote (raw words)")
        exe_sends[fn] = out
    callers: dict[str, set[str]] = defaultdict(set)
    for fn, cs in calls.items():
        for c in cs:
            callers[c].add(fn)
    level1 = {fn for s in sends.values() for fn in s} | {fn for (fn, _c) in other}
    level1 -= set(tab.values())
    level1 = {f for f in level1 if not SURFACE.match(f)}
    level: dict[str, int] = {f: 1 for f in level1}
    frontier = set(level1)
    for depth in (2, 3):
        nxt = set()
        for f in frontier:
            for c in callers.get(f, ()):
                if c not in level and not SURFACE.match(c) and c not in tab.values():
                    level[c] = depth
                    nxt.add(c)
        frontier = nxt

    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# audio_census.py static (docs/NATIVE-AUDIO.md section 1)\n")
        f.write("# kind\tid\tname\tfunction\tfile\tdetail\n")
        for i in sorted(tab):
            fn = tab[i]
            snd = sorted(sends.get(i, {}).items())
            f.write(f"cmd\t0x{i:02X}\t{CMD_NAMES.get(i, '?')}\t{fn}\t{bodies.get(fn, ('?',))[0]}\t"
                    f"sends {'; '.join(exe_sends.get(fn, [])) or '-'} | senders {len(snd)}: "
                    f"{' '.join(f'{s}x{n}' if n > 1 else s for s, n in snd) or '-'}\n")
        for fno in sorted(rpcs):
            f.write(f"pcm\t0x{fno:04X}\t-\t{' '.join(sorted(rpcs[fno]))}\t-\tSoundRpcCall\n")
        for fno in sorted(sdrs):
            f.write(f"sdr\t0x{fno:04X}\t-\t{' '.join(sorted(sdrs[fno]))}\t-\tsceSdRemote direct\n")
        for (fn, c), n in sorted(other.items()):
            if fn in tab.values():
                continue
            f.write(f"edge\t1\t{c}\t{fn}\t{where.get(fn, '?')}\tsites {n}\n")
        for fn, lv in sorted(level.items(), key=lambda kv: (kv[1], kv[0])):
            if lv == 1:
                continue
            below = sorted(c for c in calls[fn] if c in level and level[c] < lv)
            f.write(f"api\t{lv}\t-\t{fn}\t{where.get(fn, '?')}\tcalls {' '.join(below)}\n")
    by = Counter(level.values())
    used = sorted(i for i in tab if sends.get(i))
    print(f"thread commands: {len(tab)} in the table, {len(used)} with a literal sender: "
          + " ".join(f"0x{i:02X}" for i in used))
    print("unsent (no literal call site): " + " ".join(f"0x{i:02X}" for i in sorted(tab) if not sends.get(i)))
    print(f"pcm_mixer fnos: {' '.join(f'0x{x:04X}' for x in sorted(rpcs))}")
    print(f"direct sceSdRemote fnos: {' '.join(f'0x{x:04X}' for x in sorted(sdrs))}")
    surf = Counter(c for (_fn, c) in other)
    print("other surface: " + ", ".join(f"{c} ({n} callers)" for c, n in sorted(surf.items())))
    print(f"levels: " + ", ".join(f"{k}: {v}" for k, v in sorted(by.items())))
    print(f"wrote {out}")
    return 0


# ---- dynamic -----------------------------------------------------------------------------------
def cmd_dynamic(a) -> int:
    rows = []
    for path in a.logs:
        cnt: Counter = Counter()
        span: dict[str, list[int]] = {}
        kind = "?"
        for ln in Path(path).read_text(encoding="utf-8", errors="replace").splitlines():
            if not ln or ln.startswith("#"):
                if ln.startswith("# rg_audio cmdlog"):
                    kind = "cmdlog"
                elif ln.startswith("# frame\tfno"):
                    kind = "sndlog"
                continue
            c = ln.split("\t")
            if kind == "cmdlog" and len(c) >= 3:
                # frame  T|P  id  words...  result
                fr, typ, cid = int(c[0]), c[1], c[2]
                if typ == "T":
                    i = int(cid, 16)
                    key = f"T{i:02X} {CMD_NAMES.get(i, '?')}"
                    if i in (0x20, 0x1C, 0x1B) and len(c) > 9:   # key on/off: (track, id, bank, prog)
                        key += f" track {int(c[3], 16)}"
                    if i == 0x26 and len(c) > 3:
                        key += f" fno {c[3]}"
                elif typ == "P":
                    key = f"P{cid} pcm_mixer"
                elif typ == "B":
                    key = "B bank load" if cid == "5" else "B sequence load"
                elif typ == "K":
                    key = "K engine voice key on"
                else:
                    continue
            elif kind == "sndlog" and len(c) >= 3:
                fr, fno = int(c[0]), int(c[1], 16)
                if (fno & 0xFFF0) == 0x90F0:
                    w = [int(x, 16) for x in c[2:13]]
                    g = "?"  # module is w0 (not logged); infer from the HLE log's w1.. only
                    key = f"SK S{w[0]:X} w2 {w[1]:X} w3 {w[2]:X}"
                else:
                    key = f"sdr {fno & 0xFFF0:04X}"
            else:
                continue
            cnt[key] += 1
            span.setdefault(key, [fr, fr])[1] = fr
        for key, n in sorted(cnt.items()):
            rows.append((Path(path).name, key, n, span[key][0], span[key][1]))
        tot = sum(cnt.values())
        print(f"{path}: {kind}, {tot} commands, {len(cnt)} kinds")
        for key, n in cnt.most_common(a.top):
            print(f"  {n:7d}  {key}")
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# audio_census.py dynamic\nlog\tcommand\tcount\tfirst_frame\tlast_frame\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")
    print(f"wrote {out}")
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("static")
    s.add_argument("--out", default=str(PORT / "census" / "native_audio_static.tsv"))
    d = sub.add_parser("dynamic")
    d.add_argument("logs", nargs="+")
    d.add_argument("--top", type=int, default=40)
    d.add_argument("--out", default=str(PORT / "census" / "native_audio_dynamic.tsv"))
    a = ap.parse_args(argv)
    return cmd_static(a) if a.cmd == "static" else cmd_dynamic(a)


if __name__ == "__main__":
    sys.exit(main())
