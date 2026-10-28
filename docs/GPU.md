# GPU GS renderer (`src/gpu`)

PLAN.md D3: a hardware-accelerated renderer for the Graphics Synthesizer. It emulates the
GS, not the game: it consumes the same GIF stream as the software model (`src/ps2/gs`,
docs/GS.md) and must produce the same local memory and the same display. Direct3D 11
first (feature level 11_0, hardware or WARP), behind a small backend interface.

All of it is original CC0 code. No PCSX2/GSdx or other GPL code was used or paraphrased
(D7). The design follows the GS User's Manual semantics and the project's own software
reference, rule for rule.

```
cmake --build <builddir> --target rg-gpu-tests rg-host-demo
ctest --test-dir <builddir> -L '^gpu$'        # 92 tests (incl. 12 gpu.gfx.*), WARP, headless
set RG_GPU_HW=1 & ctest ... -L gpu            # same tests on the hardware GPU
rg-host-demo --gpu [--warp] [--gpu-scale N]   # demo through the GPU renderer
```

Windows only (the backend is D3D11). `src/gpu/CMakeLists.txt` returns quietly when not on
Windows or when the SDK's `fxc.exe` is not found, and `tests/gpu` then registers nothing.

## Architecture

```
 GIF / VIF / VU1 ──► gs_state (CPU: GIF, registers, transfers, CLUT, vertex queue)
                         │ hooks.draw: one resolved primitive + gs->reg
                         │ hooks.mem : READ / WRITE_BEGIN / WRITE_END of a vram rectangle
                         ▼
               gpu_core.cpp  (API-agnostic)
                 state key → derive (passes, masks, blend path, constants)
                 primitive expansion → batch (split on state change / overlap)
                 render-target table + page coherence
                         │ GpuBackend (gpu_internal.h)
                         ▼
               nr_d3d11.cpp: mirror buffer, targets, uber-shaders, display, read-back
```

| File | What |
| --- | --- |
| `src/gpu/gpu.h` | Public C API: create/destroy, attach/detach to a `gs_state`, flush, sync, `gpu_mem_written`, `gpu_read_display`, stats, target list, `gpu_read_target` (a target at the internal resolution, tests) |
| `src/gpu/gpu_internal.h` | `GpuBackend` interface, vertex format, constant layout |
| `src/gpu/gpu_core.cpp` | Hooks, register decode, primitive expansion, batching, coherence |
| `src/native/render/nr_d3d11.cpp` | Direct3D 11 backend (was `src/gpu/gpu_d3d11.cpp` until 2026-10-24: rg_gpu compiles it with `RG_GPU_EXACT=1`, the native-only device without the GS-exact batch path; docs/NATIVE-RENDER.md "Checkpoint 10") |
| `src/gpu/shaders/gs_common.hlsli` | Local-memory swizzles (port of `gs_mem.c`), stored-colour conversion |
| `src/gpu/shaders/gs_draw.hlsl` | `VS_main`, `PS_main`: the whole GS pixel pipeline |
| `src/gpu/shaders/gs_util.hlsl` | Target load/write-back passes, depth copy, PCRTC display |
| `src/gpu/shaders/gs_post.hlsl` | Output post chain: resample, FXAA-style, sharpen, gamma/scanlines/CRT ("Graphics settings") |
| `src/gpu/gpu_gfx.c` | `graphics.*` settings → renderer parameters (`gpu_gfx`) |

Shaders are compiled at build time by the Windows SDK `fxc` (`/O3`, SM 5.0) into byte-array
headers in the build tree; nothing is compiled at run time and `d3dcompiler_47.dll` is not
needed.

### Hooks (`src/ps2/gs`)

`gs.h` gained `gs_hooks hooks` at the end of `gs_state` (all NULL by default; the software
path behaves exactly as before, `ctest -L '^gs$'` 41/41):

| Hook | Called from | Meaning |
| --- | --- | --- |
| `draw(user, gs, v, nv, type)` | `gs_draw_kick`, before the SW rasterizer | One primitive, strips/fans already split; register state in `gs->reg` |
| `mem(user, gs, GS_MEM_READ, r)` | local→host and local→local source (`gs_xfer_start`), CLUT load (`gs_tex0_written`) | Write back anything newer before returning |
| `mem(..., GS_MEM_WRITE_BEGIN, r)` | host→local start, local→local destination | Write back what overlaps, then stop trusting copies of `r` |
| `mem(..., GS_MEM_WRITE_END, r)` | last pixel of a host→local transfer, end of a local→local copy, or an abandoned transfer (new TRXDIR / reset) | The write is complete |

`r` is a buffer rectangle (`bp`, `bw`, `psm`, `x`, `y`, `w`, `h`), so a renderer can work out
the exact pages. Writes that bypass the core (`gs_write_pixel`, poking `gs->vram`) must be
announced with `gpu_mem_written`. Reads that bypass it (`gs_read_pixel`, `gs_read_display`,
dumps) must call `gpu_sync` first.

`gpu_attach` sets `gs->sw_raster = 0`; the core keeps doing GIF parsing, registers,
transfers and CLUT loads.

### Local memory: three levels

1. **`gs->vram` (CPU)** is the authoritative 4 MB.
2. **The mirror**: a 4 MB raw buffer on the GPU (SRV for sampling, UAV for write-back). All
   texturing reads it directly with the real swizzles (`gs_common.hlsli`, a 1:1 port of
   `gs_mem.c`'s bit formulas). Every PSM, CLUT, TEXA, mip level and wrap mode works the same
   way, so there is **no texture cache to key or invalidate**: TBP/TBW/PSM/CLUT changes cost
   nothing. The CLUT itself is the core's 512-cell buffer, uploaded to a constant buffer
   when `stats.clut_loads` changes.
3. **Render targets**, keyed by (FBP, FBW, PSM) for colour and (ZBP, FBW, ZPSM) for depth,
   `FBW*64` wide and as many rows as draws have touched (whole pages), optionally at an
   integer upscale factor. Colour is `R8G8B8A8_UNORM` holding the RGBA8 the stored value
   decodes to (CT16 values are kept quantised, CT24 alpha is unused). Depth is
   `D32_FLOAT` holding `z / 2^32`.

Coherence is tracked per 8 KB page with two bitsets (`cpu_newer`: the mirror must be
refreshed from `gs->vram`; `gpu_newer`: `gs->vram` must be refreshed from the mirror) plus a
dirty rectangle per target (newer than the mirror).

### Coherence rules

| Event | What happens |
| --- | --- |
| Draw to target T | Other targets overlapping T's pages are written back and dropped. T is created/grown by loading the rows from the mirror (after uploading `cpu_newer` pages). T's dirty rectangle grows by the batch's bounding box. |
| Textured draw, texture = a live target | **Sampled directly** from the target at the internal resolution, no write-back (see "Direct sampling"). |
| Other textured draw | Every target whose dirty pages overlap the batch's **read set** (see "Render targets as textures") is **written back on the GPU** (compute shader, target → mirror). `cpu_newer` pages of the read set are uploaded. Sampling from a target, including the one being drawn, therefore needs no CPU round trip. |
| Textured primitive sampling memory drawn earlier in its own batch | The batch is flushed first, and the primitive starts a new one (render-target feedback). |
| Core reads r (`GS_MEM_READ`) | Flush the batch, write back overlapping targets, download `gpu_newer` pages of r into `gs->vram`. This is `sceGsExecStoreImage`, local→local copies and CLUT loads from drawn memory. |
| Core writes r (`WRITE_BEGIN`) | As a read (partial writes merge with current data), then mark overlapping targets stale and r's pages `cpu_newer`. |
| `WRITE_END` | Mark r's pages `cpu_newer` again and overlapping targets stale (a draw may have reloaded them mid-transfer). A stale target reloads from the mirror on its next use. |
| FRAME and ZBUF on the same pages | The software rasterizer draws the primitive (see below); its pages count as a CPU write. |
| Display | A circuit whose DISPFB matches a live target reads the target (at the upscaled resolution). Otherwise overlapping targets are written back, pages uploaded, and the circuit reads the mirror. |
| `gpu_sync` | Flush, write back every target, download every `gpu_newer` page. |

Write-back details: 16-bit formats share 32-bit words, so the compute shader uses
`InterlockedAnd/Or` on its half; 24-bit formats keep the high byte. Depth write-back keeps
the stored value whenever it converts to the same float the target holds, so Z32 values
above 2^24 that were loaded but not drawn survive bit-exactly.

### Render targets as textures (feedback)

The game samples its own render targets: bloom, blur and depth-of-field passes texture
from the frame buffer or the Z buffer, CLUT tricks read a CT32 buffer as T8/T4/T8H, and
`GfxEndFrame_141c20` reads four 8x8 rectangles of the Z24 buffer back as PSMZ32
(`sceGsExecStoreImage`). Textures are always read from the mirror with the real swizzles,
so **any format reinterpretation** (CT32 as T8/T4/T8H/T4HL/T4HH/CT16/Z, Z24 as CT32/T8,
Z16 as CT16/T4, ...) is the same code as a plain texture. What has to be right is *which
version of memory* the sampler sees:

* **Read set per primitive.** `prim_read_pages` bounds the texels a primitive can sample:
  the UV (or, with Q of one sign, S/Q and T/Q) extremes of its vertices, two texels of
  margin for float error and the bilinear taps, then the wrap mode (REPEAT only when
  nothing wraps, CLAMP, REGION_CLAMP; REGION_REPEAT and mipmapped states use the whole
  texture page set). The batch's read set is the union. Only targets dirty in it are
  written back at flush, so a declared 1024x1024 texture of which a sprite samples 64x32
  no longer writes back unrelated targets.
* **Write set per primitive** (only for states whose texture pages can alias the frame
  buffer, or the Z buffer when Z is written): the pages of the primitive's box in FRAME
  and, when ZMSK=0, in ZBUF.
* **Ordering.** The GS draws primitives in order, so a primitive must see what earlier
  primitives drew. A batch samples the mirror as it was at flush, so a primitive whose
  read set overlaps the write set of the pending batch flushes it and starts a new batch.
  That flush writes the target back, and the primitive samples the new data. Counted in
  `gpu_stats.feedback_splits`. A chain of copies (block k-1 to block k), an in-place pass
  repeated (each pass reads what the previous one wrote), and a sprite reading Z that
  another sprite of the same state just wrote all match the reference exactly.
* **Within one primitive** texture reads see memory as it was when the primitive started,
  in both renderers (checkpoint 4): the GPU samples the mirror or a target as of the
  batch's flush (with the feedback split above, that is the primitive's start), and the
  reference samples a copy of the texture's pages whenever the primitive can write any of
  them (`gs_raster.c` `tex_snapshot`). Before checkpoint 4 the reference read memory as it
  wrote it, in raster order, so a primitive reading memory it had already overwritten
  (the game's in-place strip blur reading one pixel behind; a Z32 buffer written over the
  texture's page, which arranges the page's blocks differently) differed from the GPU.
  The GS reads texels through its texture buffer, which drawing does not update (software
  flushes it with TEXFLUSH after drawing into a texture), so the snapshot is also the
  closer model of the hardware: the game's 32-pixel strips adding the buffer shifted by a
  pixel to itself are written for it (read in raster order they smear).
* **Readbacks** (`GS_MEM_READ`) flush the batch, write back the overlapping targets and
  download their pages, so an 8x8 PSMZ32 store-image of a Z24 target returns the 24
  drawn bits plus the untouched high byte, every frame.
* **Drawing into a buffer as another format** (clearing the Z buffer by drawing a colour
  sprite into its pages, a CT16 view of a CT32 target) drops the other target after
  writing it back. The next draw in the original format reloads it from the mirror.
* **Another view of the same memory** (2026-10-24, BRINGUP item 8). The battle renderer
  draws each character through its own page-offset FBP into one 512-wide buffer (bp 10752,
  10848, 10880 bw8, plus bw1 64x64 work targets inside it) and copies each part's box into
  the frame with a CT24 sprite. A target evicted by a view with the same kind and format
  and page-aligned bases (`rt_page_compatible`; any widths) is still written back, but its
  texture is kept until the new view is loaded, and the pages they share are then copied
  over at the internal resolution (`rt_copy_pages`, backend `rt_copy`; rt log line `C`).
  Through the 1x mirror alone, every view switch threw away the upscaled detail drawn so far.
* **Staleness per page.** A CPU write marks the targets overlapping it stale *in those
  pages* (`Rt.stale_pages`). A stale target reloads only those pages (`rt_load_stale_pages`,
  rt log `L`), its other pages keep their upscaled pixels, the page copy skips them, and
  direct sampling refuses a stale target only when the pages read are stale
  (`rt_current_in`). The game uploads textures into the top rows of the 512-wide character
  buffer between the two composite passes of each part, and the second pass then read the
  whole part from the mirror: the "low-res pauldron / gun / hip item" of item 8.
  `RG_GPU_RT_PAGECOPY=0` restores whole-target staleness, drop + reload (A/B control).

### Direct sampling

A texture that maps cleanly onto a live render target is read **from the target itself**
(`direct_source` in `gpu_core.cpp`), at the internal resolution, instead of from the
mirror: no write-back, no upload, and at scale > 1 the upscaled detail survives bloom,
blur, depth of field and the per-frame flip copy (GfxFlipBuffersMaybe_143650 copies the
512x448 draw buffer to the display buffer with one textured sprite every frame; through
the mirror that copy alone threw all upscaling away). Conditions, per batch:

* the target has the texture's TBP0 and TBW and is not stale in the pages read;
* the formats agree exactly: the same PSM (CT32, CT24, CT16, CT16S, Z24, Z16, Z16S), or
  a CT32 target read as CT24. Not Z32 (values above 2^24 do not survive `D32_FLOAT`; the
  mirror keeps loaded pixels bit-exact), not a CT24 target read as CT32 (the high byte
  lives only in memory), not CLUT formats (T8/T4/T8H/T4HL/T4HH views of CT32 or of Z),
  not a Z buffer read as colour or a colour buffer read as Z (different block
  arrangement), not CT16 read as CT16S. All of those keep using the mirror with the real
  swizzles;
