/* SPDX-License-Identifier: CC0-1.0 */
/* PS2 Graphics Synthesizer: GIF front end, register file, 4 MB local memory
 * with the exact block/page swizzles, transfers, CLUT, a SOFTWARE reference
 * rasterizer and the display read-out.  docs/GS.md.
 *
 * Written from public hardware descriptions (GS User's Manual semantics).
 * No emulator code was copied or paraphrased (PLAN.md D7).
 *
 * This is the ORACLE: correctness first, not speed.  The production renderer
 * (GPU, PLAN.md D3) consumes the same register/GIF stream and is checked
 * against this model.
 *
 * ---------------------------------------------------------------------------
 * GIF INPUT CONTRACT (what VIF1/VU1, the DMA model and libgraph feed us)
 *
 *   gs_gif_write(gs, path, qwords, nqw)
 *     path  : GS_PATH1 (VU1 XGKICK), GS_PATH2 (VIF1 DIRECT/DIRECTHL),
 *             GS_PATH3 (GIF DMA channel 2).
 *     qwords: little-endian 128-bit quadwords, 16-byte units, exactly as they
 *             sit in EE/VU memory.  Need not be aligned in host memory.
 *     A call may hold several packets, or end in the middle of one (in the
 *     middle of a GIFtag's data, never in the middle of a qword).  The path
 *     keeps its tag state between calls.
 *
 *   Arbitration: a path that has started a packet (read a GIFtag whose packet
 *   has not reached EOP) owns the bus.  Data written to another path meanwhile
 *   is queued (copied) and runs when the owner finishes its packet, in
 *   priority order PATH1 > PATH2 > PATH3.  All work is synchronous: when
 *   gs_gif_write returns, every packet it could run has been drawn.
 *
 *   Ready-made adapters with the exact sink signatures of the VU/VIF models:
 *     vu1->gif_sink  = gs_vu1_gif_sink;  vu1->gif_user  = gs;   (XGKICK, PATH1)
 *     vif1->gif_sink = gs_vif1_gif_sink; vif1->gif_user = gs;   (DIRECT, PATH2)
 *   The GIF DMA channel (PATH3) calls gs_gif_write(gs, GS_PATH3, ...).
 * ---------------------------------------------------------------------------
 */
#ifndef RG_PS2_GS_H
#define RG_PS2_GS_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GS_VRAM_BYTES (4u * 1024u * 1024u)

enum { GS_PATH1 = 1, GS_PATH2 = 2, GS_PATH3 = 3 };

/* ---- pixel storage modes ---- */
enum {
    GS_PSMCT32 = 0x00, GS_PSMCT24 = 0x01, GS_PSMCT16 = 0x02, GS_PSMCT16S = 0x0A,
    GS_PSMT8 = 0x13, GS_PSMT4 = 0x14, GS_PSMT8H = 0x1B, GS_PSMT4HL = 0x24,
    GS_PSMT4HH = 0x2C, GS_PSMZ32 = 0x30, GS_PSMZ24 = 0x31, GS_PSMZ16 = 0x32,
    GS_PSMZ16S = 0x3A
};

