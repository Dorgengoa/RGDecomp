# SPDX-License-Identifier: CC0-1.0
"""Port side of the state-trace lockstep: run the port headless with an input
script, record a trace (src/trace, rg_trace), and compare it against a PCSX2
golden with trace.py's compare (docs/TRACE-PORT.md).

  python tools/trace/port_trace.py run --exe EXE --out port.tsv --regions R
         [--portcfg P] [--input script.txt] [--stop-vbl V] [--every N]
         [--keys-from golden.tsv] [--fault ADDR:VBL[:XOR]] [--demo] [-- exe args...]
  python tools/trace/port_trace.py compare golden.tsv port.tsv [--portcfg P]
         [--strict] [--only RE] [--ignore RE] [--key vbl|frame]
  python tools/trace/port_trace.py check golden.tsv --exe EXE --out port.tsv ...
         (run, keyed to the golden's vbls and stopping at its last one, then compare)

The exe reads RG_TRACE_* environment variables (rg_trace_apply_env); this
script only sets them.  --demo adds rg-runtime-demo's own arguments
(--headless --fields N).  The default compare is the lockstep one:
--key vbl, --only '^sym:', and --ignore built from the exclude/pending lines
of the port config (pending ones are judged with --strict).
"""
import argparse
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import trace  # noqa: E402  (shared: read_trace, compare)

DEFAULT_PORTCFG = os.path.join(HERE, "port_regions.cfg")
DEFAULT_REGIONS = os.path.join(HERE, "regions_symbols.cfg")


def read_portcfg(path):
    """-> (exclude [(regex, reason)], pending [(regex, reason)])."""
    exc, pend = [], []
    if not path:
        return exc, pend
    with open(path, encoding="utf-8") as f:
        for line in f:
            t = line.split("#", 1)[0].split(None, 2)
            if len(t) >= 2 and t[0] in ("exclude", "pending"):
                re.compile(t[1])
                (exc if t[0] == "exclude" else pend).append((t[1], t[2].strip() if len(t) > 2 else ""))
    return exc, pend


def ignore_regex(portcfg, strict=False, extra=None):
    exc, pend = read_portcfg(portcfg)
    pats = [p for p, _ in exc] + ([] if strict else [p for p, _ in pend])
    if extra:
        pats.append(extra)
    return "|".join("(?:%s)" % p for p in pats) if pats else None


def golden_vbls(path):
    """The game-vbl keys a trace emitted (what compare --key vbl matches)."""
    t = trace.read_trace(path)
    out = set()
    for fr in t:
        v = int(t[fr].get("@vbl", "0"))
        if v:
            out.add(v)
    return sorted(out)


def run(args):
    out = os.path.abspath(args.out)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    env = dict(os.environ)
    for k in [k for k in env if k.startswith("RG_TRACE_")]:
        del env[k]
    env["RG_TRACE_OUT"] = out
    env["RG_TRACE_REGIONS"] = os.path.abspath(args.regions)
    if args.portcfg:
        env["RG_TRACE_PORTCFG"] = os.path.abspath(args.portcfg)
    if args.input:
        env["RG_TRACE_INPUT"] = os.path.abspath(args.input)
    if args.every:
        env["RG_TRACE_EVERY"] = str(args.every)
    stop = args.stop_vbl
    if args.keys_from:
        keys = golden_vbls(args.keys_from)
        kf = out + ".keys"
        with open(kf, "w", encoding="utf-8", newline="\n") as f:
            f.write("".join("%d\n" % v for v in keys))
        env["RG_TRACE_KEYS"] = kf
        if not stop and keys:
            stop = keys[-1]
    if stop:
        env["RG_TRACE_STOP_VBL"] = str(stop)
    if args.frames:
        env["RG_TRACE_FRAMES"] = str(args.frames)
    if args.fault:
        env["RG_TRACE_FAULT"] = args.fault
    if args.ps2_pointers:
        env["RG_TRACE_PS2PTRS"] = "1"
    if args.vbl_kernel:
        env["RG_TRACE_VBL_KERNEL"] = "1"
    cmd = [os.path.abspath(args.exe)]
    if args.demo:
        # rg-runtime-demo stops on its own after --fields; the recorder's
        # stop-vbl quits earlier.  Leave room for the counter's start offset.
        fields = args.fields or ((stop or 600) + 120)
        cmd += ["--headless", "--fields", str(fields)]
    cmd += args.exe_args
    work = os.path.abspath(args.workdir or os.path.dirname(out))
    os.makedirs(work, exist_ok=True)
    print("port_trace: %s" % " ".join(cmd), flush=True)
    r = subprocess.run(cmd, env=env, cwd=work, timeout=args.timeout,
                       stdout=None if args.verbose else subprocess.DEVNULL)
    if not os.path.exists(out):
        print("port_trace: no trace written (exe exit %d)" % r.returncode)
        return 2
    stop_line = None
    with open(out, encoding="utf-8") as f:
        for line in f:
            if line.startswith("# stop\t"):
                stop_line = line.strip()
    print("port_trace: exe exit %d; %s; wrote %s" % (r.returncode, stop_line or "no stop line", out))
    return 0 if stop_line else 2


