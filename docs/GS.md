# GS model (`src/ps2/gs`)

The Graphics Synthesizer as a software model: GIF front end, register file, 4 MB local
memory with the real swizzles, transfers, CLUT, a **software reference rasterizer**, and the
display read-out. It is the oracle for the GPU renderer (PLAN.md D3) and for tests. It
favours correctness over speed: a full-screen 640x448 bilinear CLUT sprite takes about
0.15 s.

It was written from public descriptions of the hardware (the GS User's Manual and its
register and memory-arrangement figures). No PCSX2 or DobieStation code was used (PLAN.md
D7). No third-party code is vendored.

Build and test (i686 toolchain, see TOOLCHAIN.md):

```
cmake --build <builddir> --target rg-gs-tests
ctest --test-dir <builddir> -L '^gs$'      # 41 tests, 2 of them WILL_FAIL controls
```

## Interfaces (`gs.h`)

| Call | Purpose |
| --- | --- |
| `gs_create` / `gs_destroy` / `gs_reset` | Lifetime. A reset (or CSR.RESET) clears registers, CLUT and paths, but keeps VRAM. |
| `gs_gif_write(gs, path, qwords, nqw)` | **GIF input.** Takes 128-bit little-endian qwords for PATH1, PATH2 or PATH3. See the contract below. |
| `gs_vu1_gif_sink` | Has the exact `vu_gif_sink_fn` signature (`src/ps2/vu/vu.h`). Set `vu1->gif_sink = gs_vu1_gif_sink; vu1->gif_user = gs;` to send XGKICK packets to PATH1. |
| `gs_vif1_gif_sink` | Has the exact `vif_gif_sink_fn` signature (`src/ps2/vif/vif.h`). Sends VIF1 DIRECT/DIRECTHL data to PATH2. |
| `gs_write_reg(gs, addr, v)` | Writes a general register. This is the same path an A+D write takes. |
| `gs_write_priv` / `gs_read_priv` | Privileged registers, by EE physical address (`0x12000000`…, `0x12001000`…). Reading CSR returns event bits, FIELD, and FIFO-empty. |
| `gs_vsync` | Call at VBlank start. Toggles CSR.FIELD when SMODE2.INT is set, and raises VSINT. |
| `gs_fifo_pending` / `gs_read_fifo` | Local→host data, produced when TRXDIR=1 is written. This is what `sceGsExecStoreImage` needs. |
| `gs_pixel_addr` / `gs_read_pixel` / `gs_write_pixel` | Swizzled access for each PSM. Used by tools, tests and the renderer's upload path. |
| `gs_read_display(gs, field, out, cap, &w, &h)` | What the PCRTC shows, as RGBA8. Use it to present frames and take screenshots. |
| `gs_read_rect_rgba` | One buffer rectangle as RGBA8. Use it for debug dumps. |
| `gs->irq` / `irq_user` | Called on SIGNAL, FINISH or VSINT when IMR leaves that event unmasked. |
| `gs->sw_raster = 0` | Turns rasterization off and keeps everything else: state, transfers, CLUT. The GPU backend runs this way. `sw_raster` is read after the `draw` hook, so a renderer may set it to 1 inside the hook to have the software rasterizer draw that one primitive into `gs->vram` (the GPU renderer does this for FRAME and ZBUF on the same pages, GPU.md "FRAME and ZBUF on the same pages"). |
| `gs->hooks` | Renderer hooks, all NULL by default: `draw` gets every resolved primitive before the software rasterizer; `mem` announces local-memory reads (local→host, local→local source, CLUT loads) and writes (host→local, local→local destination) as buffer rectangles. The GPU renderer (GPU.md "Hooks") keeps its copies coherent through them. |
| `gs->stats` | Primitive counts by type, fragments tested and written, CLUT loads, transfer pixel counts, and writes to unknown registers. |
| `gs->rec` / `rec_user` | Input recorder, NULL by default: called before the model acts on every input from outside: `gs_gif_write` (path, qwords), `gs_write_priv`, `gs_vsync`, `gs_gif_reset`, `gs_read_fifo` (bytes asked for). See "Recordings". |
| `gs_rec_snapshot` / `gs_rec_event` / `gs_rec_open` / `gs_rec_load` / `gs_rec_next` / `gs_rec_apply` (`gs_rec.c`) | Write and replay a recording. |