/* ---- general register addresses (A+D / packed / reglist) ---- */
enum {
    GS_PRIM = 0x00, GS_RGBAQ = 0x01, GS_ST = 0x02, GS_UV = 0x03,
    GS_XYZF2 = 0x04, GS_XYZ2 = 0x05, GS_TEX0_1 = 0x06, GS_TEX0_2 = 0x07,
    GS_CLAMP_1 = 0x08, GS_CLAMP_2 = 0x09, GS_FOG = 0x0A, GS_XYZF3 = 0x0C,
    GS_XYZ3 = 0x0D, GS_TEX1_1 = 0x14, GS_TEX1_2 = 0x15, GS_TEX2_1 = 0x16,
    GS_TEX2_2 = 0x17, GS_XYOFFSET_1 = 0x18, GS_XYOFFSET_2 = 0x19,
    GS_PRMODECONT = 0x1A, GS_PRMODE = 0x1B, GS_TEXCLUT = 0x1C,
    GS_SCANMSK = 0x22, GS_MIPTBP1_1 = 0x34, GS_MIPTBP1_2 = 0x35,
    GS_MIPTBP2_1 = 0x36, GS_MIPTBP2_2 = 0x37, GS_TEXA = 0x3B,
    GS_FOGCOL = 0x3D, GS_TEXFLUSH = 0x3F, GS_SCISSOR_1 = 0x40,
    GS_SCISSOR_2 = 0x41, GS_ALPHA_1 = 0x42, GS_ALPHA_2 = 0x43, GS_DIMX = 0x44,
    GS_DTHE = 0x45, GS_COLCLAMP = 0x46, GS_TEST_1 = 0x47, GS_TEST_2 = 0x48,
    GS_PABE = 0x49, GS_FBA_1 = 0x4A, GS_FBA_2 = 0x4B, GS_FRAME_1 = 0x4C,
    GS_FRAME_2 = 0x4D, GS_ZBUF_1 = 0x4E, GS_ZBUF_2 = 0x4F,
    GS_BITBLTBUF = 0x50, GS_TRXPOS = 0x51, GS_TRXREG = 0x52,
    GS_TRXDIR = 0x53, GS_HWREG = 0x54, GS_SIGNAL = 0x60, GS_FINISH = 0x61,
    GS_LABEL = 0x62,
    /* not a GS register: the native renderer's draw marker (docs/NATIVE-RENDER.md
     * "Coexistence"); a write calls hooks.native in GIF order */
    GS_NATIVE_MARK = 0x7E
};

/* ---- privileged registers: physical EE addresses ---- */
enum {
    GS_P_PMODE = 0x12000000, GS_P_SMODE1 = 0x12000010, GS_P_SMODE2 = 0x12000020,
    GS_P_SRFSH = 0x12000030, GS_P_SYNCH1 = 0x12000040, GS_P_SYNCH2 = 0x12000050,
    GS_P_SYNCV = 0x12000060, GS_P_DISPFB1 = 0x12000070,
    GS_P_DISPLAY1 = 0x12000080, GS_P_DISPFB2 = 0x12000090,
    GS_P_DISPLAY2 = 0x120000A0, GS_P_EXTBUF = 0x120000B0,
    GS_P_EXTDATA = 0x120000C0, GS_P_EXTWRITE = 0x120000D0,
    GS_P_BGCOLOR = 0x120000E0, GS_P_CSR = 0x12001000, GS_P_IMR = 0x12001010,
    GS_P_BUSDIR = 0x12001040, GS_P_SIGLBLID = 0x12001080
};

/* CSR event bits (write 1 to clear) */
enum {
    GS_CSR_SIGNAL = 1u << 0, GS_CSR_FINISH = 1u << 1, GS_CSR_HSINT = 1u << 2,
    GS_CSR_VSINT = 1u << 3, GS_CSR_EDWINT = 1u << 4, GS_CSR_FLUSH = 1u << 8,
    GS_CSR_RESET = 1u << 9, GS_CSR_FIELD = 1u << 13
};

/* primitive types */
enum {
    GS_PRIM_POINT = 0, GS_PRIM_LINE = 1, GS_PRIM_LINESTRIP = 2,
    GS_PRIM_TRIANGLE = 3, GS_PRIM_TRISTRIP = 4, GS_PRIM_TRIFAN = 5,
    GS_PRIM_SPRITE = 6
};

/* One queued vertex, as latched at the XYZ write (raw register units). */
typedef struct gs_vertex {
    uint16_t x, y;      /* 12.4 primitive coordinates (before XYOFFSET) */
    uint32_t z;
    uint8_t r, g, b, a;
    float q;            /* RGBAQ.Q */
    float s, t;         /* ST */
    uint16_t u, v;      /* UV, 10.4 */
    uint8_t f;          /* fog */
} gs_vertex;