def compare(args):
    ign = ignore_regex(args.portcfg, args.strict, args.ignore)
    exc, pend = read_portcfg(args.portcfg)
    print("compare: key %s, only %s, %d exclude + %d pending (%s)" % (
        args.key, args.only or "(all)", len(exc), len(pend), "judged: --strict" if args.strict else "ignored"))
    ns = argparse.Namespace(a=args.a, b=args.b, key=args.key, only=args.only, ignore=ign, limit=args.limit)
    return trace.compare(ns)


def add_run_args(p):
    p.add_argument("--exe", required=True, help="port exe that honours RG_TRACE_* (the game, rg-runtime-demo)")
    p.add_argument("--out", required=True)
    p.add_argument("--regions", default=DEFAULT_REGIONS)
    p.add_argument("--portcfg", default=DEFAULT_PORTCFG)
    p.add_argument("--input", help="input script (tools/trace/input.py format)")
    p.add_argument("--stop-vbl", type=int, default=0, help="stop once the game VBlank counter reaches this")
    p.add_argument("--frames", type=int, default=0, help="stop after this many samples (kernel VBlanks)")
    p.add_argument("--every", type=int, default=0, help="emit vbls that are multiples of N")
    p.add_argument("--keys-from", help="emit exactly the vbls this trace has (e.g. the golden)")
    p.add_argument("--fault", help="deliberate-fault control: ADDR:VBL[:XOR] flips a byte at that vbl")
    p.add_argument("--ps2-pointers", action="store_true", help="stored pointers are PS2 addresses")
    p.add_argument("--vbl-kernel", action="store_true", help="key by the kernel VBlank count")
    p.add_argument("--demo", action="store_true", help="add rg-runtime-demo arguments (--headless --fields N)")
    p.add_argument("--fields", type=int, default=0, help="--demo: --fields value")
    p.add_argument("--workdir", help="exe working directory (default: the --out directory)")
    p.add_argument("--timeout", type=float, default=3600)
    p.add_argument("--verbose", action="store_true", help="show the exe's stdout")
    p.add_argument("exe_args", nargs="*", help="extra exe arguments (after --)")


def add_compare_args(p, two=True):
    if two:
        p.add_argument("a", help="reference trace (PCSX2 golden)")
        p.add_argument("b", help="port trace")
    p.add_argument("--key", choices=("frame", "vbl"), default="vbl")
    p.add_argument("--only", default="^sym:", help="regex of judged regions ('' = all)")
    p.add_argument("--ignore", help="extra regex of regions to skip")
    p.add_argument("--strict", action="store_true", help="also judge the 'pending' regions")
    p.add_argument("--limit", type=int, default=60)


def main(argv=None):
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    add_run_args(r)
    c = sub.add_parser("compare")
    add_compare_args(c)
    c.add_argument("--portcfg", default=DEFAULT_PORTCFG)
    k = sub.add_parser("check")
    k.add_argument("golden")
    add_run_args(k)
    add_compare_args(k, two=False)
    args = ap.parse_args(argv)
    if getattr(args, "only", None) == "":
        args.only = None
    if args.cmd == "run":
        return run(args)
    if args.cmd == "compare":
        return compare(args)
    if not args.keys_from:
        args.keys_from = args.golden
    rc = run(args)
    if rc:
        return rc
    args.a, args.b = args.golden, args.out
    return compare(args)


if __name__ == "__main__":
    sys.exit(main())
