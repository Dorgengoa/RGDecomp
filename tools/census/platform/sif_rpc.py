#!/usr/bin/env python3
"""platform_sif_rpc.tsv -- SIF RPC boundary between EE and IOP.

kind column:
  server     an RPC server id: who registers it (IOP module from the IRX scan
             or IOPRP300.IMG, or an EE-side sceSifRegisterRpc), which EE
             library binds it, client struct address
  call       one (server id, function number) pair with the EE functions that
             issue it.  fno comes from straight-line const-prop at the
             sceSifCallRpc site, or through a pass-through wrapper (the
             wrapper's argument is resolved at each of ITS call sites):
             SifCallRpcRetry_11ad90 (fileio), FileIoPathCmdRpc_11ca10,
             SifLoadModuleRpc_11f578/_sceSifLoadElfPart (loadfile),
             sceSdRemote_1229e8 (sdremote: fno = command), SoundRpcCall_1bc5e0
             (pcm_mixer 0x123456: fno = arg0).
  module     an IOP module the game loads (LoadIopModules_15e240 ->
             IopLoadModuleRetry_15e420 -> sceSifLoadModule): path + arg
             string as stored in retail .data
  iop_module every retail IOP module with its RPC servers / imports (so the
             HLE plan sees modules that serve no RPC, e.g. the SK sound stack)
`game_reached`: the EE caller is game code, or a library function reachable
from game code (common boundary closure); `via` names the game-called API.
"""
from __future__ import annotations

import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402
import irx  # noqa: E402
from ee_syscalls import boundary_closure, via_names  # noqa: E402

COLS = ["kind", "sid", "fno", "iop_module", "iop_file", "ee_family", "ee_api",
        "callers", "game_reached", "via", "client", "detail"]

# wrapper: (client arg reg or fixed client, fno arg reg)
WRAPPERS = {
    "sceSifCallRpc": (4, 5),
    "SifCallRpcRetry_11ad90": (4, 5),
    "FileIoPathCmdRpc_11ca10": (0x489AC0, 5),
    "sceSdRemote_1229e8": (0x48D940, 5),
    "SoundRpcCall_1bc5e0": (0x4A25C0, 4),
    "SifLoadModuleRpc_11f578": (0x489F80, 8),
    "_sceSifLoadElfPart": (0x489F80, 7),
}
# (wrapper sites inside these functions are not counted as real calls:
#  their fno is resolved one level up)
PASS_THROUGH = set(WRAPPERS) - {"sceSifCallRpc"}

SDR_CMDS = {0x8010: "SdSetParam", 0x8020: "SdGetParam", 0x8030: "SdSetSwitch",
            0x8040: "SdGetSwitch", 0x8050: "SdSetAddr", 0x8060: "SdGetAddr",
            0x8070: "SdSetCoreAttr", 0x8080: "SdGetCoreAttr", 0x8090: "SdNote2Pitch",
            0x80A0: "SdPitch2Note", 0x80B0: "SdProcBatch", 0x80C0: "SdProcBatchEx",
            0x80D0: "SdVoiceTrans", 0x80E0: "SdBlockTrans", 0x80F0: "SdVoiceTransStatus",
            0x8100: "SdBlockTransStatus", 0x8110: "SdSetTransCallback",
            0x8120: "SdSetIRQCallback", 0x8130: "SdSetEffectAttr",
            0x8140: "SdGetEffectAttr", 0x8150: "SdClearEffectWorkArea",
            0x8160: "SdSetTransIntrHandler", 0x8170: "SdSetSpu2IntrHandler",
            0xE620: "SdRemoteCallbackInit(sdrdrv)", 0xE630: "SdRemoteCallbackQuit(sdrdrv)"}


def read_cstr(imgs, image, addr, n=96):
    im = imgs["main"] if (image == "main" or addr < C.OVL_BASE) else imgs[image]
    o = addr - im.base
    if not 0 <= o < len(im.data):
        return None
    s = im.data[o:o + n].split(b"\0")[0]
    return s.decode("latin-1")