typedef struct gs_gif_path {
    int in_tag;          /* a GIFtag is being processed */
    int in_packet;       /* packet started, EOP not yet consumed */
    uint32_t nloop;      /* loops remaining */
    uint32_t nreg;       /* 1..16 */
    uint32_t flg;        /* 0 PACKED, 1 REGLIST, 2/3 IMAGE */
    uint32_t eop;
    uint64_t regs;       /* 16 4-bit descriptors */
    uint32_t reg_i;      /* next descriptor index */
    /* bytes queued while another path owns the bus */
    uint8_t *q;
    uint32_t q_len, q_cap, q_off;
    uint64_t packets, qwords;
} gs_gif_path;

/* Counters useful for tests and the later GPU-renderer cross-check. */
typedef struct gs_stats {
    uint64_t prims[8];      /* drawn primitives by type */
    uint64_t pixels_tested; /* fragments reaching the pixel tests */
    uint64_t pixels_written;
    uint64_t clut_loads;
    uint64_t xfer_h2l_px, xfer_l2l_px, xfer_l2h_px;
    uint64_t unknown_reg_writes;
} gs_stats;

typedef void (*gs_irq_fn)(void *user, uint32_t csr_event_bits);

/* ---- renderer hooks (docs/GPU.md "Hooks") --------------------------------
 * A hardware renderer (src/gpu) attaches through gs_state.hooks.  Every hook
 * is optional; with all of them NULL (the default) the model behaves exactly
 * as before.  Local memory stays authoritative in gs->vram; the hooks exist
 * so a renderer that keeps copies of it (textures, render targets on a GPU)
 * can stay coherent:
 *
 *   draw  called for every drawing kick, BEFORE the software rasterizer
 *         (which still runs when sw_raster = 1).  v[0..nv-1] are the
 *         resolved vertices of ONE primitive (nv = 1 point, 2 line/sprite,
 *         3 triangle; strips/fans already split), in kick order; the
 *         register state that applies is gs->reg[] (PRIM/PRMODE select the
 *         context).  prim_type is GS_PRIM_*.
 *   mem   local-memory traffic of the core, as a rectangle of a buffer:
 *         GS_MEM_READ        the core is about to read r (local->host and
 *                            local->local sources, CLUT loads).  A renderer
 *                            holding newer data for those bytes must write
 *                            it back to gs->vram before returning.
 *         GS_MEM_WRITE_BEGIN the core is about to write r (host->local
 *                            transfer start, local->local destination).  A
 *                            renderer must write back newer data overlapping
 *                            r first (partial writes merge with it) and
 *                            stop trusting its copies of r.
 *         GS_MEM_WRITE_END   the write announced by the last BEGIN has
 *                            completed (all pixels of a host->local transfer
 *                            arrived, the local->local copy finished, or the
 *                            transfer was abandoned by a new TRXDIR/reset).
 *   Direct callers of gs_write_pixel / writers of gs->vram bypass the hooks;
 *   they must tell the renderer themselves (gpu_mem_written in src/gpu).
 */
