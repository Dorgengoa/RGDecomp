# 3D scene performance (field, battle)

User play-test 2026-10-13 (BRINGUP.md): 3D scenes ran at about 1-2 fps windowed
(`build/render-i686`, `RG_GPU=hw`, release -O3, RTX 3080). Earlier numbers (GPU.md
"Performance" / checkpoints 2-4, VU.md "Performance" / "Block translator") were taken on
builds that drew little or no 3D (camera in the sky, VU1 microcode words missing:
RENDER-BRINGUP.md), so this lane re-profiles the corrected scene from scratch.

Target: 60 fields/s windowed on the RTX 3080, frame output unchanged.

Build `build/perf3d-i686` (same configuration as `render-i686`: Release, clang i686,
`out/perf3d/b.ps1`). Scratch tools, runs and logs: `out/perf3d/` (game data and
measurements, never committed). Golden input `tools/trace/goldens/newgame_battle.input.txt`:
the post-FMV 3D field is fields ~7,400-16,000, the first battle starts at ~22,900.

## Checkpoint 4 (GPU.md) state

Checked first: `src/gpu` and `src/ps2/gs` at the end of checkpoint 4 build cleanly in a
fresh tree and every `gpu`/`gs` test passes on the RTX 3080 (162 + the 4 game-replay tests
with `RG_DATA` set; `settings.core_defs` fails, a settings-lane test that `-L gs` matches
by name). Checkpoint 4's only open item was the windowed real-time runs, which this
document supersedes.

## How the game spends a frame