The struct is public on purpose, so the GPU backend can read the decoded state (`reg[]`,
`preg[]`, `clut[]`, the vertex queue) without accessor churn.

### Recordings (`gs_rec.c`)

A recording is a snapshot of the whole model followed by the inputs, so a stretch of the
real game replays exactly through any renderer (`rg-gpu-tests replay`, GPU.md "Real game
validation"). File: `RGGSREC1`, `sizeof(gs_vertex)`, then reg[128], preg[32], CSR
events and FIELD, the PACKED Q, the vertex queue, CLUT and CBP0/1, the transfer state
(direction, position, carry), the unread FIFO bytes, each path's tag state with its queued
data, the bus owner, the open host→local rectangle of the hooks, and the 4 MB of local
memory; then events `{u32 kind, u32 a, u64 v, u32 bytes, data}` (kinds `GS_REC_*`). The
snapshot must be taken with `gs->vram` current (`gpu_sync` first) and loaded before a
renderer attaches. The runtime writes one with `RG_GS_REC` / `RG_GS_REC_FIELDS`
(RUNTIME.md "GS renderer"); `tools/gsrec_dump.py` lists one as text (GIFtags, A+D and
PACKED register writes). Recordings of the game are game data: they stay under `out/`.

### GIF input contract

- A qword is 16 bytes, exactly as it sits in EE or VU memory. The host buffer doesn't
  need to be aligned.
- One call can hold several packets. It can also stop in the middle of a packet, or in
  the middle of a GIFtag's data, but always on a qword boundary. Each path keeps its tag
  state between calls.
- **Arbitration.** A path that has read a GIFtag whose packet hasn't reached EOP owns the
  bus. Data that arrives on another path meanwhile is copied into that path's queue. When
  the owner finishes its packet, queued paths run in priority order PATH1 > PATH2 > PATH3.
  Everything is synchronous: when `gs_gif_write` returns, every runnable packet has been
  drawn.
- Not modelled: PATH3 IMAGE intermittent mode (slices interrupted by PATH1/2), the
  MSKPATH3 / M3R / M3P masks (those belong to the VIF/DMA model), and FIFO back-pressure.

## Coverage

**GIF.** PACKED, REGLIST and IMAGE (FLG=3 is treated as IMAGE).
- PRE/PRIM, NLOOP=0, NREG=0 (meaning 16), EOP.
- REGLIST pads an odd item count to a full qword. A+D and NOP descriptors are ignored in
  REGLIST.
- PACKED decodes PRIM, RGBAQ, ST, UV, XYZF2/XYZ2 (ADC=1 selects XYZF3/XYZ3), FOG,
  TEX0/CLAMP, XYZF3/XYZ3, A+D and NOP.
- PACKED Q is latched by ST, reset to 1.0 at each GIFtag, and used by the next RGBAQ.

**Registers.**
- Both contexts: FRAME, ZBUF, TEX0/1/2, CLAMP, XYOFFSET, MIPTBP1/2, SCISSOR, ALPHA, TEST
  and FBA.
- Global: PRMODECONT/PRMODE, TEXCLUT, SCANMSK, TEXA, FOGCOL, TEXFLUSH (no-op), DIMX,
  DTHE, COLCLAMP and PABE.
- Transfers: BITBLTBUF, TRXPOS, TRXREG, TRXDIR and HWREG.
- Events: SIGNAL (ID/mask into SIGLBLID), FINISH and LABEL.
- Privileged: PMODE, SMODE2, DISPFB1/2, DISPLAY1/2, BGCOLOR, CSR (events, FIELD, RESET)
  and IMR. The rest are stored only.
- Writes to an undefined register are counted in `stats.unknown_reg_writes`.

**Vertex queue.** Queue depth is 1, 2, 2, 3, 3, 3 or 2 for POINT, LINE, LINESTRIP,
TRIANGLE, TRISTRIP, TRIFAN and SPRITE.
- Strips keep the last vertices; fans keep the first vertex and the last one.
- XYZ3/XYZF3 advance the queue without drawing.
- A PRIM write empties the queue.
- XYZF2/3 also latch FOG.

**Memory.** 4 MB. Exact page/block/column arrangement for PSMCT32, 24, 16 and 16S; PSMT8,
T4, T8H, T4HL and T4HH; and PSMZ32, Z24, Z16 and Z16S.
- The block pointer adds within a page (`bp + 32*page + block`) and wraps at 4 MB.
- Coordinates wrap at 2048.
- T8 and T4 use `bw/2` pages per row.

**Transfers.**
- Host→local takes IMAGE data or A+D HWREG writes. CT24 is packed 3 bytes per pixel, and
  pixels can straddle qwords. T4 sends the low nibble first. Extra data is dropped.
- Local→host is padded to a whole qword.
- Local→local honours TRXPOS.DIR (the order matters when rectangles overlap), and copies
  raw pixel bits.

**CLUT.**
- Loads are triggered by TEX0_n and TEX2_n, and only for indexed PSMs.
- CLD 0–5 use the CBP0 and CBP1 comparison registers.
- CSM1: T8 swaps entries 8–15 with 16–23 within each group of 32, and T4 uses an 8x2
  arrangement, both in a 64-px-wide buffer.
- CSM2: one row at TEXCLUT (CBW, COU*16, COV).
- CSA offsets the start.
- The buffer is 512 16-bit cells. A CT32 entry keeps its low half in cells 0–255 and its
  high half in cells 256–511, so CT16 and CT32 loads alias the way they do on hardware.

**Texturing.**
- Every texture PSM, including Z formats read as textures. TEXA expands alpha for 24-bit
  and 16-bit texels; AEM applies only when the A bit is 0.
- TFX MODULATE, DECAL, HIGHLIGHT and HIGHLIGHT2, each with TCC.
- CLAMP REPEAT, CLAMP, REGION_CLAMP and REGION_REPEAT. Each bilinear tap wraps
  independently (see memory note `gs-texture-wrap`).
- TEX1: LOD = `(log2(1/|Q|) << L) + K`, or `K` when LCM=1. MMAG/MMIN cover all six
  filters, MXL up to 6, and mip levels come from MIPTBP1/2.

**Rasterizer.**
- Points, lines and line strips. Triangles, strips and fans. Sprites.
- Flat or Gouraud colour, with XYOFFSET, scissor and SCANMSK.
- STQ texturing with a per-pixel divide (perspective-correct), or UV texturing.
- Pixel pipeline, in this order: texture function → fog → alpha test (8 methods, AFAIL
  KEEP/FB_ONLY/ZB_ONLY/RGB_ONLY) → destination alpha test (DATE/DATM) → depth test
  (NEVER/ALWAYS/GEQUAL/GREATER) → blend `((A-B)*C>>7)+D` with PABE → dither (16-bit
  frames) → COLCLAMP clamp or wrap → FBA → FBMSK.
- ZMSK, with Z clamped to the Z format's range.
- Frame formats: CT32, CT24 and CT16/16S. Z formats: Z32, Z24 and Z16/16S.

**Display.**
- Two read circuits, each with DBX/DBY, MAGH/MAGV and DX/DY placement.
- Merge with ALP (MMOD=1) or circuit-1 pixel alpha (MMOD=0); SLBG selects the background.
- Interlace: the FIELD and FRAME modes are described below.

## Rasterization rules, and the accuracy caveats

These rules are this model's. The tests hand-check every one of them. Where the hardware
is known to differ in rounding, the model **approximates**, and the GS-dump validation
below exists to settle those cases.

1. **Coverage.** Pixel centres sit at integer coordinates; vertices are in 12.4 window
   coordinates after XYOFFSET.
   - Triangles use a top-left rule.
   - Sprites are half-open, covering `x0 <= 16*px < x1`, so (0,0)-(640,448) covers exactly
     640x448 pixels.
   - Points draw at `ceil(x/16), ceil(y/16)`.
   - Lines are a DDA on the major axis, half-open at the end, with the minor coordinate
     rounded to nearest. GS line rasterization (diamond-exit-like behaviour, AA1) is
     **not** bit-exact here.
2. **Interpolation** (triangles, lines) uses doubles, truncated per fragment. Hardware
   uses fixed-point DDAs, so Gouraud colours, Z, fog and UV can differ by 1 LSB at some
   pixels. Z clamps at the format maximum. Triangles evaluate `a + (b-a)*w1 + (c-a)*w2`,
   so an attribute equal at all three vertices (a constant-Z triangle, an even Gouraud
   colour) is exactly that value at every fragment; the `a*w0 + b*w1 + c*w2` form used
   before landed one ulp low and truncated to z-1 at scattered pixels.
3. **Sprite attributes.** Colour, Z, fog and Q all come from the second vertex. S and T
   are interpolated linearly across the rectangle (double). **U and V (FST=1) use a
   fixed-point DDA** (`gs_sprite_uv_step` / `gs_sprite_uv_at` in `gs.h`):
   - corners are sorted by position; `c0, c1` are the UV register values (1/16 texel) at
     the low and high corner, `p0 < p1` their 12.4 window coordinates;
   - `step = (c1-c0) * 2^20 / (p1-p0)`, a 16.16 value in 1/16-texel units per pixel,
     truncated toward zero and saturated to int32;
   - pixel `px` samples `floor((c0*2^16 + floor(step*(16*px - p0)/16)) / 2^16)` in 1/16
     texel, i.e. the DDA value at the pixel centre with its fraction below 1/16 texel
     dropped. Stepping one pixel adds exactly `step`.
   - Consequences, each hand-checked in `prim_sprite_uv`: a 1:1 or integer-ratio mapping
     is exact on every pixel (448 rows of V 0..7168 sample rows 0..447; the double
     formula used before read texel row y-1 on rows 61, 115, 122, 230, 237, 244 and 251);
     a step that is not a whole 16.16 value is truncated, so a pixel whose exact U falls
     on a texel boundary can sample the texel before it (2 texels over 6 px: px 3 samples
     texel 0); a mirrored sprite (U 64 -> 0) samples texel 64 at its first pixel (clamped
     to 63 under CLAMP).
   - The truncation direction and the 16 fraction bits are this model's choice; the
     hardware's exact step precision is unverified (a GS dump of a scaled UV sprite
     settles it, see below).