struct gs_state;
typedef struct gs_mem_rect {
    uint32_t bp, bw;    /* block pointer (256-byte units), width (64-px units) */
    int psm;            /* GS_PSM* */
    uint32_t x, y, w, h;
} gs_mem_rect;
enum { GS_MEM_READ = 0, GS_MEM_WRITE_BEGIN = 1, GS_MEM_WRITE_END = 2 };
typedef struct gs_hooks {
    void *user;
    void (*draw)(void *user, struct gs_state *gs, const gs_vertex *v, int nv,
                 int prim_type);
    void (*mem)(void *user, struct gs_state *gs, int op, const gs_mem_rect *r);
    /* native  a write to GS_NATIVE_MARK (0x7E, unused by the GS): the
     *         native renderer draws record `value` here, between the
     *         primitives before and after it (docs/NATIVE-RENDER.md) */
    void (*native)(void *user, struct gs_state *gs, uint64_t value);
    /* xfer_clean  1 when the renderer holds nothing newer than local memory
     *             for r (no dirty target, no GPU-newer page, no pending batch
     *             writing it): a redundant upload into r may be elided
     *             (gs_mem_gen_bump).  NULL: never elided. */
    int (*xfer_clean)(void *user, struct gs_state *gs, const gs_mem_rect *r);
    /* lazy_ok     1 when a host->local transfer into r may stay pending (gs.h
     *             "lazy transfers"): the renderer holds nothing for r's pages
     *             (no live target, nothing newer, no pending batch) and will
     *             ask for them (gs_mem_materialize) before it reads or draws
     *             there.  NULL: transfers are written at once. */
    int (*lazy_ok)(void *user, struct gs_state *gs, const gs_mem_rect *r);
    /* clut_load   a CLUT load (TEX0 / TEX2 CLD) is about to read r: return 1 when
     *             the renderer performs it itself (on the GPU, from its newer copy
     *             of the pages: docs/NATIVE-RENDER.md "GPU-side CLUT loads"); the
     *             model then neither reads local memory nor changes gs->clut for
     *             it (the renderer owns those cells until it hands them back,
     *             gpu_sync).  csm / csa / cpsm / n as TEX0 says (n = 16 or 256).
     *             NULL or 0: the model loads it (hooks.mem GS_MEM_READ first). */
    int (*clut_load)(void *user, struct gs_state *gs, const gs_mem_rect *r, int csm, uint32_t csa, int cpsm,
                     uint32_t n);
    /* core-private: the host->local transfer announced and not yet ended */
    gs_mem_rect xfer_rect;
    int xfer_open;
} gs_hooks;

/* ---- input recorder (gs_rec.c, docs/GPU.md "Real game validation") ------
 * Called on every input the model takes from outside, before it acts:
 *   GS_REC_GIF        gs_gif_write: a = path, data/bytes = the qwords
 *   GS_REC_PRIV       gs_write_priv: a = EE address, v = value
 *   GS_REC_VSYNC      gs_vsync
 *   GS_REC_GIF_RESET  gs_gif_reset
 *   GS_REC_FIFO_READ  gs_read_fifo: a = bytes asked for
 * A recording (gs_rec_*) of these plus a state snapshot replays the GS
 * exactly through any renderer.  NULL by default. */
enum { GS_REC_GIF = 1, GS_REC_PRIV = 2, GS_REC_VSYNC = 3, GS_REC_GIF_RESET = 4,
       GS_REC_FIFO_READ = 5 };
typedef void (*gs_rec_fn)(void *user, int kind, uint32_t a, uint64_t v,
                          const void *data, uint32_t bytes);

typedef struct gs_state {
    uint8_t *vram;              /* GS_VRAM_BYTES */

    /* general registers, raw 64-bit values indexed by address (0x00-0x7F) */
    uint64_t reg[128];
    /* privileged registers: [0..15] = 0x12000000 + 16*i, [16..31] = 0x12001000 + 16*i */
    uint64_t preg[32];
    uint32_t csr_events;        /* CSR bits 0-4 */
    uint32_t csr_field;         /* current field (CSR bit 13) */

    /* vertex state */
    float internal_q;           /* PACKED-mode Q latched by ST, 1.0 at tag start */
    gs_vertex vq[3];            /* vertex queue (oldest first) */
    int vq_n;                   /* vertices queued */
    int strip_n;                /* vertices seen since PRIM (for strips/fans) */

    /* CLUT buffer: 512 16-bit cells; CT32 entries keep the low halves in
     * cells 0-255 and the high halves in cells 256-511. */
    uint16_t clut[512];
    uint32_t cbp0, cbp1;        /* CLD 2..5 comparison registers */

    /* image transfer (BITBLTBUF/TRXPOS/TRXREG/TRXDIR) */
    int xfer_dir;               /* -1 none, 0 host->local, 1 local->host */
    uint32_t xfer_x, xfer_y;    /* next pixel, relative to the rectangle */
    uint8_t xfer_carry[8];
    uint32_t xfer_carry_n;
    void *xfer_cache;           /* gs_mem.c: bulk host->local address tables */
    void *xfer_elide;           /* gs_mem.c: redundant upload elision (page generations, recent transfers) */
    void *xfer_lazy;            /* gs_mem.c: pending (lazy) host->local transfers */
    uint8_t *rb;                /* local->host data, read with gs_read_fifo */
    uint32_t rb_len, rb_off, rb_cap;

    gs_gif_path path[4];        /* [1..3] used */
    int bus_owner;              /* path mid-packet, or 0 */
    int in_arbitration;

    int sw_raster;              /* 1 (default): draw into vram */
    gs_irq_fn irq;
    void *irq_user;
    gs_stats stats;
    gs_hooks hooks;             /* renderer hooks, all NULL by default */
    gs_rec_fn rec;              /* input recorder (NULL by default) */
    void *rec_user;
    struct gs_async *async;     /* gs_async_start: GIF input runs on a worker thread */
} gs_state;