The game draws at 30 Hz: every odd field carries the whole frame (EE game code, the
frame's VIF1 chain kicked by `GfxEndFrame_141c20`, VU1, GS, GPU) and the even field is
almost empty (0.3 ms). "60 fields/s" therefore means one frame's work in 33 ms. The
tables below give means per field over a range (half the per-frame cost).

`RG_FIELD_TIMES` gained three columns (`src/runtime/runtime.c`, measurement only):
`step_ms` (the field's `ps2k_step`: EE, DMA, VIF, VU, GS model, GPU submission),
`read_ms` (fetching the frame to present: the display read-back, which waits for the GPU
to finish the frame) and `present_ms` (`rg_host_present`). `out/perf3d/ft2.py` averages
them per range.

## Baseline (build `base_bin` = current sources before this work)

Windowed, default settings (internal resolution "window" = 3x for the default
1280x960 window, anisotropic 16x), `--unthrottled`, golden input. The machine was shared
with other sessions' headless runs throughout (2-4 other `rg-game` processes), so absolute
numbers carry noise of 10-30 %; comparisons below are interleaved runs.

| fields | baseline ms/field | note |
| --- | --- | --- |
| 7400-7999 (post-FMV cutscene) | 78.7 | |
| 8000-9999 | 60.4 | |
| 10000-15999 (field) | 75-89 | |
| 16000-19999 | 104.0 | |
| 20000-22899 | 143.0 | |
| 22900-23400 (first battle) | 140.9 | ~3.5 game frames/s |

GPU profile of the baseline (`RG_GPU_PROFILE=1`, fields 7400-8400, x1 headless): 37.3 ms
of GPU time per field, 1,400 batches per field, almost all of them one or two triangles:
1,462 destination snapshots per field (5.2 ms), "draw exact tex" 805 calls (19.5 ms),
plus 4.5 ms of CPU in `Flush` (kicks). The run's totals: 2.74 M batches and 2.52 M
destination copies in 9,000 fields.

**Cause:** the 3D scene's blended (and alpha-test FAIL two-pass) primitives are drawn
under a depth test that can fail (ZTST GEQUAL/GREATER). Ordered blending (GPU.md
"Performance") could not take those, because the colour view is written whatever the
depth test decides; so every such primitive went to the serial path: a batch split at
each overlapping primitive and a destination snapshot per batch.

## Fixes

Each fix keeps the frame output identical; the evidence is listed per fix and summed up
under "Exactness" below.

### 1. Depth in ordered views (`zrov`)

On a device with rasterizer-ordered views (the RTX 3080 and WARP) depth targets are no
longer D32_FLOAT depth buffers but `R32_TYPELESS` textures with RTV, SRV and UAV views
(`R32_FLOAT`), holding exactly what the depth buffer held (z / 2^32). The pixel shader
(`GS_ZROV` variants of `PS_main*`) reads the depth through a
`RasterizerOrderedTexture2D<float>` after every discard (scan mask, line DDA, exact
coverage, alpha test, DATE), compares with the output merger's comparison (float >= / >),
discards on failure and writes Z when the pixel's pass writes Z (`D[11].z`: test, Z write of
passing / failing pixels). Every pixel's depth read-modify-write is therefore in primitive
order, so the core lets any depth test and per-pass Z masks through ordered blending
(`gpu_core.cpp` `derive`: `rov_depth_ok`), and both alpha-test passes are one draw.
Loads into a depth target render into its RTV (`PS_load_depth_rt`), resizes copy it,
write-backs and direct sampling read the same `R32_FLOAT` SRV as before. Non-blended
batches draw colour through the RTV as before and depth through the view.
`gpu_config.no_zrov` / `RG_GPU_NO_ZROV=1` (and `RG_GPU_NO_ROV=1`) keep the old path;
`gpu_ordered_depth()` tells which is on.

Result (windowed, 3x, aniso 16x, fields to 8400; interleaved with the baseline):

| | baseline | zrov |
| --- | --- | --- |
| batches / destination copies (fields 0-8400) | 2.31 M / 2.15 M | 288 k / 0 |
| 7400-7999 ms/field | 78.7 | 47.4 |
| 8000-8400 ms/field | 60.9 | 28.4 |

Test: `scene.ordered` gained a "zgreater" pass for each format, opaque Gouraud triangles
and AFAIL ZB_ONLY / FB_ONLY two-pass primitives under the Z test, and with depth in ordered
views the scene must batch its depth-tested primitives too (442 primitives: 33 batches,
was 165 with `RG_GPU_NO_ZROV=1`); exact (tol 0) on the RTX 3080 and WARP.

### 2. Zero-copy presentation

The presenter read every frame back (8 MB at 3x), copied it twice on the CPU and uploaded it
to SDL's own D3D11 device: 3-6 ms per field, and a wait for the GPU to finish the frame.
Now `gpu_present_shared` composes the display (and the post chain) as before but copies it
into one of two textures shared with other devices (`D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX`,
keyed mutex 0 -> 1), and `rg_host_present_shared` opens it on the SDL renderer's device
(`SDL_PROP_RENDERER_D3D11_DEVICE_POINTER`, `SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_POINTER`),
acquires key 1, draws it with the same scaling as before and releases key 0 after
`SDL_FlushRenderer`. The runtime uses it whenever the renderer and the window are both
Direct3D 11 (falls back to the read-back otherwise, or with `RG_PRESENT_COPY=1`). The run
hash and dumps still read the display itself (unchanged); F12 then saves the window.

### 3. Smaller exact shaders (`GS_NOTEX`, no indexable temps)

Untextured exact-triangle batches use variants compiled with `GS_NOTEX` (texture paths
compiled away: 21 temp registers and ~800 instructions instead of 40 and ~3,900), and the
two small arrays the exact path indexed dynamically (`g_axd[2]`, `g_tc[4]`, DXBC
indexable temps = local memory) became scalars. Same arithmetic. `RG_GPU_NO_NOTEX=1`
selects the full shader (check only).

### 4. Platform code at -O2

`src/ps2/vu`, `src/ps2/gs`, `src/ps2/vif`, `src/ps2/dmac` and `src/gpu` are original port
code, not decompiled game code; they now compile at -O2 (source-level `COMPILE_OPTIONS`,
which come after `rg_flags`' -O1). PLAN.md D2's -O1 stays for the game sources until their
UB audit. VU1 replay of the battle capture (`rg-vu-replay C_v24804 --reps 7`, best):
47 -> 43 ms, same HASH line.

### 5. VU1: call-threaded variants

`vu_block.c` turns each compiled variant's op list into straight code (i686: one
`mov eax, esi / mov edx, edi / mov ecx, op / call handler` per op, in an 8 MB executable
arena reset with the block pool; `RG_VU_JIT=0` off). Same handlers in the same order.
43 -> 41 ms on the battle capture (the handlers themselves dominate).

### 6. Anisotropic filtering: decoded textures

Anisotropic taps (up to 32 bilinear samples per pixel) read the texture through the
swizzled mirror, one address computation per texel. A batch with anisotropic taps now
decodes the whole level-0 wrap rect (any format) into the RGBA copy the decoded-texture
path already used (cached under the same content key, now up to 256 copies), and bilinear
samples whose 2x2 block lies inside it take four plain loads after one bounds test. Same
texels, same weights. Renderer replay of the 3D field (`rec/f3d_7600.rggs`, 20 fields, 3x,
`RG_GPU_ANISO=16`, best of 8): 1,082 -> 639 ms of GPU time (54 -> 32 ms per field). For
scale: the same replay without anisotropy is ~335 ms; 2x/4x cost ~490-500 ms, 8x/16x
~630-690 ms.

The Gather of the first measurement was replaced by four plain loads after WARP showed that
`GatherRed` on the R32_UINT copy selected other texels there (`gpu.gfx.anisotropic` failed
on WARP, reported by the prompts lane; fixed, now passing on both devices).
`RG_GPU_ANISO=N` (measurement) sets the taps in renderer-only replays. The replay test now
prints `GPUHASH` (every presented frame at the internal resolution plus local memory at the
end): with `RG_GPU_ANISO=16` at 3x it is identical with `RG_GPU_NO_DECODE=1`,
`RG_GPU_NO_NOTEX=1` and `RG_GPU_NO_ZROV=1`, i.e. fixes 1, 3 and 6 are bit-exact where the
software reference does not apply (upscaling, enhancements).

### 7. GS worker thread (`src/ps2/gs/gs_async.c`)

`gs_async_start` (the runtime calls it after the renderer starts; `RG_GS_ASYNC=0` keeps the
synchronous model) makes `gs_gif_write` / `gs_gif_reset` copy their input into a 64 MB
single-producer ring that a worker thread executes in order; the GS model and the renderer
hooks (all of `src/gpu`'s drawing) then run beside the EE, VIF and VU1 work that produces
the packets. Nothing the EE side can observe changes:

- Privileged registers stay on the caller's thread. The only GIF writes that touch them
  (SIGNAL, FINISH, LABEL) are found by a GIFtag walk of each packet as it is queued
  (per path, PACKED A+D descriptors). If the event's interrupt is unmasked the packet runs
  synchronously after a drain; otherwise it is queued and the next read of CSR or
  SIGLBLID (or write of IMR) drains first. `raise_event` ORs `csr_events` atomically.
  Census (`RG_GS_CENSUS=N`, measurement): from field ~8,500 the game raises one masked
  FINISH per frame and reads CSR 1.5 times per field, and reads the GS FIFO once per frame;
  no SIGNAL, no unmasked GS interrupt. (A first version ran every FINISH packet
  synchronously: the battle got slower.)
- `gs_read_fifo` (local->host data: the per-frame Z read), `gs_path_idle`,
  `gs_read_display`, `gs_rec_snapshot`, a CSR write (RESET), the recorder and
  `gs_destroy` drain the ring first; the runtime drains at the start of each field's
  presentation (it then calls the renderer directly) and before screenshots.
- The worker makes the same calls in the same order as the synchronous model.

Signalling is lock-free on the fast path (atomic head/tail, a condition variable only when
a side sleeps); `GS worker: entries, MB, drains, packets run synchronously` is printed at
shutdown.

Windowed 3x, aniso 16x, fields to 8400, one binary with `RG_GS_ASYNC=1` / `0`:

| ms per field | async | sync |
| --- | --- | --- |
| 7400-7999: wall / step / read / present | 30.1 / 10.8 / 16.9 / 2.1 | 34.0 / 17.2 / 14.6 / 2.2 |
| 8000-8400 | 25.0 / 10.0 / 12.4 / 2.1 | 26.2 / 16.0 / 7.9 / 2.2 |

The main thread's step drops by 6-7 ms per field; the field is then GPU-bound ("read" is
the wait for the GPU). Headless 1x, fields 20,000-20,500: 81.7 -> 73.7 ms per field.

### 8. VU1 single-precision fast path

`vu_block.c`'s FMAC handlers (ADD/SUB/MUL/MADD/MSUB, every operand source) first try one
SSE single-precision operation under round-toward-zero with denormals-are-zero (a variant
switches MXCSR at entry and exit; handlers that call out or need the double path switch back
to the caller's mode): for operands that keep the VU result an ordinary float it equals the
interpreter's double computation truncated to 23 bits. Conditions (dest lanes only): no
operand exponent 255; products of nonzero operands with an exponent sum in [128, 380] (no
overflow, no underflow); sums with exponents at most 28 apart (the double sum is then
exact) and below 254; no denormal result. Everything else takes the double path as before.
MAC bits as the double path's fast lanes. `RG_VU_FAST=0` turns it off.

Two compiler hazards found on the way, both handled: clang may turn the integer "magnitude
== 0" test of a result into a float compare, which under DAZ reads a denormal as zero (a
denormal result then looked like an exact zero: `rg-vu-blkfuzz` seeds 0xD4 and 0xB2 failed);
the result now passes an empty `asm` before the integer tests. And the compiler does not
model MXCSR, so the double path's loads and arithmetic are fenced between the mode switches
(memory clobbers, register barriers on the operands).

Checks: `out/perf3d/fmacdiff.c` compares the fast path with the double path lane by lane on
edge-biased random operands (exponents 0, 1-4, 250-254, 255; fractions 0 / all ones /
random; every kind and dest mask): 50 M cases, 0 differences. `rg-vu-blkfuzz` 10,000
iterations on 8 seeds, `ctest -L vu` 186/186, replay HASH lines unchanged. VU1 replay of the
battle capture (`rg-vu-replay C_v24804 --reps 9`, best): 51 ms (before fixes 4, 5 and 8) ->
40 ms; with the fast path off but the variant's MXCSR switches still in place the slow
path costs 61 ms (two `ldmxcsr` per FMAC), so the switches stay out of the common path.

## Exactness (all fixes together)

- `ctest` in `build/perf3d-i686`: 635 / 635 (WARP for `gpu`, `RG_DATA` set);
  `-L "gpu|gs|vu|runtime|host|settings"` on the RTX 3080 397 / 397; `-L "gpu|gs"` on WARP
  176 / 176; `-L gpu` with `RG_GPU_NO_ROV=1` 92 / 92 (game replays included).
- Golden run, headless 1x, `base_bin` (before) vs the final binary (`out/perf3d/vrun.sh`,
  `vrun16.sh`, `vcmp.sh`): screenshot at field 8000 and at field 16000 byte-identical, 32
  and 64 STATUS lines identical, GS recordings of fields 7900-7960 and 13900-13930
  identical in every bit the GS uses (differences only in ALPHA_1 bits 40-63, ZBUF_1's high
  word and FBA_1 bits 1-63, where the game leaves host pointers), EE RAM at 7000 / 8000
  differing only in relocated pointers (`out/vuperf/ramcmp2.py`; exe bases inferred with
  `out/perf3d/basefind.py`).
- `GPUHASH` of the 3D-field recording at 3x with 16x anisotropy identical with each fix
  switched off (fix 6 above). VU: see fix 8.

## Results

Windowed, default settings (3x, anisotropic 16x), `--unthrottled`, golden input, ms per
field (the machine's GPU was shared with up to 6 other sessions' `rg-game` runs throughout,
often at 85-96 % utilisation, so these are upper bounds):

| fields | baseline | after fix 1 (zrov) | final (`z9`) |
| --- | --- | --- | --- |
| 7400-7999 cutscene | 78.7 | 57.7 | 29.1 |
| 8000-9999 | 60.4 | 34.8 | 21.5 |
| 10000-11999 field | 88.2 | 56.5 | 28.7 |
| 12000-13999 | 89.3 | 50.2 | 27.1 |
| 14000-15999 | 75.3 | 54.4 | 25.3 |
| 16000-19999 | 104.0 | 59.8 | 34.6 |
| 20000-22899 | 143.0 | 75.6 | 48.1 |
| 22900-23400 battle | 140.9 | 58.2 | 41.0 |

16.7 ms per field (one game frame per 33 ms) is not reached. What is left is GPU time
(below) and VU1 on the main thread.

## Data for the native renderer (re-scope 2026-10-17)

The orchestrator re-scoped this lane: the emulated VIF / VU1 / GS path stays as the
reference ("Original" oracle); the shipping exe is to be 100 % native (PLAN.md D9 "Native
end state": no emulation in the shipping exe; a native renderer driven from the game's own
render API). No further emulation-path optimisation was done after that; the tools and data
below are the input for the native lane. Everything here is regenerated by the scripts in
`tools/perf3d/` (next section).

### Cost per field by subsystem

`tools/perf3d/perf3d.sh` profile run (`out/perf3d/runs/p12_full/report.md`), windowed 3x,
anisotropic 16x, GS model on the main thread (`RG_GS_ASYNC=0`) so the shares add up on one
thread; ms per field (frames are 2 fields), sampling profiler at ~9 ms:

| | 7400-7999 cutscene | 14000-14999 field | 20000-20599 field | 23000-23399 battle |
| --- | --- | --- | --- | --- |
| wall | 37.9 | 25.2 | 54.7 | 76.3 |
| EE game code (`game`) | 0.95 | 1.41 | 1.89 | 2.84 |
| VIF / DMAC | 1.16 | 0.88 | 1.81 | 2.23 |
| VU1 (block translator) | 8.95 | 9.51 | 16.64 | 18.18 (+4.25 waiting below XGKICK) |
| GS model | 3.50 | 3.44 | 5.75 | 8.18 |
| GPU renderer CPU + driver | 6.04 | 4.43 | 7.49 | 9.84 |
| waiting for the GPU (read-backs, full queue) | 13.84 | 2.06 | 12.82 | 26.13 |
| CRT (memcpy etc.) | 1.94 | 1.64 | 1.95 | 1.64 |
| presentation (read + present, timing columns) | 15.3 | 3.8 | 5.6 | 5.2 |

GPU time of the same scenes, recordings replayed through the renderer alone
(`tools/perf3d/gpu_replay.sh`, best of 2-3, 3x; the GPU was shared): 3D cutscene
(`f3d_7600`) 19.9 ms per field without anisotropy / 36.0 with 16x; field `f3d_14000`
10.9 / 13.9; field `f3d_16000` 33.3 / 48.7-68.1; battle `f3d_23000` 25.5 / 32.5-34.2. The
largest category is "draw rov decoded exact tex" (textured, blended, exact triangles:
13-32 ms per field with 16x anisotropy), then "draw decoded exact tex" and "draw rov exact
flat" (battle: 185 batches per field, 5.6 ms).

**EE game code alone is 1-3 ms per field** (2-6 ms per game frame) in all four scenes; the
rest is the emulated pipeline. -O2 for the game sources: not measured yet (a measurement
tree with `tools/perf3d/o2wrap.py` was ~40 % built when the work was paused; see
"Resume").

### VU1 microprograms

`tools/perf3d/census.py` on the census run (`RG_PERF_CENSUS`; VU host time from the
`p12_full` run, async GS so it excludes GS work). Programs are identified by start address
and the hash of the 16 pairs there, and matched to the retail MPG packets that upload
exactly those bytes (`census/platform_vu1.tsv` + the retail ELF):

| program (start, hash) | retail packet / VuMicrocodeTableInit slots | cutscene calls, k pairs / field | field 14000 | battle 23000 | share of VU1 time |
| --- | --- | --- | --- | --- | --- |
| 0x0328 9B8147C2 | 0x436CB0 (a[0][0,2,3,7,9,11][0]), same code in 0x436FB0, 0x440970, 0x4441A0 | 238, 470 | 373, 876 | 2,236, 4,617 | 57-72 % |
| 0x0330 EECD5533 | same packets (second entry of the program) | 99, 164 | 97, 225 | 628, 1,226 | 21-36 % |
| 0x0328 5D4D6A4C | 0x441660 (a[0][1][0]) | - | 26, 20 | 170, 136 | 1-3 % |
| 0x0328 06BE44CE / 0x0330 453B910D | 0x4425F0 (a[0][4][0]) | 3, 4 | 20, 21 | 71, 78 | 1-3 % |
| 0x0960 568273EF | 0x445C60 | 9, 1 | 20, 5 | 114, 20 | 1-4 % |
| 0x0000 2878F695 | not a retail packet (uploaded at run time) | 46, 4 | 52, 4 | 352, 30 | < 1 % |

One program family (the 0x436CB0 code at 0x0320/0x0328/0x0330, MSCAL entries 0x320 and
0x330 plus a 0x320 prologue) does 93-95 % of all VU1 work in every scene: nativising (or
replacing) it covers nearly everything. **Battle anomaly:** the port's battle runs 6.1 M
VU1 pairs and ~4,200 MSCALs per field (two-field frames: ~12 M pairs per frame); the retail
battle capture (`C_v24804`) has 2.74 M pairs and 2,224 MSCALs per frame. The 3D cutscene
matches retail (port 0.645 M pairs per field = 1.29 M per frame, retail `C_v09002` 1.27 M).
The battle segment of the golden run is in the known divergent state (BRINGUP.md: the
"escape?" window loop instead of the tutorial), so it may draw a different scene; worth a
check by the battle lane (models drawn twice, culling or LOD not applied). **Update 2026-10-17 (BRINGUP.md "first hit"):** with hits landing, fields 23050-23099 run 1.40 M pairs / field (= retail 1.37 M / field); after the tutorial 4.25 M / field with enemies crowding the camera (not the same scene as retail's capture).

### GS features used

`tools/perf3d/census.py` (GS feature census; the run above had a masking bug in the texture
fields, so texture formats are shown as "psm03" where the format is T8 = 0x13 and "psm00"
for CT32; corrected in `gs_census.c` but not re-run). Per field, field 14000 / battle:

- Primitives: 5.6 k / 20.2 k per field; 82-90 % triangle strips (Gouraud), the rest fans,
  sprites (2D, post passes), a few lines.
- Blend: `(Cs-Cd)*As+Cd` (normal alpha) 62-67 % of primitives; opaque 25-32 %;
  `(Cs-0)*As+Cd` (additive) 4-6 %; `(0-Cs)*As+Cd` (subtractive) 0.1-2 %;
  `(Cs-0)*128+Cd`, `(Cs-Cd)*128+Cd`, `(Cs-0)*As+0`, `(Cs-0)*Ad+0`: rare (2D/effects).
- Alpha test: GEQUAL (atst 5, AREF typically 1) on 90-97 %, GREATER 1-5 %, AFAIL always
  KEEP (0); no FB_ONLY/ZB_ONLY/RGB_ONLY in these scenes.
- Destination alpha test: practically unused (one effect draw).
- Depth: Z24 (PSMZ24 = 0x31) everywhere; GEQUAL with Z write 90 %, GEQUAL without write
  1-6 % (blended effects), no test 3-6 % (2D).
- Textures: 8-bit indexed (T8) with a CT32 CLUT 87-88 %, CT32 7 %, CT24 1 %, CT16
  rarely; bilinear (MMAG/MMIN linear), no mipmaps (MXL 0), STQ perspective for 3D, UV for
  sprites; TFX MODULATE with TCC on; fog on 88-92 % of 3D primitives.
- Frame: CT32; FBMSK (partial channel writes) on 1-2 % (post effects).
- Local memory traffic: 130-230 host->local transfers per field (1.5-3 MB: texture and
  CLUT uploads every frame); one local->host read every other field (the lens flare depth
  probe, `LensFlareDraw_2ed830` -> `DepthProbeGetSlot_13fc80`, an 8x8 Z read); 1-3
  local->local copies per field. Screen effects render to texture and sample it (CBlur,
  DOF/focus, glare, bloom: see the render-API table); the census's render-to-texture
  counts are inflated (textures uploaded into pages drawn earlier in the range counted too;
  the upload tracking was fixed in `gs_census.c` but not re-run).

### The game's render API (where a native renderer would intercept)

`tools/perf3d/render_api.py` (text census of the decompiled sources; virtual calls through
vtables are not counted, so draw methods called only through vtables show 0 call sites).
Layers, top to bottom:

1. **Frame**: `MainLoop_1c2c10` -> `DrawListFrameBegin_1425d0` ... `GfxEndFrame_141c20`
   (kicks the frame's one big VIF1 DMA chain; also `MoviePlayModal_267c60`,
   `LoadingScreenThread_343510`). `GfxFlipBuffersMaybe`, `GsDbufPutEnv`.
2. **Draw list** (77 functions, 1,240 direct call sites): sorted buckets of DMA call tags.
   `DrawListAddNode_140a10` (models, via `ModelQueueSortedPackets_14f0d0`),
   `DrawListBeginPrim_141b00` / `EndPrim` (187 call sites in 110 files: immediate 2D/effect
   packets), `DrawListAddTexLoad_1418c0` (177 sites in 105 files: texture + CLUT uploads,
   built by `TexBuildUploadPkt_158610` / `GsBuildImageUploadPkt_1581b0`),
   `DrawListAddEnv_1421d0` (56 sites: GS environment changes), `DrawListAddVramCopy*`,
   `DrawListSortBuckets`, `DrawListEmitBucket`, `DrawListCommitTo_1489f0`; camera / light /
   view packets (`DrawListAddCameraMatrixPacket`, `DrawListAddLightPacket`,
   `DrawListAddViewPacket`, `DrawPktBuildCameraMatrix`), plane shadows
   (`DrawListBeginPlaneShadowPass` / `End...`).
3. **Models** (74 functions, 106 direct sites + vtables): load time
   `ModelBuildFromRes_150f60` -> `ModelBuildFrames_1506c0` -> `ModelBuildMeshes_152380` ->
   `ModelMeshBuild*FromResMaybe`, `MeshPktUnpackV2/V3/V4Indexed`, `MeshMaterialBuildPkt_14ac90`
   (static VIF packets with vertex data and GS state, referenced later by DMA call tags);
   per frame `ModelDraw_14f6d0` / `ModelDrawSorted_14f650` / `ModelObjExDraw_1ad7a0` ->
   `ModelPrepareDrawMaybe_14f760` (-> `ModelBuildSkinMtxPacketMaybe_150390`: bone
   matrices) -> `ModelEmitDrawPacketsMaybe_14ec20` (per mesh: call tags to the static
   packets + `DmaPktAddMscalCall_145b20`, the VU1 program per `ModelMeshGetVuVariantFlagsMaybe`
   and `VuMicrocodeTableInitMaybe_152830`'s table) -> `ModelQueueSortedPackets_14f0d0` ->
   `DrawListAddNode_140a10`. Shadows: `ModelDrawShadowCaster_14f5d0` ->
   `ModelEmitShadowCasterPacketsMaybe_14e780`. Effects: `EffModelDrawNodes_1a7b80`,
   `EffQuadDrawNodes_1a7890` (their own MSCAL calls); map: `MapAreaModelDrawBucketLit_1883c0`,
   `MapSkyDrawLayers_17e760`; characters `Character2Draw_1ae920` (vtable).
   **The natural interception point** is `ModelEmitDrawPacketsMaybe_14ec20` (plus
   `ModelPrepareDrawMaybe_14f760` for skinning and the effect/shadow emitters): at that point
   the mesh, its material, the bone matrices, camera and light are known as data, and the
   only VU1 program that matters (above) is what turns them into GS primitives.
4. **2D / immediate GS packets** (93 functions, 4,374 direct call sites): the `GsPkt*`
   builder (`GsPktOpenPrim_13f730` 286 sites in 134 files, `GsPktSetXYZ_13ef10` 151, ...),
   `GsDraw*` sprites, `Draw*` rect/quad helpers, `GfxBlitTexRect*`: UI, HUD, menus, fades,
   post passes. A native backend would implement this small register-level API (PRIM,
   RGBAQ, ST/UV, XYZ, TEX0/1, ALPHA, TEST, FRAME/ZBUF, SCISSOR) directly.
5. **Screen effects / render to texture** (24 functions): `CBlur*`, `GameSceneCBlur*`,
   `DofFilterDrawMaybe`, `FocusFilterDrawMaybe_17c000`, `GlareFilterDrawMaybe_17a0d0`,
   `BloomExtractBlurMaybe`, `ShadowMapBlur_145b60`, work-texture registration
   (`*WorkTexRegister`).
6. **Read-backs**: `DepthProbeGetSlot_13fc80` (lens flare Z probe, every frame),
   `GsDownloadImage_140f20` (screen captures for menus / fades).

Full table: `python tools/perf3d/render_api.py` (8 s; `out/perf3d/render_api2.md` holds
one run).

## Transition stutter (2026-10-18 late, stutter lane)

User play-test 2026-10-18 (BRINGUP.md): hitches when things load, at battle start and at
battle end (`RG_GPU=hw`, native defaults, gamepad). Lane build `build/stutter-i686`
(Release, RG_NATIVE_ONLY, -O2 game, VU0 native), scratch `out/stutter/`. The PC was shared
with two other agents' builds and `rg-game` runs throughout, so every number below is from
interleaved A/B runs, and single fields of 0.6-25 s that sit outside the emulation step are
log-file writes blocking on the busy disk (see "Measurement artifacts").

### Tools (new, reusable)

| tool | what |
| --- | --- |
| `RG_FIELD_STATS=file` (runtime, `src/runtime/runtime.c` `fstats_field`, `src/runtime/fstats_sys.c`) | one TSV row per field of counter deltas: `fstats_ms` (the sampling's own cost), process / main-thread CPU (cycle counts: `QueryProcessCycleTime` / `QueryThreadCycleTime`; `GetThreadTimes` moves in 15.6 ms ticks), page faults, private KB, file reads (count / KB / host ms, `rg_fs`), sound banks / sequences (native engine), GS worker payload, host->local pixels, lazy-transfer bytes materialized, CLUT loads, GPU batches / target creates / loads / write-backs / upload KB / download KB / read-backs / read-back wait ms / flush ms / texture decodes, native-renderer draws / texture decodes / mesh uploads / lazy decodes, presents and **new images** (presents after a field in which the game handed the GS a frame), and every thread's CPU (`start:tid:ms`, `m` = the field loop's thread; thread list refreshed every 300 fields by a system snapshot, ~35 ms, reported in `fstats_ms`). 4 MB buffer, flushed every 4,096 fields. Off by default; nothing feeds back into a run (run hashes identical with and without) |
| `tools/perf3d/stutter.py run DIR --exe EXE (--state F \| --boot-save NAME) --fields N [--env K=V] [--headless]` | windowed run (`RG_GPU=hw`, shipping defaults) with `RG_FIELD_TIMES`, `RG_FIELD_STATS`, `RG_STATUS_EVERY=1`, then `report.md` |
| `stutter.py report DIR [--win NAME:A-B] [--thr MS] [--top N]` | per window (default: every game-mode / overlay change from the STATUS lines, -30..+120 fields, plus the whole run): present intervals, **new-image intervals** (what the player sees), excess ms per column of the frames over the threshold, mean counters per frame, the worst frames with every millisecond attributed (step / gs_wait in step / sync / present / pace / out / host half / unattributed) and their counters and per-thread CPU |
| `stutter.py compare DIR_A DIR_B` | the image-interval summaries side by side |
| `tools/perf3d/stutter_states.sh EXE OUT [FIELDS]` | copies the exe and writes route states (default 22,600 = before the first battle, 26,700 = before it is won) headless in ~3 min |
| `tools/perf3d/stutter_ab.sh STATES OUT ROUNDS "ENV_A" "ENV_B" ["bs be"]` | interleaved A/B on battle start (22,600-23,400) and battle end + results + Hooded Man scene + Salgin load (26,700-29,300); summary rows in `OUT/summary.md` |

### Causes, ranked (current tree, battle start and battle end windows)

1. **Pacing amplified every over-budget frame (fixed).** `display.pacing = host` skipped
   the present whenever ANY phase was owed after a phase. In the battle the host runs a
   2-phase game frame in ~30-40 ms (close to the 33.4 ms budget), so a frame a few ms over
   made the next present wait for up to k = 4 phases (`phases/present: 4:N`): ~60-70 ms
   without a new image, then a two-game-frame jump, and the game frame drawn in between was
   never shown. Unit model (rg-kernel-tests `pace`): a host 5 % over budget presented 142
   times in 10 s with the first design (batches of 4) against 556 now. In game (battle start,
   2 interleaved rounds): images shown 357 / 340 of ~400 game frames before, 396 / 395 now;
   image intervals > 50 ms 36 / 50 before, 0 / 4 now (table below).
2. **Steady battle cost of the emulated GS residue (renderer lane).** Per battle game frame
   (2 fields, current tree): GS worker CPU 14-18 ms + GPU read-back waits 5-15 ms
   (`download_ms`, 1-2 read-backs), the main thread waiting for the worker 10-25 ms inside
   the step (`gs_wait`); counters 1.8-4.6 M host->local pixels, 270-400 CLUT loads, 19-26
   render-target creates, 50-66 target write-backs, 1.8-4 MB uploads. That is about twice
   the field's per-frame work just before the battle, and it is what keeps battle frames at
   30-47 ms on this PC. In the user's exe of 18:36 (`out/play/exeT` = play-i686 + columns,
   profile `out/stutter/base/p1`) the same: 60-77 % of the main thread in
   `gs_async_drain`. Proposals in "Proposals for the renderer lane".
3. **First battle frame: native-renderer first use.** Field 22,865 (first battle frame): 19
   mesh uploads, 38 texture decodes, +5 MB private bytes, 2,188 page faults: a 47 ms image
   interval against 33 ms around it (~10-14 ms extra, once per battle start). Renderer lane
   (pre-warm meshes of the encounter on the load, or upload on the worker ahead of first use).
4. **Not causes (measured):** file I/O: at most one 208 KB read per frame in the windows,
   0.0-0.2 ms host time (`fs_ms`), the whole battle start ~0.6 MB (OS cache warm; cold cache
   would add a few ms); sound: 0 bank loads in the windows, audio host work 0.01-0.02 ms per
   field; D3D shader / state objects: all created at `gpu_create` (`gpu_d3d11.cpp`
   CreateVertexShader / CreatePixelShader / CreateBlendState / CreateRasterizerState at
   init), none on first use; overlay loads: none at these transitions (the battle runs in
   NORMAL, ovl 3 throughout: game modes 11 -> 7 -> 11 -> 6); the Salgin load (mode 11 -> 6 at
   28,957): image interval p99 42-49 ms, no frame over 50 ms caused by the load.

### Fix: catch-up only when it can win the time back (`src/native/threads/rg_pace.[ch]`)

`rg_pace_config.catchup` (default 2 phases = one 30 Hz logic tick; `RG_PACE_CATCHUP=1` = the
first design) and a moving average of a phase's host cost (`cost_ns`, phase start -> present
decision, samples clamped at 4 phases so a hitch is not taken for the host's speed): after a
phase the present is skipped only while at least `catchup` phases are owed AND a phase costs
under 90 % of one. A host a little behind presents every phase and catches up by not
sleeping; a host that cannot catch up presents every phase and the debt beyond k is dropped
as before (the game slows down evenly instead of in batches of k); after a hitch on a fast
host the catch-up burst stays (unit: 3 phases after a 1 s hitch). Game state: pacing never
reaches it (run hashes of windowed runs identical between `RG_PACE_CATCHUP=1` and 2, and to
the headless fixture runs). `rg_pace:` shutdown line (`RG_PACE_LOG`) gained `catchup`,
`slow_presents` (presents made although owed, because catching up was impossible) and
`phase_cost`.

Before / after (exe `out/stutter/s6`, interleaved, windowed, `RG_GPU=hw`, internal
resolution 3x default, shared PC; A = `RG_PACE_CATCHUP=1` = before, B = default = after;
image intervals in ms, whole run):

| run | new images | median | p99 | max | > 40 ms | > 50 ms |
| --- | --- | --- | --- | --- | --- | --- |
| battle start 22,600-23,400, before, round 1 / 2 | 357 / 340 | 33.3 / 34.0 | 100.5 / 187.9 | 161.5 / 1032 | 50 / 61 | 36 / 50 |
| battle start, after, round 1 / 2 | 396 / 395 | 33.4 / 33.1 | 40.1 / 50.5 | 47.9 / 219.7 | 4 / 14 | 0 / 4 |
| battle end + results + scene + Salgin load 26,700-29,300, before | 1,265 / 1,280 | 33.4 / 33.4 | 60.2 / 49.0 | 6,457 / 272 | 49 / 44 | 27 / 12 |
| battle end ..., after | 1,283 / 1,291 | 33.2 / 33.2 | 119.0 / 42.1 | 25,152 / 1,689 | 48 / 27 | 19 / 5 |

Recheck on the tree after the renderer's 16-bit-UV fix and the mapreg re-ingest (exe
`out/stutter/s7`, one interleaved round, `out/stutter/ab5`):

| run | new images | median | p99 | max | > 40 ms | > 50 ms |
| --- | --- | --- | --- | --- | --- | --- |
| battle start, before / after | 390 / 397 | 33.3 / 33.2 | 67.2 / 36.1 | 89.2 / 46.8 | 31 / 1 | 5 / 0 |
| battle end ... Salgin load, before / after | 1,216 / 1,294 | 34.2 / 33.2 | 73.5 / 38.4 | 1,141 / 383 | 372 / 7 | 76 / 4 |

Verification: rg-kernel-tests `pace` PASS (+ new over-budget cases; `pace_control` fails as
designed), ctest `kernel|runtime` 47/47; fixture set of the lane exe (`regen.py --check 300`)
`verify.py` 8/8; `bootcheck.py --all` 29/29 (ch08b_juraika failed once at 0 s with exit 1
before any field, i.e. the process did not start a run; PASS on rerun); route run hashes at
22,600 / 26,700 identical for every lane exe (fstats / pacing do not reach game state).

The maxima of 0.2-25 s (and the 119 ms p99 of after-round 1) are the log-write stalls below,
in both configurations. Battle-start window alone (22,833-22,983, after, round 1): 75
images, p99 47.9 ms, none over 50 ms; the 40-48 ms ones are steady battle frames (cause 2)
and the first battle frame (cause 3).

### Measurement artifacts (read before trusting a max)

Fields of 0.6-25 s whose time is in `out` (between fields, where rg-game prints the
`RG_STATUS_EVERY` line to stderr) or unattributed (where the stats / times rows are
written): main-thread CPU ~0 in them, so the thread was blocked, and they coincide with the
other agents' links. They are writes of the measurement logs blocking on the shared disk,
not game work (the shipping game writes nothing per field). `RG_FIELD_STATS` now buffers
4 MB; `RG_FIELD_TIMES` still flushes every 100 fields. The play lane's "under load" 0.7-1.6 s
fields (BRINGUP.md) fit the same explanation.

### Proposals for the renderer lane (src/gpu, src/ps2/gs: not edited here)

Per battle game frame the counters above point at, in order of milliseconds:
1. the GS model's host->local transfers (1.8-4.6 M pixels per frame through
   `xfer_image_body` / `gs_pixel_addr`; the 18:36 profile: largest worker item) and
   materialized lazy transfers (0.3-1.4 MB per frame): a block-swizzle fast path or keeping
   these on the GPU;
2. 1-2 GPU read-backs per frame with 5-15 ms worker waits (`download_ms`; the two CLUT loads
   from GPU-drawn pages already identified in NATIVE-RENDER.md "Performance"): the GPU-side
   CLUT load;
3. 19-26 `rt_creates` and 50-66 write-backs per frame even with the target pool: check
   whether pooled reuse is counted as a create; if not, the pool misses in the battle;
4. first battle frame: 19 mesh uploads + 38 texture decodes in one frame: pre-upload on
   the worker when the encounter's models are registered, or spread over the transition.

Renderer lane answer (2026-10-19, NATIVE-RENDER.md checkpoint 8): (2) GPU-side CLUT loads exist
but are limited to pages the CPU has not touched; the battle's palettes are CPU uploads into a
target's page, so their read-backs stay until that case is made exact ("GPU-side CLUT loads").
(3) `rt_creates` counts logical targets: on `boot:save2_battle2` 84,654 of 84,671 came from the
backend pool (`rt_pool_hits` in the exit line), i.e. 17 D3D allocations: no pool misses. (4) not
done (one frame per battle start). Also: the native texture cache missed 88 % on textures it had
already decoded (512 entries); now 4,096 entries with a hash lookup, -86 % decodes on save2.

### Resume

States of the current exe: `tools/perf3d/stutter_states.sh build/stutter-i686/rg-game.exe
out/stutter/sN`; A/B: `tools/perf3d/stutter_ab.sh out/stutter/sN out/stutter/abN 2
"RG_PACE_CATCHUP=1" "-"`; single report: `python tools/perf3d/stutter.py report DIR`.
Open: a quiet-PC rerun of the table (absolute numbers); a second encounter
(`--boot-save save2_battle2`) and a later-chapter card; `RG_FIELD_TIMES` buffering like the
stats file.

## Rerunning the measurements (`tools/perf3d/`)

| tool | what |
| --- | --- |
| `perf3d.sh OUT EXE FIELDS RANGES [h\|w\|wu]` | one golden-input run: `times.tsv` (per field wall / step / read / present / GS-worker wait), census TSVs per range (`RG_PERF_CENSUS`), sampling profile (`rgprof`), and `report.md` (per range: time columns, subsystem breakdown, top functions, census). `PROF=0`, `CENSUS=0`, `ASYNC=1`, `REPORT_ONLY=1` |
| `census.py DIR` | VU1 microprogram table (matched to retail MPG packets) and GS feature tables from the census TSVs |
| `breakdown.py PROF TIMES MAP EXE --fields a-b` | the profile's cost by subsystem and top functions (from `out/gpuperf2/prof/anal.py`) |
| `fieldtimes.py TIMES RANGE...` | mean of the `RG_FIELD_TIMES` columns per range |
| `gpu_replay.sh TESTS_EXE N REC...` | GPU ms per field of GS recordings replayed through the renderer (`ANISO`, `SC`) |
| `render_api.py` | the game's render API census above |
| `o2wrap.py` | compiler launcher: game sources at `$RG_GAME_OPT` (-O2) in a measurement tree |
| `rgprof.c` | the sampling profiler (built by `perf3d.sh` on first use) |
| `stutter.py`, `stutter_states.sh`, `stutter_ab.sh` | transition stutter: per-field counters (`RG_FIELD_STATS`), new-image intervals, A/B (section "Transition stutter") |

Instrumentation they use, all off by default: `RG_PERF_CENSUS=DIR:a-b,...` (runtime ->
`gs_features_begin/dump`, `vif_census_begin/dump`), `RG_GS_CENSUS=N` (GS event census),
`RG_FIELD_TIMES` (now 6 columns), `RG_GPU_PROFILE`, `RG_GPU_ANISO` (replays).

## Resume checkpoint (2026-10-17, work paused by the user)

State: all fixes 1-8 are in the source tree (uncommitted, as instructed) and pass the tests
listed under "Exactness". `build/perf3d-i686` builds `all` and `rg-game` from the current
sources (one transient failure of another lane's override, `CdDatArchiveOpen_183110.cpp`,
cleared on the next build). Scratch data in `out/perf3d/` (runs, recordings `rec/*.rggs`,
`verify/`, binaries `z*_bin`, `base_bin`). Changed files: `src/gpu/` (gpu.h,
gpu_internal.h, gpu_core.cpp, gpu_d3d11.cpp, CMakeLists.txt, shaders/gs_draw.hlsl,
shaders/gs_util.hlsl), `src/ps2/gs/` (gs.h, gs_internal.h, gs_core.c, gs_mem.c,
gs_display.c, gs_raster.c, gs_rec.c, CMakeLists.txt, new gs_async.c, gs_census.c),
`src/ps2/vu/` (vu_block.c, CMakeLists.txt), `src/ps2/vif/` (vif.c, vif.h,
CMakeLists.txt), `src/ps2/dmac/CMakeLists.txt`, `src/host/` (host.h, host_sdl.c),
`src/runtime/runtime.c`, `tests/gpu/` (gpu_scenes.c, gpu_replay.c, gpu_tests.c), new
`tools/perf3d/`, this document.

Not finished:
1. **EE game code at -O2** (step 3 of the re-scope). Configure a measurement tree and build:
   `powershell -File out/perf3d/b_o2.ps1 -Configure -Target rg-game` (= `out/perf3d/b.ps1`
   with `BuildDir build/perf3d-o2` and `-DCMAKE_C_COMPILER_LAUNCHER=python;tools/perf3d/o2wrap.py`
   for C and C++); it was stopped at 10,300 / 25,728. Then compare with the -O1 build:
   `out/perf3d/vrun.sh` / `vrun16.sh` + `vcmp.sh` (screenshots, STATUS lines, GS stream),
   `tools/trace` timing alignment, and `perf3d.sh` for the `game` bucket.
2. **Census re-run** with the corrected texture-field mask and render-to-texture tracking
   (fixed in `gs_census.c`, built into `build/perf3d-i686/rg-game.exe` 18:48, not run):
   `PROF=0 ASYNC=1 tools/perf3d/perf3d.sh out/perf3d/runs/c14 build/perf3d-i686/rg-game.exe 23400 7400-7999,14000-14999,20000-20599,23000-23399 h`,
   then copy the GS tables into "GS features used".
3. Battle VU1 workload vs retail (4.5x the pairs per frame): hand to the battle lane.
4. For a faster emulated path in the meantime (if ever needed again): anisotropic 16x
   costs as much GPU as all other 3D drawing at 3x; defaults of 4x (or off) would roughly
   halve the GPU time in the heavy scenes (settings lane decision).
