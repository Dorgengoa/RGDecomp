#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of the game's own render API above the DMA packets (docs/PERF-3D.md
"Native renderer: where to intercept").

    render_api.py [--src game/src] [--group NAME] [--callers N]

For each group of entry points (regex on the function name, below) lists every
matching function the decompiled sources define, the file that defines it, how
many call sites it has in the game sources (text match `Name(` outside its
own definition) and in how many files, and the busiest calling files.  Pure
text census: virtual calls through vtables are not seen (noted per group)."""
import argparse, collections, os, re, sys

GROUPS = [
    ("frame + draw list (buckets, sort, commit, env, texture loads)",
     r"^(GfxEndFrame|GfxFlipBuffersMaybe|GfxSysInit|DrawList\w+|DrawEnv\w+|DrawCtx\w+|DrawBufPairInitMaybe)$"),
    ("models / meshes (static VU packets, skinning, materials)",
     r"^(Model(Draw|Emit|Build|Mesh)\w*|Mesh(Pkt|Material)\w+|Character2Draw|MapAreaModelDrawBucketLit|EffModelDrawNodes|EffQuadDrawNodes|EffModelResInitFromMds)$"),
    ("VU1 program selection / MSCAL", r"^(VuMicrocode\w+|DmaPktAddMscalCall|DmaPktAddCallTag\w*|DmaPktPushQword|DmaTagMake|DmaAddrFromSpr)$"),
    ("2D / immediate GS packets", r"^(GsPkt\w+|GsDraw\w+|GsEnv\w+|Draw(Billboard32|ClippedGouraudQuad|ColorRect|RotatedQuad\w*|ScreenFillRect|TexturedRect|Wire\w+)|GfxBlitTexRect\w*)$"),
    ("textures / VRAM", r"^(FixedTex\w+|GsBuildImageUpload\w+|GsDownloadImage|GsClearDoubleBuffers|GsDbufPutEnv|GsFrameSet\w*)$"),
    ("screen effects (render-to-texture passes)", r"^(\w*(Filter|Blur|Bloom|Glare|Dof|Focus)\w*(Draw|Register|Process|Init)\w*|GameSceneCBlur\w+|BloomExtractBlurMaybe|DepthProbeGetSlot)$"),
]

ap = argparse.ArgumentParser()
ap.add_argument("--src", default=os.path.join(os.path.dirname(__file__), "..", "..", "game", "src"))
ap.add_argument("--group", default="")
ap.add_argument("--callers", type=int, default=3)
a = ap.parse_args()

files = []
for root, _, fs in os.walk(a.src):
    for f in fs:
        if f.endswith((".c", ".cpp")):
            files.append(os.path.join(root, f))
# every identifier followed by "(" in every file, counted per file (one pass)
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
calls = {}
for f in files:
    try:
        calls[f] = collections.Counter(CALL.findall(open(f, encoding="utf-8", errors="replace").read()))
    except OSError:
        pass

# functions defined: the generated tree has one function per file named
# <Name>_<addr>.c[pp]; the C name is the file stem
defs = {}
for f in files:
    stem = os.path.splitext(os.path.basename(f))[0]
    m = re.match(r"(.+?)_([0-9a-f]{6})$", stem)
    if m:
        defs[stem] = (m.group(1), f)

for title, pat in GROUPS:
    if a.group and a.group not in title:
        continue
    rx = re.compile(pat)
    names = sorted(s for s, (base, f) in defs.items() if rx.match(base))
    print("### %s\n" % title)
    print("%d functions.\n" % len(names))
    print("| function | file | call sites | caller files | busiest callers |")
    print("| --- | --- | --- | --- | --- |")
    total = 0
    for n in names:
        per = collections.Counter()
        for f, cc in calls.items():
            c = cc.get(n, 0)
            if f == defs[n][1]:
                c -= 1   # the definition itself
            if c > 0:
                per[os.path.splitext(os.path.basename(f))[0]] += c
        sites = sum(per.values())
        total += sites
        top = ", ".join("%s (%d)" % (k, v) for k, v in per.most_common(a.callers))
        print("| %s | %s | %d | %d | %s |" % (n, os.path.relpath(defs[n][1], a.src).replace("\\", "/"), sites, len(per), top))
    print("\n%d call sites in total (direct calls; virtual calls through vtables are not counted).\n" % total)