/* ---- asynchronous GIF input (gs_async.c, docs/PERF-3D.md) ----------------
 * gs_async_start: from now on gs_gif_write / gs_gif_reset copy their input
 * into a ring that a worker thread executes in order (the GS model and the
 * renderer hooks run there).  What the caller can observe is unchanged:
 * privileged registers stay on the caller's thread (a packet that writes
 * SIGNAL / FINISH / LABEL runs synchronously), and gs_read_fifo,
 * gs_path_idle, gs_read_display, CSR writes, the recorder and gs_destroy wait
 * for the worker first.  A program that reads gs->vram or calls the renderer
 * directly calls gs_async_drain before. */
typedef struct gs_async gs_async;
int gs_async_start(gs_state *gs);
void gs_async_stop(gs_state *gs);
void gs_async_drain(gs_state *gs);
int gs_async_on(const gs_state *gs);
/* entries queued, payload bytes, drains that waited, packets run synchronously */
void gs_async_stats(const gs_state *gs, uint64_t out[4]);
/* total time the calling thread waited for the worker (drains), ms */
double gs_async_wait_ms(const gs_state *gs);
/* Pipelining (docs/NATIVE-RENDER.md "Overlap"):
 * gs_async_call queues fn(user, gs, data) to run on the worker after
 * everything queued so far (data: `bytes` copied into the ring; without the
 * worker it runs at once on the caller).  gs_async_mark returns a position in
 * the stream (everything queued so far); gs_async_wait_mark waits until the
 * worker has executed up to it (0 or a past mark: no wait). */
typedef void (*gs_async_fn)(void *user, gs_state *gs, const void *data);
void gs_async_call(gs_state *gs, gs_async_fn fn, void *user, const void *data, uint32_t bytes);
uint64_t gs_async_mark(const gs_state *gs);
void gs_async_wait_mark(gs_state *gs, uint64_t mark);

/* ---- feature census (gs_census.c, measurement; docs/PERF-3D.md) ----
 * gs_features_begin starts counting every drawing kick by pipeline state and
 * the local-memory transfers; gs_features_dump writes the counts (TSV) and
 * stops.  With the GS worker, call both while it is drained. */
void gs_features_begin(void);
int gs_features_dump(const char *path);

/* ---- lifetime ---- */
gs_state *gs_create(void);
void gs_destroy(gs_state *gs);
/* Power-on / CSR.RESET: registers, CLUT, paths; VRAM contents are kept. */
void gs_reset(gs_state *gs);

/* One primitive through the draw path (hooks.draw, then the software
 * rasterizer when sw_raster is on) with the register state in gs.  Used by
 * the native renderer for primitives it generates in place of a VU1
 * program (called from hooks.native, i.e. on the thread executing the GIF
 * stream; docs/NATIVE-RENDER.md "Shadow volumes"). */
