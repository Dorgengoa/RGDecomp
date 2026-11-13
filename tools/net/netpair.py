#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Online 2-Player Battle loopback test: two rg-game processes, host and joiner, on this machine
(127.0.0.1) or host here + joiner on another machine, play a whole scripted match in lock-step
and must agree on the run hash at every check (lane insnet 2026-11-12; docs/INSECTRON-VERSUS.md
"Tests").

    python tools/net/netpair.py match [--exe EXE] [--exe-join EXE2] [--route R] [--saves DIR]
                                      [--out D] [--delay N] [--port P] [--windowed]
    python tools/net/netpair.py lost  [same] [--kill-at S]     (the joiner killed mid-match)
    python tools/net/netpair.py proto [--exe EXE]              (a bad peer: garbage, wrong
                                                                 version, oversized message)

match: the route of tools/net/netmatch.py (both players' input, game VBlank keyed) moved
`delay` VBlanks earlier (the lock-step publishes each pad `delay` VBlanks ahead) is the local
pad of BOTH processes: the host's turns read port 0 (the host's pad), the joiner's port 1.
Host saves: card 1 = P1's save; joiner saves: card 1 = P2's save (each brings its own).  PASS =
both reach the end of the session (the players leave the 2-Player Battle: --net-exit-at-end),
the same hash checks (>= 1) all equal, both exit 0, no desync, and the players' own saves
unchanged.  --exe-join: the joiner's exe (i686 vs x64).
lost: the joiner is killed at --kill-at seconds into the live part; PASS = the host notes the
lost connection, keeps running (the match goes on locally), exits 0 at --fields, its own saves
unchanged, no crash.
proto: a fake peer (this script) connects to a host and sends garbage / a wrong-version HELLO /
an oversized frame; PASS = the host refuses each cleanly (exit 7, a message), no crash.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import random
import re
import shutil
import socket
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / "fixtures"))
import fxlib  # noqa: E402

PORT_ROOT = fxlib.PORT
DEF_ROUTE = PORT_ROOT / "tests" / "fixtures" / "net_route.txt"   # tools/net/netmatch.py play, copied
DEF_SAVES = PORT_ROOT / "out" / "insnet" / "saves_base"


def tree_hash(d: Path) -> str:
    h = hashlib.sha256()
    for p in sorted(d.rglob("*")):
        if p.is_file():
            h.update(str(p.relative_to(d)).replace("\\", "/").encode())
            h.update(p.read_bytes())
    return h.hexdigest()[:16]


def shifted(route: Path, delay: int, out: Path) -> int:
    last = 0
    lines = []
    for ln in route.read_text(encoding="utf-8").splitlines():
        t = ln.split("#")[0].split()
        if len(t) == 3:
            a, b = int(t[0]) - delay, int(t[1]) - delay
            lines.append(f"{a} {b} {t[2]}")
            last = max(last, b)
    out.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return last


def saves_for(base: Path, card: str, dst: Path):
    """a saves dir whose card 1 holds `card` of the base (card1 / card2)"""
    shutil.rmtree(dst, ignore_errors=True)
    dst.mkdir(parents=True)
    shutil.copytree(base / card, dst / "card1")
    if (base / f"{card}.card").exists():
        shutil.copy2(base / f"{card}.card", dst / "card1.card")


def net_hashes(log: Path) -> dict:
    out = {}
    if log.exists():
        for ln in log.read_text(encoding="utf-8", errors="replace").splitlines():
            m = re.match(r"hash (\d+) ([0-9a-f]{16})$", ln)
            if m:
                out[int(m.group(1))] = m.group(2)
    return out


def free_port() -> int:
    for _ in range(50):
        p = random.randint(40000, 60000)
        s = socket.socket()
        try:
            s.bind(("", p))
            s.close()
            return p
        except OSError:
            s.close()
    return 47490


def launch(exe, saves, role_args, inp, log, out_txt, fields, extra_env=None, windowed=False):
    cmd = [str(exe)] + ([] if windowed else ["--headless"]) + ["--fields", str(fields), "--saves", str(saves),
                                                               "--net-save", "1:0", "--net-input", str(inp),
                                                               "--net-log", str(log), "--net-exit-at-end"] + role_args
    if windowed:
        cmd += ["--set", "system.throttle=false"]
    env = fxlib.game_env(extra_env or {})
    f = open(out_txt, "w", encoding="utf-8")
    f.write(" ".join(cmd) + "\n")
    f.flush()
    return subprocess.Popen(cmd, env=env, stdout=f, stderr=subprocess.STDOUT), f