4. **Bilinear** samples at `u - 0.5` with a 4-bit fraction, rounding taps down. A UV
   that lands exactly on a texel boundary (with no +8 offset) blends 50/50, as on
   hardware. The hardware's exact rounding of the filter weights is unverified.
5. **Mipmapping.** LOD is computed per fragment from Q. MTBA (automatic MIPTBP) is not
   implemented. For REGION_CLAMP, the region bounds are shifted right by the level.
   (The town census found MXL=0 everywhere, but `SaveSlotListRefreshDetail` writes
   TEX1=0xEA, which is MXL=2 with MMIN=3.)
6. **Destination alpha.** For CT24, Ad reads as 0x80 and DATE always passes. For CT16, Ad
   is 0x80 or 0 depending on the A bit.
7. **Dithering** is applied only to 16-bit frame buffers.
8. **Fog** is `(F*C + (255-F)*FOGCOL) >> 8`. It is interpolated under IIP=1; otherwise
   the provoking vertex's value is used.
9. **Not implemented:** AA1 antialiasing (the census shows `GsPktSetAntialias(1)` at 2
   sites; it is ignored), PRIM.FIX, the FINISH-waits-for-drawing timing (everything is
   instantaneous), the SIGNAL stall-on-pending behaviour, EXTBUF/EXTDATA feedback write,
   and HSINT/EDWINT.