void gs_draw_kick(gs_state *gs, const gs_vertex *v, int nv, int prim_type);
/* $RG_NR_FXCENSUS=1: the residue census (gs_core.c), printed by the runtime at exit */
void gs_fx_census_dump(FILE *f);
/* IMAGE data run outside the GIF parser (the native renderer's immediate
 * records, docs/NATIVE-RENDER.md "Immediate packets"): exactly what nqw qwords of
 * IMAGE data arriving on `path` do (HWREG writes, transfer staging), then the
 * staged transfer is written (the caller's next register write is not a GIF
 * tag, which would flush it). */
void gs_image_write(gs_state *gs, int path, const void *qwords, uint32_t nqw);

/* ---- GIF ---- */
void gs_gif_write(gs_state *gs, int path, const void *qwords, uint32_t nqw);
/* vu_gif_sink_fn-compatible adapter (user = gs_state*), routes to PATH1. */
void gs_vu1_gif_sink(void *user, const uint8_t *data, uint32_t bytes,
                     uint32_t vu_addr);
/* vif_gif_sink_fn-compatible adapter (src/ps2/vif/vif.h; user = gs_state*),
 * routes VIF1 DIRECT/DIRECTHL data to PATH2. */
void gs_vif1_gif_sink(void *user, const uint8_t *data, uint32_t bytes);
/* GIF_CTRL.RST: drop every path's tag/packet state and queued data and
 * release the bus.  GS registers, VRAM and the CLUT are untouched (unlike
 * gs_reset / CSR.RESET). */
void gs_gif_reset(gs_state *gs);
/* Is the path idle (no packet in progress, nothing queued)? */
int gs_path_idle(const gs_state *gs, int path);

/* ---- registers ---- */
void gs_write_reg(gs_state *gs, uint32_t addr, uint64_t data); /* A+D */
void gs_write_priv(gs_state *gs, uint32_t ee_addr, uint64_t data);
uint64_t gs_read_priv(gs_state *gs, uint32_t ee_addr);
/* VBlank start: toggles CSR.FIELD when interlaced, raises VSINT. */
void gs_vsync(gs_state *gs);

/* ---- local -> host ---- */
/* Bytes of local->host data still unread (a TRXDIR=1 write produces them). */
uint32_t gs_fifo_pending(const gs_state *gs);
/* Copy up to `bytes` bytes of readback data; returns bytes copied. */
uint32_t gs_read_fifo(gs_state *gs, void *dst, uint32_t bytes);

/* ---- direct memory helpers (tests, tools, renderer upload) ---- */
/* Byte address of pixel (x,y) of a buffer at block pointer bp (256-byte
 * units) and width bw (64-pixel units).  For 4-bit formats the address of the
 * byte holding the nibble; *nib (may be NULL) gets 0 (low) or 1 (high). */
uint32_t gs_pixel_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x,
                       uint32_t y, int *nib);
/* Raw pixel bits (CT24/Z24: 24 bits; T8H: 8 bits from 31:24; ...). */
uint32_t gs_read_pixel(const gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                       uint32_t x, uint32_t y);
void gs_write_pixel(gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                    uint32_t x, uint32_t y, uint32_t v);
/* Bits per pixel of a PSM in transfers (4/8/16/24/32), 0 if invalid. */
int gs_psm_bpp(int psm);

/* ---- redundant upload elision (gs_mem.c, docs/NATIVE-RENDER.md "Texture
 * uploads") ----
 * The game uploads most textures again every frame with the same bytes.  A
 * host->local transfer whose data (one IMAGE run holding the whole transfer)
 * hashes equal to the last completed transfer into the same rectangle, while
 * no write of any kind touched its pages since, is skipped: local memory
 * already holds exactly those bytes, so the vram writes and the renderer's
 * WRITE_BEGIN / WRITE_END hooks (mirror upload, texture re-decode) are not
 * made; transfer position, carry and statistics advance as if written.  Only
 * with a renderer that implements hooks.xfer_clean (it vetoes rectangles it
 * holds newer data for); $RG_GS_ELIDE=0 turns it off.
 * gs_mem_gen_bump: pages (bit set of 512) were written behind the model's
 * transfers (renderer write-backs of drawn targets, CPU-fallback draws,
 * gs_write_pixel callers); NULL = every page. */
