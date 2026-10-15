#!/usr/bin/env python3
"""Compile every registered source with the REAL compiler, on the Linux host.

    hostbuild.py [symbol...]      default: everything in config/units.txt

mwccps2 3.0.1b210 links LMGR8C.DLL (FLEXlm 8) statically and no licence for it
exists on Windows. Under wibo it needs no licence at all -- which is how
decomp.me runs it, and is now verified here. So the compile step, and only the
compile step, happens over SSH: sources go over as one tar, every object comes
back as one tar, and objdiff scores them locally as before.

The whole tree is pushed each run because it is a few hundred KB and the
round trip dominates; per-file staleness checks would cost more than they save.
"""
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rgd

HOST = rgd.BUILD_HOST
KEY = rgd.SSH_KEY
REMOTE = rgd.REMOTE_ROOT + "/work"

# â˜…â˜…â˜…â˜…â˜… THE COMPILE IS EMBARRASSINGLY PARALLEL AND WAS RUNNING ON ONE CORE.
# Every unit is its own translation unit with its own object, so nothing
# orders them -- but the driver issued `cmd1; cmd2; ...` inside one `ssh`,
# which a POSIX shell runs SEQUENTIALLY.  Measured 2026-08-24 mid-run: 3,481
# of 5,292 objects after ~85 minutes with `uptime` reporting a load average
# of 1.00 on a 12-core box, i.e. eleven idle cores.  `xargs -P` fixes it.
# âš  10, not 12: the host also serves the `--tag` sandbox batches a session
# runs alongside, and leaving headroom keeps those responsive.
JOBS = 10
CC = "../mwcps2-3.0.1b210-060308/mwccps2.exe"
CC205 = "../mwcps2-3.0.1b205-051227/mwccps2.exe"
CC_FLAGS = "-O4 -c -Cpp_exceptions off -RTTI off -strings readonly -nostdinc -stderr -i include"

# config/toolchain.txt: the few units that are NOT plain `mwcc CC_FLAGS`.
#   <symbol>  mwcc   <extra flags>   -- e.g. `-sdatathreshold 16` (no pragma exists)
#   <symbol>  mwcc205 <extra flags>  -- b205 runtime codegen; staged beside b210
#   <symbol>  gcc29  <flags>         -- Sony ee-gcc 2.9-ee-991111-01 cc1 + Sony as,
#                                       for the non-mwcc islands (0x165608, 0x446xxx)
# Use the matching Sony cpp before cc1 so SDK header macros work. -undef and
# -nostdinc keep preprocessing independent of the host system headers.
# `-ffunction-sections` gives each function its own `.text.<name>`; objfix.py then
# folds them back to `.text` and link.py carves guests out exactly as for mwcc.
# Measured 2026-09-30: the island's 17 sections are byte-identical to the
# single-.text build that was verified against retail.
TOOLCHAIN = rgd.ROOT / "config" / "toolchain.txt"
GCC = rgd.EEGCC
GCC_CC1 = (f"{GCC}/cc1.sh {GCC}/sony29/lib/gcc-lib/ee/2.9-ee-991111-01/cc1"
           " -quiet -G0 -ffunction-sections")
GCC_AS = f"{GCC}/cc1.sh {GCC}/sony29/ee/bin/as -G0"
GCC_CPP = (f"{GCC}/cc1.sh {GCC}/sony29/lib/gcc-lib/ee/2.9-ee-991111-01/cpp"
           " -P -undef -nostdinc -Iinclude")


def toolchains() -> dict:
    """{symbol: (toolchain, flags)} from config/toolchain.txt."""
    out = {}
    if TOOLCHAIN.exists():
        for ln in TOOLCHAIN.read_text().splitlines():
            f = ln.split("#")[0].split()
            if f:
                out[f[0]] = (f[1], " ".join(f[2:]))
    return out