10. **Display.** In interlaced FRAME mode (SMODE2 INT=1 FFMD=1), DH counts two display
    lines per buffer line. libgraph's `sceGsSetDefDispEnv` writes `DH = 2*height-1`
    there, and `height-1` in FIELD mode, which is what this model assumes. A FIELD-mode
    field is every other line. In FRAME mode each field shows every line. DY offsets use
    the same vertical unit.
    - The merge uses `ALP/255`. In MMOD=0 it uses circuit-1 alpha × 2 clamped to 255, so
      0x80 means opaque.
    - The game's own `GsDbufPutEnv_144150` setup is covered by a test. That setup is PMODE
      0x7F23, circuit 1 at DBY=1 with DH-1, and circuit 2 at DBY=0: a two-line vertical
      flicker filter at ALP 0x7F.
    - **Open:** the exact vertical unit, and the merge rounding, both need a real-hardware
      or PCSX2 capture.
11. **CSR.** The ID/REV fields read as 0x55 and 0x1B, which are nominal values. The FIFO
    always reads as empty.

## Test map (`tests/gs`, `ctest -L gs`)

| Test | What is checked |
| --- | --- |
| `swizzle_tables` | Every pixel of a 256x300 buffer, for all 13 PSMs and two base pointers (page-aligned and odd), against a reference typed in from the manual's arrangement figures as literal tables. The implementation uses bit formulas instead. |
| `swizzle_bijection` | Every pixel of a page maps to a distinct slot, and a page is exactly 8 KB. |
| `xfer_*` | Upload → per-pixel placement → readback round trip, for every PSM. H and 24-bit formats don't touch other bits. 24-bit data split across qwords and packets. HWREG through A+D. Local→local, including overlap DIR and T4. CT32/T8/T8H aliasing. |
| `clut_*` | CSM1 T8 swap, CSM1 T4 with CSA in CT16 and CT32, TEXA/AEM, CSM2, CLD 0–5, TEX2. |
| `blend_presets` | All 12 entries of the census blend table `D_00449EF0` on a known Cs/Cd pair, with hand-computed results. |
| `blend_misc` | COLCLAMP wrap, C=Ad, PABE (both sides), FBA, FBMSK, CT24 and CT16 frames. |
| `depth_matrix` | Z32/Z24/Z16 × ZTST × ZMSK × (below, equal, above). Z clamping. |
| `alpha_matrix` | 8 ATST × 3 values, 4 AFAIL modes, DATE/DATM. |
| `dither_fog`, `tex_functions` | DIMX ±, fog arithmetic, latched FOG, TFX × TCC. |
| `prim_sprite_uv` | Sprite UV DDA (rule 3): the 448-row 1:1 mapping, 3:1 minification on 100 px, step truncation at a texel boundary, a mirrored sprite, half-pixel corners given in reverse order, and the two helper functions directly (including saturation). |
| `prim_*` | Golden masks drawn by hand: sprites (including half-pixel and reversed corners), triangles (both windings, exact 4x4 strip tiling), Gouraud and flat, lines, point, queue semantics, the 4 wrap modes, bilinear, perspective STQ (a value affine interpolation gets wrong), mip selection, scissor, XYOFFSET, PRMODECONT, context 2, SCANMSK, and a full 640x448 frame. |
| `gif_*` | Packed field extraction, Q latch and reset, ADC, REGLIST padding, NREG=0, NLOOP=0, split packets, arbitration order, both sink adapters (whose types are compile-checked against vu.h/vif.h), SIGNAL/FINISH/LABEL/IMR/IRQ, FIELD toggling, RESET. |
| `display_*` | One circuit with DBX/DBY, the merge modes, FIELD/FRAME interlace, the game's 0x7F23 anti-flicker setup, a CT16 frame buffer. |
| `swizzle_control`, `blend_control` | **Deliberately wrong** references, registered `WILL_FAIL`. They prove the checks are armed. |