void gs_mem_gen_bump(gs_state *gs, const uint32_t *pages16);
/* transfers seen, elided, bytes elided, transfers hashed */
void gs_xfer_elide_stats(const gs_state *gs, uint64_t out[4]);
/* OR into mask[GS_VRAM_BYTES] the bits that the first npx pixels (raster
 * order) of a host->local transfer into the rectangle write (exactly the
 * bits gs_write_pixel changes).  w <= 4096. */
void gs_xfer_mask(int psm, uint32_t bp, uint32_t bw, uint32_t x0, uint32_t y0,
                  uint32_t w, uint32_t h, uint32_t npx, uint8_t *mask);

/* ---- lazy transfers (gs_mem.c, docs/NATIVE-RENDER.md "Texture uploads") ----
 * A whole host->local transfer whose rectangle the renderer does not hold
 * (hooks.lazy_ok) is not written into local memory: it is kept pending (its
 * data, geometry and a 64-bit content hash) and written (materialized, with
 * the renderer's WRITE_BEGIN / WRITE_END hooks) only when something needs the
 * bytes: the model's own reads (CLUT loads, local->host and local->local
 * transfers, overlapping transfers, a reset), and the renderer's (it calls
 * gs_mem_materialize for the pages it is about to read or draw into, and
 * gpu_sync materializes everything).  A transfer into exactly the rectangle
 * of a pending one replaces it (texture pools: slots rewritten before any
 * read cost nothing); native draws can take a texture straight from the
 * pending data (gs_mem_lazy_find).  Nothing the game observes changes: every
 * read sees the bytes it would have seen.  $RG_GS_LAZY=0 turns it off.
 *   gs_mem_materialize        pending transfers with blocks in pages16 (NULL:
 *                             all); hooks 0: without the renderer hooks (the
 *                             renderer itself, inside its own bookkeeping)
 *   gs_mem_materialize_rect   those with blocks in a buffer rectangle
 *   gs_mem_lazy_pages         OR the pages holding pending blocks into
 *                             pages16; returns 1 when there are any
 *   gs_mem_lazy_texels        the texture (bp, bw, psm) [0, w) x [0, h) when
 *                             all its blocks belong to one pending transfer
 *                             (in any format: textures are often uploaded as
 *                             CT32): a content key (the transfer's bytes and
 *                             geometry relative to the texture) and, when
 *                             raw is not NULL, the w * h raw texel values as
 *                             gs_read_pixel would return them; 0 when none
 *   gs_mem_lazy_stats         accepted, materialized, replaced, bytes
 *                             accepted, bytes materialized, refused by the
 *                             renderer, served to native draws, raw writes */
void gs_mem_materialize(gs_state *gs, const uint32_t *pages16, int hooks);
void gs_mem_materialize_rect(gs_state *gs, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                             uint32_t w, uint32_t h);
int gs_mem_lazy_pages(const gs_state *gs, uint32_t *pages16);
/* gs_mem_materialize_rect with or without the renderer hooks */
void gs_mem_materialize_rect_h(gs_state *gs, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                               uint32_t w, uint32_t h, int hooks);
/* OR the pages materializations wrote since the last call into pages16 (may
 * be NULL: forget them); the renderer marks them after writes without hooks */
void gs_mem_lazy_take_written(gs_state *gs, uint32_t *pages16);
int gs_mem_lazy_texels(gs_state *gs, uint32_t bp, uint32_t bw, int psm, uint32_t w, uint32_t h, uint64_t *key,
                       uint32_t *raw);
void gs_mem_lazy_stats(const gs_state *gs, uint64_t out[8]);
/* changes whenever a transfer is accepted as pending (0: nothing pending) */
uint64_t gs_mem_lazy_gen(const gs_state *gs);

