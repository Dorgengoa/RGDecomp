#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""tests/protos: run the protos stage (tools/stages/protos.py) over the fixture
corpus and write the staged files + game_protos.h + PROTOS.tsv.

    run_stage.py --out DIR [--fault providers|bits|wide] [--check]

--fault providers  stage without the provider table (callees with no C truth
                   keep their callers' views): the deliberately-wrong control
--fault bits       stage with double treated as an 8-byte integer (no bit
                   transport, no double carriers): second control
--fault wide       stage without the 64-bit carrier rules (RG_PROTOS_NO_WIDE):
                   third control
--fault vslot      stage without the vtable-slot float lane rule
                   (RG_PROTOS_NO_VSLOT): fourth control
--fault abi2       stage without the 2026-10-18 rules (ee-round-floor, def-v0-return,
                   u128-view, extern "C" block linkage, overlay-import tail value): fifth
                   control
--fault shortagg   stage without rule short-agg (RG_PROTOS_NO_SHORTAGG): sixth control
--fault abi3       stage without the 2026-10-25 manual-row rules (agg-view, the u128-view
                   extra lane, ret-narrow-view, object-like type macros): seventh control
--check            also assert the stage's per-site decisions in PROTOS.tsv and
                   the outputs (exit 1 when one is missing)
"""
from __future__ import annotations

import argparse
import os
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
FIX = HERE / "fixture"
sys.path.insert(0, str(PORT / "tools" / "stages"))
import protos  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--fault", choices=("providers", "bits", "wide", "vslot", "abi2", "shortagg", "abi3"))
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    files = {}
    for sub in ("src", "include", "config"):
        for f in sorted((FIX / sub).rglob("*")):
            if f.is_file():
                files[f.relative_to(FIX).as_posix()] = f.read_bytes()
    if a.fault == "wide":
        os.environ["RG_PROTOS_NO_WIDE"] = "1"
    if a.fault == "vslot":
        os.environ["RG_PROTOS_NO_VSLOT"] = "1"
    if a.fault == "abi2":
        for k in ("RG_PROTOS_NO_EEROUND", "RG_PROTOS_NO_V0RET", "RG_PROTOS_NO_U128VIEW",
                  "RG_PROTOS_NO_EXTERNC", "RG_PROTOS_NO_IMPORTTAIL"):
            os.environ[k] = "1"
    if a.fault == "shortagg":
        os.environ["RG_PROTOS_NO_SHORTAGG"] = "1"
    if a.fault == "abi3":
        for k in ("RG_PROTOS_NO_AGGVIEW", "RG_PROTOS_NO_U128EXTRA", "RG_PROTOS_NO_NARROWVIEW",
                  "RG_PROTOS_NO_TYPEMACRO"):
            os.environ[k] = "1"
    if a.fault == "bits":
        kind = protos.T.kind.fget
        protos.T.kind = property(lambda t: "q" if kind(t) == "d" else kind(t))
    st = protos.ProtoStage(port_root=FIX,
                           provider_dirs=() if a.fault == "providers" else ("overrides",),
                           provider_headers=() if a.fault == "providers" else ("providers/crt.h",))
    st.addr_table = {"main": {0x300000: "Target_300000"}, "entries": {},
                     # retail listing of the listing-rule fixtures (src/main/listing)
                     "asm_text": protos.split_listing(
                         (FIX / "asm" / "main.s").read_text(encoding="utf-8")),
                     "asm_paths": {}, "ovl_text": {}, "gp": 0x485170, "by_name": {}}
    st.prepare(dict(files))
    out = {}
    for rel, data in files.items():
        if rel.startswith("src/"):
            new, _ = st.apply(rel, data)
            if st.apply(rel, new)[0] != new:
                print(f"FAIL not idempotent: {rel}")
                return 1
            out[rel] = new
    out.update(st.extra_outputs())
    for rel, data in out.items():
        f = a.out / rel
        if not f.exists() or f.read_bytes() != data:
            f.parent.mkdir(parents=True, exist_ok=True)
            f.write_bytes(data)
    if not a.check:
        return 0
    log = out["PROTOS.tsv"].decode()
    hdr = out["include/port/game_protos.h"].decode()
    rows = [ln.split("\t") for ln in log.splitlines()[1:]]

    def row(callee, rule, needle="", file=""):
        return any(r[2] == callee and r[3] == rule and needle in r[4] and file in r[0]
                   for r in rows)
    checks = [
        ("provider prototype in header", "double dpmul(double, double);" in hdr),
        ("override is truth (float)", "float VecLen_1cb3c0(void *);" in hdr),
        ("per-site import: normal", row("func_4EC000", "overlay-import-site", "normal",
                                        "FieldHudFadeIn")),
        ("per-site import: factory", row("func_4EC000", "overlay-import-site", "factory",
                                         "FactoryMenuResReady")),
        ("per-site import: no header prototype", "func_4EC000" not in hdr),
        ("per-site import: decl patched to normal's shape",
         "extern void func_4EC000(const u8 *, f32, f32);" in
         out["src/main/ovl/FieldHudFadeIn_203ee0.c"].decode()),
        ("hosted-unstatic", row("Guest_200100", "hosted-unstatic")),
        ("hosted guest lost static", "static s32 Guest_200100" not in
         out["src/main/hosted/Host_200000.c"].decode()),
        ("addr-alias", row("func_300000", "addr-alias", "Target_300000")),
        ("double-param", row("DoubleLess_1002b0", "double-param")),
        ("double-local", row("SoftMulInt_100020", "double-local")),
        ("ret-bitcast", row("fptodp", "ret-bitcast")),
        ("def-tail-vcall-return", row("IconRec_3ae3e0", "def-tail-vcall-return")),
        ("missing-passthrough", row("MatFromQuat_13c440", "missing-passthrough", "q")),
        ("provider array typedef decays to a pointer",
         row("FixCopyVector_13c480", "missing-passthrough", "src")
         and "FixCopyVector_13c480(void *, void *);" in hdr),
        ("lane reorder", row("MotionListSetRateById_172110", "reorder", "(ggfg) -> def 4 (gggf)")),
        # retail-listing rules (docs/PROTOS-MISSING-ARGS.md A-G)
        ("C: FPR passthrough", row("SetScale_400100", "missing-passthrough", "passed a, b")),
        ("A: callee never reads $5", row("UseNothing_400200", "missing-unused", "$5")),
        ("A: no def-widen for an unread register",
         "rgp_a1" not in out["src/main/listing/ListingRules_400000.c"].decode()),
        ("B: leftover of an earlier call", row("ReadsA1_400300", "missing-dead",
                                               "CLOBBER(Other_400400)")),
        ("E: symbol address held in a C local", row("ClearClip_400500", "missing-asm", "-> p")),
        ("E: local passed", "ClearClip_400500((void *)(p))" in
         out["src/main/listing/ListingRules_400000.c"].decode()),
        ("F: array local kept", "VecFill_400600(u, s)" in
         out["src/main/listing/ListingRules_400000.c"].decode()),
        ("G: inline struct parameter", row("FindFree_400700", "missing-passthrough", "arg0")),
        ("def-vthunk-naked", row("VThunk_4000c0", "def-vthunk-naked", "0x88")),
        ("def-vthunk-naked body", "void __attribute__((naked)) VThunk_4000c0" in
         out["src/main/listing/ListingRules_400000.c"].decode()),
        ("def-struct-by-ref", row("BigByValue_4000e0", "def-struct-by-ref", "b")),
        ("def-struct-by-ref copy", "Big b = *rgp_sbv_b;" in
         out["src/main/listing/ListingRules_400000.c"].decode()),
        # virtual call: forwarded entry registers + surviving $v0
        ("vcall-forward", row("v1", "vcall-forward", "p1, p2", "MeshGroupPkts")),
        ("vcall-forward decl", "virtual s32 v1(int rgp_fwd1 = 0, int rgp_fwd2 = 0);" in
         out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()),
        ("def-vcall-v0", row("v1", "def-vcall-v0", "", "MeshGroupPkts")),
        ("def-vcall-v0 body", "rgp_v0 = p0->v1((int)(long)(p1), (int)(long)(p2));" in
         out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()
         and 'extern "C" s32 MeshGroupPkts_400900' in
         out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()
         and "return rgp_v0;" in out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()),
        ("vcall-widen", row("GetEquipped_400980", "vcall-widen", "rgp_a1")),
        ("vcall-widen forwards", "return o->g0((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));" in
         out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()
         and "GetEquipped_400980(W8 *o, int rgp_a1, int rgp_a2, int rgp_a3)" in
         out["src/main/listing/MeshGroupPkts_400900.cpp"].decode()),
        # split locals retail keeps as one stack block
        ("stack-block", row("StackBlock_400a00", "stack-block", "b@0x0")),
        ("stack-block coverage guard", row("HoleBlock_400a80", "manual-stack-block", "0x10")
         and "rgp_blk" not in out["src/main/listing/HoleBlock_400a80.c"].decode()),
        ("stack-block trailing pad (callee-written slot)",
         row("PadBlock_401600", "stack-block", "h@0x0") and
         row("PadBlock_401600", "stack-block", "padded slot(s) 0x10")),
        ("stack-block switch callee (jump-table case reach)",
         row("PadBlock_401600", "stack-block", "k+0x10")),
        ("stack-block LEN_ARG memcpy length",
         not row("PadBlock_401600", "info-stack-block-unresolved", "memcpy")
         and not row("PadBlock_401600", "stack-block", "t@")),
        ("stack-block function-table target resolved (sbresolve dtbl)",
         row("FnTblBlock_401800", "stack-block", "v+0x10")
         and not row("FnTblBlock_401800", "info-stack-block-unresolved", "")),
        ("stack-block local placed by its spNNN name (not padded)",
         row("NameBlock_401700", "stack-block", "sp60@0x10")
         and not row("NameBlock_401700", "stack-block", "padded")),
        ("stack-block member placement",
         "(*(Ray *)(rgp_blk1 + (0x20 - __builtin_offsetof(Ray, c0))))" in
         out["src/main/listing/StackBlock_400a00.c"].decode()
         or "(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, d0))))" in
         out["src/main/listing/StackBlock_400a00.c"].decode()),
        # 64-bit values through 4-byte C
        ("wide-param", row("WideFind_400c40", "wide-param", "bne $2,$3")),
        ("wide-local", row("WideFind_400c40", "wide-local", "`s32 a`")),
        ("wide-arg", "WideFind_400c40(r, (long long)(*flags))" in
         out["src/main/listing/WideFlags_400c00.c"].decode()),
        ("wide: 32-bit use keeps its s32", not row("WideNarrow_400cc0", "wide-param")
         and "WideNarrow_400cc0((int)*flags)" in
         out["src/main/listing/WideFlags_400c00.c"].decode()),
        # 64-bit values returned through 4-byte C / inlined helpers
        ("wide-ret", row("WideRetWrap_400d60", "wide-ret", "ret@")
         and "long long WideRetWrap_400d60(" in out["src/main/listing/WideRet_400d00.c"].decode()),
        ("wide-ret accumulator", row("WideRetOr_400dc0", "wide-ret")
         and row("WideRetOr_400dc0", "wide-local", "`s32 acc`")),
        ("wide-local in a wide-ret def", row("WideRetWrap_400d60", "wide-local", "`s32 m`")),
        ("ret-zext", row("ZextParse_400e40", "ret-zext", "dsll32/dsrl32")
         and "| ((unsigned int)ZextParse_400e40(b))" in out["src/main/listing/ZextFlags_400e40.c"].decode()),
        ("ret-zext: a sign-extending caller keeps s32",
         "return ZextParse_400e40(a);" in out["src/main/listing/ZextFlags_400e40.c"].decode()),
        ("wide-inline-param", row("WideMatch", "wide-inline-param", "mask")
         and "unsigned long long mask" in out["src/main/listing/WideRet_400d00.c"].decode()),
        # float parameters of a vtable slot shared with a wider sibling
        ("vslot-lane", row("VStepA_401000", "vslot-lane", "int rgp_a1")
         and "s32 VStepA_401000(u8 *o, int rgp_a1, f32 dt)" in
         out["src/main/vslot/VStep_401000.c"].decode()
         and "int VStepA_401000(void *, int, float);" in hdr),
        ("vslot-lane: the wider sibling is left alone", not row("VStepB_401040", "vslot-lane")),
        ("vslot-lane: a direct caller fills the padding lane",
         "return VStepA_401000(o, dt);" not in out["src/main/vslot/VStep_401000.c"].decode()),
        # 2026-10-18 rules
        ("ee-round-floor", row("-", "ee-round-floor", "12582912", "Abi2_401200")
         and "t = __builtin_floorf(t);" in out["src/main/abi2/Abi2_401200.c"].decode()),
        ("def-v0-return", row("V0Pick_4012c0", "def-v0-return", "V0Flag_401280 (2 call(s))")
         and "(rgp_v0 = V0Flag_401280(o, 1))" in out["src/main/abi2/Abi2_401200.c"].decode()
         and "int V0Pick_4012c0(void *, int);" in hdr),
        ("def-v0-return: `G(..); return;` early exit",
         row("V0Early_401300", "def-v0-return", "(2 call(s))")
         and "return rgp_v0;" in out["src/main/abi2/Abi2_401200.c"].decode()
         and "return (void)" not in out["src/main/abi2/Abi2_401200.c"].decode()),
        ("def-v0-return: the caller reads the value",
         not row("V0Pick_4012c0", "void-value-zero")),
        ("u128-view", row("U128Id_401340", "u128-view", "ret u128 vs s32")
         and not row("U128Id_401340", "manual-call")),
        ("extern \"C\" block linkage", "void LinkTake_401500(void *);" in hdr
         and row("LinkTake_401500", "missing-passthrough", "p")),
        # 2026-10-25: short view of a definition with a word-size aggregate parameter
        ("short-agg", row("HandleGet_401900", "short-agg-call", "g1 = k (passthrough)")
         and row("HandleGet_401900", "short-agg-decl", "added int")
         and "HandleGet_401900(o + 8, (int)k)" in
         out["src/main/abi2/HandleUser_401940.c"].decode()
         and "extern void **HandleGet_401900(void *t, int);" in
         out["src/main/abi2/HandleUser_401940.c"].decode()
         and not row("HandleGet_401900", "manual-call")),
        # 2026-10-25: the protos manual-row close-out rules
        ("agg-view", row("GaijiDraw_402000", "agg-view", "align 8")
         and row("GaijiDraw_402000", "agg-bits", "long long")
         and "__builtin_bit_cast(long long, (c))" in
         out["src/main/abi3/GaijiUser_402040.c"].decode()
         and not row("GaijiDraw_402000", "manual-call")),
        ("u128-view: extra GPR lane dropped", row("PushApart_402080", "u128-view", "never reads")
         and row("PushApart_402080", "drop-extra")
         and "PushApart_402080(p, 2.0f, 3.0f)" in out["src/main/abi3/PushUser_4020a0.c"].decode()),
        ("type macro: the definition's `RT` return is u8",
         "unsigned char Low8Sum_4020c0(void *);" in hdr
         and row("Low8Sum_4020c0", "ret-narrow", "", "NarrowUser_4020e0")),
        ("ret-narrow-view: C++ pointer view of a u8 definition",
         row("Low8Sum_4020c0", "ret-narrow-view", "", "NarrowPtrUser_402100")
         and "((void *)(long)(unsigned char)Low8Sum_4020c0(p))" in
         out["src/main/abi3/NarrowPtrUser_402100.cpp"].decode()),
        ("overlay import: tail value of the overlay definition",
         row("normal_ResReady_4ec100", "def-tail-return")
         and not row("func_4EC100", "void-value-zero")),
    ]
    bad = 0
    for name, ok in checks:
        print(("ok   " if ok else "FAIL ") + name)
        bad += not ok
    print(f"{bad} failure(s)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