## What we need from PCSX2 to validate further

PCSX2 is used only as a trace tool (D7). Its GS dumps (`.gs`, made with the "Save GS
dump" hotkey) record the GIF transfers, privileged register writes, VSyncs and a VRAM
snapshot. A replay harness would feed those into `gs_gif_write` / `gs_write_priv` and
compare VRAM and display output against PCSX2's **software** renderer screenshots,
captured at native resolution. The memory note `gs-texture-wrap` explains why window
captures can't be trusted for fine detail. The dumps needed:

1. **Title screen and menus.** These use sprites, the CT32 frame, blend presets 1, 2 and
   9, CLUT T8/T4 fonts, CSM1, TEXA, and the 0x7F23 display merge.
2. **A town scene.** This covers VU1 XGKICK geometry (triangle strips, STQ), REPEAT and
   CLAMP wrap, bilinear filtering, Z24 GEQUAL, fog, and the TEX1=0xEA mip path if it is
   hit.
3. **A battle with effects.** This covers additive and subtractive presets 3, 7 and 10,
   PABE, destination alpha (`GsPktSetDestAlphaTest` at 19 sites), FBMSK passes, and the
   bloom, blur and depth-of-field local→local copies.
4. **A frame that reads back** through `sceGsExecStoreImage`, from `GfxEndFrame_141c20`
   or `GsDownloadImage_140f20`. This validates local→host byte order.
5. **Interlace and field behaviour.** Two consecutive frames, to pin down the FRAME-mode
   vertical unit and the merge rounding (caveat 10).
6. **A scaled UV sprite** (any bloom/blur downsample or upsample pass, e.g. in dump 3),
   point-sampled, whose step is not a whole 16.16 value. Its per-pixel texels pin down
   the hardware's sprite DDA precision and truncation (rule 3).

Each dump also tells us the GS feature set actually used at runtime. That replaces the
static census's `dyn` rows and decides how much of caveats 1, 2 and 4 the GPU renderer
must reproduce bit-exactly.