/* ---- sprite UV stepping (docs/GS.md rule 3) ----
 * A sprite's U (or V) is a fixed-point DDA: c0/c1 are the UV register values
 * (1/16 texel) of the corners sorted by position, p0 < p1 their window
 * coordinates (12.4).  The step per pixel is (c1-c0) * 2^20 / (p1-p0) (16.16
 * in 1/16-texel units), truncated toward zero and saturated to int32; pixel
 * px samples floor((c0 * 2^16 + floor(step * (16*px - p0) / 16)) / 2^16).
 * Exposed so the GPU renderer computes bit-identical coordinates. */
int64_t gs_sprite_uv_step(int64_t c0, int64_t c1, int64_t p0, int64_t p1);
int32_t gs_sprite_uv_at(int64_t c0, int64_t p0, int64_t step, int px);

/* ---- display read-out ---- */
enum {
    GS_READ_FRAME = -1   /* full (both-field) frame, see docs/GS.md */
};
/* Render what the PCRTC would show: PMODE/DISPFBn/DISPLAYn/SMODE2/BGCOLOR,
 * both read circuits and the merge.  field: GS_READ_FRAME, 0 or 1.  Output is
 * RGBA8 (byte order R,G,B,A; A = 0xFF).  Returns 0 and sets *w,*h, or -1 when
 * nothing is enabled or out_cap_px is too small (then *w,*h hold the size). */
int gs_read_display(const gs_state *gs, int field, uint32_t *out,
                    uint32_t out_cap_px, uint32_t *w, uint32_t *h);
/* Read one buffer rectangle as RGBA8 (CT32/24/16/16S; A as stored). */
void gs_read_rect_rgba(const gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                       uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                       uint32_t *out);

/* ---- texture reads within a primitive (gs_raster.c) ----
 * A primitive samples local memory as it was when it started (its own
 * colour and Z writes are not seen by its texture reads; docs/GPU.md
 * "Checkpoint 4").  gs_tex_snapshot_off = 1 restores reading memory as the
 * primitive writes it (test control only).  gs_tex_snapshots counts the
 * primitives whose texture pages they could write, which read a copy. */
extern int gs_tex_snapshot_off;
extern uint64_t gs_tex_snapshots;

/* ---- recordings (gs_rec.c) ----
 * File: "RGGSREC1", a snapshot of the whole model state (registers, CLUT,
 * vertex queue, transfer and GIF path state with queued data, the FIFO and
 * the 4 MB of local memory), then events {u32 kind, u32 a, u64 v, u32 bytes,
 * data}.  gs_rec_snapshot needs gs->vram current (gpu_sync first). */
#include <stdio.h>
int gs_rec_snapshot(FILE *f, const gs_state *gs);
void gs_rec_event(FILE *f, int kind, uint32_t a, uint64_t v, const void *data, uint32_t bytes);
typedef struct gs_rec_file {
    uint8_t *buf;
    size_t len, off, events_off;
} gs_rec_file;
typedef struct gs_rec_ev {
    int kind;
    uint32_t a;
    uint64_t v;
    uint32_t bytes;
    const uint8_t *data;
} gs_rec_ev;
/* Read a whole recording; 0 ok, -1 (not a recording / truncated). */
int gs_rec_open(gs_rec_file *rf, const char *path);
void gs_rec_close(gs_rec_file *rf);
/* Load the snapshot into gs (call before attaching a renderer) and rewind
 * the events. */
int gs_rec_load(gs_rec_file *rf, gs_state *gs);
/* Next event: 1, or 0 at the end, -1 when truncated. */
int gs_rec_next(gs_rec_file *rf, gs_rec_ev *ev);
/* Apply one event to gs (GS_REC_FIFO_READ reads into fifo_out, which must
 * hold ev->a bytes, and returns the bytes read; others return 0). */
uint32_t gs_rec_apply(gs_state *gs, const gs_rec_ev *ev, uint8_t *fifo_out);

#ifdef __cplusplus
}
#endif
#endif