* only mip level 0 can be sampled (`tex_lvl0`);
* every texel the batch can address lies inside the rows the target owns (for a source
  other than the target drawn into, up to 2 texels of bilinear margin past its last row or
  column count as inside: the shader clamps to the target's edge, DIRECT bits 16-28, as
  the native path does; the character composites at the bottom of the frame and the
  192x192 blur passes read one or two texels past their source). Per primitive
  the texel rectangle is the axis_range bounds (or the wrap mode's reachable rectangle),
  and for UV sprites the **exact** texels of the reference's DDA over the covered pixels
  (`sprite_texel_rect`; a full-frame copy reads exactly the frame, not the 2 texels of
  margin that would reach into the display buffer below it);
* no other live target shares the pages actually read;
* it is not the depth buffer the same batch tests or writes (a bound DSV cannot be
  sampled; the mirror path is used).

The shader (`sample_direct`, `fetch_direct`) recovers the stored value from the target
exactly (`to_stored` of the RGBA8; `z * 2^32` for Z24/Z16) and decodes it per the texture
PSM with TEXA/AEM as `tex_fetch` does, so **at scale 1 direct sampling is bit-identical
to the mirror path** (every exact scene uses it: `scene.rtt_*`, `scene.coherence`). The
wrap modes work in upscaled texels (`wrap_hr`: the same native ranges, the sub-sample
kept). A batch that samples the target it draws into (in-place passes) samples a copy of
the texel rectangle taken before the draw (the blend snapshot texture, `tex_copies`),
which is what the mirror path saw too. Feedback splitting is unchanged.

At scale > 1 the texture coordinate follows the sub-sample: sprites evaluate the
reference's per-pixel UV (the 16.16 DDA, or the STQ formula) at the sub-sample's own
position `px - 0.5 + (k + 0.5)/scale`; interpolated primitives already do. Bilinear then
filters the upscaled texels (4-bit weights as the GS). Point sampling of a sprite keeps
**the native texel the reference picks** and takes the sub-sample of it at the same
offset (`g_anchor`), so a 1:1 copy on texel corners or on texel centres reproduces the
source bit for bit at the internal resolution, and a point-sampled pass never reads a
texel the reference does not.

Stats: `direct_samples` (batches), `writebacks_avoided` (write-backs the mirror path
would have done for them), `tex_copies`. `gpu_config.rtt_native = 1` turns direct
sampling off (every target read through the mirror, the previous behaviour).

### FRAME and ZBUF on the same pages

When Z is tested or written and the FRAME and ZBUF pages overlap inside the scissor
(`Derived::alias`), the reference interleaves every pixel's colour and Z write in one
memory (CT32 and Z24 arrange a page's blocks differently, so one pixel's Z lands in
another pixel's colour). Two GPU targets cannot do that, so such primitives are drawn by
the **software rasterizer**: the hook flushes, writes back and downloads everything the
primitive touches (FRAME and ZBUF pages of its box, the texture pages), marks the
targets there stale and the pages `cpu_newer`, and sets `gs->sw_raster = 1` for that one
kick (`gs_draw_kick` reads it after the hook; the next hook or API call turns it off).
Exact by construction, slow (a CPU round trip per primitive), and not seen in the game's
census. Counted in `gpu_stats.cpu_prims`.

### Drawing

**Batching.** A key of every register that shapes a draw (attribute bits, FRAME, ZBUF,
TEST, ALPHA, FBA, PABE, COLCLAMP, DTHE, DIMX, FOGCOL, SCANMSK, SCISSOR, TEX0/1, CLAMP,
MIPTBP, TEXA, CLUT generation by contents) is compared per primitive; a change flushes. A
batch whose pixels read the destination is drawn through the target's rasterizer-ordered
view where the device has one ("Performance"), so overlapping primitives share it.
Otherwise (no ROVs, or a depth test that can fail) it is *serial*: a primitive whose
bounding box overlaps one already in the batch flushes first, so each batch is a set of
non-overlapping primitives.

**Primitive expansion** (CPU, `on_draw`), in window pixels (XYOFFSET applied):

| GS primitive | Expansion |
| --- | --- |
| Sprite | Quad. Colour, Z, fog, Q from the 2nd vertex. UV (FST=1) is the reference's fixed-point DDA (GS.md rule 3): the CPU computes, with `gs_sprite_uv_step` and int64, the DDA value at the first covered pixel and the 16.16 step, split into 16-bit halves (all below 2^24, exact as float vertex attributes); the shader evaluates `Shi + Thi*k + ((Slo + Tlo*k) >> 16)` with `k = px - base` in 32-bit integers, bit-identical to `gs_sprite_uv_at`. S/T (FST=0) are recomputed per pixel with the reference's formula `s0 + (s1-s0)*(16*px - x0)/dx`. Neither is interpolated: 2D texel addressing is exact. |
| Triangle / strip / fan | One triangle each. Flat shading copies the provoking (3rd) vertex's colour and fog. Every attribute is evaluated per pixel exactly as the reference does (see "Exact triangles"); on a device without double-precision shader ops, interpolated by the rasterizer, with Z from a plane equation (gradients in double on the CPU) unless constant. |
| Line / strip | A band 2 px wide along the minor axis; the pixel shader keeps exactly the reference DDA's pixel `q = floor((b0 + 8 + floor(db*(16p - a0)/da)) / 16)` using integer math. D3D's fill rule cannot express the reference's `(b-0.5, b+0.5]` interval; the major-axis extent `[ceil(lo), ceil(hi))` is the band's own edges. |
| Point | A 1x1 quad on `(ceil(x/16), ceil(y/16))`. |

Coordinates map to NDC through a power-of-two viewport, so `(x + 0.5) * 2/vp - 1` is exact in
float and every 12.4 vertex lands exactly on the rasterizer's subpixel grid. Triangle
coverage then follows the same top-left rule as the reference.

### Exact triangles

Triangles and lines are **bit-exact** with the reference (`gs_raster.c` draw_triangle /
draw_line), not just within a tolerance. For each triangle the core writes a `GpuTri`
record (128 bytes, a structured buffer at t4, indexed by the vertex's `spr_u0`): the
12.4 window coordinates in the reference's vertex order (v1 and v2 swapped when the area
is negative), its `inv = 1.0 / area` as a double, and every vertex attribute (RGBA and
fog with flat shading already applied, Z, S/T/Q, U/V). The pixel shader variant
`PS_main_x` (`/DGS_EXACT=1`) then repeats the reference per pixel in double precision:
the edge functions of the pixel centre (exact: products of 17-bit integers), `w1 = e1 *
inv`, `w2 = e2 * inv`, every attribute `a + (b-a)*w1 + (c-a)*w2`, colour and fog truncated
and clamped, Z truncated to uint32, U/V divided by 16 or S/Q and T/Q scaled by the texture
size, and the texel index and the 4-bit bilinear weight taken from those doubles
(`exact_axis`). Lines use `t = (16p - a0) / da` along the major axis. The LOD (mipmap and
MMAG/MMIN choice) is still computed in float from Q.

What it took to make the GPU's doubles agree with the reference's SSE2 doubles:

* **No fused multiply-add.** The NVIDIA driver contracts `dmul` + `dadd` into one fused
  operation even for `precise` DXBC. The reference rounds the product first, and the
  difference decides truncations: at (286,136) of `scene.frame640`, red is
  82.99999999999997 → 82 in the reference and 83.0 fused. Each product goes through
  `max(p, bound)`, with the bound read from the record (pad word 0) so no optimiser can
  fold it; no compiler fuses across a `max`.
* **No reliance on `dtoi` truncation.** WARP's `dtoi` rounds to nearest (39.99999999999997
  → 40 on the left edge of the same triangle). `floor_d`/`ufloor_d` correct the converted
  value with double comparisons, so they are right either way.
* **No `itod` of a converted value.** On WARP, `(double)t` of an `int` that came out of
  `dtoi` is wrong (`(double)(int)100.92 != 100.0`), so `floor_d` returned 101 for 100.92:
  Gouraud slivers one step off (the 22 `scene.formats` pixels once blamed on edge coverage,
  and 100 pixels of one thin triangle in `scene.offscreen`). `utod` of the same register is
  right, so every signed conversion goes through `i2d(t) = utod(t ^ 0x80000000) - 2^31`.
* **Coverage is the shader's.** Each exact triangle is drawn as its bounding box (clipped
  to the scissor; at scale > 1 one pixel wider, since a native pixel's sub-samples span
  `(p - 0.5, p + 0.5)`), and the shader keeps a pixel when `e > 0 || (e == 0 && top-left)`
  for its three exact edge functions (the reference's `e + bias >= 0`). Leaving coverage
  to the rasterizer was exact on the RTX 3080 but not on WARP, which clips a triangle
  reaching outside the viewport into a fan with float vertices: pixels on the fan's inner
  edges were drawn twice or not at all (2 pixels of the NORMAL story screen, see "Real
  game validation"; `control_cover`). The batch's overlap boxes and dirty rectangles were
  already the bounding box, so batching is unchanged.
* Needs `D3D11_FEATURE_DOUBLES` and the D3D11.1 extended doubles (`ddiv`, `dtoi`, `itod`;
  `ExtendedDoublesShaderInstructions`), which the RTX 3080 and WARP have. Without them the
  backend loads the float shader (`PS_main`) and `gpu_exact_triangles()` returns 0; the
  device name then ends in `[float triangles]`. `gpu_config.fault = 4` forces the float
  path (test control).

**Float fast path** (checkpoint 4). Double operations run at 1/64 rate on consumer
GPUs, so the shader evaluates in doubles only what float cannot decide. Coverage uses
32-bit integer edge functions when every coordinate difference over the drawn pixels is
below 2^15 (`TF_SMALL`; at scale s the sub-sample's edge function is `s*n + d`, n the
native pixel's, both exact), the double path otherwise (and for lines). An attribute
equal at the three vertices is taken as it is (the reference's `a + 0 + 0 = a`;
`TF_C*`). Colour, fog, Z below 2^24 and the texture coordinates are evaluated in float
with a bound E on their distance to the reference's double (each float operation
faithful; product and sum errors bounded separately, the sums' by min(ulp-relative,
smaller operand), so a constant attribute has E = 0; S/Q through
(E_S|Q| + |S|E_Q) / (|Q|(|Q| - E_Q)) plus the division's 2.5 ulp). A value is used when
every number within E truncates the same way (`decide`); otherwise that value alone is
evaluated in double: for integer attributes one double comparison against the integer
the float value leaves (`floor_choice`), for STQ the reference's whole sequence. Texels
and 4-bit weights are decided once per pixel for every level the sample reads
(`tex_levels`), so the double fallback exists once in the shader. Z of 2^24 and above,
and the LOD's `(float)Q`, stay double. `scene.exact_float` and its control check it.

At scale > 1 the same evaluation runs at each sub-sample's own GS position (so upscaled
triangles keep their sub-pixel detail); lines stay one native pixel wide.

Effect: `scene.blend_gouraud` 99.77% → 100%, `scene.tex_filter` 99.94% → 100%,
`scene.prims` 99.93% → 100%, `scene.frame640` 99.96% → 100%, `scene.formats` 92.2% →
100% on the RTX 3080 and on WARP (99.998% before the `itod` fix above). Every golden scene is now compared with tolerance 0. On
the game: the NORMAL overlay's star field (rotated, bilinear, T4 star layers drawn as
triangle strips) differed from the reference on 0.17% of the frame, max 10 per channel
(float UV interpolation flipping 1/16 bilinear weights); it is now identical.

**Pixel shader** (`PS_main`), in the reference's order: SCANMSK → texture (STQ divide or UV;
LOD from Q per TEX1 incl. LCM/L/K; MMAG/MMIN all six filters; manual 4-tap bilinear with the
4-bit fraction; trilinear blend; REPEAT/CLAMP/REGION_CLAMP/REGION_REPEAT per tap) → TFX ×
TCC → fog → alpha test → DATE/DATM → Z → blend `((A-B)*C >> 7) + D` with PABE → dither
(16-bit frames) → COLCLAMP clamp or wrap → FBA → FBMSK. All arithmetic is integer, as in
the reference.