def run_pair(a, kill_at=None) -> dict:
    out = Path(a.out)
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    exe_h = fxlib.exe_path(a.exe)
    exe_j = Path(a.exe_join).resolve() if a.exe_join else exe_h
    base = Path(a.saves)
    saves_for(base, "card1", out / "host_saves")
    saves_for(base, "card2", out / "join_saves")
    own_h, own_j = tree_hash(out / "host_saves" / "card1"), tree_hash(out / "join_saves" / "card1")
    inp = out / "input.txt"
    last = shifted(Path(a.route), a.delay, inp)
    fields = a.fields or last + 4000
    port = a.port or free_port()
    t0 = time.time()
    ph, fh = launch(exe_h, out / "host_saves", ["--net-host", str(port), "--net-delay", str(a.delay)], inp,
                    out / "host_net.log", out / "host.txt", fields, windowed=a.windowed)
    time.sleep(1.0)
    pj, fj = launch(exe_j, out / "join_saves", ["--net-join", f"127.0.0.1:{port}"], inp, out / "join_net.log",
                    out / "join.txt", fields, windowed=a.windowed)
    killed = False
    while ph.poll() is None or pj.poll() is None:
        time.sleep(0.5)
        if kill_at is not None and not killed and pj.poll() is None:
            live = (out / "join_net.log").exists() and "live from" in (out / "join_net.log").read_text(errors="replace")
            if live:
                if not hasattr(run_pair, "_live_t"):
                    run_pair._live_t = time.time()
                if time.time() - run_pair._live_t >= kill_at:
                    pj.kill()   # our own child, by its handle (PID)
                    killed = True
        if time.time() - t0 > a.timeout:
            for p in (ph, pj):
                if p.poll() is None:
                    p.kill()
            break
    fh.close()
    fj.close()
    hh, hj = net_hashes(out / "host_net.log"), net_hashes(out / "join_net.log")
    common = sorted(set(hh) & set(hj))
    diff = [f for f in common if hh[f] != hj[f]]
    ht, jt = (out / "host.txt").read_text(errors="replace"), (out / "join.txt").read_text(errors="replace")
    res = {"exe_host": str(exe_h), "exe_join": str(exe_j), "delay": a.delay, "port": port,
           "seconds": round(time.time() - t0), "rc_host": ph.returncode, "rc_join": pj.returncode,
           "checks": len(common), "first_check": common[0] if common else None,
           "last_check": common[-1] if common else None, "mismatches": diff[:5],
           "host_end": re.findall(r"rg-game: net (.*)", ht)[-1:] , "join_end": re.findall(r"rg-game: net (.*)", jt)[-1:],
           "host_run_hash": re.findall(r"run_hash=(\w+)", ht)[-1:], "join_run_hash": re.findall(r"run_hash=(\w+)", jt)[-1:],
           "host_own_saves_unchanged": tree_hash(out / "host_saves" / "card1") == own_h,
           "join_own_saves_unchanged": tree_hash(out / "join_saves" / "card1") == own_j,
           "killed_join": killed}
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    return res


def route_handover(route: Path):
    """the hand-over VBlank the route was recorded with ("# handover N" line), or None"""
    for ln in route.read_text(encoding="utf-8").splitlines():
        m = re.match(r"#\s*handover\s+(\d+)", ln)
        if m:
            return int(m.group(1))
    return None


def live_vbl(log: Path):
    if log.exists():
        m = re.search(r"live from VBlank (\d+)", log.read_text(encoding="utf-8", errors="replace"))
        if m:
            return int(m.group(1))
    return None


def cmd_match(a) -> int:
    r = run_pair(a)
    want, got = route_handover(Path(a.route)), live_vbl(Path(a.out) / "host_net.log")
    if want is not None and got is not None and want != got:
        # the exe's built-in prefix hands over at another VBlank than the route was recorded for:
        # an rg-game older (or newer) than tests/fixtures/net_route.txt -- rebuild rg-game, or
        # re-record the route (tools/net/netmatch.py play, then copy route.txt)
        print(json.dumps(r, indent=1))
        print(f"netpair match: the exe hands over at VBlank {got}, the route was recorded for {want}: "
              "rebuild rg-game (or re-record the route); not a lock-step failure")
        return 1
    ok = (r["rc_host"] == 0 and r["rc_join"] == 0 and r["checks"] >= 1 and not r["mismatches"] and
          r["host_own_saves_unchanged"] and r["join_own_saves_unchanged"] and
          any("left the 2-Player" in e or "ended the session" in e for e in r["host_end"] + r["join_end"]))
    print(json.dumps(r, indent=1))
    print("netpair match:", "PASS" if ok else "FAIL")
    return 0 if ok else 1