def main():
    facts, imgs, edges, files = C.cached()
    m = imgs["main"]
    via, roots = boundary_closure(imgs, edges)

    def reach(f):
        if f.is_game:
            return "yes", "(game)"
        vk = via.get(f.key, {})
        if not vk:
            return "no", ""
        vn = via_names(m, vk)
        return "yes", " ".join(vn[:3]) + (f" (+{len(vn) - 3})" if len(vn) > 3 else "")

    # ---- IOP side
    iop_srv = {}
    iop_rows = []
    for fname, stem, blob in irx.modules():
        info = irx.parse(blob)
        sites = irx.rpc_sites(info)
        regs = [v for k, _, v in sites if k == "sceSifRegisterRpc"]
        binds = [v for k, _, v in sites if k == "sceSifBindRpc"]
        for v in regs:
            if v is not None:
                iop_srv[v] = (info["name"], fname)
        libs = sorted({lib for lib, _ in info["imports"].values()})
        iop_rows.append({
            "kind": "iop_module", "iop_module": f"{info['name']} {info['version']}",
            "iop_file": fname,
            "sid": " ".join(f"0x{v:X}" if v is not None else "?" for v in regs),
            "detail": ("binds " + " ".join(f"0x{v:X}" for v in binds if v is not None) + "; "
                       if binds else "") + "imports: " + " ".join(libs)})

    # ---- EE binds + EE-side servers
    tn = {n: m.by_name[n].addr for n in
          ["sceSifBindRpc", "sceSifRegisterRpc", "IopLoadModuleRetry_15e420",
           "sceSifRebootIop_11fcd0"] +
          list(WRAPPERS) if n in m.by_name}
    rev = {a: n for n, a in tn.items()}
    sites = []
    for iname, im in imgs.items():
        for f in im.fns:
            for site, tgt, (r, stk, mem) in C.callsites(im, f, set(rev), imgs):
                sites.append((iname, f, rev[tgt], site, r))
    client_sid = {}
    servers = {}
    ee_reg = {}
    for iname, f, t, site, r in sites:
        if t == "sceSifBindRpc" and isinstance(r.get(5), int):
            client_sid[r.get(4)] = r[5]
            servers.setdefault(r[5], []).append((f, r.get(4)))
        if t == "sceSifRegisterRpc" and isinstance(r.get(5), int):
            ee_reg[r[5]] = f
    # ---- calls: resolve pass-through wrappers one level up
    by_callee = defaultdict(list)
    for s in sites:
        by_callee[s[2]].append(s)
    calls = defaultdict(set)   # (sid, fno) -> {fn}
    unresolved = []
    init_fno = set()

    def resolve(callee, client_v, fno_v, f):
        if isinstance(client_v, tuple) and client_v[0] == "arg":
            client_v = None
        return client_v, fno_v

    for wname, (creg, freg) in WRAPPERS.items():
        for iname, f, t, site, r in by_callee.get(wname, []):
            if f.name in PASS_THROUGH and wname in ("sceSifCallRpc", "SifCallRpcRetry_11ad90"):
                continue  # resolved at the wrapper's own callers
            client = creg if creg > 31 else r.get(creg)
            fno = r.get(freg)
            if isinstance(fno, tuple) and fno[0] == "load" and isinstance(fno[2], int):
                fno = fno[2]   # loaded from .data: use the retail initial value
                init_fno.add((f.name, fno))
            sid = client_sid.get(client)
            if sid is None or not isinstance(fno, int):
                unresolved.append((f.name, wname, C.fmt(client), C.fmt(fno)))
                calls[(sid, "?")].add((f, wname))
                continue
            calls[(sid, fno)].add((f, wname))

    rows = []
    fam_of = lambda f: "/".join(f.lib) if f.lib else "GAME"
    all_sids = sorted(set(servers) | set(ee_reg) | {k[0] for k in calls if k[0] is not None},
                      key=lambda x: x)
    for sid in all_sids:
        mod, mf = iop_srv.get(sid, ("", ""))
        if sid in ee_reg:
            mod, mf = "(EE-side server)", ee_reg[sid].name
        b = servers.get(sid, [])
        if sid in ee_reg:
            b = [(ee_reg[sid], None)]
        rr = [reach(f) for f, _ in b]
        rows.append({"kind": "server", "sid": f"0x{sid:X}", "iop_module": mod,
                     "iop_file": mf,
                     "ee_family": " ".join(sorted({fam_of(f) for f, _ in b})),
                     "callers": " ".join(sorted({f.name for f, _ in b})),
                     "client": " ".join(sorted({C.fmt(c) for _, c in b})),
                     "game_reached": "yes" if any(x[0] == "yes" for x in rr) else "no",
                     "via": " ".join(sorted({x[1] for x in rr if x[1]}))[:200]})
    for (sid, fno), fs in sorted(calls.items(), key=lambda kv: (kv[0][0] or 0, str(kv[0][1]).rjust(8))):
        mod, mf = iop_srv.get(sid, ("", ""))
        rr = [reach(f) for f, _ in fs]
        det = ""
        if sid == 0x80000701 and isinstance(fno, int):
            det = SDR_CMDS.get(fno, "")
        if any((f.name, fno) in init_fno for f, _ in fs):
            det = "fno read from a .data word (retail initial value shown)"
        rows.append({"kind": "call", "sid": f"0x{sid:X}" if sid is not None else "?",
                     "fno": f"0x{fno:X}" if isinstance(fno, int) else fno,
                     "iop_module": mod, "iop_file": mf,
                     "ee_family": " ".join(sorted({fam_of(f) for f, _ in fs})),
                     "ee_api": " ".join(sorted({w for _, w in fs})),
                     "callers": " ".join(sorted({f.name for f, _ in fs})),
                     "game_reached": "yes" if any(x[0] == "yes" for x in rr) else "no",
                     "via": " ".join(sorted({x[1] for x in rr if x[1]}))[:200],
                     "detail": det})
    # ---- modules loaded
    for iname, f, t, site, r in by_callee.get("IopLoadModuleRetry_15e420", []):
        name = read_cstr(imgs, iname, r.get(4)) if isinstance(r.get(4), int) else None
        d = read_cstr(imgs, iname, r.get(5)) if isinstance(r.get(5), int) else None
        argsz = r.get(7)
        arg = ""
        a8 = r.get(8)
        if isinstance(a8, int) and isinstance(argsz, int) and argsz:
            im = m
            o = a8 - im.base
            arg = im.data[o:o + argsz].replace(b"\0", b"|").decode("latin-1")
        rows.append({"kind": "module", "iop_file": f"{d or '?'}{name or '?'}",
                     "callers": f"{f.name}@0x{site:X}",
                     "detail": f"upper/;sep={C.fmt(r.get(6))} argsz={C.fmt(argsz)} "
                               f"args='{arg}'", "game_reached": "yes"})
    for iname, f, t, site, r in by_callee.get("sceSifRebootIop_11fcd0", []):
        img = read_cstr(imgs, iname, r.get(4)) if isinstance(r.get(4), int) else None
        rows.append({"kind": "module", "iop_file": img or "?",
                     "callers": f"{f.name}@0x{site:X}", "game_reached": "yes",
                     "detail": "IOP reboot with replacement image (sceSifRebootIop); "
                               "then sceSifSyncIop/InitRpc/InitIopHeap"})
    rows += iop_rows
    C.write_tsv(C.OUT / "platform_sif_rpc.tsv", COLS, rows, C.meta(
        "sif_rpc", {"rows": len(rows),
                    "unresolved_sites": "; ".join(f"{a}->{b}(client={c},fno={d})"
                                                  for a, b, c, d in unresolved) or "none",
                    "note": "IOP side from irx.py (sifcmd export 17 = "
                            "sceSifRegisterRpc, export 15 = sceSifBindRpc)"}))
    print(len(rows), "rows; unresolved:", unresolved)


if __name__ == "__main__":
    main()