def compile_cmd(s: str, r: str, tc: dict) -> str:
    kind, flags = tc.get(s, ("mwcc", ""))
    if kind == "gcc29":
        return (f"{GCC_CPP} {r} {s}.i > {s}.log 2>&1 && "
                f"{GCC_CC1} {flags} {s}.i -o {s}.s >> {s}.log 2>&1 && "
                f"{GCC_AS} -o {s}.o {s}.s >> {s}.log 2>&1\n")
    if kind not in ("mwcc", "mwcc205"):
        raise SystemExit(f"hostbuild: {s}: unknown toolchain {kind!r}")
    compiler = CC205 if kind == "mwcc205" else CC
    return f"../wibo {compiler} {CC_FLAGS} {flags} {r} -o {s}.o > {s}.log 2>&1\n"


SSH = ["ssh", "-i", str(KEY), "-o", "StrictHostKeyChecking=no",
       "-o", "UserKnownHostsFile=/dev/null", "-o", "BatchMode=yes"]


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=rgd.ROOT, **kw)


def main() -> int:
    # â˜… `--tag T` moves BOTH sides of the build into a sandbox: remote
    # `~/rgd/work-T` and local `build/obj-T`.  Without it there is no way to
    # try a change to this script while a real build owns `~/rgd/work` and
    # `build/obj` -- and a real build is ~an hour, so "just re-run it" is not
    # an option.  âš  `link.py` READS `build/obj`; an untagged run DELETES it.
    global REMOTE
    argv = sys.argv[1:]
    tag = ""
    if argv and argv[0] == "--tag":
        tag = argv[1]
        argv = argv[2:]
        REMOTE = f"{rgd.REMOTE_ROOT}/work-{tag}"
        rgd.OBJ_DIR = rgd.ROOT / "build" / f"obj-{tag}"

    # Always push the WHOLE tree; only the named symbols get compiled. Pushing
    # a subset would delete the rest on the host, which silently breaks any
    # later ad-hoc compile against a file that is no longer there.
    #
    # â˜…â˜…â˜…â˜… THIS FUNCTION USED TO SPEND LONGER WALKING src/ THAN COMPILING.
    # The two comprehensions below call rgd.src_path() once per registered
    # symbol and each call was two full rglob()s -- 206 s at 5,507 units,
    # growing quadratically (build/p27_srcindex_proof.py).  Primed, the same
    # 5,510 lookups take 0.00 s and return byte-for-byte the same answers.
    # âš  The index is dropped again before anything else runs, because
    # w1_score.resolve() relies on a FRESH enumeration to see files written
    # moments ago.
    rgd.prime_src_index()
    every = [s for s in rgd.registered() if rgd.src_path(s)]
    symbols = argv or every
    allrel = [str(rgd.src_path(s).relative_to(rgd.ROOT)).replace("\\", "/") for s in every]
    rel = [str(rgd.src_path(s).relative_to(rgd.ROOT)).replace("\\", "/") for s in symbols]
    rgd.drop_src_index()

    # âš  The file list goes to tar through -T, not on the command line.
    # Windows caps a command line at 32 KB: at 137 units the inline form is
    # 5 KB and works, at 3,626 it is ~130 KB and CreateProcess fails with
    # "The filename or extension is too long" -- which reads like a missing
    # tar, not like a length limit.
    listfile = rgd.ROOT / "build" / f"hostbuild_files{'_' + tag if tag else ''}.txt"
    listfile.parent.mkdir(parents=True, exist_ok=True)
    listfile.write_text("\n".join(["include"] + allrel) + "\n",
                        encoding="utf-8", newline="\n")
    push = subprocess.Popen(["tar", "czf", "-", "-T",
                             str(listfile.relative_to(rgd.ROOT)).replace("\\", "/")],
                            cwd=rgd.ROOT, stdout=subprocess.PIPE)
    sh(SSH + [HOST, f"rm -rf {REMOTE} && mkdir -p {REMOTE} && tar xzf - -C {REMOTE}"],
       stdin=push.stdout)
    push.wait()

    # Drop the local object for everything about to be rebuilt. Without this a
    # compile error leaves the PREVIOUS object in place and status.py/hb.sh
    # happily score it -- which reads exactly like "the edit changed nothing".
    for s in symbols:
        (rgd.OBJ_DIR / f"{s}.o").unlink(missing_ok=True)

    # Compile, all of them, `xargs -P JOBS` over a command FILE.
    #
    # âš  The command list must not travel on a command line: the remote shell
    # silently truncates past roughly 8 KB and then dies with "unexpected EOF
    # while looking for matching quote", which looks exactly like every file
    # failing to compile at once.  It rides in the push tar instead, the same
    # fix `-T` already applies to the file list -- so the length cap is gone
    # rather than merely avoided by chunking, and there is ONE round trip.
    #
    # NEVER pipe the compiler into `head` -- it closes the pipe and mwcc takes
    # SIGPIPE, so a unit with more than six lines of WARNINGS dies before
    # writing its object and reads as a compile failure with no error in the
    # log.  Each compile redirects to its own file; the logs are headed
    # afterwards, when the compiler has already exited.
    cmdfile = rgd.ROOT / "build" / f"hostbuild_cmds{'_' + tag if tag else ''}.txt"
    tc = toolchains()
    cmdfile.write_text(
        "".join(compile_cmd(s, r, tc) for s, r in zip(symbols, rel)),
        encoding="utf-8", newline="\n")
    push2 = subprocess.Popen(["tar", "czf", "-",
                              str(cmdfile.relative_to(rgd.ROOT)).replace("\\", "/")],
                             cwd=rgd.ROOT, stdout=subprocess.PIPE)
    sh(SSH + [HOST, f"cd {REMOTE} && tar xzf - --strip-components=1"],
       stdin=push2.stdout)
    push2.wait()

    cmdname = cmdfile.name
    # âš  The delimiters go over the wire as the two characters backslash-r and
    # backslash-n for the REMOTE shell to interpret, not as the bytes
    # themselves -- a raw CR or newline embedded in an `ssh` command string is
    # the "unterminated quote" failure mode from the other direction.
    run = (f"cd {REMOTE} && tr -d '\\r' < {cmdname} | "
           f"xargs -P {JOBS} -d '\\n' -I CMD sh -c CMD; "
           # report only the units that said something -- a silent log is a
           # clean compile, and printing 5,000 blank headers buries the two
           # that matter.
           'for f in *.log; do if [ -s "$f" ]; then echo "== ${f%.log}"; '
           'head -6 "$f"; fi; done')
    r = sh(SSH + [HOST, run], capture_output=True, text=True)
    if r.returncode != 0 and r.stderr:
        print(r.stderr.strip().splitlines()[-1])
    for line in r.stdout.splitlines():
        print(line)

    # Pull every object back in one stream.
    rgd.OBJ_DIR.mkdir(parents=True, exist_ok=True)
    pull = subprocess.Popen(SSH + [HOST, f"cd {REMOTE} && tar czf - *.o"],
                            stdout=subprocess.PIPE)
    sh(["tar", "xzf", "-", "-C", str(rgd.OBJ_DIR.relative_to(rgd.ROOT)).replace("\\", "/")],
       stdin=pull.stdout)

    # Record who wrote these objects. status.py --host refuses to score
    # anything it did not build: a plain status.py run compiles with the local
    # stand-in into this same directory, and scoring THAT under the b210
    # heading prints a wholly different board that still looks plausible.
    pull.wait()
    # Post-process the objects that need it (gcc section folding, data-symbol
    # redirects, config/objfix.txt) before the stamp, so link.py only ever
    # reads a fixed object.  A failed fix drops the object: it must read as a
    # build failure, not as the unfixed object.
    import objfix
    for s in symbols:
        o = rgd.OBJ_DIR / f"{s}.o"
        if o.exists():
            try:
                objfix.apply(s, o, tc.get(s, ("mwcc", ""))[0])
            except Exception as e:
                print(f"objfix: {s}: {e}")
                o.unlink()
    (rgd.OBJ_DIR / ".built-by").write_text("host")

    missing = [s for s in symbols if not (rgd.OBJ_DIR / f"{s}.o").exists()]
    print(f"built {len(symbols) - len(missing)}/{len(symbols)} on {HOST}")
    if missing:
        print("FAILED: " + " ".join(missing))
        return 1
    return 0


if __name__ == "__main__":
    import data2c_integration
    if data2c_integration.enabled():
        import data2c_runner
        sys.argv.insert(1, "build")
        sys.exit(data2c_runner.main())
    sys.exit(main())