def cmd_lost(a) -> int:
    r = run_pair(a, kill_at=a.kill_at)
    ok = (r["killed_join"] and r["rc_host"] == 0 and r["host_own_saves_unchanged"] and
          any("lost" in e or "closed" in e or "stopped answering" in e for e in r["host_end"]))
    print(json.dumps(r, indent=1))
    print("netpair lost:", "PASS" if ok else "FAIL")
    return 0 if ok else 1


def cmd_proto(a) -> int:
    """a fake peer against a real host: each case must make the host exit 7 cleanly"""
    exe = fxlib.exe_path(a.exe)
    out = Path(a.out)
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    saves_for(Path(a.saves), "card1", out / "saves")

    def hello(magic=b"RGINSNET", proto=1, role=1, build=0, data=0):
        body = magic + struct.pack("<IIQQ", proto, role, build, data) + b"fake".ljust(16, b"\0")
        return struct.pack("<HHI", 1, 0, len(body)) + body

    cases = {"garbage": b"\xff" * 64,
             "oversized": struct.pack("<HHI", 3, 0, 0x7FFFFFFF) + b"x" * 32,
             "unknown_type": struct.pack("<HHI", 0x4242, 0, 4) + b"abcd",
             "bad_magic": hello(magic=b"NOTRGNET"),
             "wrong_version": hello(proto=99),
             "wrong_build": hello(build=0x1234)}
    results, ok = {}, True
    for name, payload in cases.items():
        port = free_port()
        log = out / f"{name}.txt"
        f = open(log, "w", encoding="utf-8")
        p = subprocess.Popen([str(exe), "--headless", "--fields", "100", "--saves", str(out / "saves"),
                              "--net-host", str(port), "--net-timeout", "5"], env=fxlib.game_env({}), stdout=f,
                             stderr=subprocess.STDOUT)
        s = None
        for _ in range(100):
            try:
                s = socket.create_connection(("127.0.0.1", port), timeout=1)
                break
            except OSError:
                time.sleep(0.2)
        if s:
            try:
                s.sendall(payload)
                time.sleep(1.0)
            except OSError:
                pass
        try:
            rc = p.wait(timeout=60)
        except subprocess.TimeoutExpired:
            p.kill()
            rc = "timeout"
        if s:
            s.close()
        f.close()
        txt = log.read_text(errors="replace")
        msg = re.findall(r"rg-game: online battle: (.*)", txt)
        good = rc == 7 and bool(msg) and "EXCEPTION" not in txt
        ok &= good
        results[name] = {"rc": rc, "message": msg[-1] if msg else None, "ok": good}
        print(f"  {name:14s} rc {rc}  {msg[-1] if msg else '-'}  {'ok' if good else 'FAIL'}")
    (out / "result.json").write_text(json.dumps(results, indent=1), encoding="utf-8")
    print("netpair proto:", "PASS" if ok else "FAIL")
    return 0 if ok else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("match", "lost", "proto"):
        p = sub.add_parser(name)
        p.add_argument("--exe")
        p.add_argument("--exe-join")
        p.add_argument("--route", default=str(DEF_ROUTE))
        p.add_argument("--saves", default=str(DEF_SAVES))
        p.add_argument("--out", default=str(PORT_ROOT / "out" / "insnet" / f"pair_{name}"))
        p.add_argument("--delay", type=int, default=4)
        p.add_argument("--port", type=int, default=0)
        p.add_argument("--fields", type=int, default=0)
        p.add_argument("--timeout", type=int, default=3600)
        p.add_argument("--windowed", action="store_true")
        p.add_argument("--kill-at", type=float, default=20.0)
    a = ap.parse_args(argv)
    if not Path(a.saves).is_dir():
        # the two-card saves dir of tools/fixtures/insvs.py (card 1 = P1, card 2 = P2)
        import insvs
        insvs.cards(Path(a.saves))
    if not Path(a.route).exists() and a.cmd != "proto":
        print(f"netpair: no route {a.route} (run tools/net/netmatch.py play first)")
        return 77
    return {"match": cmd_match, "lost": cmd_lost, "proto": cmd_proto}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