**Fixed function vs shader.** Blending is done in the shader with the destination read
through the ordered view ("Performance") or from a snapshot (a `CopySubresourceRegion` of
the batch's bounding box before the draw), so it is exact (truncation, negative terms, wrap, `C = Ad`, FIX). Blend equations that reduce to
`Cs` (A=B, D=Cs; or Cs*128>>7) skip the destination; `A=B, D=Cd` becomes a channel write
mask (unless PABE). FBMSK whose bits cover whole channels (bytes for 32/24-bit, 5-bit
fields for 16-bit) is the hardware write mask; any other mask merges in the shader in the
stored format. Depth test and write are fixed function (`GREATER_EQUAL`, `GREATER`,
`ALWAYS`; NEVER drops the draw; ZTE=0 still writes Z unless ZMSK, as in the reference); the
shader outputs `SV_Depth` = `min(z, zmax) / 2^32`.

**Alpha-test FAIL modes** are two passes: pass 0 draws the pixels that pass (Z write per
ZMSK); pass 1 draws the failing pixels with FB_ONLY (no Z write), ZB_ONLY (no colour) or
RGB_ONLY (no alpha, no Z). KEEP discards in pass 0. Two-pass batches are serial (no
overlap) so primitive order is preserved.

### Display

`gpu_read_display` computes the circuits exactly as `gs_display.c` (PMODE, SMODE2
FRAME/FIELD, DISPFB, DISPLAY with MAGH/MAGV/DX/DY/DW/DH, BGCOLOR, MMOD/ALP/SLBG merge,
`(s*a + d*(255-a) + 127)/255`), composes on the GPU into a `(W*scale) x (H*scale)` texture,
and reads it back as RGBA8. FIELD mode selects every other line; FRAME mode shows every
line (the GS.md caveat 10 assumptions are inherited, not re-decided).

**Anti-flicker merge at the internal resolution.** The game displays with PMODE 0x7F23:
both circuits read the same 512x448 buffer, circuit 1 one row lower (DISPFB1.DBY = 1),
blended 50/50, i.e. every output row is the mean of two buffer rows. At scale > 1,
offsetting circuit 1 by a whole native row (`scale` internal rows) showed every upscaled
detail twice, `scale` rows apart: the NORMAL overlay's small stars became vertical pairs
of dots. When both circuits read the same target at the same position one row apart, the
lower one is now offset by one *internal* row (`GpuCircuit.af_hr`, `gpu_stats.display_af_hr`):
the same two-row filter at the internal resolution. Scale 1 and the mirror path are
unchanged; `gpu_config.native_af = 1` restores the native-row offset. Checked by
`gpu.scale2/scale4.af_upscaled`.

### Presentation (host integration)

Chosen: **read-back into the existing `rg_host_present`**. The GPU builds the display
frame, it is read back (1.2 ms at 640x448 on an RTX 3080, including the pipeline sync) and
handed to the unchanged SDL path, so scaling modes, screenshots (F12, `--screenshot`), the
frame hash and `--headless` all keep working, and **no `src/host` file changed**
(`rg-host-demo` only gained `--gpu`, behind `RG_HAVE_GPU`, which `src/gpu/CMakeLists.txt`
defines on the demo target).

Considered for later: zero-copy through SDL's own D3D11 device
(`SDL_PROP_RENDERER_D3D11_DEVICE_POINTER`, wrap the display texture with
`SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_POINTER`). SDL 3.4's D3D11 renderer sets its input
layout and VS constant buffer only once at creation, so sharing the immediate context needs
`SDL_FlushRenderer` before our work (it flushes and invalidates SDL's cached state) and a
restore of those two bindings after (or `ID3D11DeviceContext1::SwapDeviceContextState`). It
also needs a small host API (`rg_host_renderer` + present-texture). Worth it once upscaled
output makes the read-back cost matter.

### Upscaling

`gpu_config.scale` (1–8) renders targets at `scale` x. The mapping keeps GS geometry exact:
native pixel `p`'s sub-samples sit at GS coordinate `p - 0.5 + (k + 0.5)/scale`. Write-back
to local memory uses the sub-sample `(scale/2, scale/2)`, which equals the native result
for primitives with whole-pixel edges (`ctest gpu.scale2.*`). Lines and points stay one
*native* pixel wide (the line shader decides per native pixel). Validation of the GS
behaviour itself is done at scale 1.

**Sprites cover whole blocks** at scale > 1: their quad edges are placed on
`ceil(x) - 0.5`, so they cover exactly the `scale x scale` blocks of the pixels the
reference draws (`ceil(x0) <= p < ceil(x1)`). With the GS edges a full-screen sprite
covered half of its first column/row and spilled half a pixel past its last one (left
behind a strip of stale sub-samples at the top and left of every flip copy and
full-screen pass). Every attribute of a sprite is evaluated per pixel, so only coverage
moves; scale 1 keeps the GS edges.

Render targets sampled as textures stay upscaled (see "Direct sampling"); CPU reads
(`sceGsExecStoreImage`, the frame captures ScreenFadeBlockCaptureFrame_177ed0 and
MenuCaptureScreenTex_298810, GfxEndFrame's 8x8 Z readbacks) go through the write-back
and keep native semantics.

## Validation (`tests/gpu`, `ctest -L gpu`)

`rg-gpu-tests` drives a software-reference `gs_state` and a GPU-rendered `gs_state` with the
same packets and compares them. Comparison (`gpu_compare.c`): every live target region is
decoded per PSM and compared per channel (16-bit formats in 5-bit steps) or per Z value;
**every other byte of the 4 MB must be identical**; local→host FIFO data must be
identical; display frames are compared per channel.

* **golden.\*** — the `tests/gs` golden scenes themselves (28 of them: all `prim_*`,
  `blend_*`, `depth_matrix`, `alpha_matrix`, `dither_fog`, `tex_functions`, `clut_*`,
  `display_*`), recompiled with `-include gpu_tee.h`: every GS entry point is renamed to a
  tee that drives both states, and every read the test makes is a comparison checkpoint.
  The tests' own hand checks still run against the reference.
* **scene.\*** — `gpu_scenes.c`: every frame format × every Z format (CT32/24/16/16S ×
  Z32/24/16/16S); the 12 census blend presets × COLCLAMP × PABE plus all 81 A/B/C/D
  combinations and FBA in CT32/CT24/CT16 over a random destination (incl. random
  destination alpha); Gouraud blending; every texture format (CT32/24/16/16S, T8 and T4
  with CT32 and CT16 palettes, CSM1/CSM2, CSA, T8H/T4HL/T4HH, TEXA/AEM) × TFX × TCC and the
  four wrap modes; bilinear, all six MMIN filters with MIPTBP levels, STQ perspective with
  LOD from Q; the ATST × AFAIL matrix, DATE/DATM, partial and whole-channel FBMSK, ZMSK,
  SCANMSK, dithering, fog, context 2 + XYOFFSET, PRMODE; lines in all octants, strips,
  fans, points; coherence (read-back right after drawing, read-back as another PSM,
  local→local from a target into a texture, an upload over a target then blending on it,
  render-to-texture, a CLUT drawn by the GPU, a Z24 read-back); the PCRTC (demo setup,
  the game's 0x7F23 anti-flicker merge, MMOD=0 with background, FIELD mode both fields, a
  CT16 buffer no target covers); a 640x448 frame.
* **scene.rtt_\*** — render targets as textures, all exact (tol 0):
  * `rtt_formats`: a CT32 frame (re-dirtied on the GPU before every pass) sampled back
    as CT32, CT24, CT16, CT16S, T8 (CT32 and CT16 CLUTs, TBW 4 and 8), T4, T8H, T4HL,
    T4HH, Z32, Z24 and Z16; a bloom chain (bilinear 2x2 downsample to 1/2 and 1/4, added
    back onto the frame magnified x4); a CLUT drawn by the GPU, then the frame as T8
    through it.
  * `rtt_depth`, CT32+Z24 and CT16+Z16: depth-tested sprites and constant-Z triangles;
    three rounds of GfxEndFrame's four 8x8 PSMZ32 store-images plus readbacks as the Z
    format and as colour, with more drawing between them; part of the Z buffer cleared
    by drawing into it as a colour buffer, then depth-tested against; the Z buffer
    sampled as CT32, CT24, Z24, Z32, T8, T8H, T4HH (Z16: CT16, Z16, CT16S, T8, T4, CT32)
    with depth-tested drawing between the samples; a depth-of-field blend (Z blurred to
    half size as colour, then `(Cs-Cd)*As+Cd` onto the frame).
  * `rtt_feedback`: texture = the frame being drawn: a chain of seven copies in one
    batch; a vertical chain of bilinear band copies; an in-place pass repeated three
    times; an additive (blended) copy chain; sprites sampling, as CT32, the Z the
    previous sprite wrote; T8H palette lookup in place with FBMSK keeping alpha; the
    frame as T4 feeding itself; an upload into the sampled block between two primitives.
* **scene.rtt_upscaled** (exact at scale 1; **scale2/scale4** with tolerance): a bloom
  down/up chain (frame → 1/2 → 1/4 bilinear, then 1/4 → 1/2 and 1/2 → frame magnified x2
  and added), an in-place blur of the 1/2 buffer (twice, through the target copy), and a
  depth-of-field blend (the frame blurred to 1/2; the Z24 buffer sampled directly as
  PSMZ24 into a mask buffer, AEM: alpha 0 where nothing was drawn; the mask moved into the
  blur's alpha with FBMSK; the frame blended towards the blur by that alpha, magnified x2).
  Every pass samples a dirty target directly; the scene checks `direct_samples`, zero
  write-backs and `writebacks_avoided` (4 for the bloom chain, 3 for the DOF chain, the Z
  buffer being clean there) per chain. Then **upscaled detail**: Gouraud triangles with
  sub-pixel vertices, the frame copied 1:1 to another buffer; at the internal resolution
  the copy must be bit-identical to the source and the source must vary inside native
  pixels. At scale > 1 each colour target is read with `gpu_read_target`, box-filtered
  (truncated mean of each block: the reference downsampled) and compared with
  **tolerance ±4 per channel, 0 pixels beyond** (measured max: 3 at x2, 4 at x4, WARP and
  RTX 3080). The sources are smooth (gradients, as bloom/DOF inputs are): a magnified
  pass over a hard edge differs more by design (an upscaled bilinear resolves the edge
  inside the pixel; with a 0x60 mask step the max difference was 36 at x2, 52 at x4).
* **scene.rtt_flip** (exact; also **scale2/scale4**): the game's present: a 512x448
  draw buffer (random upload, sub-pixel Gouraud triangles, blended sprites) copied to
  the display buffer by one point-sampled sprite: CT32 with UV on texel corners and on
  texel centres, CT16 on corners. The copy must be direct (1 direct sample, no
  write-back), the display buffer must equal the draw buffer at the internal resolution
  bit for bit, and the PCRTC output (`gpu_read_display`, 512x448 FIELD, `scale` x) must
  equal it too; then a whole-pixel frame is flipped, displayed and captured to main
  memory (local→host, 917,504 bytes per format) and compared with the reference exactly.
* **scene.rtt_alias** (exact; also **scale2**): FRAME and ZBUF on the same pages
  (CT32+Z24 at the same base, CT32+Z32 over the lower half, CT16+Z16), depth-tested
  sprites and triangles over GPU targets that were live before, then GPU drawing and
  sampling over the CPU-drawn pages, then textured aliased sprites (96 primitives through
  the software rasterizer).
* **scale2.\*** — exact 2D scenes at internal resolution x2 (`blend_flat`, `pixel_ops`,
  `display`, `rtt_feedback`, `rtt_alias`, `rtt_flip` with direct sampling;
  `rtt_formats` through the native mirror (`scale2n.`, `gpu_config.rtt_native`), because
  its bloom downsamples hard-edged random sprites, which an upscaled pass resolves
  differently by design).
* **control** — `scene.blend_flat` with the GPU blend shifting by 6 instead of 7; registered
  `WILL_FAIL` (it reports 40,688 pixels beyond tolerance), proving the comparison is armed.
* **control_feedback** — `scene.rtt_feedback` with feedback splitting off
  (`gpu_config.fault = 2`); registered `WILL_FAIL` (every chain samples stale data),
  proving the feedback scenes exercise the splitting.
* **control_direct** — `rtt_upscaled` at x2 with `rtt_native = 1`; `WILL_FAIL`: no
  direct samples, and the 1:1 copy differs from its source at 16,243 sub-samples (the
  mirror path's copy is blocky). Proves the upscaled-detail check is armed.
* **control_alias** — `rtt_alias` without the software fallback (`fault = 3`);
  `WILL_FAIL` (65,211 pixels beyond tolerance, max 255).
* **control_exact** — `scene.frame640` through float attribute interpolation
  (`fault = 4`) held to the exact-triangle tolerance 0; `WILL_FAIL` (252 pixels off by
  1 on WARP), proving the exact path is what makes triangles bit-exact.
* **scene.offscreen** (exact) — triangles reaching far outside the target: the NORMAL
  story screen's blended rotated quad (XYOFFSET 0x7000/0x7200, a strip from (-124,-168)),
  24 blended rotated quads 600–3000 px wide around a 256x224 target (flat and Gouraud),
  and the `scene.formats` Gouraud sliver that exposed WARP's `itod`; CT32 and CT24 over a
  random destination, so a pixel drawn twice or missed changes the result.
* **scene.ordered** (exact) — overlapping destination-reading primitives (the 12 blend
  presets × COLCLAMP/PABE/FBA, Gouraud strips and lines, DATE/DATM, partial FBMSK, AFAIL
  FB_ONLY/ZB_ONLY/RGB_ONLY, dithering, bilinear textured sprites) over a random
  destination, CT32/CT24/CT16, without Z, with Z under ZTST ALWAYS and with a Z test;
  with ordered blending the first two must batch (366 primitives → 29-43 batches).
* **control_ordered** — `scene.ordered` with those batches drawn from one snapshot and no
  overlap split (`fault = 6`); `WILL_FAIL`, proving the scene's overlaps matter.
* **control_cover** — `scene.offscreen` with exact triangles drawn as triangles
  (`fault = 5`: the rasterizer decides coverage); `WILL_FAIL` on WARP (8 pixels, max 19:
  the clipped fans' inner edges), skipped (77) where the device covers them exactly (the
  RTX 3080), proving the bounding-box path is what makes WARP exact there.
* **scale2/scale4.af_upscaled** — sub-pixel Gouraud triangles displayed with the game's
  anti-flicker merge (PMODE 0x7F23, DISPFB1.DBY = 1): every output pixel must equal the
  merge of target rows Y+1 and Y at the internal resolution, exactly (917,504 / 3,670,016
  display px); the scene also checks it is armed (a native-row offset would differ at
  408,823 / 2,039,146 of them).
* **game_replay, scale2.game_replay** — the real game: every GS recording under
  `out/p3/gsrec` (see "Real game validation"); skipped without `RG_DATA` or recordings.
* **readback_lag** — the pipelined display read-back returns every previous frame bit for
  bit (`load_2400`, x1 and x3; "Performance").
* **control_decode** — decoded textures with a wrong red channel (`fault = 7`) in
  tex_point; `WILL_FAIL`, proving the scenes sample the decoded copy.
* **scene.alias_pages** (exact) — FRAME / ZBUF / TEX pages aliasing within a primitive,
  within a batch and across batches and contexts (checkpoint 4); **control_shared**
  (`fault = 10`), **control_selfread** (the reference without its texture snapshot) and
  **control_readcurrent** (`fault = 14`: CPU reads of split pages served from `gs->vram`
  without checking the transfer bits cover them) are `WILL_FAIL`.
* **scene.exact_float** (exact) — the exact-triangle shader's float fast path on values
  on and near the integers (checkpoint 4); **control_floatpath** (`fault = 12`: every
  float value taken without its bound) is `WILL_FAIL` (2,145 pixels off).
* **control_early** — `scene.rtt_depth` with early copies of hot read-back regions kept
  after later draws into their pages (`fault = 16`); `WILL_FAIL`.

Tolerance policy: with exact triangles (every device here) **everything is exact**
(tol 0), golden and scenes, on WARP and on the RTX 3080. On a device without double-precision shader ops (float triangles) the previous policy
applies: interpolated scenes (formats, blend_gouraud, tex_filter, prims, frame640) use ±2
per channel (Z: ±(2 + z/2^20)) and allow 50 ppm beyond, and the golden scenes ±2.

Results (WARP, 2026-10-12; `RG_GPU_HW=1` on an RTX 3080 also 66/66, `control_cover`
skipped there):

| Test | Pixels compared | Exact | Beyond tol | Notes |
| --- | --- | --- | --- | --- |
| 28 golden scenes | 1.2 M | 100% | 0 (tol 0) | incl. prim_fullscreen (573,440 px, no longer excused rows: see below), prim_sprite_uv, prim_perspective and prim_mipmap. Display golden scenes: 20,512 display px, 100% exact |
| scene.formats (16 combos) | 1,048,576 | 100% | 0 (tol 0) | was 92.2% with float interpolation; WARP 99.998% before the `itod` fix |
| scene.offscreen | 245,760 | 100% | 0 (tol 0) | the NORMAL story screen's blended rotated quad from (-124,-168), 24 blended rotated quads up to 3000 px wide around the target, the `formats` sliver; CT32 and CT24 |
| scene.blend_flat | 253,952 | 100% | 0 | |
| scene.blend_gouraud | 98,304 | 100% | 0 (tol 0) | was 99.77% |
| scene.tex_point | 131,072 | 100% | 0 | |
| scene.tex_filter | 131,072 | 100% | 0 (tol 0) | was 99.94% (mip/weight boundaries) |
| scene.pixel_ops | 180,224 | 100% | 0 | |
| scene.prims | 131,072 | 100% | 0 (tol 0) | was 99.93% (Gouraud lines) |
| scene.coherence | 71,680 | 100% | 0 | 46,192 FIFO bytes identical |
| scene.display | 573,440 | 100% | 0 | 1,290,240 display px identical |
| scene.frame640 | 573,440 | 100% | 0 (tol 0) | was 99.96% |
| scene.rtt_formats | 1,081,344 | 100% | 0 | 16 checkpoints |
| scene.rtt_depth | 1,622,016 | 100% | 0 | 58,464 FIFO bytes identical (incl. 24 GfxEndFrame 8x8 PSMZ32 readbacks) |
| scene.rtt_feedback | 360,448 | 100% | 0 | 29 feedback splits; 30 batches sampled directly (through the target copy) |
| scene.rtt_upscaled | 352,256 | 100% | 0 | 11 direct samples, 9 write-backs avoided |
| scale2/scale4.rtt_upscaled | 221,184 (box-filtered) | 70.7% / 60.4% | 0 | max diff 3 / 4 (tol 4) |
| scene/scale2/scale4.rtt_flip | 2.06 M + 688,128 display px + 2.29 MB FIFO | 100% | 0 | copy and PCRTC output identical to the draw buffer at x1/x2/x4 |
| scene/scale2.rtt_alias | 491,520 | 100% | 0 | 96 primitives through the software rasterizer |
| scale2.* | 2.4 M | 100% | 0 | |
| control_feedback | 360,448 | — | > 0 | WILL_FAIL, as intended |
| control_direct, control_alias, control_exact | | | | WILL_FAIL, as intended |
| scale2/scale4.af_upscaled | 917,504 / 3,670,016 display px | 100% | 0 | |
| game_replay (10 recordings, 197 fields, incl. 3 of the 3D field) | 7.32 M target + 45.2 M display px | 100% | 0 (tol 0) | see "Real game validation"; RTX 3080 and WARP |
| scale2.game_replay | same, box-filtered (field_* report only) | 96.1% / 89.8% | 88 / 28 px (tol 64, 200 ppm allowed) | isolated sub-pixel stars, max 114 / 72 |

**Reference artifacts found by the harness, now fixed in the reference.**
`golden.prim_fullscreen` (a 640x448 bilinear sprite with UV on texel centres): the
reference computed `v = 8 + 7168 * ((16*y) / 7168)` in double, one ulp below `16*y + 8` on
rows 61, 115, 122, 230, 237, 244 and 251, so its bilinear weight there was 15/16 instead
of 0 (2,730 px were excused). Sprite UV is now a fixed-point DDA in both renderers
(GS.md rule 3) and the excuse is gone. `scene.rtt_depth` found that constant-Z triangles
wrote z-1 at scattered pixels in the reference (barycentric weights summing to 1 - ulp);
triangle attributes are now interpolated as `a + (b-a)*w1 + (c-a)*w2` (GS.md rule 2).

Performance (`rg-host-demo --headless --frames 120`, 640x448, RTX 3080 / WARP on the same
machine):

| Path | GS draw | Display | Present | fps (no pacing) |
| --- | --- | --- | --- | --- |
| Software rasterizer | 21.6 ms | 6.2 ms | 0.16 ms | 36 |
| `--gpu` (hardware) | 0.07 ms | 1.22 ms (incl. read-back) | 0.12 ms | 713 |
| `--gpu --warp` | 0.29 ms | 5.4 ms | 0.14 ms | 173 |
| `--gpu --gpu-scale 2` | 0.06 ms | 1.27 ms | 0.49 ms | 549 |

The demo frame through the GPU differs from the software frame on 213 of 286,720 pixels,
each by 1 (the Gouraud triangle).

## Real game validation

The real game (`rg-game`, headless, deterministic) run through the GPU renderer and
compared with the software GS reference for the same run. Two inputs:

* **title** (no input, 4000 fields): TITLE overlay at field 39, the logo movie from ~287,
  the title menu by 1500 (title art, logo movie frames, menu text over the logo);
* **golden** (`tools/trace/goldens/newgame_battle.input.txt`, 6000 fields): NEW GAME at
  vbl 1900, the NORMAL overlay at ~2107 and its story screen (rotated bilinear starfield
  layers drawn as triangle strips, the "Story" title, the message window) to 6000.

Each run dumps fields with `RG_GS_DUMP_DIR` / `RG_GS_DUMP_FIELDS` (RUNTIME.md "GS
renderer"): the presented frame, `gs_read_display` of local memory after `gpu_sync`, the
4 MB of local memory and the registers; at scale > 1 also `fNNNNN_target.png`, the
displayed buffer at the internal resolution. `tools/gpu_validate.py REF GPU` compares
them: exact %, max channel difference, pixels beyond ±2, differing local-memory
bytes/pages, and that both runs fed the GS the same register stream.

### Repro

```sh
# from Git Bash in .; the scripts are in out/p3/scripts/
powershell.exe -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build/p3-i686
cmd.exe /c out\p3\scripts\build_game.cmd     # rg-game into build/p3-i686 (run it from PowerShell)
# one run: NAME RENDERER(sw|hw|warp|null) SCALE FIELDS DUMP_FIELDS [golden]
out/p3/scripts/run_game.sh hw hw 1 4000 100,300,600,1000,1500,2500,4000
out/p3/scripts/batch3.sh                      # the 12 runs below, sequential
out/p3/scripts/compare_all.sh                 # every table below; diff images -> out/p3/diff
# a GS recording of fields a..b (game data: keep it under out/), replayed in lockstep
RG_GS_REC=out/p3/gsrec/x.rggs RG_GS_REC_FIELDS=2150-2200 \
  out/p3/scripts/run_game.sh rec hw 1 2200 2200 golden
build/p3-i686/tests/gpu/rg-gpu-tests.exe replay out/p3/gsrec/x.rggs   # RG_REPLAY_BISECT=1: first bad event
# the window as presented (windowed run): RG_WINDOW_SHOT=field:path
```

### Results (2026-10-12, RTX 3080 and WARP)

**Scale 1: bit-identical on both devices.** Every dumped field of both inputs: display
100.000% exact (max 0), local memory identical byte for byte, same registers.

| Run | Fields compared | Display | Local memory (4 MB) |
| --- | --- | --- | --- |
| title, RTX 3080 | 100, 300, 600, 1000, 1500, 2500, 4000 | 100% exact | identical |
| title, WARP | same | 100% exact | identical |
| golden, RTX 3080 | 1900, 2000, 2107, 2150, 2200, 2500, 3000, 4000, 5000, 6000 | 100% exact | identical |
| golden, WARP | same | 100% exact | identical (4 bytes differed at 2200 before fix 1) |

`gpu.game_replay` / `gpu.scale2.game_replay` replay 7 recordings in `out/p3/gsrec`
(`title_1496`, `movie_400`, `normal_2140`, `normal_2150_warp`: 71 fields, 5.5 MB of GIF
data; since the "Performance" work also the loading screen's `load_2400`, `load_2800`,
`load_3040`: 93 fields, 25 MB, which pass the same checks; the x2 figures below are for
the first four). At scale 1 every FIFO read, every field's display and the final local memory are
identical on both devices. At x2 (box-filtered, tol 64, 200 ppm allowed beyond): 96.1% of
target and 89.8% of display pixels exact; 88 / 28 isolated pixels beyond 64 (max 114 /
72), all stars smaller than a native pixel landing between sub-samples or shifted a
quarter pixel by the internal-resolution anti-flicker merge.

**Scale 2 and 4: the image is upscaled.** The presented frame is 1024x896 / 2048x1792
(`out/p3/diff/hw_s2_f*_display.png`, `ghw_s4_f*_display.png`), and the window shows it:
`out/p3/window/golden_s1_f02500.png` vs `golden_s2_f02500.png` (1280x960 windowed, field
2500; crop `crop_story_s1_vs_s2.png`: smaller, sharper stars and title edges at x2).
"Detail" is the share of `s x s` blocks of the internal-resolution display buffer that
are not uniform (0% = the native image replicated):

| Run | Fields | Display vs reference (box-filtered): exact, max | Detail | Local memory |
| --- | --- | --- | --- | --- |
| title x2 | 300 / 1500 / 4000 | 99.999% / 73.6% / 60.9%, max 1 / 52 / 52 | 0.0% | identical |
| title x4 | 300 / 1500 / 4000 | 99.999% / 73.6% / 60.9%, max 1 / 78 / 78 | 0.0% | identical |
| golden x2 | 2107 / 2500 / 6000 | 99.999% / 86.8% / 85.9%, max 1 / 55 / 59 | 0.0% / 16.1% / 18.3% | 224 pages differ from 2150 on |
| golden x4 | 2107 / 2500 / 6000 | 99.999% / 84.7% / 83.1%, max 1 / 61 / 67 | 0.0% / 22.1% / 25.5% | 224 pages differ from 2150 on |

Both differences are by design ("Upscaling", "Display", "Known gaps"):

* **The title is 2D art on whole pixels.** Its buffer at x2/x4 is the native image
  replicated (detail 0.0%, local memory identical); the whole display difference is the
  anti-flicker merge at the internal resolution (circuit 1 one *internal* row lower),
  whose box-filtered output weighs the two rows 3:1 instead of 1:1, so horizontal edges
  differ. `gpu_config.native_af = 1` restores the reference merge (and shows upscaled
  detail twice).
* **The NORMAL story screen** has real sub-pixel detail (16–26% of the blocks).
  Local memory (two 512x448 CT32 buffers, 224 pages) is written back from the sub-sample
  `(s/2, s/2)`, which sits at GS `p + 0.5/s`, not on the pixel centre, so sub-pixel edges
  differ there. Field 2107 (before the stars) is exact apart from one pixel off by 1.

### Fixes from real frames

1. **WARP: rasterizer coverage of clipped triangles.** Golden run, field 2200 on WARP:
   4 bytes (one CT32 pixel, page 63) differed. A recording of fields 2150–2200
   reproduced it, and `RG_REPLAY_BISECT=1` stopped at the story screen's blended,
   textured triangle strip from (-124,-168) (XYOFFSET 0x7000/0x7200): 2 pixels on a line
   at y 222–223 drawn twice or not at all. WARP clips a triangle that reaches outside
   the viewport into a fan with float vertices, and the fan's inner edges do not tile
   exactly. Exact triangles are now drawn as their scissored bounding box and the pixel
   shader decides coverage with the reference's integer edge functions and top-left rule
   ("Exact triangles"). Tests: `scene.offscreen` (exact on both devices),
   `control_cover` (rasterizer coverage: 8 pixels wrong on WARP; skipped on the RTX
   3080, which clips exactly), recording `normal_2150_warp.rggs`.
2. **WARP: `itod` of a `dtoi` result.** Found while checking fix 1 against the 22
   `scene.formats` pixels WARP had always missed (documented as edge coverage): they were
   Gouraud slivers one step off. `floor_d(100.92)` returned 101 because WARP's
   `(double)(int)x` is wrong for an integer that came out of `dtoi`; signed conversions
   now go through `utod`. WARP is exact everywhere and `scene.formats` runs at tol 0.
3. **Windowed GPU runs crashed at boot** (`EXCEPTION 0xC0000005` at rva 0x3878F4, a
   28-bit masked address). With a window, SDL's D3D11
   renderer loads the display driver before the game RAM block was allocated (step 9),
   and malloc returned 0x1CFCB000 (headless: 0x05A26000). The block is now allocated
   first in `rg_runtime_init`, with `VirtualAlloc` at the lowest free range from
   0x04000000 (`src/runtime/crt0.c`): windowed x1 and x2 runs reach the story screen
   (game RAM at 0x05570000 / 0x061F0000). The 28-bit masks themselves are a game-side
   matter (bring-up).

Earlier fixes on real frames: the anti-flicker merge at the internal resolution
(upscaled stars shown twice), sprites covering whole blocks at scale > 1, the renderer
created after every game allocation (headless boot crash with the block at
0x143A2000), exact triangles (the starfield's 1/16 bilinear weights).

### Wall time per field

Mean wall ms per field (EE + host half, `RG_FIELD_TIMES`; dump fields excluded). The
game runs at 30 fps, so fields alternate between ~1 ms and a whole frame. "No rasterizer"
is `RG_GS_NULL` (the GS model without drawing): the game and host alone. Same machine,
sequential headless unthrottled runs, scale-1 runs with the bounding-box triangles;
another `rg-game` process was running concurrently, so allow ±10%.

| Renderer | title 1–300 | title 300–1500 (movie) | title 1500–4000 (menu) | title, 4000 fields | golden 2100–6000 (NORMAL) | golden, 6000 fields |
| --- | --- | --- | --- | --- | --- | --- |
| software GS | 45.7 | 45.2 | 53.1 | 210 s | 89.8 | 451 s |
| GPU, RTX 3080 | 15.0 | 5.2 | 9.2 | 37 s | 10.6 | 59 s |
| GPU x2 | 15.3 | 5.5 | 10.0 | 36 s | 11.6 | 63 s |
| GPU x4 | 15.3 | 6.2 | 10.4 | 40 s | 15.7 | 97 s |
| GPU, WARP | 68.6 | 13.2 | 25.0 | 107 s | 67.7 | 314 s |
| no rasterizer | 6.7 | 4.2 | 7.5 | 26 s | 7.7 | 44 s |

Above the no-rasterizer baseline the software GS costs ~40–80 ms per field and the GPU
~1–3 ms at x1 (the whole run is 5.7x / 7.6x faster than software), ~4 ms at x2 and ~8 ms
at x4 on the story screen. Fields 1–300 include device creation and the boot loads.
WARP got slower on the story screen with bounding-box triangles (228 s before, 314 s):
its software pixel shader now runs over the whole box.

### Open differences and next steps

* None at scale 1 on the fields and recordings above. Covered so far: TITLE, the logo
  movie, the title menu, NEW GAME and the NORMAL story screen. Since "Performance"
  checkpoint 2 also the 3D field after the opening FMV (three recordings, exact on both
  devices); battle scenes are next once the golden run reaches them (vbl ~24,000).
* Upscaled write-back: the `(s/2, s/2)` sub-sample is off the pixel centre, so local
  memory of upscaled sub-pixel geometry differs from the reference (CPU captures such as
  the menu's screen capture see it). Averaging the central sub-samples, or an odd scale,
  would centre it.
* The anti-flicker merge at the internal resolution makes the upscaled title differ from
  a box-filtered reference; a frame without sub-pixel detail could keep the native-row
  merge.
* WARP throughput with bounding-box triangles: drawing the triangle itself when it lies
  inside the viewport (keeping the shader's coverage test) would restore it.

## Performance

Checkpoint 2026-10-12 (`build/gpuperf-i686`). The NORMAL loading screen ran at 60-75 %
speed and its music starved the audio device (SOUND.md "Load-screen audio"): every
alpha-blended state was *serial*, so its few hundred overlapping sprites per frame became
one batch each, with a destination snapshot, a target write-back and ~20 D3D11 calls.
Four changes, each exact by construction (same integer pipeline, same results; every
`gpu`/`gs`/`settings`/`host`/`runtime` test and the game recordings stay bit-exact on the
RTX 3080 and on WARP, with and without ordered blending).

**1. Ordered blending (rasterizer-ordered views).** On a device with D3D11.3 ROVs
(`D3D11_FEATURE_D3D11_OPTIONS2.ROVsSupported`: the RTX 3080 and WARP both have them),
colour targets are `R8G8B8A8_TYPELESS` with an `R32_UINT` UAV, and a batch whose pixels
read the destination (blend, DATE, partial FBMSK) is drawn by `PS_main_rov` /
`PS_main_x_rov` (`/DGS_ROV=1`): the shader reads the target through a
`RasterizerOrderedTexture2D<uint>` at the point where it read the snapshot, computes
exactly what the snapshot path computes, applies the pass's channel mask (what the
hardware write mask did) and writes the result back. The hardware orders every pixel's
read-modify-write by primitive, so overlapping primitives share one batch and no snapshot
is taken (`gpu_stats.rov_batches`). Both alpha-test passes are resolved per pixel in one
draw (`DrawCB D[11].y`: pass/fail channel masks). The UAV is written whatever the depth
test decides, so a depth target is allowed only with a test that always passes (ZTE=0 or
ZTST ALWAYS, as the game's 2D draws use while writing Z) and one Z write mask for both
passes; depth writes keep primitive order like any output-merger operation. Batches with
a depth test that can fail keep the snapshot path. `gpu_config.no_rov` /
`RG_GPU_NO_ROV=1` turn it off; `gpu_ordered_blend()` tells whether it is on.

**2. Texels in the high byte.** The loading screen's glyphs are PSMT4HH textures living
in bits 28-31 of its Z24 buffer, drawn while Z is written. A 24-bit frame (CT24) or Z
buffer (Z24) never writes bits 24-31 (the GS keeps them, and so do the write-backs), so
for T8H/T4HL/T4HH textures such a buffer is no longer in the feedback write set and is not
written back for the texture (`Derived::hbyte_tex`). This removed one feedback split and
one target write-back per primitive.

**3. Batches survive unchanged CLUT reloads.** The game reloads the same palette
(TEX0.CLD) every 5 sprites. The batch key now carries a CLUT generation that changes with
the CLUT's *contents* (`clut_copy`, compared on each load), the pending batch keeps its own
copy (`batch_clut`, uploaded at flush), and a `GS_MEM_READ` or `WRITE_BEGIN` ends the
pending batch only when it meets what the batch draws (FRAME/ZBUF over its box) or samples
(`pending_writes`, `batch_read`). The read set of a UV sprite is its exact texel rectangle
(`sprite_texel_rect`), not `axis_range`'s two-texel margin: the 16-px strip copies of the
frame into the CT24 buffer below it no longer split on the page row under the frame.

**4. Cheaper batches.** The backend keeps a shadow of the draw path's bound state and sets
only what changed (no `unbind_all` per draw; an output that is still bound as an input is
unbound first), `NO_OVERWRITE` vertex and triangle rings (`MapNoOverwriteOnDynamicBufferSRV`
for the triangle buffer), constant updates only on change, the CLUT as a `Buffer<uint>`
(t5) instead of a dynamically indexed constant buffer, and the float pixel shader for
batches without exact triangles or lines (the double-precision paths only run on
`vflags & 64`, so sprites and points compute the same values in both).

**Benchmark.** `rg-gpu-tests gfxbench DIR perf [MATCH]` replays every recording whose
name contains MATCH through the renderer alone at the Original preset (x1) and at x3 (the
windowed default), best of `RG_BENCH_REPS` (3), and prints per field: ms (GS replay +
batches + display read-back), the part spent in the display read-back (which waits for the
GPU), primitives, batches, ordered batches, destination copies, write-backs and upload KB;
"GS model only" rows replay without drawing (the floor). Recordings of the golden NEW GAME
run (game data, `out/p3/gsrec`, not committed): `load_2400`, `load_2800`, `load_3040`
(fields 2400-2430, 2800-2830, 3040-3070; the screen draws every other field, so a drawn
frame has twice the per-field counts). They also joined `gpu.game_replay` (7 recordings,
161 fields; exact on both devices). Raw output: `out/gpuperf/final_bench_*.txt`,
`base_bench_hw2.txt`.

RTX 3080 (another application was using the GPU at ~35 % throughout, so GPU-bound
numbers carry noise of a few ms):

| Recording | before x1 | after x1 | before x3 | after x3 | batches / dst copies / write-backs per field, before → after | GS model alone |
| --- | --- | --- | --- | --- | --- | --- |
| load_2400 | 15.7 | 6.6 | 23.0 | 13.5 | 255 / 238 / 234 → 3.5 / 0 / 0 | 4.8 |
| load_2800 | 31.2 | 6.7 | 37.9 | 14.4 | 665 / 648 / 644 → 3.5 / 0 / 0 | 4.9 |
| load_3040 | 39.7 | 6.7 | 46.3 | 14.6 | 925 / 908 / 904 → 3.5 / 0 / 0 | 4.9 |

ms per field ("before": the build before these changes, `gfxbench` "original (x1)" and
"internal x3" rows; a first run of it measured 28.6 / 55.9 / 76.5 at x1). At x1 the
renderer now costs ~1.8 ms per field above the GS model (1.2-1.4 ms of it the display
read-back); at x3 ~9 ms, almost all of it GPU time waited for in the read-back. Ordered
blending off (`RG_GPU_NO_ROV=1`, changes 2-4 only): 10.9 / 16.2 / 20.1 at x1, 17.4 / 24.4
/ 27.8 at x3. WARP, x1: 72 / 78 / 86 (ordered blending off: 93 / 148 / 192).

**The game, windowed, x3, `RG_AUDIO_LOG`** (golden input, 3,600 fields, RTX 3080;
`out/gpuperf/win_base`, `win_new`):

| Fields | before: wall ms/field, device starved | after: wall ms/field, device starved |
| --- | --- | --- |
| 2150-3150 (loading screen) | 35.7, 4.45 s (544 starves) | 19.1, 0.06 s (31 starves) |
| batches / dst copies per field there | 480 / 462 | 4.3 / 0.1 |
| same fields at x1 (`RG_GPU_SCALE=1`, `win_new_x1`) | | 16.75 (work 15.7), 0.002 s (1 starve) |

Whole run: 641,968 → 12,155 batches, 578,944 → 160 destination copies, 456,455 → 394
write-backs. The loading screen now runs at about 87 % of real time at x3 (it was ~47 %
in this session's baseline run; 60-75 % in SOUND.md's) and the device practically no
longer starves there; at x1 it runs in real time (wall 16.75 ms per field, 0.002 s starved). What
is left at x3 is GPU fill: the screen draws ~1.6 M native pixels of bilinear CLUT sprites
per frame (14 M at x3) through the uber-shader. Next steps: a per-batch decode of CLUT
textures into an RGBA texture (one decode per texel instead of four taps per
sub-sample), and pipelining the display read-back.

### Checkpoint 2: the 3D field, decoded textures, read-back (2026-10-12)

Since build l the golden input reaches the 3D field after the opening FMV (GameMode 11,
fields ~7,000 on; BRINGUP.md). Same build dir; scratch tools and raw output in
`out/gpuperf2/` (game data and measurements, never committed).

**Profiler.** `out/gpuperf2/prof/rgprof.exe OUT.tsv PERIOD_MS EXE ARGS` (CC0, ~100 lines
of Win32: `SuspendThread` + `GetThreadContext` of every thread of the child every
PERIOD_MS, EIP plus the stack words that point into the exe) and `anal.py`, which maps the
samples with `rg-game.map` (a sample in a DLL, i.e. the driver, `ntdll` waits or the CRT,
is charged to the first call-checked return address in the exe) and splits them per
field window using `RG_FIELD_TIMES`. `out/gpuperf2/frun.sh NAME sw|hw SCALE FIELDS EXE`
runs the golden input headless under it with `RG_AUDIO_LOG`. GPU time per kind of work:
`RG_GPU_PROFILE=1` (timestamp queries around every draw, decode, write-back, load,
snapshot and display, summed per category and printed at exit).

**Where a field goes** (main thread; every other thread waits; ms per field, headless,
unthrottled, before this checkpoint's changes; two runs shared the machine):

| | loading screen 2150-3150, hw x1 | hw x3 | software GS | field 7000-11000, hw x1 | hw x3 | software GS (7000-10000) |
| --- | --- | --- | --- | --- | --- | --- |
| wall | 9.2 | 9.5 | 124.7 | 325.6 | 337.7 | 752.9 |
| VU1 interpreter (microprograms) | 0.03 | 0.02 | 0.06 | **295.4** | **292.0** | 277.7 |
| GS model (GIF, registers, transfers; software: also the rasterizer) | 5.4 | 5.2 | 121.2 | 12.3 | 12.1 | 471.4 |
| EE kernel / scheduler (`ps2k_step`, `k_trace`, ...) | 2.5 | 2.3 | 2.4 | 0.05 | 0.05 | 0.04 |
| EE game code | 0.13 | 0.14 | 0.12 | 1.6 | 1.6 | 1.6 |
| VIF / DMAC / bus | 0.04 | 0.03 | 0.07 | 0.8 | 0.6 | 0.7 |
| GPU renderer, CPU side (`rg_gpu` + driver) | 0.36 | 0.39 | - | 2.0 | 2.1 | - |
| waiting for the GPU (`mirror_download`) | 0.23 | 0.77 | - | 11.4 | 26.8 | - |
| display read-back + present | 0 (headless) | 0 | 0 | 0 | 0 | 0 |
| audio, CD, movie | 0.3 | 0.3 | 0.3 | 0.4 | 0.4 | 0.5 |

**The field is VU1-bound: 87-91 % of its time.** The VU1 interpreter's float helpers
(`src/ps2/vu/vu_float.c`) build and split doubles with `ldexp`/`frexp`, and the static
CRT's versions save, set and restore the FP control word on every call (`__ctrlfp`,
`__set_exp`, `__decomp`): those CRT internals alone are ~75 % of the field's wall time
(`__ctrlfp <- vu_f_mul` 34 %, `<- vu_f_add` 17 %, `<- vu_itof` 4 %, ...; `vu_step` itself
8 %). Finding for the VU task (not changed here): `vu_f_to_d` is exact as bit assembly
(sign, exponent `e - 127 + 1023` << 52, fraction << 29), `vu_f_from_d` as bit extraction
(`E` = the double's exponent field - 896; fraction = the top 23 of the 52 mantissa bits,
which is the current chop), and `ldexp(x, +-n)` in `vu_ftoi`/`vu_itof` is a
multiplication by an exact power of two; that removes every CRT call from the VU float
path, bit for bit. (Done since: VU.md "Performance", fields 7000-8000 at x1 went from
212 to 22 ms per field, same game state.) The GPU renderer is a few per cent of a field; its largest share is
the CPU waiting in `mirror_download` for the GPU at the once-per-frame 8x8 Z read-back
(`GfxEndFrame`: ZBUF block 7168, PSMZ32, at 494,219) that must see the frame's drawing.
The software GS spends 471 ms of a field rasterizing (`pixel`, `gs_pixel_addr`,
`sample_level`, a `log2` in `gs_tex_lod` for every textured pixel).

**Changes** (each exact by construction; every `gpu` test incl. `game_replay` on the RTX
3080, on WARP and with `RG_GPU_NO_ROV=1`, and the `gs`/`settings`/`host`/`runtime`
labels pass):

1. **Decoded textures** (`GpuDraw.dec`, `CS_decode`, `gpu_stats.tex_decodes` /
   `tex_decode_hits`; off with `RG_GPU_NO_DECODE=1` / `gpu_config.no_tex_decode`). The
   level-0 texels a batch can read (`batch_texrect` within the wrap rect) are decoded
   once by a compute shader that calls the pixel shader's own `tex_fetch` (swizzle, CLUT
   for T8/T4/T8H/T4HL/T4HH with CSM1/CSM2 and CSA, TEXA expansion) into an R32_UINT
   texture; `tex_fetch` reads that texture for level 0 inside the rect and the mirror
   everywhere else (other mip levels, texels outside, anisotropic taps). Filtering is
   unchanged and happens after the per-texel lookup, which is the GS order (`gs_tex.c
   sample_level`: CLUT and expansion per tap, then the 4-bit bilinear weights), so no
   state needs the old path for correctness. Copies are cached (64, LRU) under an exact
   key: TBP/TBW/PSM, CPSM/CSA, TEXA, the CLUT's content generation, the newest mirror
   write stamp of the pages read (`page_stamp`, bumped by every upload and write-back)
   and the rect. Control: `gpu.control_decode` (red channel of every decoded texel off
   by one, `fault = 7`) must fail, and does (tex_point: 34,532 pixels). **Measured: no
   GPU-time gain** on these recordings (field ~345 vs 329 ms of GPU time with it off,
   loading screen 394 vs 392: within run-to-run noise): the texel fetch is not where the
   GPU's time goes (below). Only indexed textures with at most one texel per covered
   sample are decoded now (`dec_new`), ~2 per field.
2. **Kick** (`GpuBackend::kick`, `ID3D11DeviceContext::Flush` after every 256 K target
   pixels drawn; `RG_GPU_KICK_PX` for measurements, 0 = never). The driver otherwise held
   the field's draws until the display read-back mapped, and the GPU started on them only
   then. This is most of the loading screen's x3 gain below.
3. **Pipelined display read-back** (`gpu_config.readback_lag`, `RG_GPU_READBACK_LAG=1`):
   `gpu_read_display`/`gpu_read_output` queue this frame's copy into one of two staging
   textures and return the frame the previous call queued (first call or a new size: the
   current frame, now). Presentation only (one field of latency), never with dumps or
   validation. `gpu.readback_lag` replays `load_2400` at x1 and x3 and checks every read
   returns the previous frame bit for bit (31 reads, 15 distinct frames). Off by default:
   the runtime (not this module) decides when to use it.
4. **Grown triangles instead of boxes** (`grow_poly`, `gpu_stats.grown_tris`;
   `RG_GPU_TRI_BOX=1` restores the boxes). Exact triangles were drawn as their scissored
   bounding box ("Exact triangles", the WARP clipping fix); now as the triangle grown by
   one pixel on every side, clipped to the box plus a pixel inside the viewport (x in
   [0, FBW*64), y in [0, 1024): every target has at least 1024 rows), as a fan of up to
   6 triangles whose shared vertices are bit-identical: the rasterizer covers a superset
   of the reference's samples (one pixel is far beyond its snapping error), never clips,
   and covers each sample once; the shader still decides coverage. The box is kept when
   the polygon is larger (slivers). Loading screen's rotated starfield: 1.64 -> 1.27 ms
   of GPU per exact-triangle batch.
5. **Unused exact attributes are skipped**: Z without a depth target (`GF_NOZ`), fog
   without FGE, S/T/Q/UV without TME (the exact path's doubles).
6. **GS model transfers inlined** (`src/ps2/gs/gs_mem.c`): the host->local transfer loop
   called `gs_write_pixel` -> `gs_pixel_addr` per pixel (7 stack arguments each on i686);
   both are now `always_inline` internals with the exported functions as wrappers (same
   code). `gfxbench` "GS model only": loading screen 4.9 -> 2.3 ms per field, field
   11.0 -> 6.4. The software reference uses the same transfer path and got faster too.

**Where the GPU's time goes now** (`RG_GPU_PROFILE=1`, RTX 3080; GPU ms over the
recordings at x1 + x3): loading screen (load_3040) 71 % in ordered, decoded, *exact*
textured triangles (the rotated starfield layers: 1.24 ms per batch), 14 % ordered
sprites, 11 % display + copy; field (3 recordings) 29 % decoded exact textured
triangles, 15 % ordered direct-sampled sprites (the post-process chains), 14 % direct
exact triangles, 6 % snapshots, ~5 % each decodes, write-backs and display. The exact
path's double-precision arithmetic runs at 1/64 rate on consumer GPUs: the next GPU step
is a float evaluation of the reference's interpolation with a rigorous error bound that
falls back to doubles only where `floor` is ambiguous.

**Results** (RTX 3080; "before" = the build at the start of this checkpoint
(`out/gpuperf2/base_bin`), "after" = all six changes; ms per field; sequential runs, one
other `rg-game` on the machine throughout, so allow +-10 %).

| | before | after |
| --- | --- | --- |
| loading screen 2150-3150, headless x1 / x3 (wall, `RG_FIELD_TIMES`) | 8.4 / 8.7 | 5.8 / 5.8 |
| field 7000-8000, headless x1 / x3 | 221.3 / 235.3 | 215.5 / 224.6 |
| field: of which waiting for the GPU, x1 / x3 (profiler) | 10.7 / 21.4 | 11.1 / 21.3 |
| field: of which GS model, x1 / x3 | 9.4 / 9.7 | 5.0 / 5.1 |
| loading screen, windowed x3 (`RG_AUDIO_LOG`): wall, present, device starves | 18.1, 8.1, 109 | 16.75 (real time), 3.8, 2 |
| same with `RG_GPU_READBACK_LAG=1` | | 16.75, 3.3, 2 |
| loading screen, windowed x1: wall, present | 16.75, 2.7 | 16.73, 1.7 |
| `gfxbench perf` load_2400 / 2800 / 3040, x1 | 6.1 / 6.5 / 6.8 | 3.0 / 3.4 / 3.4 |
| same, x3 (display + wait part) | 11.5 / 11.5 / 11.9 (6.3) | 5.6 / 5.8 / 6.0 (2.9) |
| `gfxbench perf` field_7600 / 8800 / 10400, x1 | 15.8 / 17.2 / 17.6 | 11.2 / 11.6 / 12.2 |
| same, x3 | 25.4 / 28.0 / 29.8 | 17.2 / 20.2 / 20.8 |
| GS model alone, load / field recordings | 4.8-5.1 / 10.8-11.2 | 2.3-2.4 / 6.2-6.6 |

**The "not met at x3" note is closed:** the windowed loading screen runs in real time at
x3 (16.75 ms per field, the 60 Hz pacing) with 2 device starves in 1,000 fields (109 in
the same run before). The field is far from real time (~220 ms per field, ~8 % speed) and
that is the VU1 interpreter (above); the renderer's share of a field is ~5-10 %, most of
it the once-per-frame wait for the GPU at the Z read-back, which the kick did not shorten
(the read must see the frame's own drawing). Next GPU steps: the float fast path for exact
triangles, and a GPU-side local->local transfer (the field's post-process chains copy
targets through the CPU model).

**3D field validation.** Recordings `field_7600`, `field_8800`, `field_10400` (fields
7600-7610, 8800-8810, 10400-10410 of the golden run; 11 fields and 10-11 MB of GIF data
each; `out/gpuperf2/rec.sh`) joined `out/p3/gsrec`: **the first real 3D content, exact at
scale 1 on the RTX 3080 and on WARP** (and without ordered blending): every display,
every FIFO read and the final local memory identical. They exercise what the 2D screens
did not: depth testing, ~110 batches per field, ~6 target creations and ~25 write-backs
per field, feedback splits, direct sampling in the post-process chains, FRAME/ZBUF alias
primitives through the software rasterizer (267 in the run to field 8810). No exactness
bug was found. At x2 their sub-pixel geometry and Z differ from the native reference by
design ("Upscaling"; field_7600: 93.4 % of target and 96.1 % of display pixels exact, Z
max diff 115,897; identical before and after these changes), so `scale2.game_replay`
replays and reports `field_*` but counts only their FIFO reads (`gpu_replay.c
replay_one`).

### Checkpoint 3: the 3D field after the VU1 fix (2026-10-13)

> **Correction (checkpoint 4).** The game snapshots this checkpoint measured on (game
> builds 19-28, incl. the 01:31 and 02:58 snapshots below) drew **no 3D** in the field: a
> stack-block rule of the bring-up broke the camera, which is also why VU1 time there was
> ~0.15 ms per field. The 7600-8000 numbers below are therefore of a 2D-only field (the
> post-process chains, HUD and overlays) and understate the real field load; the 3D field
> is measured in checkpoint 4 (fields 8000-16000 of a build that draws it). The
> "per-frame 8x8 Z read" that the x3 note below names as 73 % of the main thread's time
> was, in that snapshot, a CLUT load at block 16243 whose page set the core over-estimated
> by one page (a page the GPU drew every frame); the 8x8 Z read only happens while the 3D
> field is drawn (checkpoint 4 "Read-backs").

Build `build/fieldperf-i686`; scratch tools and raw output in `out/fieldperf/` (game data
and measurements, never committed). Files: `src/ps2/gs/gs_mem.c`, `gs_core.c`, `gs.h`,
`gs_internal.h`; `src/gpu/gpu_core.cpp`, `gpu.h`, `gpu_internal.h`, `gpu_d3d11.cpp`,
`shaders/gs_util.hlsl`, `CMakeLists.txt`; tests `tests/gs/test_gs_xfer.c`,
`tests/gpu/gpu_scenes.c` and both `CMakeLists.txt`. `src/runtime` unchanged.

**Tests** (`build/fieldperf-i686`): labels gs, gpu, settings, host, runtime, dmac,
hwbus, movie on WARP (238 tests; the 2 `movie.play_tool*` not built there), gpu +
settings + host on the RTX 3080 (121) and gpu with `RG_GPU_NO_ROV=1` (85): all pass,
incl. `gpu.game_replay` (7 game recordings, tol 0) and the new controls. Starting point: VU.md "Performance" (22.1 ms per
field over 7000-8000, headless x1; 12.6 for 7000-7599, 36.2 for 7600-8000).

**Why 7600-8000 cost 3x 7000-7599.** Mostly the window, not the scene: fields
7000-7299 are still the opening FMV (3.7 ms per field: movie decode and its texture
uploads); the 3D field starts at ~7300. Per 50-field window (VU agent's final run): 3.7
up to 7299, 6-16 while the field fades in, ~27 for 7400-7750, ~41 for 7750-8000. Inside
the 3D field the difference is VU1 work (`anal.py`, main thread, ms per field):

| | 7000-7299 (FMV) | 7400-7749 | 7750-8000 |
| --- | --- | --- | --- |
| wall | 3.7 | 27.3 | 41.2 |
| VU1 interpreter | 0 | 12.9 | 23.6 |
| GS model (`gs_xfer_hwreg` most of it) | 1.9 | 6.0 | 6.2 |
| CPU waiting for the GPU (ntdll, driver) | 0.1 | 6.5 | 9.0 |
| movie | 1.1 | 0 | 0 |

The later scene runs ~1.8x the VU1 microprogram work (more geometry on screen); the GS
model is flat. Note on the profiler: samples in `ntdll` were charged to
`D3D11Backend::draw` by a stale return address left on the stack; the deeper frames
(`out/fieldperf/callers.py`) show they are `mirror_download` (the per-frame Z read,
~65 %) and `kick` (the `Flush`, ~30 %).

**GS model: bulk IMAGE transfers** (`gs_xfer_image`, `src/ps2/gs/gs_mem.c`;
`gs_gif_write` hands every queued qword of an IMAGE loop over at once). The field
uploads ~0.55 M pixels per field (field_7600: 405 K PSMT4, 152 K PSMCT32), and every
pixel went through the per-word `gs_xfer_hwreg` -> `xfer_put_pixel` -> full address
swizzle. The address splits into an x part and a y part for every PSM (the page term is
a sum, each block-number bit comes from x or from y, the Z formats' `^ 24` flips one
x-owned and one y-owned bit, the 8/4-bit column rotation flips an x-owned bit by a
y-dependent amount): `addr(x,y) = ((Xblk + Yblk - Oblk) & 0x3FFF) << S | (Xlow ^ Ylow ^
Olow)` with X = addr(x, 0) at BP 0 (a table per transfer), Y = addr(0, y) (once per row),
O = addr(0, 0). Rows are then written with one table load and an add per pixel.
`gs_xfer_hwreg` is unchanged (HWREG through A+D) and is the reference. Tests:
`gs.xfer_separable` (the identity for every PSM, all x, y < 2048, 11 BW x 6 BP:
795 M addresses), `gs.xfer_bulk` (3,000 random transfers of every PSM, sizes 1x1 to
4095 wide, wrapping, data past the end, abandoned transfers, IMAGE data in random
pieces: local memory, transfer state, carry bytes, counters, HWREG and the hook calls
identical to the per-word path), `gs.xfer_bulk_control` (one bit flipped, must fail).
GS replay alone (`out/fieldperf/gsb`, field_7600 / field_8800): 10.8 / 10.3 -> 1.23 /
1.26 ms per field, final local memory identical.

**The GPU waits were not the Z read.** Counters added for this (`gpu_stats.downloads`,
`download_us`, `kicks`, `kick_us`, `merges`; printed at exit with `RG_GPU_PROFILE=1`) and
`RG_GPU_SYNC_LOG=FILE` (every hook call that made the CPU read back, with its rectangle)
showed ~14 read-backs per 3D field, not one per frame: GPU time was only ~3 ms per field
(`RG_GPU_PROFILE`, 7400-8000), but each read-back drains the queue. 96 % of them were
`GS_MEM_WRITE_BEGIN` of the game's texture uploads (PSMT4 512x416, 512x256, CT32 64x64,
...) into pages a render target had written earlier in the frame (the field reuses
texture memory for render-to-texture): the old rule wrote the target back and downloaded
the pages so the upload could merge with them; the per-frame 8x8 Z read was the other
~4 %.

**Split pages instead of read-backs** (`gpu_core.cpp` `merge_split`, backend
`mirror_merge` + `CS_merge`, `gs_xfer_mask` in the GS model). At the BEGIN of a
host->local transfer, dirty targets over its pages are written back to the mirror (GPU
work, no wait) and the pages the mirror is newer on become *split*: no download, the
CPU model writes `gs->vram` as always, and at the END the bits the transfer wrote are
OR-ed into a mask (`gs_xfer_mask`: exactly the bits `gs_write_pixel` changes, incl.
CT24's kept byte 3, the H formats' byte/nibble and T4 nibbles; `gs.xfer_mask` checks it
against `gs_write_pixel` of all-ones pixels). Bits in the mask are newest in `gs->vram`,
every other bit of a split page newest in the mirror. When anything needs a split page
(an upload for sampling or a target load, a download for a CPU read, a target
write-back over it, the display), `merge_split` sends (data, mask) per word and the GPU
does `mirror = (mirror & ~mask) | (data & mask)` in queue order; the pages are then
mirror-newer (or current in both, when every bit was written). A complete transfer that
covers whole pages (page-aligned BP, full-word format) leaves those pages simply
CPU-newer. If a split page is needed while the transfer into it is still open, the bits
so far are merged and the pages read back, and the rest of the transfer is an ordinary
CPU write (the old path). Transfers that wrap at 2048 keep the old path
(`pages_of` does not wrap). `RG_GPU_NO_DEFER=1` restores the read-backs. Replays of
field_7600: 225 merges per 10 fields when merged per transfer (the first version; it
made the FMV 0.7 ms per field slower: one merge per macroblock row), 14 with the lazy
merge; downloads 19 (the Z reads and the final checkpoint). Control: `gpu.control_merge`
(`gpu_config.fault = 8`: split pages merged without their mask, i.e. the whole page from
`gs->vram`) replays field_7600 and must fail; it does, on the RTX 3080 and on WARP.
`gpu.scene.split` drives the same packets through the reference and the GPU: partial-word
uploads over drawn pages (CT24 keeps byte 3, T4HH one nibble of it, T4 nibbles over a
drawn Z buffer), a page-aligned CT32 upload (whole pages), an abandoned transfer, a CLUT
load that reads a transfer's half-written pages while it is open (merge + read-back
mid-transfer), then drawing over and sampling the results; target, FIFO and final memory
identical (tol 0) on both devices, with and without ordered blending and with
`RG_GPU_NO_DEFER=1`; `gpu.control_merge_scene` (fault 8) must fail and does. (Writing
this scene first with context 2's ZBUF left at 0, i.e. Z on the CT32 frame's pages while
FRAME_2 drew elsewhere, gave a 109-max difference with the old read-back path too: an
existing alias case, not followed up here.)

**Mask rows.** `gs_xfer_mask` runs only over the rows of page bands that hold split
pages (the PSMT4 512x416 uploads cover 12 whole pages and 4 split ones: 32 of 416 rows).

**Measurement setup.** Two other agents changed `src/ps2/vu` and `game/` throughout
(at times the game did not compile or crashed at field ~2000). `out/fieldperf/b.ps1`
configures this build with `CMAKE_PROJECT_INCLUDE=out/fieldperf/freeze_vu.cmake`, which
links a frozen copy of `src/ps2/vu` (taken 01:31, the block translator then in
progress); `mkpair.sh TAG` builds only the GS/GPU/runtime libraries and links
`TAG_new` (these sources) and `TAG_base` (the sources before this checkpoint,
`out/fieldperf/orig`) from the *same* game objects with `mklink.py`. In the game
snapshot used for the final pairs (02:58) VU1 time in the field is ~0.15 ms per field
(the VU1 work is no longer where VU.md measured it), so the 3D field is now GS model +
GPU waits; earlier pairs on the 01:31 snapshot (VU1 ~11 ms per field) are listed too.
Another `rg-game` and other GPU users were running throughout: base runs of the same
binary varied 14-31 ms per field in 7600-8000; alternating runs, all listed.

**Results** (golden input, headless, unthrottled, `RG_GPU=hw`, RTX 3080; ms per field
from `RG_FIELD_TIMES`; `out/fieldperf/cmp.sh`, runs in `out/fieldperf/runs/c*`; each
cell lists the alternating runs, median first):

| pair | scale | 7000-7599 before | after | 7600-8000 before | after |
| --- | --- | --- | --- | --- | --- |
| p5 + p6 (02:58 game) | x1 | 10.2 (7.8, 8.3, 10.2, 11.2, 13.8) | **3.5** (3.1, 3.1, 3.5, 3.8, 4.5) | 18.0 (14.2, 15.0, 18.0, 21.7, 25.7) | **5.1** (4.2, 4.7, 5.1, 6.0, 7.0) |
| p5 (02:58 game) | x3 | 10.2 (10.1, 10.2, 10.9) | **5.5** (5.4, 5.5, 7.2) | 19.6 (19.6, 19.6, 20.0) | **11.5** (11.2, 11.5, 19.9) |
| base_bin / new2 (01:31 game, VU1 ~11 ms) | x1 | 11.6 (11.4, 11.8) | 7.9 (7.7, 8.0) | 30.8 (30.5, 31.2) | 21.2 (21.1, 21.3) |

(new2 is the first version: GS bulk transfers and one merge per transfer; it made the
FMV 7000-7299 slower, 3.7 -> 4.4, fixed by the lazy merge: 4.1 -> 2.1 in p5/p6.)
Windowed (real time, `out/fieldperf/win.sh`, p5): x3 (window default) 7600-8000 27.7 ms
per field before, **16.73 after (real time, 60 Hz pacing)**; x1 16.68 after; the FMV
16.7 in all.

**Exactness of the game.** p5 and p6 pairs (`vrun.sh` / `vcmp.sh`): screenshot at field
8000 byte-identical, the 32 `RG_STATUS_EVERY=250` lines identical, the GS recording of
fields 7900-7960 identical in every bit the GS uses (30 `ALPHA_1` lines differ in bits
40-63, the host pointer the game leaves there), EE RAM at 7000/7500/8000: 897/945/960
words differ, all of them pointers (into game RAM at the same offset, or into the exe at
the same page offset; ASLR and the changed image).

**Where a 3D field goes now** (p5_new, 7400-8000, profiled): x1 4.6 ms: GS model 1.9
(`xfer_row` 1.2, most of it the PSMT4 nibble stores; `gs_xfer_mask` 0.5 before the row
restriction), CPU waiting for the GPU 1.2 (the Z read once per frame, kicks, driver),
game 0.5, GPU renderer CPU side 0.3, audio 0.25, VU1 0.15. x3: GPU-bound, ~73 % of the
main thread waits in the per-frame Z read for the GPU. GPU time at x3
(`RG_GPU_PROFILE`, 8000 minus 7400): 7.4 ms per field, of which exact triangles 4.7
(`draw exact tex` 2.4, `draw rov exact flat` 1.4, `draw direct exact tex` 0.9), ordered
direct-sampled sprites 0.9, snapshots 0.5, write-backs 0.3. The game's 3D geometry is
STQ (48,700 STQ against 9,000 UV writes in field_7600), so a float fast path for exact
triangles pays only if it covers S/T/Q and their division as well as colour and fog; Z
(Z32 values up to 2^32) and `qf = (float)qd` (the LOD needs the double's own float
rounding) stay double. Not done here: x1 and x3 already run in real time windowed.

### Checkpoint 4: aliasing within and across batches; x3 (2026-10-13)

Build `build/gpufix-i686` (configured by `out/gpufix/b.ps1`, which links a frozen copy of
`src/ps2/vu`, `out/gpufix/vu_frozen`); scratch tools and raw output in `out/gpufix/`
(game data and measurements, never committed). `src/runtime` unchanged.

**The 109 difference (root cause).** Checkpoint 3's note: `scene.split` with context 2's
ZBUF left at 0 differed from the reference by up to 109, with the old read-back path
too. Context 2's sprite then writes Z32 at block 0 (ZMSK = 0, FBW 2) while its TEX0_2,
never set, is a 1x1 CT32 texture at block 0: part-way through the sprite one pixel's Z
word lands on that texel. The reference, reading memory as it wrote it, gave every later
pixel the new texel (RGB 0 after MODULATE, alpha from the vertex); the GPU sampled memory
as it was before the primitive (109 is a channel of the old texel). Not a context-2
register path and not a coherence bug: the two renderers disagreed on what a primitive's
texture reads see of its own writes ("Render targets as textures", "Within one
primitive", which called it unmodelled). Logging every primitive whose texture pages meet
its own write pages over the game recordings found the real case: the 3D field's blur
passes (field_7600: ~45 per field), 32-pixel strips adding the CT32 buffer shifted by one
or two pixels to itself, reading one pixel behind on the same row. Read in raster order
that smears along the strip; the GS's texture buffer is not updated by drawing (TEXFLUSH),
which is what such passes rely on. (The recordings still matched because the blurred
buffer is black there.)

**Fix: one semantics, in the reference.** A primitive's texture reads see memory as of
the primitive's start in both renderers: `gs_raster.c` `tex_snapshot` copies the
texture's pages (every mip level, as far as the wrap modes reach) into a shadow buffer
when the primitive's FRAME or ZBUF pages (its pixel box inside the scissor) can meet
them, and samples that (`gs_tex_snapshots` counts them; `gs_tex_snapshot_off` is the test
control). The GPU already worked this way; routing such primitives through the software
rasterizer to match the old reference would have cost a GPU sync per strip. Earlier
primitives are still seen (the feedback splits; TEXFLUSH stays a no-op). The software
renderer's output changes only for primitives that read what they overwrite. (GS.md, not
edited here, still describes the reference without this rule.)

**Second class: colour and depth targets sharing pages.** With the scissor keeping
FRAME and ZBUF apart (no `Derived::alias`), a colour target grown over the Z buffer's
pages by earlier draws stayed live next to the depth target (`rt_bind`'s `keep`): the
depth target loaded those rows from a mirror the colour target had not written back, and
each target later wrote back its dirty rectangle over bytes the other had changed.
`flush_batch` now writes the colour target back before binding a depth target its pages
reach, and after a batch whose two targets share pages writes both back and marks them
stale (reloaded on next use; `gpu_stats.shared_rt_batches`, 0 in every game recording).

**Tests.** `gpu.scene.alias_pages` (tol 0, 10 checkpoints): the scene that found it
(`scene.split` with ZBUF_2 at 0); context 2 drawing with its Z32 buffer on context 1's
frame while sampling that frame (sprites point and bilinear, UV and STQ triangles),
interleaved with context 1 blending on it; the game's in-place strips (shifted by 1-2
pixels right, down, up, left, diagonally, half-texel bilinear; CT32 and CT16); the Z
buffer sampled while the same primitives write it, as Z24 and as CT32; triangles sampling
the frame they draw into (UV and STQ); the CT32 frame read in place as CT16 and T8; a
colour target over the Z pages and a Z target over the colour pages, three rounds each;
two contexts with FRAME and ZBUF swapped, alternating. `gpu.control_shared` (fault 10: no
write-backs around shared targets; 23,117 pixels off) and `gpu.control_selfread` (the
reference without the snapshot; 35,785 pixels and 18,333 FIFO bytes off) are `WILL_FAIL`
and fail. `gs.prim_self_read` checks the reference alone (an in-place shift gives each
pixel its neighbour's old value; Z32 writes over the sampled texel do not change what the
sprite reads; with the snapshot off the shift smears). RTX 3080, WARP and
`RG_GPU_NO_ROV=1`: every `gpu` test passes (88 incl. the controls), `gs` 46 (at that
point; final counts below).

**Game objects.** The first pairs of this checkpoint were linked from a game snapshot
taken at its start (no 3D drawn in the field, see the correction under checkpoint 3);
when the bring-up restored the 3D field, `build/gpufix-i686` recompiled the game once
and every later pair (`base2` = the GS/GPU sources at the start of this checkpoint,
`new8` = this checkpoint) is linked from those objects (`out/gpufix/mknew.sh`,
`mklink.py` with the link line frozen in `build.ninja.base`), with the frozen
`src/ps2/vu` copy. Results below are from that build unless marked "2D snapshot".

**Read-backs.** What makes the CPU wait for the GPU, per frame (`RG_GPU_SYNC_LOG`,
fields 0-10000 of the 3D build): the 8x8 PSMZ32 read at (494,219) of the Z buffer (block
7168), once per frame while the 3D field is drawn, and two CLUT loads (16x16 CT32 at
blocks 16244 and 16211-16252). Three changes:

1. *Exact page sets for buffers that do not start on a page* (`pages_of`). The page-grid
   estimate added the next page of every page; a 16x16 CLUT at block 16243 is inside
   page 507 but was also given page 508, a render target the GPU draws every frame, so
   loading the palette read that page back. Now the pages of the blocks the rectangle
   covers (each block lies in one page; at most 4,096 blocks, else the estimate). This
   also exposed a latent crash of checkpoint 3: `end_write` cleared the split mask of
   whole pages through `merge_mask` before anything had allocated it (now
   `split_mask(r)`); the spilled page had always allocated it first.
2. *Reads of bits the CPU itself wrote* (`read_current`, `gpu_stats.reads_current`). In
   the 3D build the palettes live in the last page of a 256x256 render target at block
   15232: the game uploads a palette into it and loads it as the CLUT right after. A
   CPU read needs no read-back when no dirty target covers its pages, none of them is
   newer on the GPU, and on split pages the bits the transfers wrote (`merge_mask`)
   cover every bit the read uses (`gs_xfer_mask` of the read rectangle). Test:
   `scene.alias_pages` part 8 (a palette uploaded into a drawn page, whole and an 8x8
   part of it); `gpu.control_readcurrent` (fault 14: split pages taken as current) fails.
3. *Early copies of the per-frame Z read* (`HotRead`, `gpu_stats.early_copies` /
   `early_reads`; `RG_GPU_NO_EARLY_READ=1` turns it off). A region read back (at most 4
   pages, the 4 most recent) is remembered; after each batch, a remembered region whose
   pages the batch wrote is marked, and the first later batch that leaves them alone
   copies them: the mirror is made current there (uploads, the write-back of the dirty
   targets' cells on those pages only) and the pages go to a staging slot
   (`GpuBackend::snap_copy`, then a Flush). The read then maps that slot, which waits for
   the copy only, not for the post-processing and HUD queued behind it, and installs the
   pages as a read-back would. A CPU write to the pages voids the copy. Test:
   `scene.rtt_depth` (24 GfxEndFrame-style reads among draws: 4 served early);
   `gpu.control_early` (fault 16: a copy kept after later draws into its pages) fails.

In the 3D field at x3 the main thread's wait for the GPU went from 3.67 to 1.95 ms per
field (8000-10000, profiled); what is left is the GPU still working on the frame's 3D
when the game asks (GPU 5.05 ms per field there).

**Exact triangles: the float fast path** ("Exact triangles"). In the 2D snapshot the
exact-triangle draws were 4.7 of 7.5 ms of GPU time per field at x3 (the field's
half-resolution strips: 16 single-triangle batches per frame with U on whole 1/16
texels at every pixel; an 80-triangle Gouraud ray fan through the ordered view; direct
exact draws). GPU ms over the replay of fields 7600-7610 at x3 (`out/gpufix/gbench.sh`,
min of 5, RTX 3080 shared with other applications):

| | before | after |
| --- | --- | --- |
| draw exact tex (160 batches) | 60.0 | 17.1 |
| draw rov exact flat (5) | 38.2 | 5.0 |
| total GPU (11 fields) | 204.8 | 95.6 |

In the game (2D snapshot, x3, 7400-8000): GPU 7.54 -> 4.48 ms per field (exact draws
4.7 -> 1.4). The ray fan reaches far off screen, so its triangles were not `TF_SMALL`
at x3/x6 until the edge functions were split into `s*n + d` (x6: 3.0 -> 0.8 ms per
field). What still costs in an exact draw is the shader's size (register pressure) and
Z of 2^24 and above in double. Measured and dropped: decoding direct-colour textures at
high scales (no gain; the texel fetch is not the cost).

**Kicks** are counted in native pixels (`kick_px`): at x3 the old count of upscaled
pixels flushed 9 times as often for the same field, ~50-70 us of driver time each
(2D snapshot x3: 4.2 -> ~0.4 ms of kicks per field).

**Results** (golden input, headless, unthrottled, `RG_GPU=hw`, RTX 3080, ms per field
from `RG_FIELD_TIMES`; `base2` vs `new8`, same game objects; other applications used
the GPU throughout, so a run varies by ~10 %; `out/gpufix/final_runs.txt`):

| scale | 7600-7999 base | new | 8000-15999 base | new | 14000-14999 base | new | 15000-15999 base | new |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| x1 | 12.0 | 11.6 | 12.1 | 11.3 | 12.6 | 11.7 | 18.8 | 17.9 |
| x3 (2 runs) | 17.8, 22.8 | 12.7, 14.5 | 19.1, 20.0 | 12.5, 13.5 | 21.1, 18.7 | 12.6, 13.2 | 24.2, 24.0 | 18.8, 18.7 |
| x4 (2 runs) | 22.3, 24.8 | 19.9, 15.1 | 23.2, 23.3 | 19.6, 15.9 | 24.1, 18.7 | 20.4, 16.2 | 32.8, 23.7 | 28.7, 21.4 |
| x6 | 34.2 | 23.6 | 34.3 | 23.7 | 27.3 | 23.0 | 30.7 | 27.6 |

x3 now costs what x1 costs plus ~1.5 ms per field (8000-15999); 15000-15999 is
CPU-bound at every scale (17.9 ms at x1). x8 cannot be measured in this i686 build:
with scale 8 the game's RAM lands above 0x10000000 ("28-bit address masks will
fault") and the run stays on the title screen, before and after this checkpoint.
In the 2D snapshot the same changes took x3 (7600-8000) from 12.1 to 6.0 and x4 from
16.7 to 10.0 ms per field.

Windowed real-time runs for this checkpoint were not completed (the session ended
before they finished); the headless numbers above are the measured result. Closed by docs/PERF-3D.md
(2026-10-17), which re-measures the corrected 3D scene windowed and adds depth in ordered
views (`zrov`), zero-copy presentation, `GS_NOTEX` shader variants, decoded textures for
anisotropic taps and the GS worker thread.

**Exactness.** RTX 3080, WARP and `RG_GPU_NO_ROV=1`: every `gpu` test passes (92 incl.
the 7 new controls), `gs` 46; `gpu.game_replay` includes two recordings of the 3D field
(`out/p3/gsrec/field_3d_8000.rggs`, `field_3d_14000.rggs`, made with this build).
Golden run `base2` vs `new8` at x1 (`out/gpufix/vrun.sh`, `vcmp.sh`): screenshot at
field 8000 byte-identical, the 32 status lines identical, the GS recording of fields
7900-7960 identical in every bit the GS uses (30 `ALPHA_1` lines differ in bits 40-63,
the host pointer), EE RAM at 7000/7500/8000 differing only in pointers (into game RAM at
the same offset, or into the exe image, all by the image's relocation 0x7C0000). The
same check on the 2D snapshot (`base` vs `new5`) gave the same result.

**Files.** `src/gpu/gpu_core.cpp`, `gpu.h`, `gpu_internal.h`, `gpu_d3d11.cpp`,
`shaders/gs_draw.hlsl`; `src/ps2/gs/gs_raster.c`, `gs.h`; `tests/gpu/gpu_scenes.c`,
`gpu_tests.c`, `gpu_compare.c` (variadic notes, buffer base in pixel notes),
`CMakeLists.txt`; `tests/gs/test_gs_prim.c`, `CMakeLists.txt`. Measurement only:
`RG_GPU_TRACE=FILE` (every batch, memory op and display read). `src/runtime`
unchanged. Later (2026-10-22): `RG_GPU_RT_LOG=FILE` logs only target creates (`R depth bp bw psm h`),
drops (`X ... dirty`) and display reads (`D`), cheap enough for a whole run.


## Graphics settings

PLAN.md P6 "Graphics settings", the renderer side. The settings live in the registry
(docs/SETTINGS.md); `gpu_gfx_from_settings` (`src/gpu/gpu_gfx.c`) turns `graphics.*` into
renderer parameters, and the presenter (`src/runtime/runtime.c`, `rg-host-demo --gpu`) applies
them every field. All of it is original CC0 code; no third-party shader was used, so
THIRD_PARTY_NOTICES.md is unchanged.

**Rules kept.** The Original preset maps to `gpu_gfx_original()`: scale 1, no
enhancement, an identity post chain, and `gpu_read_output` is then `gpu_read_display` bit
for bit. Every option is a toggle on top. No option touches the GS model, the game or the
virtual clock: they act on how primitives are rasterised and textured on the GPU (scale,
texture filter, anisotropy) or on the presented image only (everything else). The run hash
(`display_hash_every`) always folds the display itself, never the post-processed frame. What
the CPU can see of drawn memory (store-image readbacks, screen captures) is the written-back
render targets: at scale > 1 the sub-sample `(s/2, s/2)` ("Upscaling"), and with the
texture filter override or anisotropy the 3D pixels as drawn. Game logic does not read
those pixels back in the parts reached so far (TITLE, NORMAL story screen).

| Setting | Values (Original first) | Where | Live |
| --- | --- | --- | --- |
| `graphics.internal_res` | native, 2x..8x, window | `gpu_set_scale` | yes |
| `graphics.antialiasing` | off, fxaa, ssaa2, ssaa3, ssaa4 | scale x N + post | yes |
| `graphics.downsample` | box, bilinear, bicubic, lanczos | post (SSAA, any minification) | yes |
| `graphics.texture_filter` | original, bilinear, nearest | `gpu_enhance`, draw shader | yes |
| `graphics.anisotropic` | off, 2x..16x (default 16x) | `gpu_enhance`, draw shader | yes |
| `graphics.gamma`, `graphics.brightness` | 1.0 | post, final pass | yes |
| `graphics.sharpen` | 0..1 (0) | post | yes |
| `graphics.output_filter` | off, scanlines, crt | post, at the window resolution | yes |
| `graphics.bloom`, `depth_of_field`, `motion_blur` | original, enhanced, off | `gpu_enhance.fx` (plumbing only) | - |
| `display.scale` | linear, nearest, integer, stretch | present scaling (host), post upscale filter | yes |
| `display.frame_rate` | original, 30, 60, 120, 144, uncapped | runtime: presentation cap | yes |
| `display.vsync`, `window_mode`, `monitor`, `width/height` | | host (docs/HOST.md) | yes (display trial) |

### Internal resolution (live)

`gpu_set_scale(r, s)` flushes, writes every render target back to the mirror, destroys the
targets and the display surfaces, and changes the factor; targets reload from local
memory at the new scale on their next use (one field of intermediate buffers at native
detail; local memory is exact throughout). The derived batch constants carry the scale, so
the batch key is reset. The runtime calls it between fields only. "window" picks the
smallest factor whose height reaches the window rectangle (`gpu_gfx_scale`: 960 px for 448
lines → 3x; on a 16:9 canvas the runtime passes the canvas width converted to rows when it
is larger, docs/WIDESCREEN.md), times the SSAA factor, capped at 8x (the SSAA factor drops first). A forced
scale (`cfg.gpu_scale`, `$RG_GPU_SCALE`) wins over the setting. `gpu.gfx.internal_res`
changes 1 → 2 → 3 → 1 → 4 in the middle of a stream: every sub-sample of whole-pixel
content equals the reference, and local memory is identical after the changes.

### Output post chain (`gpu_read_output`, `gs_post.hlsl`)

Presentation only. With a non-identity `gpu_post` the display is composed at native x
scale (as `gpu_read_display`) and then, on the GPU:

1. **SSAA**: resampled down by the SSAA factor with `downsample` (box = exact area
   average; tent, Mitchell bicubic and Lanczos-2 widen with the ratio).
2. **FXAA** (own FXAA-style pass: luma edge test, orientation from second differences,
   edge-end search up to 8 steps, sub-pixel blend) and **sharpening** (contrast-adaptive
   unsharp mask over the cross neighbourhood, clamped to its min/max: no halos).
3. **To the window rectangle** (`out_w x out_h`, from `rg_fit_rect` with the host's
   scaling mode): only when the frame is larger than it (a proper minifying filter instead
   of the presenter's bilinear) or an output filter needs the final pixel grid. Upscaling
   uses the scaling mode's filter (nearest; integer = sharp bilinear; else bilinear).
   Otherwise the presenter scales as before.
4. **Final pass** into RGBA8: brightness, gamma, then scanlines (a Gaussian beam per
   source line, wider for bright lines) or CRT (scanlines + an aperture-grille mask with
   brightness compensation). Scanlines fade in between 1 and 2 output rows per line.

Intermediates are RGBA16F; the result is read back like the display (the read-back
presenter, "Presentation"). MSAA is not offered: coverage of exact triangles is decided in
the pixel shader, which hardware multisampling would not see; SSAA through the internal
resolution covers it.

### Texture filtering and anisotropy (`gpu_enhance`, `D[11]`)

`DrawCB D[11].x` carries the override (bits 0-1), the anisotropy cap (bits 4-8) and
`GE_ORDINARY` (bit 12); 0 for Original, so the draw shader takes exactly the old path.
The core sets it per batch only when the texture is **ordinary memory**: not sampled
directly from a target and no live render target in the batch's read set that a GPU
draw wrote since those pages were last uploaded (`tex_pages_ordinary`, renderer page set
`drawn`; 2026-10-24: page overlap alone also caught textures uploaded into a slot a
short-lived target had covered; `RG_NR_TEXRT=overlap` = the old rule). `RG_NR_FILTLOG=file`
logs per textured draw the filter choice and whether the texture came from a target or
the 1x mirror (`tools/native/filtlog.py` summarises it; native device since checkpoint 12:
`dir 5` = a live target of another format sampled through a reinterpreted copy, `RG_NR_REINT=2`,
and `I` lines = a target bound over another format's filled at the internal resolution,
docs/NATIVE-RENDER.md "Checkpoint 12"). Render-target
reads (bloom/DOF passes, the flip copy, CLUT tricks, Z reads) keep the GS filter, and the
shader also leaves **sprites** (2D UI, text, full-screen passes) and lines alone, so the
options act on 3D triangles.

* **Texture filter**: bilinear forces MMAG linear and MMIN nearest → linear (per mip
  mode: nearest-mip → linear-mip); nearest does the opposite. Mip level selection (the GS
  LOD from Q) is unchanged.
* **Anisotropic**: on exact-triangle devices the triangle record gives the texel-space
  gradients per target pixel (analytic: edge-function derivatives, perspective via the
  quotient rule). At the GS-chosen level, taps are spread over the footprint
  parallelogram: along the major axis as many as its length in level texels (up to the
  setting), across the minor axis too when that also exceeds a texel (unmipmapped
  textures, or a GS LOD finer than the footprint), 2 x the setting in all. A footprint
  within one texel is the plain GS sample. Limits: only where the GS filters bilinearly
  (after the override) and samples ordinary memory; no effect on the float-triangle path
  (no gradients); the GS LOD itself (depth-based, from Q) is kept, so mipmapped textures
  keep their level choice and the taps fight the aliasing that choice leaves; taps beyond
  the batch's read set make the texture's whole page set current first.

### Screen effects (`graphics.bloom`, `depth_of_field`, `motion_blur`)

Plumbing only: the settings reach `gpu_enhance.fx[GPU_FX_*]` and `gpu_core.cpp` has the
hook, `effect_class(r, g)`, called for every batch before it is drawn. It returns -1 (no
class) for now, so every mode draws the original and the settings stay flagged planned.
What it needs, game side: which call sites/buffers form each effect (the field renderer's
bloom and DOF chains are not reached yet: GameMode stays -1, BRINGUP.md), recorded with
`RG_GS_REC` and identified by their FRAME/TEX0 pairs (the down/up-sample chain over the
512x448 buffer, the Z-as-colour mask) or, better, tagged from the game code (a marker
register write around the pass). With a class: "off" skips the pass's batches (the
target keeps the pre-effect image), "enhanced" draws its intermediate buffers at the
internal resolution instead of their native size (they already sample upscaled sources
directly).

### Display (host)

`display.window_mode` borderless uses SDL's desktop fullscreen; exclusive picks the display
mode closest to `display.width x height` (`SDL_GetClosestFullscreenDisplayMode`) and falls
back to borderless; `display.monitor` moves the window (and fullscreen) to that display
(`rg_host_set_monitor`, `rg_host_set_fullscreen_mode`). VSync is the renderer's.
`display.frame_rate` caps how often the runtime presents (wall clock); fields keep running
on the virtual clock, so 120/144/uncapped do nothing more than "original" until the
unlocked frame rate (PLAN.md) exists.

### Tests (`ctest -L settings`, also `-L gpu`)

| Test | Checks |
| --- | --- |
| `gpu.gfx.original` | the Original preset through the registry: `gpu_gfx_original`, scale 1, identity chain; a mixed scene (nearest/bilinear/perspective triangles, a flat triangle, a sprite) through `gpu_read_output` is bit-exact with the reference, local memory identical; the default preset is not Original |
| `gpu.gfx.settings_map` | each graphics setting moves `gpu_gfx` off Original (downsample alone does not); scale math (4x x SSAA4 → 8x with SSAA 2; window 960/448 → 3, 896 → 2, headless → 1); the renderer settings are no longer flagged planned |
| `gpu.gfx.internal_res` | live scale changes mid-stream (see above) |
| `gpu.gfx.texture_filter` | bilinear on a nearest state: 4,477 px change, >10 colours; nearest on a bilinear state: 2 colours; same-mode overrides change nothing; a sprite and a render-target read are untouched (local memory exact) |
| `gpu.gfx.anisotropic` | a receding striped plane: magnified rows unchanged, far rows 4,130 px changed, horizontal high-frequency energy 31.6 → 20.0; a 1:1 mapping unchanged |
| `gpu.gfx.ssaa` | SSAA 2 (box/bilinear/bicubic/Lanczos) and 4 (box): native-size output, differences only within 2 (3) px of an edge, flat areas exact (box) / ±1 |
| `gpu.gfx.fxaa` | only edge pixels change (614) |
| `gpu.gfx.sharpen` | changes the soft transitions, never beyond the neighbourhood range, flat rows unchanged |
| `gpu.gfx.color` | gamma 2.0 / 0.6, brightness 1.3 per formula ±1 |
| `gpu.gfx.output_filter` | scanlines and CRT at 3x: line centres brighter than the gaps, the CRT mask period; without an output filter a larger window is left to the presenter |
| `gpu.gfx.resample` | a 4x frame to a 2x window with each filter (flat colours ±1); nearest 2x blocks |
| `gpu.gfx.game_replay` | the 4 game recordings with the Original preset applied through the settings and the display read through `gpu_read_output`: exact (as `gpu.game_replay`) |

All green on WARP and on the RTX 3080 (`RG_GPU_HW=1`), with `-L "gpu|gs|settings|host|runtime"`
(178 tests at the time, `control_cover` skipped on hardware as before; 181 since "Performance").

### Cost per field (RTX 3080)

`rg-gpu-tests gfxbench out/p3/gsrec` (`RG_GPU_HW=1`, best of 5): the four recordings
replayed through the renderer alone (no reference), every field presented through the
chain for a 1280x960 window, mean ms per field including the GS replay and the read-back.
The recordings are 2D (title, logo movie, story screen), so the texture filter and
anisotropy have nothing to act on there (their cost on 3D scenes is still to measure).
Raw output: `out/gfxset/bench_rtx3080.txt`.

| Configuration | ms/field | vs Original |
| --- | --- | --- |
| Original (x1) | 3.65 | |
| internal x2 / x3 (match 1280x960) / x4 | 4.76 / 6.90 / 9.89 | +1.1 / +3.2 / +6.2 |
| internal x6 / x8 | 17.9 / 29.5 | +14.3 / +25.8 |
| SSAA 2 (x2 → native, box) / SSAA 4 | 4.51 / 7.96 | +0.9 / +4.3 |
| x3 + SSAA 2 (x6 → 1280x960, bicubic) | 16.8 | +13.1 |
| x4 → 1280x960 window, box / Lanczos | 8.45 / 8.68 | +4.8 / +5.0 |
| FXAA (x1) / FXAA at x3 | 3.67 / 6.88 | +0.02 / +3.2 (x3 itself) |
| sharpen 0.5 | 3.69 | +0.04 |
| gamma + brightness | 3.64 | 0 |
| scanlines / CRT (to 1280x960) | 4.14 / 4.28 | +0.5 / +0.6 |
| texture filter bilinear / nearest, anisotropic 16x | 3.67 / 3.59 / 3.59 | 0 (no 3D in the recordings) |
| everything (x6, SSAA 2, FXAA, sharpen, aniso, CRT) | 17.3 | +13.6 |

Noise is about ±0.1 ms. The post passes themselves are cheap (≤ 0.6 ms at 1280x960); the
large costs are the internal resolution (drawing, the flip copy and the display at x6/x8
move 8-15 MB per pass) and the read-back of large frames (the present path still reads
the display back: "Presentation"; the zero-copy path would remove that part).

### Open items

* **Serial-batch cost: done** ("Performance"): the loading screen went from 240-920
  batches per field to 3.5 (ordered blending, high-byte texels, CLUT reloads, cheaper
  batches). Left: GPU fill of its CLUT sprites at x3 (~9 ms per field).
* Screen effects: the classification above (game side).
* Texture filter / anisotropy cost and look on real 3D (field, battle) once the port
  reaches it; a per-texture exclusion list if the forced bilinear blurs something that
  must stay sharp (3D text, sprites drawn as triangles).
* Zero-copy presentation would let the post chain run at window size without read-back.
* `display.frame_rate` above 60 and "uncapped" wait for the unlocked frame rate.
* The software GS path (no `--gpu`) has no post chain; the settings only take effect with
  the GPU renderer (the frame cap and window settings work either way).

### Checkpoint

* 2026-10-12 (`build/gpuperf-i686`, "Performance"): ordered blending, high-byte texels,
  CLUT batching, shadow state; `gfxbench DIR perf`; `scene.ordered`, `control_ordered`;
  3 loading-screen recordings. `-L "gpu|gs|settings|host|runtime"` 181/181 (control_cover
  skipped on hardware) on WARP and on the RTX 3080, `-L gpu` also with `RG_GPU_NO_ROV=1`.
  The cost table below predates the 3 new recordings.
* 2026-10-12: started in `build/gfxset-i686`: settings → `gpu_gfx`, live scale, post chain,
  texture filter / anisotropy, screen-effect hook, host monitor / exclusive fullscreen,
  frame cap; 12 `gpu.gfx.*` tests. `-L "gpu|gs|settings|host|runtime"` 178/178 on WARP and
  on the RTX 3080; bench above. Windowed demo shots: `out/gfxset/demo_*.png`
  (`rg-host-demo --gpu --preset original --set graphics...`), crops `crop_*.png`.

## Known gaps

* **Z32 above 2^24** loses its low 8 bits where drawn (D32_FLOAT). Pixels loaded but not
  drawn are preserved bit-exactly on write-back. The game's 3D uses Z24.
* **Blending is always shader-side.** With ROVs (D3D11.3) overlapping blended
  primitives share a batch, except under a depth test that can fail; there, and on a
  device without ROVs, blended batches still split wherever primitive bounding boxes
  overlap, with a destination snapshot each. Fixed-function blending is not used: the
  GS equation truncates `(A-B)*C >> 7` (floor of negative terms) and UNORM blending
  rounds, so only the additive/subtractive cases with precomputed terms would be exact,
  and the ordered view already covers them.
* **Textured draws that cannot sample directly** (format reinterpretations that need the
  swizzled bytes: CT32 as T8/T4/T8H/CT16, Z as colour or colour as Z, CLUT formats,
  mipmaps, Z32, the depth buffer bound in the same draw, a texel rectangle reaching past
  the target's rows) write back the dirty targets their read set overlaps and sample the
  native-resolution mirror, so at scale > 1 they see native detail (results still match
  the reference). A depth pass that reads the Z24 buffer as CT32/T8H stays native; a
  direct Z24-as-CT32 path would need the block arrangement remapped per texel (possible:
  Z and CT differ only by `blk ^ 24` within a page). Triangles and lines sampled
  directly at scale > 1 filter the upscaled texels with their interpolated coordinates;
  their point sampling is not anchored to the reference's texel (sprites are).
* **Upscaled results differ from the reference by design** where a magnifying or
  downsampling pass crosses a hard edge of an upscaled source (measured above). The
  write-back keeps one sub-sample per pixel, so local memory after such a pass is the
  sub-sample `(scale/2, scale/2)`, not the box-filtered value; CPU captures of an
  upscaled bloom/DOF result therefore differ from the reference by up to half the edge
  step there.
* **A directly sampled target overlapped by another live target** (the FRAME/ZBUF
  partner case of the next item) falls back to the mirror.
* **FRAME and ZBUF on the same pages in one draw** go through the software rasterizer
  (exact, tested). A colour target and a depth target whose *target-level* page sets
  overlap while the scissor keeps the draws apart (a colour target grown over memory now
  used as Z) are both live for the draw and written back and reloaded around it
  (checkpoint 4; exact, `scene.alias_pages`); not seen in the game's recordings.
* **Targets alias by page.** Two live targets overlapping in memory cannot coexist: the
  older one is written back and dropped. A game that ping-pongs two overlapping formats
  over the same pages pays a write-back + reload each time.
* Draws beyond `FBW*64` columns are clipped (the GS would wrap into the next page row).
* Presentation reads the frame back (see above); no zero-copy path yet.
* Not implemented, as in the reference: AA1, PRIM.FIX, MTBA, FINISH timing, SIGNAL stall.
* Upscaled lines and points stay one native pixel wide.
* Windows/D3D11 only. The backend interface (`GpuBackend`, 12 methods) is the seam for a
  Vulkan/Metal backend; the shaders would need porting from HLSL.
* Single-threaded, synchronous: draws are submitted when a batch flushes, and a CPU read
  of drawn memory stalls on the GPU (since checkpoint 4 only until the copy queued after
  the region's last write, for regions read every frame; reads of bits the CPU wrote
  itself do not stall).
* Internal resolution x8 does not run in the i686 build: the D3D allocations push the
  game's RAM above 0x10000000 (a runtime/address-space limit, not the renderer's).
