/* SPDX-License-Identifier: CC0-1.0 */
/* Native renderer, scene side (nr.h, docs/NATIVE-RENDER.md "Architecture").
 *
 * Records: one per natively drawn mesh, in a ring indexed by the record id
 * the marker carries.  Written on the EE thread (nr_model_record at draw-list
 * time, the VIF1 tap at DMA time), read on the GS thread when the marker
 * reaches the GS.  The GS ring orders them: everything the EE writes before
 * gs_gif_write queues the marker is visible to the worker that executes it. */
#include "nr.h"
#include "nr_mesh.h"
#include "nr_vu1.h"
#include "nr_const.h"
#include "nr_vu1sh.h"
#include "nr_vu1ln.h"
#include "nr_comp.h"
#include "nr_interp.h"   /* interpolated presentation (docs/NATIVE-RENDER.md) */
#include "nr_im.h"
#include "nr_mem.h"     /* walkers' readable memory, poison mode */

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "gs.h"
#include "vif.h"
#include "vu.h"
#ifdef RG_HAVE_GPU
#include "gpu.h"
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
/* native-only (docs/NATIVE-RENDER.md "Checkpoint 10"): the native state block and worker, no GS
 * draw path: generated primitives always go to gpu_nr_im_submit (genim_on) */
#include "nr_gs.h"
#define gs_draw_kick(gs, v, nv, type) ((void)(gs), (void)(v), (void)(nv), (void)(type))
#define NR_ONLY 1
#else
#define NR_ONLY 0
#endif
#endif
#ifndef NR_ONLY
#define NR_ONLY 0
#endif

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

/* ---- mode ----------------------------------------------------------------- */
static int g_mode = -1;
int nr_mode(void)
{
    if (g_mode < 0) {
        const char *e = getenv("RG_RENDER");
        /* native is the default since 2026-10-18 (docs/NATIVE-RENDER.md "RG_RENDER=native
         * as the default"); emu = the emulated VIF/VU1 path, the verification oracle */
        g_mode = (e && !strcmp(e, "emu")) ? NR_EMU : (e && !strcmp(e, "verify")) ? NR_VERIFY : NR_NATIVE;
    }
    return g_mode;
}
static int active(void) { return nr_mode() == NR_NATIVE || nr_mode() == NR_VERIFY; }
#ifdef RG_HAVE_GPU
/* mesh pre-warm (nr_model_record, docs/NATIVE-RENDER.md "Pre-warm"); RG_NR_PREWARM=0: off */
static gpu_renderer *g_store_gr;
static uint32_t g_prewarm_hi;
static int prewarm_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_PREWARM"); on = !(e && e[0] == '0'); }
    return on && nr_mode() == NR_NATIVE;
}
#endif
int nr_keep_original(void) { return nr_mode() == NR_VERIFY; }

/* ---- records ---------------------------------------------------------------- */
#define NR_RECS 4096u
typedef struct nr_rec {
    uint32_t id;
    int variant;
    const nr_mesh *mesh;
    int filled;              /* constants present: from the game (cn) or the VIF tap (c) */
    int tapped;              /* the VIF tap took VU memory into c / bones (check, verify, tap modes) */
    nr_qw c[NRQ_CONST_N];    /* VU1 qwords 0..111 as drawn with (game constants, or the tap's) */
    nr_qw bones[NR_BONE_ROWS];   /* VU1 qwords 768..1023 */
    uint32_t bones_hi;       /* bone rows the game's skin packet wrote */
    uint32_t src[8];         /* the builders' packets the constants came from (diagnostics; [7] microcode list) */
    uint32_t cam;            /* the camera matrix packet used */
    uint32_t frame;          /* nr_frame_begin count at record time */
    int has_box;             /* box: GS window rectangle (pixels) the mesh can touch (coherence) */
    float box[4];
    /* Z-scale meshes: the screen-vector min / max the output piece would merge
     * into VU qw98/99 (computed at record time, bbox_compute) */
    int has_bb;
    int vu_bbox;             /* the VIF tap must merge bb into VU memory (the composite runs emulated) */
    nr_qw bb_lo, bb_hi;
} nr_rec;
static nr_rec *g_rec;
static uint32_t g_next = 1;
static int g_attached;       /* the VIF tap and the GS handler are both in place */

static struct {
    uint64_t meshes, recorded, fallback_variant, fallback_mesh, fallback_off, fallback_const;
    uint64_t tapped, tap_stale, drawn, not_filled, stale_gs, gpu_fail, bbox_meshes;
} g_st;

static nr_rec *rec_of(uint32_t id) { return &g_rec[id % NR_RECS]; }

void nr_marker_qwords(uint32_t id, uint32_t q[12])
{
    /* DMA CNT qwc 2, VIF codes NOP + DIRECT 2 */
    q[0] = 0x10000002u; q[1] = 0; q[2] = 0; q[3] = 0x50000002u;
    /* GIF tag: NLOOP 1, EOP, PACKED, NREG 1, REGS = A+D */
    q[4] = 0x00008001u; q[5] = 0x10000000u; q[6] = 0x0000000Eu; q[7] = 0;
    /* A+D: id -> GS_NATIVE_MARK */
    q[8] = id; q[9] = 0; q[10] = GS_NATIVE_MARK; q[11] = 0;
}

/* ---- constants from the game's builders (nr_const.h) ---------------------
 * RG_NR_CONST = game (default): the record's constant block is filled here, at
 * record time, from the packets the game's builders just wrote (camera view,
 * camera matrix, lights, object matrix + the VU program at 0, model info, skin
 * matrices, material); VU memory is not read.  check: the same, and the VIF1
 * tap compares every qword the native pipeline reads with VU memory when the
 * marker passes (the verification of this slice).  tap: the transition path
 * (constants snapshotted from VU memory at the marker). */
enum { NRC_GAME = 0, NRC_CHECK = 1, NRC_TAP = 2 };
static int g_cmode = -1;
static int cmode(void)
{
    if (g_cmode < 0) {
        const char *e = getenv("RG_NR_CONST");
        g_cmode = (e && !strcmp(e, "check")) ? NRC_CHECK : (e && !strcmp(e, "tap")) ? NRC_TAP : NRC_GAME;
    }
    return g_cmode;
}
/* the VIF1 tap is needed: tap-mode constants, the check, verify mode */
/* The VIF1 tap stays installed in every mode, but in the default mode it
 * reads nothing: it only merges the screen bbox of Z-scale meshes into VU
 * qw98/99 for the emulated program that still consumes it (the offscreen
 * composite, VU program 0x445C60 at 0x960, when it runs emulated; see bbox_merge_vu). */
static int need_tap(void) { return 1; }

/* Native mode with game constants: the draw list skips, for native meshes,
 * the item packets (object matrix + MSCAL 0, model info, skin) and the
 * microcode uploads: VU1 does nothing for them (RG_NR_LAZY=0 keeps sending).
 * Not in check/tap/verify modes, which read VU memory. */
int nr_lazy_item_packets(void)
{
    static int lazy = -1;
    if (lazy < 0) {
        const char *e = getenv("RG_NR_LAZY");
        lazy = (!e || atoi(e) != 0) ? 1 : 0;
    }
    return lazy && nr_mode() == NR_NATIVE && cmode() == NRC_GAME;
}

/* Packets the renderer remembers across draws and frames, and the lifetime the PS2 gave them.
 * On the PS2 a constant packet goes to VU memory once when the DMA chain runs and VU memory keeps
 * the values; the game never reads such a packet again and its memory (a frame's packet stack,
 * a menu's draw context) is reused.  The port remembers packets by ADDRESS and applies them at
 * record time, so an address that outlives its data is walked as DMA tags: garbage REF tags
 * into unmapped memory, the 1025b shop-close crash in nr_const_apply.  (The PS2 never faulted:
 * DMA addresses wrap to 32 MB and the VIF takes any words.)
 * 1. The camera / light / plane-shadow packet a draw context built last (for draws whose request
 *    does not carry one) is COPIED when built (the builders write one RET tag with the payload
 *    inline) and applied from the copy; the address stays the key (cache key, record ->cam).
 * 2. The light packet a draw REQUEST names (src[2] = LightStateGetPacket_1428f0: the current
 *    light record's +4 "emitted" pointer) is the crash: the game sets it when
 *    LightStateWritePacket_1484a0 writes the packet into a frame's packet stack and only uses
 *    it as an "already emitted" mark; a record that stays current while its context does not
 *    draw (the field context during a shop menu, frames 2,488 -> 3,007 in the regression)
 *    keeps a pointer into a stack the menu has reused.  Every light packet written is noted BY
 *    ADDRESS too (g_lpk) and a request's light packet is applied from the copy written there
 *    for that context.  One the table does not know (written before the renderer attached,
 *    recycled) is read in place only when it is still one self-contained RET block (no pointer
 *    in it is followed), else the context's last light packet is used (what VU memory holds).
 * 3. lstate (the shadow volumes' light region) is applied when built: no re-read.
 * 4. The camera VIEW packet (qw 0-19, CameraWriteViewPacket_148740 (override) -> nr_note_view)
 *    is noted by address like the lights (g_vpk): a request's view packet (src[1], the context's
 *    +0x36B0 "view built this frame" pointer, the same kind of mark) is applied from the copy
 *    written there for that context; unknown = read in place only when still one RET block.
 * 5. The SORTED path's DMA chain (2026-10-26, rpkt): ModelQueueSortedPackets_14f0d0 writes the
 *    view and light packet addresses into every node header and DrawListEmitBucket CALLs them,
 *    so the frame chain (walked by nr_fx.c, and by VU1 on the PS2) followed the same stale marks.
 *    nr_chain_packet resolves them at build time like the records: an address whose memory still
 *    holds what the builder wrote (normal play) is kept (chain and run hash unchanged), else the
 *    copy the record applies is written into the frame's packet stack and the node CALLs that.
 * Every walker's host() also refuses unreadable memory and poisoned packets (nr_mem.h), and
 * RG_NR_POISON=1|2 poisons each frame packet stack when the game resets it, so any stale read
 * left fails loudly (tools/fixtures/poisoncheck.py, ctest fixtures.poison).
 * RG_NR_STALE=1 counts uses whose game memory no longer matches the copy (diagnostic: it reads
 * the old address).  RG_NR_NOTE_COPY=0 = the old re-reading behaviour (A/B: crashes the
 * regression tools/fixtures/shopcrash.py again). */
#define NR_NOTE_MAX 1024   /* bytes: camera 96, light / plane packets a few hundred */
typedef struct { uint32_t ctx, pkt, bytes, frame; uint8_t copy[NR_NOTE_MAX]; } nr_note;
static nr_note g_cam[16], g_light[16], g_plane[16];
#define NR_LPK 256   /* light / view packets by address: a frame writes a few per context */
typedef struct { nr_note e[NR_LPK]; uint32_t next; } nr_ptab;
static nr_ptab g_lpk, g_vpk;
static struct {
    uint64_t notes, uncopyable, stale_cam, stale_light, used_cam, used_light, req_light, req_unknown, req_inplace;
    uint64_t stale_view, used_view, req_view, view_unknown, view_inplace, view_bad;
    uint64_t chain[2], chain_sub[2], chain_empty[2];   /* sorted-path chain packets: [0] view, [1] light */
} g_nst;
static uint32_t g_frame_no;   /* EE: frames begun (DrawListFrameBegin_1425d0) */
static int note_copy_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_NOTE_COPY"); on = !(e && e[0] == '0'); }
    return on;
}
static int stale_check_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_STALE"); on = e && atoi(e) != 0; }
    return on;
}
static void note_put(nr_note *t, uint32_t ctx, uint32_t pkt)
{
    int i, free_i = -1;
    for (i = 0; i < 16; i++) {
        if (t[i].ctx == ctx) break;
        if (!t[i].ctx && free_i < 0) free_i = i;
    }
    if (i == 16) i = free_i >= 0 ? free_i : (int)(ctx >> 4) & 15;
    t[i].ctx = ctx;
    t[i].frame = g_frame_no;
    g_nst.notes++;
    t[i].bytes = nr_const_inline_bytes(pkt, NR_NOTE_MAX);
    if (!t[i].bytes) {
        g_nst.uncopyable++;   /* not a builder's layout: dropped (its draws count as no camera / light) */
        t[i].pkt = note_copy_on() ? 0 : pkt;
        return;
    }
    t[i].pkt = pkt;
    memcpy(t[i].copy, (const void *)(uintptr_t)pkt, t[i].bytes);
}
/* a light / view packet written at pkt for ctx (by address; the newest write at an address wins) */
static void ptab_put(nr_ptab *t, uint32_t ctx, uint32_t pkt)
{
    uint32_t i, k = NR_LPK;
    nr_note *n;
    for (i = 0; i < NR_LPK; i++) if (t->e[i].pkt == pkt) { k = i; break; }
    if (k == NR_LPK) { k = t->next; t->next = (t->next + 1) % NR_LPK; }
    n = &t->e[k];
    n->ctx = ctx;
    n->frame = g_frame_no;
    n->bytes = nr_const_inline_bytes(pkt, NR_NOTE_MAX);
    n->pkt = n->bytes ? pkt : 0;
    if (n->bytes) memcpy(n->copy, (const void *)(uintptr_t)pkt, n->bytes);
}
static const nr_note *ptab_of(const nr_ptab *t, uint32_t ctx, uint32_t pkt)
{
    uint32_t i;
    for (i = 0; i < NR_LPK; i++)
        if (t->e[i].pkt == pkt) return t->e[i].ctx == ctx ? &t->e[i] : NULL;
    return NULL;
}
static void lpk_put(uint32_t ctx, uint32_t pkt) { ptab_put(&g_lpk, ctx, pkt); }
static const nr_note *lpk_of(uint32_t ctx, uint32_t pkt) { return ptab_of(&g_lpk, ctx, pkt); }
static const nr_note *note_of(const nr_note *t, uint32_t ctx)
{
    int i;
    for (i = 0; i < 16; i++) if (t[i].ctx == ctx && t[i].pkt) return &t[i];
    return NULL;
}
/* apply a note (its copy) to b; *stale counts a use whose game memory changed since the note */
static int note_apply(nr_cblock *b, const nr_note *n, uint64_t *used, uint64_t *stale)
{
    (*used)++;
    if (stale_check_on() && n->bytes && memcmp(n->copy, (const void *)(uintptr_t)n->pkt, n->bytes) != 0) {
        if (++*stale <= 8)
            fprintf(stderr, "nr: stale %s note: ctx %08X packet %08X noted frame %u, used frame %u\n",
                    stale == &g_nst.stale_cam ? "camera" : stale == &g_nst.stale_view ? "view" : "light", n->ctx, n->pkt,
                    n->frame, g_frame_no);
    }
    if (!note_copy_on() || !n->bytes) return nr_const_apply(b, n->pkt);
    return nr_const_apply_inline(b, n->copy, n->bytes);
}

/* camera matrix packet (qw 24-28): DrawPktBuildCameraMatrix_1486c0 override */
void nr_note_cammtx(uint32_t ctx, uint32_t pkt)
{
    if (!active()) return;
    note_put(g_cam, ctx, pkt);
}
static uint32_t cam_of(uint32_t ctx)
{
    const nr_note *n = note_of(g_cam, ctx);
    return n ? n->pkt : 0;
}
/* The light region (qw 30-51) as uploads accumulate in VU memory: every
 * light and plane-shadow packet a context builds, applied in build order (the
 * order DrawListBeginPlaneShadowPass / DrawListAddPlaneShadowMtxPkt_147ae0
 * emit them).  The shadow volumes read qw30-40 from it: the per-object plane
 * packets rewrite 30-34 only and leave the pass's register packets at 35-40.
 * Applied when built, so it never re-reads game memory either. */
static struct { uint32_t ctx; nr_cblock *b; } g_lst[8];
static void lstate_apply(uint32_t ctx, uint32_t pkt)
{
    int i, free_i = -1;
    for (i = 0; i < 8; i++) {
        if (g_lst[i].ctx == ctx) break;
        if (!g_lst[i].ctx && free_i < 0) free_i = i;
    }
    if (i == 8) {
        i = free_i >= 0 ? free_i : (int)(ctx >> 4) & 7;
        g_lst[i].ctx = ctx;
        if (!g_lst[i].b) g_lst[i].b = (nr_cblock *)calloc(1, sizeof(nr_cblock));
        else memset(g_lst[i].b, 0, sizeof(nr_cblock));
    }
    if (g_lst[i].b) nr_const_apply(g_lst[i].b, pkt);
}
static const nr_cblock *lstate_of(uint32_t ctx)
{
    int i;
    for (i = 0; i < 8; i++) if (g_lst[i].ctx == ctx) return g_lst[i].b;
    return NULL;
}

/* the light packet (qw 30-51) most recently written per draw context
 * (LightStateWritePacket_1484a0 override): for draws whose request carries
 * no light packet (the lights then stay what was uploaded last) */
void nr_note_light(uint32_t ctx, uint32_t pkt)
{
    if (!active()) return;
    lstate_apply(ctx, pkt);
    note_put(g_light, ctx, pkt);
    lpk_put(ctx, pkt);
}
static const nr_note *light_of(uint32_t ctx) { return note_of(g_light, ctx); }
/* the plane-shadow packet (qw 30-40) most recently built per draw context
 * (DrawPktBuildPlaneShadowMtx_147eb0 override): the "lights" of the shadow
 * volumes (DrawListBeginPlaneShadowPass emits it before the pass's models);
 * only a cache key here (the region itself comes from lstate_of) */
void nr_note_plane(uint32_t ctx, uint32_t pkt)
{
    if (!active()) return;
    lstate_apply(ctx, pkt);
    note_put(g_plane, ctx, pkt);
}
static uint32_t plane_of(uint32_t ctx)
{
    const nr_note *n = note_of(g_plane, ctx);
    return n ? n->pkt : 0;
}
/* the camera view packet (qw 0-19) ctx wrote at pkt (CameraWriteViewPacket_148740 override):
 * the copy a request naming pkt applies (item 4 above) */
void nr_note_view(uint32_t ctx, uint32_t pkt)
{
    if (!active()) return;
    ptab_put(&g_vpk, ctx, pkt);
}

/* How a draw request's view (kind 0) / light (kind 1) packet is applied, the same rule for the
 * record (game_constants) and the sorted path's chain (nr_chain_packet): the copy written at
 * that address for ctx (*n); else, when the memory is still one self-contained RET block, in
 * place (returns 1, *n NULL: no pointer in it is followed); else a light falls back to the
 * context's last light packet (*n) and a view to nothing (*n NULL, returns 0). */
static int req_resolve(int kind, uint32_t ctx, uint32_t pkt, const nr_note **n)
{
    *n = ptab_of(kind ? &g_lpk : &g_vpk, ctx, pkt);
    if (*n) return 0;
    if (nr_const_inline_bytes(pkt, NR_NOTE_MAX)) return 1;
    *n = kind ? light_of(ctx) : NULL;
    return 0;
}

uint32_t nr_chain_packet(uint32_t ctx, int kind, uint32_t pkt, uint32_t dst, uint32_t *qw)
{
    static struct { uint32_t ctx, pkt, frame, addr; } last[2];
    const nr_note *n;
    const uint8_t *mem;
    kind = kind ? 1 : 0;
    *qw = 0;
    if (!active() || !note_copy_on() || !pkt || !dst) return pkt;
    g_nst.chain[kind]++;
    if (req_resolve(kind, ctx, pkt, &n)) return pkt;            /* in place: a self-contained block */
    if (n && n->pkt == pkt && (mem = nr_game_ptr(pkt, n->bytes)) != NULL && !memcmp(mem, n->copy, n->bytes))
        return pkt;                                              /* live: what the builder wrote (normal play) */
    if (last[kind].ctx == ctx && last[kind].pkt == pkt && last[kind].frame == g_frame_no && last[kind].addr)
        return last[kind].addr;                                  /* this frame's copy (same packet stack) */
    if (n) {
        memcpy((void *)(uintptr_t)dst, n->copy, n->bytes);
        *qw = n->bytes / 16u;
        g_nst.chain_sub[kind]++;
    } else {
        static const uint32_t ret0[4] = { 0x60000000u, 0, 0, 0 };   /* RET, nothing: VU memory keeps what it has */
        memcpy((void *)(uintptr_t)dst, ret0, 16);
        *qw = 1;
        g_nst.chain_empty[kind]++;
    }
    if (stale_check_on() && g_nst.chain_sub[kind] + g_nst.chain_empty[kind] <= 8)
        fprintf(stderr, "nr: sorted-chain %s packet %08X ctx %08X frame %u: not live, the node CALLs %s at %08X\n",
                kind ? "light" : "view", pkt, ctx, g_frame_no, n ? "the copy" : "an empty RET", dst);
    last[kind].ctx = ctx;
    last[kind].pkt = pkt;
    last[kind].frame = g_frame_no;
    last[kind].addr = dst;
    return dst;
}

static struct {
    uint64_t models, model_fail[12], mat_fail[12], no_cam, no_view, no_light, light_noted;
} g_cst;
static nr_cblock g_base;          /* the last model item's block (meshes of one item share it) */
static uint32_t g_base_key[6];
static int g_base_err = 1;
static nr_cblock g_blk;
static int g_rec_tme = -1;
void nr_frame_begin(uint32_t ctx)
{
    (void)ctx;
    g_frame_no++;
    nr_game_mem_frame();   /* walkers' readable-region cache (nr_mem.h) */
    nr_ip_frame_begin(g_frame_no);   /* interpolated presentation: a log boundary (when on) */
#ifdef RG_HAVE_GPU   /* no GPU backend (Linux, docs/LINUX.md): no filter log */
    gpu_nr_filtlog_frame(g_frame_no);
#endif
}
uint32_t nr_frame_no(void) { return g_frame_no; }   /* record2: the material's PRMODE TME bit (qw87.x bit 4), -1 unknown */
static int g_dbg_info;

static int err_slot(int e) { return e < 0 && e > -11 ? -e : 11; }

/* src: [0] draw context, [1] camera view packet, [2] light packet, [3] object
 * matrix packet (item +0x14), [4] model info packet (+0x18), [5] skin packet
 * (+0x1C), [6] the mesh's texture/material packet (DrawListWriteTexEnvPacket) */
static int game_constants(const uint32_t *src, int variant, nr_cblock **out)
{
    uint32_t key[6];
    int e;
    const nr_note *lt = NULL, *vt;
    if (!note_copy_on()) {
        lt = src[2] ? NULL : light_of(src[0]);
        key[2] = src[2] ? src[2] : lt ? lt->pkt : 0;
    } else if (src[2]) {
        key[2] = 0;
        /* the request's light packet: the copy written there for this context (see g_lpk) */
        g_nst.req_light++;
        lt = lpk_of(src[0], src[2]);
        if (!lt) {
            g_nst.req_unknown++;
            if (stale_check_on() && g_nst.req_unknown <= 8) {
                uint32_t i;
                for (i = 0; i < NR_LPK && g_lpk.e[i].pkt != src[2]; i++) {}
                fprintf(stderr, "nr: request light packet %08X ctx %08X frame %u: %s%08X frame %u)\n", src[2], src[0], g_frame_no,
                        i < NR_LPK ? "written there by ctx " : "never written by the light builder (", i < NR_LPK ? g_lpk.e[i].ctx : 0,
                        i < NR_LPK ? g_lpk.e[i].frame : 0);
            }
            /* not a light packet the builder wrote for this context (written before the
             * renderer attached, or the table recycled it): a packet that is still one
             * self-contained RET block is read in place as before (no pointer in it is
             * followed); anything else = the context's last light packet */
            if (req_resolve(1, src[0], src[2], &lt)) { g_nst.req_inplace++; key[2] = src[2]; lt = NULL; }
        }
        if (lt) key[2] = lt->pkt;
    } else {
        lt = light_of(src[0]);
        key[2] = lt ? lt->pkt : 0;
    }
    key[0] = cam_of(src[0]);
    key[1] = src[1]; key[3] = src[3];
    vt = NULL;
    if (note_copy_on() && src[1]) {
        /* the request's view packet: the copy written there for this context (item 4) */
        g_nst.req_view++;
        if (!req_resolve(0, src[0], src[1], &vt) && !vt) {
            g_nst.view_bad++;
            key[1] = 0;                 /* neither noted nor a self-contained block: no view */
        } else if (!vt) g_nst.view_inplace++;
        if (!vt) g_nst.view_unknown++;
    }
    if (variant & NRV_SHADOW) {
        uint32_t pl = plane_of(src[0]);
        if (pl) key[2] = pl;   /* (cache key; the region itself comes from lstate_of below) */
    } key[4] = src[4]; key[5] = src[5];
    if (memcmp(key, g_base_key, sizeof key) != 0 || g_base_err > 0) {
        memcpy(g_base_key, key, sizeof key);
        memset(&g_base, 0, sizeof g_base);
        g_cst.models++;
        g_base_err = 0;
        if (!key[0]) { g_cst.no_cam++; g_base_err = 1; }
        else if (!key[1]) { g_cst.no_view++; g_base_err = 1; }
        else if (!key[2]) { g_cst.no_light++; g_base_err = 1; }
        else {
            int k;
            /* DMA order: camera matrix, view, lights, then the item's packets
             * (the object matrix's MSCAL 0 reads camera and lights) */
            for (k = 0; k < 6 && !g_base_err; k++) {
                if (k == 5 && !key[5]) break;
                if (k == 2 && (variant & NRV_SHADOW)) {
                    const nr_cblock *ls = lstate_of(src[0]);
                    if (!ls) { g_cst.no_light++; g_base_err = 1; break; }
                    memcpy(&g_base.c[30], &ls->c[30], 22 * sizeof(nr_qw));
                    continue;
                }
                if (k == 0) e = note_apply(&g_base, note_of(g_cam, src[0]), &g_nst.used_cam, &g_nst.stale_cam);
                else if (k == 2 && lt) e = note_apply(&g_base, lt, &g_nst.used_light, &g_nst.stale_light);
                else if (k == 1 && vt) e = note_apply(&g_base, vt, &g_nst.used_view, &g_nst.stale_view);
                else e = nr_const_apply(&g_base, key[k]);
                if (e) { g_cst.model_fail[err_slot(e)]++; g_base_err = -1 - k; }
            }
        }
        if (g_base_err > 0) g_base_err = -1;
        if (g_base_err == 0) g_base_err = 0;
    }
    if (g_base_err) return -1;
    memcpy(&g_blk, &g_base, sizeof g_blk);
    if (src[6]) {
        e = nr_const_apply(&g_blk, src[6]);
        if (e) { g_cst.mat_fail[err_slot(e)]++; return -1; }
    }
    *out = &g_blk;
    return 0;
}

/* RG_NR_CENSUS=1: the microcode tuples (D_00491280 row entries: head, kind,
 * tail, decode, colour, output packet addresses) of every mesh draw, with how
 * many were recorded natively; printed by nr_runtime_stats (coverage census,
 * docs "Coverage") */
#define NR_CEN 256
static struct { uint32_t in[6]; uint64_t n, native; int variant; float q900[4], q84[4]; } g_cen[NR_CEN];
static int g_cen_on = -1, g_cen_n;
static const uint8_t *g_vu1mem;   /* VU1 data memory (census: qw900 / qw84 of uncovered tuples) */
static void census_note(const uint32_t *src, int variant, int native)
{
    const uint32_t *in;
    int i;
    if (g_cen_on < 0) { const char *e = getenv("RG_NR_CENSUS"); g_cen_on = e && atoi(e) != 0; }
    if (!g_cen_on || !src || !src[7]) return;
    in = (const uint32_t *)(uintptr_t)src[7];
    for (i = 0; i < g_cen_n; i++)
        if (!memcmp(g_cen[i].in, in, 24)) break;
    if (i == g_cen_n) {
        if (g_cen_n == NR_CEN) return;
        memcpy(g_cen[i].in, in, 24);
        g_cen[i].variant = variant;
        g_cen_n++;
    }
    g_cen[i].n++;
    if (native) g_cen[i].native++;
    if (g_vu1mem && variant < 0) {
        memcpy(g_cen[i].q900, g_vu1mem + 900 * 16, 16);
        memcpy(g_cen[i].q84, g_vu1mem + 84 * 16, 16);
    }
}

/* screen rectangle of a rigid mesh: the 8 corners of its raw position
 * bounds through qw68-71 (none when a corner is at or behind w = 0) */
static int rigid_box(const nr_mesh *m, const nr_qw *c, float box[4])
{
    const float *ps = c[NRQ_POSSCALE].f;
    int k, j;
    box[0] = box[1] = 1e30f; box[2] = box[3] = -1e30f;
    for (k = 0; k < 8; k++) {
        float p[3], cl[4], q;
        for (j = 0; j < 3; j++) p[j] = m->bbox[(k >> j & 1) ? 3 + j : j] * (1.0f / 32768.0f) * ps[j];
        for (j = 0; j < 4; j++)
            cl[j] = c[NRQ_SCREEN].f[j] * p[0] + c[NRQ_SCREEN + 1].f[j] * p[1] + c[NRQ_SCREEN + 2].f[j] * p[2] + c[NRQ_SCREEN + 3].f[j];
        if (!(cl[3] > 1e-6f)) return 0;
        q = 1.0f / cl[3];
        if (cl[0] * q < box[0]) box[0] = cl[0] * q;
        if (cl[0] * q > box[2]) box[2] = cl[0] * q;
        if (cl[1] * q < box[1]) box[1] = cl[1] * q;
        if (cl[1] * q > box[3]) box[3] = cl[1] * q;
    }
    return 1;
}

static void clip_note(nr_rec *r, uint32_t ctx);
/* A textured mesh with a batch that unpacks no UVs (the VU program reads whatever an earlier
 * batch left in VU memory there: not reproducible) is drawn natively with UV 0 (one mesh on
 * the route, 5,149 draws to field 23,260; frames identical with and without it at 28 fields
 * of 19,100-23,250).  RG_NR_MISSUV=0: it stays on the VU program. */
static int miss_uv_ok(void)
{
    static int k = -1;
    if (k < 0) { const char *e = getenv("RG_NR_MISSUV"); k = !(e && e[0] == '0'); }
    return k;
}
uint32_t nr_model_record2(uint32_t mesh_pkt, int variant, const uint32_t *src)
{
    nr_cblock *b = NULL;
    uint32_t id;
    if (!active() || !g_attached) { g_st.fallback_off++; return 0; }
    if (cmode() != NRC_TAP && variant >= 0) {
        if (game_constants(src, variant, &b) != 0) {
            g_st.meshes++;
            g_st.fallback_const++;
            census_note(src, variant, 0);
            clip_note(NULL, src[0]);
            return 0;
        }
    }
    g_rec_tme = b ? (int)((b->c[NRQ_MAT].u[0] >> 4) & 1) : -1;
    id = nr_model_record(mesh_pkt, variant);
    g_rec_tme = -1;
    census_note(src, variant, id != 0);
    if (id && b) {
        nr_rec *r = rec_of(id);
        memcpy(r->c, b->c, sizeof r->c);
        memcpy(r->bones, b->bones, sizeof r->bones);
        r->bones_hi = b->bones_hi;
        r->has_box = !(r->variant & (NRV_SKIN | NRV_SHADOW | NRV_LINES | NRV_ZSCALE)) ? rigid_box(r->mesh, r->c, r->box) : 0;
        memcpy(r->src, src, sizeof r->src);
        r->cam = g_base_key[0];
        if ((r->variant & NRV_SHADOW) && g_dbg_info < 6 && getenv("RG_NR_DEBUG")) {
            const uint32_t *in = (const uint32_t *)(uintptr_t)src[7];
            g_dbg_info++;
            if (in)
                fprintf(stderr, "nr shadow mesh %08X variant %03X: microcode %08X %08X %08X %08X %08X %08X\n", mesh_pkt, r->variant,
                        in[0], in[1], in[2], in[3], in[4], in[5]);
        }
        r->filled = 1;
        r->has_bb = 0;
        clip_note(r, src[0]);
    } else if (id) {
        nr_rec *r = rec_of(id);   /* tap constants: the tap computes and merges the bbox */
        r->has_bb = 0;
        r->vu_bbox = 1;
    } else {
        clip_note(NULL, src[0]);
    }
    return id;
}

uint32_t nr_model_record(uint32_t mesh_pkt, int variant)
{
    const nr_mesh *m;
    nr_rec *r;
    uint32_t id;
    if (!active() || !g_attached) { g_st.fallback_off++; return 0; }
    g_st.meshes++;
    if (variant < 0) { g_st.fallback_variant++; return 0; }
    if (variant & NRV_REFRACT) {
        /* RG_NR_REFRACT=0: the refraction material stays emulated */
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_NR_REFRACT"); on = !(e && e[0] == '0'); }
        if (!on) { g_st.fallback_variant++; return 0; }
    }
    m = nr_mesh_get(mesh_pkt, (variant & NRV_SKIN) != 0);
    if (m->bad) { g_st.fallback_mesh++; return 0; }
    {
        /* arrays the variant reads: UV (unless the environment map replaces
         * it), colours (vertex colour), normals (environment map, lights) */
        int need = 0;
        if (variant & NRV_SHADOW) {
            /* the shadow program takes each batch's vertices three at a time whatever the
             * batch PRIM says (strip / fan meshes too: the INSECT overlay's casters); a
             * non-list mesh needs every batch's range (batch[]) */
            if ((m->prim_mask & ~((1u << 3) | (1u << 4) | (1u << 5))) || (m->prim_mask != (1u << 3) && m->batch_overflow)) {
                static int pr;
                if (getenv("RG_NR_DEBUG") && pr < 8) {
                    pr++;
                    fprintf(stderr, "nr: shadow mesh %08X stays emulated: prim mask %x, %u batches%s\n", m->pkt, m->prim_mask,
                            m->nbatch, m->batch_overflow ? " (overflow)" : "");
                }
                g_st.fallback_mesh++;
                return 0;
            }
        } else if (variant & NRV_LINES) {
            /* the line program: its two layouts, every batch known */
            if ((m->prim_mask & ~((1u << 0x11) | (1u << 0x13))) || m->batch_overflow) { g_st.fallback_mesh++; return 0; }
        } else {
            if ((m->prim_mask & ~((1u << 3) | (1u << 4) | (1u << 5))) || !m->nidx) { g_st.fallback_mesh++; return 0; }
            /* UVs only matter when the material samples a texture */
            if (!(variant & (NRV_ENVMAP | NRV_REFRACT | NRV_REFLECT)) && g_rec_tme != 0 && !miss_uv_ok()) need |= NR_MISS_UV;
            if (variant & NRV_VCOL) need |= NR_MISS_COL;
            if (variant & (NRV_ENVMAP | NRV_LIGHT)) need |= NR_MISS_NRM;
            /* the reflection kind on a mesh without normals reads whatever an earlier batch
             * left (not reproducible, like the UV-less mesh): drawn with N = 0 (UV from the
             * view direction alone) unless RG_NR_MISSUV=0 */
            if ((variant & NRV_REFLECT) && !miss_uv_ok()) need |= NR_MISS_NRM;
        }
        if (m->missing & need) {
            static int printed;
            static uint32_t last_pkt[16];
            int seen = 0, q;
            g_st.fallback_mesh++;
            for (q = 0; q < printed && q < 16; q++) if (last_pkt[q] == m->pkt) seen = 1;
            if (!seen && printed < 16 && getenv("RG_NR_DEBUG")) {
                last_pkt[printed] = m->pkt;
                printed++;
                fprintf(stderr, "nr: mesh %08X variant %03X stays emulated: arrays missing %x (needs %x), %u batches, frame %u\n",
                        m->pkt, variant, m->missing, need, m->nbatch, g_frame_no);
            }
            return 0;
        }
    }
    if (!g_rec) {
        g_rec = (nr_rec *)calloc(NR_RECS, sizeof(nr_rec));
        if (!g_rec) return 0;
    }
#ifdef RG_HAVE_GPU
    if (!(variant & (NRV_SHADOW | NRV_LINES)) && m->id > g_prewarm_hi && g_store_gr && prewarm_on()) {
        /* a mesh decoded just now (ids only grow): its GPU copy is made here on the EE thread,
         * not at its first draw on the GS worker (docs/NATIVE-RENDER.md "Pre-warm") */
        gpu_nr_mesh pm;
        pm.id = m->id;
        pm.vtx = m->vtx;
        pm.nvtx = m->nvtx;
        pm.stride = sizeof(nr_vtx);
        pm.idx = m->idx;
        pm.nidx = m->nidx;
        gpu_nr_mesh_prewarm(g_store_gr, &pm);
        g_prewarm_hi = m->id;
    }
#endif
    id = g_next++;
    if (id % NR_RECS == 0) id = g_next++;      /* keep ids nonzero mod the ring too */
    r = rec_of(id);
    r->id = id;
    r->variant = variant;
    r->mesh = m;
    r->filled = 0;
    r->tapped = 0;
    r->has_box = 0;
    r->frame = g_frame_no;
    g_st.recorded++;
    return id;
}

/* ---- shadow volumes (nr_vu1sh.h) ----------------------------------------
 * The record's faces: positions decoded VU-exactly from the mesh (itof15 x
 * qw77, skinned by the record's bone rows), taken three at a time in batch
 * order (the mesh's triangle list = consecutive triples), and run through
 * nr_vu1sh_faces with the record's constants. */
typedef struct shbuf { float (*pos)[3]; uint32_t cap; nr_shface *f; int fcap; } shbuf;
/* one vertex's decoded position as the decode pieces compute it */
static void decode_pos(const nr_rec *r, const nr_vtx *x, float p[3])
{
    const float *ps = r->c[NRQ_POSSCALE].f;
    uint32_t k;
    p[0] = nr_vu1sh_pos(x->px, ps[0]);
    p[1] = nr_vu1sh_pos(x->py, ps[1]);
    p[2] = nr_vu1sh_pos(x->pz, ps[2]);
    if (r->variant & NRV_SKIN) {
        const float *rows[4][4];
        float w[4];
        int nb = 0;
        for (k = 0; k < 4; k++) {
            if (!x->wgt[k]) continue;
            rows[nb][0] = r->bones[x->bone[k]].f;
            rows[nb][1] = r->bones[x->bone[k] + 1].f;
            rows[nb][2] = r->bones[x->bone[k] + 2].f;
            rows[nb][3] = r->bones[x->bone[k] + 3].f;
            w[nb] = nr_vu1sh_weight(x->wgt[k]);
            nb++;
        }
        if (nb) nr_vu1sh_skin(p, (const float *const (*)[4])rows, w, nb, p);
        else p[0] = p[1] = p[2] = 0.0f;
    }
}
/* the line program's records for batch b of a line record */
typedef struct lnbuf { float (*pos)[3]; uint32_t cap; nr_lnrec *rec; int rcap; } lnbuf;
static int line_records(const nr_rec *r, uint32_t b, lnbuf *lb, int *four)
{
    const nr_mesh *m = r->mesh;
    uint32_t i, first = m->batch[b].first, n = m->batch[b].count;
    if (n > lb->cap) { lb->cap = n + 64; lb->pos = (float (*)[3])realloc(lb->pos, lb->cap * sizeof *lb->pos); }
    if ((int)n > lb->rcap) { lb->rcap = (int)n + 16; lb->rec = (nr_lnrec *)realloc(lb->rec, (size_t)lb->rcap * sizeof *lb->rec); }
    if (!lb->pos || !lb->rec) return 0;
    for (i = 0; i < n; i++) decode_pos(r, &m->vtx[first + i], lb->pos[i]);
    *four = m->batch[b].prim == 0x13;
    return nr_vu1ln_records(r->c, (const float (*)[3])lb->pos, n, *four, lb->rec, lb->rcap);
}
static int shadow_faces(const nr_rec *r, shbuf *b)
{
    const nr_mesh *m = r->mesh;
    uint32_t i, k, n = m->nidx, bi = 0, bo = 0;
    const float *ps = r->c[NRQ_POSSCALE].f;
    /* lists: the index array (consecutive triples); strip / fan meshes: each batch's
     * vertices in order, three at a time (n % 3 left over per batch, like the program) */
    int raw = m->prim_mask != (1u << 3);
    if (raw) {
        n = 0;
        for (bi = 0; bi < m->nbatch && bi < NR_MESH_MAXB; bi++) n += m->batch[bi].count / 3 * 3;
        bi = 0;
    }
    if (n > b->cap) {
        b->cap = n + 256;
        b->pos = (float (*)[3])realloc(b->pos, b->cap * sizeof *b->pos);
    }
    if ((int)(n / 3 * 5) > b->fcap) {
        b->fcap = (int)(n / 3 * 5) + 64;
        b->f = (nr_shface *)realloc(b->f, (size_t)b->fcap * sizeof *b->f);
    }
    if (!b->pos || !b->f) return 0;
    for (i = 0; i < n; i++) {
        const nr_vtx *x;
        if (raw) {
            while (bo >= m->batch[bi].count / 3 * 3) { bi++; bo = 0; }
            x = &m->vtx[m->batch[bi].first + bo++];
        } else {
            x = &m->vtx[m->idx[i]];
        }
        float p[3];
        p[0] = nr_vu1sh_pos(x->px, ps[0]);
        p[1] = nr_vu1sh_pos(x->py, ps[1]);
        p[2] = nr_vu1sh_pos(x->pz, ps[2]);
        if (r->variant & NRV_SKIN) {
            const float *rows[4][4];
            float w[4];
            int nb = 0;
            for (k = 0; k < 4; k++) {
                if (!x->wgt[k]) continue;
                rows[nb][0] = r->bones[x->bone[k]].f;
                rows[nb][1] = r->bones[x->bone[k] + 1].f;
                rows[nb][2] = r->bones[x->bone[k] + 2].f;
                rows[nb][3] = r->bones[x->bone[k] + 3].f;
                w[nb] = nr_vu1sh_weight(x->wgt[k]);
                nb++;
            }
            if (nb) nr_vu1sh_skin(p, (const float *const (*)[4])rows, w, nb, p);
            else p[0] = p[1] = p[2] = 0.0f;
        }
        b->pos[i][0] = p[0]; b->pos[i][1] = p[1]; b->pos[i][2] = p[2];
    }
    return nr_vu1sh_faces(r->c, (const float (*)[3])b->pos, n, b->f, b->fcap);
}

/* ---- verify mode: the VU1 program's packets vs the native math ----------- */
static shbuf g_vsh;          /* verify: the expected faces of the shadow record at the marker */
static struct { int nf, next, pending_reg; uint64_t meshes, faces, exact, close, bad, extra, missing, reg_bad; int printed; } g_vs;
static lnbuf g_vlb;          /* verify: the line record's expected records */
static struct { uint32_t batch; uint64_t meshes, batches, recs, exact, bad, unmatched; int printed; } g_vl;
static struct {
    const nr_rec *rec;       /* the marker most recently passed (EE thread) */
    uint32_t batch;
    uint64_t meshes, batches, vertices, adc, unmatched, mism[6], bad_meshes;
    int printed;
} g_ver;
static vu_gif_sink_fn g_p1_sink;
static void *g_p1_user;

static void verify_packet(const uint8_t *d, uint32_t bytes)
{
    const nr_rec *r = g_ver.rec;
    const nr_mesh *m;
    uint32_t prim, n, b, i;
    int bad = 0;
    if (!r || bytes < 64) return;
    m = r->mesh;
    /* the main packet: tag NLOOP 1 regs PRIM + A+D (PRMODE), then NLOOP n x {STQ, RGBAQ, XYZF2} */
    if ((rd32(d) & 0x7FFF) != 1 || rd32(d + 8) != 0xE0 || rd32(d + 40) != 0x1B) return;
    prim = rd32(d + 16);
    n = rd32(d + 48) & 0x7FFF;
    if (rd32(d + 56) != 0x412 || 64 + n * 48 > bytes) return;
    b = g_ver.batch;
    if (b >= m->nbatch || b >= NR_MESH_MAXB || m->batch[b].prim != prim || m->batch[b].count != n) {
        if (prim != 5) g_ver.unmatched++;    /* clipper fans come before the main packet */
        return;
    }
    g_ver.batch++;
    g_ver.batches++;
    for (i = 0; i < n; i++) {
        const uint8_t *v = d + 64 + i * 48;
        const nr_vtx *x = &m->vtx[m->batch[b].first + i];
        nr_vout e;
        int16_t pos[3] = { x->px, x->py, x->pz };
        int8_t nrm[3] = { x->nx, x->ny, x->nz };
        int16_t uv[2] = { x->u, x->v };
        uint8_t col[4] = { x->r, x->g, x->b, x->a };
        int32_t X = (int32_t)rd32(v + 32), Y = (int32_t)rd32(v + 36), Z = (int32_t)rd32(v + 40);
        uint32_t W = rd32(v + 44);
        float s, t, q, es[3], gsv[3];
        int fb = 0, c;
        g_ver.vertices++;
        if (W & 0x8000) { g_ver.adc++; continue; }
        nr_vu1_vertex(r->c, r->bones, r->variant, pos, nrm, uv, col, x->bone, x->wgt, &e);
        memcpy(&s, v, 4); memcpy(&t, v + 4, 4); memcpy(&q, v + 8, 4);
        if (abs((int16_t)(X - (int32_t)(e.sx * 16.0f))) > 1 || abs((int16_t)(Y - (int32_t)(e.sy * 16.0f))) > 1) fb |= 1;
        {
            int64_t dz = (int64_t)(Z >> 4) - (int64_t)((int32_t)(e.sz * 16.0f) >> 4);
            int64_t tol = 1 + (((Z >> 4) < 0 ? -(int64_t)(Z >> 4) : (Z >> 4)) >> 20);
            if (dz > tol || dz < -tol) fb |= 2;
        }
        if (abs((int)((W >> 4) & 0xFF) - (int)(((int32_t)(e.fog * 16.0f) >> 4) & 0xFF)) > 1) fb |= 4;
        {
            float ec[4] = { e.r, e.g, e.b, e.a };
            for (c = 0; c < 4; c++) if (abs((int32_t)rd32(v + 16 + 4 * c) - (int32_t)ec[c]) > 1) fb |= 8;
        }
        es[0] = e.s; es[1] = e.t; es[2] = e.q; gsv[0] = s; gsv[1] = t; gsv[2] = q;
        /* untextured material (PRMODE TME clear): S/T/Q are not used by the GS
         * (and may come from stale VU memory when the mesh has no UVs) */
        for (c = (r->c[NRQ_MAT].u[0] & 0x10) ? 0 : 3; c < 3; c++) {
            float df = es[c] - gsv[c], mg = gsv[c];
            if (df < 0) df = -df;
            if (mg < 0) mg = -mg;
            if (df > 1e-4f * mg && df > 2e-6f * (q < 0 ? -q : q) + 1e-12f) fb |= 16;
        }
        for (c = 0; c < 5; c++) if (fb & (1 << c)) g_ver.mism[c]++;
        if (fb) {
            bad = 1;
            if (g_ver.printed < 20) {
                g_ver.printed++;
                fprintf(stderr, "nr verify: mesh %u pkt %08X variant %02X batch %u v%u (bits %x): VU X %d Y %d Z %d rgba %d %d %d %d stq %g %g %g | native X %d Y %d Z %d rgba %.0f %.0f %.0f %.0f stq %g %g %g\n",
                        m->id, m->pkt, r->variant, b, i, fb, (int16_t)X, (int16_t)Y, Z >> 4, (int)rd32(v + 16),
                        (int)rd32(v + 20), (int)rd32(v + 24), (int)rd32(v + 28), s, t, q, (int16_t)(e.sx * 16.0f),
                        (int16_t)(e.sy * 16.0f), (int32_t)(e.sz * 16.0f) >> 4, e.r, e.g, e.b, e.a, e.s, e.t, e.q);
            }
        }
    }
    if (bad) g_ver.bad_meshes++;
}

/* a shadow program's kicks: register packet at qw35 / qw38, then the fan
 * packet (GIF tag NLOOP 1 PRIM + A+D, PRIM 5, PRMODE, tag NLOOP 4 EOP, 4 x
 * XYZF2) */
static void verify_shadow_packet(const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    uint32_t k;
    if (addr == 35u * 16 || addr == 38u * 16) { g_vs.pending_reg = (int)(addr / 16); return; }
    if (bytes != 128 || rd32(d + 16) != 5 || (rd32(d + 48) & 0xFFFF) != 0x8004) return;
    if (g_vs.next >= g_vs.nf) { g_vs.extra++; return; }
    {
        const nr_shface *f = &g_vsh.f[g_vs.next++];
        int ex = 1, cl = 1;
        g_vs.faces++;
        if (g_vs.pending_reg != (int)f->regq) g_vs.reg_bad++;
        g_vs.pending_reg = -1;
        for (k = 0; k < 4; k++) {
            const uint8_t *v = d + 64 + 16 * k;
            int32_t X = (int32_t)rd32(v), Y = (int32_t)rd32(v + 4), Z = (int32_t)rd32(v + 8), W = (int32_t)rd32(v + 12);
            if (X != f->x[k] || Y != f->y[k] || Z != f->z[k] || W != f->w[k]) ex = 0;
            if (abs(X - f->x[k]) > 1 || abs(Y - f->y[k]) > 1 || llabs((int64_t)(Z >> 4) - (f->z[k] >> 4)) > 1 ||
                ((W ^ f->w[k]) & 0x8FF0))
                cl = 0;
        }
        if (ex) g_vs.exact++;
        else if (cl) g_vs.close++;
        else {
            g_vs.bad++;
            if (g_vs.printed < 10) {
                g_vs.printed++;
                fprintf(stderr, "nr verify shadow: mesh %08X face %d: VU v0 %d %d %d %08X | native %d %d %d %08X\n",
                        g_ver.rec ? g_ver.rec->mesh->pkt : 0, g_vs.next - 1, (int32_t)rd32(d + 64), (int32_t)rd32(d + 68),
                        (int32_t)rd32(d + 72), rd32(d + 76), f->x[0], f->y[0], f->z[0], (unsigned)f->w[0]);
            }
        }
    }
}

/* a line program's kick: GIF tag, PRIM 1, PRMODE, vertex tag (NLOOP = records),
 * per record PACKED RGBAQ + 8 XYZF2; one per batch, in batch order */
static void verify_line_packet(const uint8_t *d, uint32_t bytes)
{
    const nr_rec *r = g_ver.rec;
    int nr, four, i, k;
    uint32_t b = g_vl.batch;
    if (bytes < 64 || rd32(d + 16) != 1) return;
    if (b >= r->mesh->nbatch) { g_vl.unmatched++; return; }
    nr = line_records(r, b, &g_vlb, &four);
    g_vl.batch++;
    g_vl.batches++;
    if ((rd32(d + 48) & 0x7FFF) != (uint32_t)nr || bytes < 64 + (uint32_t)nr * 144) { g_vl.unmatched++; return; }
    for (i = 0; i < nr; i++) {
        const uint8_t *q = d + 64 + i * 144;
        const nr_lnrec *e = &g_vlb.rec[i];
        int ok = rd32(q) == 16 && rd32(q + 4) == 16 && rd32(q + 8) == 16 && rd32(q + 12) == e->alpha;
        for (k = 0; k < 8; k++) {
            const uint8_t *v = q + 16 + 16 * k;
            if ((int32_t)rd32(v) != e->x[k] || (int32_t)rd32(v + 4) != e->y[k] || (int32_t)rd32(v + 8) != e->z[k] ||
                rd32(v + 12) != (uint32_t)e->adc)
                ok = 0;
        }
        g_vl.recs++;
        if (ok) g_vl.exact++;
        else {
            g_vl.bad++;
            if (g_vl.printed < 10) {
                g_vl.printed++;
                fprintf(stderr, "nr verify lines: mesh %08X batch %u rec %d: VU v0 %d %d %d %08X a %u | native %d %d %d %08X a %u\n",
                        r->mesh->pkt, b, i, (int32_t)rd32(q + 16), (int32_t)rd32(q + 20), (int32_t)rd32(q + 24), rd32(q + 28),
                        rd32(q + 12), e->x[0], e->y[0], e->z[0], (unsigned)e->adc, e->alpha);
            }
        }
    }
}

static uint64_t g_p1_calls;
static void comp_check_p1(const uint8_t *d, uint32_t bytes);
static void p1_comp(void *user, const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    comp_check_p1(d, bytes);
    g_p1_sink(user, d, bytes, addr);
}
static void p1_tap(void *user, const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    g_p1_calls++;
    if (g_ver.rec) {
        if (g_ver.rec->variant & NRV_SHADOW) verify_shadow_packet(d, bytes, addr);
        else if (g_ver.rec->variant & NRV_LINES) verify_line_packet(d, bytes);
        else verify_packet(d, bytes);
    }
    g_p1_sink(user, d, bytes, addr);
}

/* ---- the program's one side effect the game reads back --------------------
 * The output pieces of the Z-scale family (0x43CA90 / 0x43CD40 / 0x43D110)
 * keep a running min (qw98) and max (qw99) of every vertex's screen vector
 * (x, y, scaled and clamped Z, clamped fog) in VU1 data memory, and a later
 * emulated VU1 program consumes it: the offscreen character composite
 * (ModelDrawOffscreenCompositeMaybe_16aac0, whose packets run the program
 * D_00445C60 at 0x960) sizes each part's rectangle with it; no game code
 * reads VU memory directly.  A native mesh skips the program, so the same
 * min/max is merged here, when the marker passes the VIF (the point where the
 * program would have run), from the record's constants (RG_NR_BBOX=0: off;
 * the characters at fields 8150/8290 then vanish: PSNR 16 dB).  Since the
 * composite program is native (below) only for ranges that run it emulated. */
static int bbox_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_BBOX"); on = e ? atoi(e) : 1; }
    return on;
}
/* the screen-vector min / max of a Z-scale record's vertices (position-only
 * transcription of nr_vu1_vertex: x, y, z * 87.z min qw1.y, fog clamp) into
 * r->bb_lo / bb_hi, and its screen box (coherence rectangle).  Record time, EE. */
static void bbox_compute(nr_rec *r)
{
    const nr_mesh *m = r->mesh;
    const nr_qw *c = r->c;
    const float *ps = c[NRQ_POSSCALE].f, *fg = c[NRQ_FOG].f;
    const float *s0 = c[NRQ_SCREEN].f, *s1 = c[NRQ_SCREEN + 1].f, *s2 = c[NRQ_SCREEN + 2].f, *s3 = c[NRQ_SCREEN + 3].f;
    float zs = c[NRQ_MAT].f[2], zmax = c[NRQ_ZMAX].f[1];
    static const union { uint32_t u; float f; } w255 = { 0x3B808081u };
    nr_qw lo, hi;
    uint32_t i, k;
    int skin = (r->variant & NRV_SKIN) != 0, wok = 1;
    float bx0 = 1e30f, by0 = 1e30f, bx1 = -1e30f, by1 = -1e30f;
    for (k = 0; k < 4; k++) { lo.f[k] = 3.0e38f; hi.f[k] = -3.0e38f; }
    for (i = 0; i < m->nvtx; i++) {
        const nr_vtx *x = &m->vtx[i];
        float p[3], cl[4], q, v[4];
        p[0] = (float)x->px * (1.0f / 32768.0f) * ps[0];
        p[1] = (float)x->py * (1.0f / 32768.0f) * ps[1];
        p[2] = (float)x->pz * (1.0f / 32768.0f) * ps[2];
        if (skin) {
            float a0 = 0, a1 = 0, a2 = 0;
            for (k = 0; k < 4; k++) {
                const float *r0, *r1, *r2, *r3;
                float w, px, py, pz;
                if (!x->wgt[k]) continue;
                w = (float)x->wgt[k] * w255.f;
                r0 = r->bones[x->bone[k]].f; r1 = r->bones[x->bone[k] + 1].f;
                r2 = r->bones[x->bone[k] + 2].f; r3 = r->bones[x->bone[k] + 3].f;
                px = p[0] * w; py = p[1] * w; pz = p[2] * w;
                a0 += r0[0] * px + r1[0] * py + r2[0] * pz + r3[0] * w;
                a1 += r0[1] * px + r1[1] * py + r2[1] * pz + r3[1] * w;
                a2 += r0[2] * px + r1[2] * py + r2[2] * pz + r3[2] * w;
            }
            p[0] = a0; p[1] = a1; p[2] = a2;
        }
        for (k = 0; k < 4; k++) cl[k] = s0[k] * p[0] + s1[k] * p[1] + s2[k] * p[2] + s3[k];
        q = 1.0f / cl[3];
        v[0] = cl[0] * q;
        v[1] = cl[1] * q;
        if (!(cl[3] > 1e-6f)) wok = 0;
        if (v[0] < bx0) bx0 = v[0];
        if (v[0] > bx1) bx1 = v[0];
        if (v[1] < by0) by0 = v[1];
        if (v[1] > by1) by1 = v[1];
        v[2] = cl[2] * q * zs;
        if (v[2] > zmax) v[2] = zmax;
        v[3] = fg[0] + fg[3] * cl[3];
        if (v[3] > fg[1]) v[3] = fg[1];
        if (v[3] < fg[2]) v[3] = fg[2];
        for (k = 0; k < 4; k++) {
            if (v[k] < lo.f[k]) lo.f[k] = v[k];
            if (v[k] > hi.f[k]) hi.f[k] = v[k];
        }
    }
    r->bb_lo = lo;
    r->bb_hi = hi;
    r->has_bb = m->nvtx != 0;
    if (wok && m->nvtx) {
        r->box[0] = bx0; r->box[1] = by0; r->box[2] = bx1; r->box[3] = by1;
        r->has_box = 1;
    }
}
/* merge a record's bb into VU qw98/99 (the VIF tap, where the output piece
 * would have run) */
static void bbox_merge_vu(const nr_rec *r, vu_state *vu)
{
    nr_qw lo, hi;
    uint32_t k;
    if (!r->has_bb) return;
    memcpy(&lo, vu->mem + 98 * 16, 16);
    memcpy(&hi, vu->mem + 99 * 16, 16);
    for (k = 0; k < 4; k++) {
        if (r->bb_lo.f[k] < lo.f[k]) lo.f[k] = r->bb_lo.f[k];
        if (r->bb_hi.f[k] > hi.f[k]) hi.f[k] = r->bb_hi.f[k];
    }
    memcpy(vu->mem + 98 * 16, &lo, 16);
    memcpy(vu->mem + 99 * 16, &hi, 16);
    g_st.bbox_meshes++;
}

/* ---- offscreen composite (nr_comp.h, docs/NATIVE-RENDER.md "Offscreen composite")
 * VU qw98/99 as the EE builds the draw list: DrawListResetClipRangeMaybe_148040
 * (override: nr_clip_reset) uploads (2^24, -2^24) there, then every Z-scale
 * mesh merges its screen min / max.  While every such mesh since the reset is
 * native, g_cl holds exactly what VU memory would hold (the same C math as
 * the tap's merge), and the composite's sprites (ScreenTexOverlayWriteSprite
 * Maybe_16a890, override: nr_comp_sprite) are built here by the program's
 * semantics (nr_comp_strips) and sent as a DIRECT GIF packet: no MSCAL, no
 * VU1, no VIF tap.  An emulated mesh while the clip range is on, or no reset
 * seen yet, makes g_cl unknown: the sprites then run the VU program, and the
 * native meshes of that range are merged into VU memory by the tap (vu_bbox).
 * RG_NR_COMP = native (default) | check (VU program + tap, and every kicked
 * sprite compared with nr_comp_strips) | off (VU program + tap always). */
enum { NRCP_NATIVE = 0, NRCP_CHECK = 1, NRCP_OFF = 2 };
static int comp_mode(void)
{
    static int m = -1;
    if (m < 0) {
        const char *e = getenv("RG_NR_COMP");
        m = (e && !strcmp(e, "check")) ? NRCP_CHECK : (e && !strcmp(e, "off")) ? NRCP_OFF : NRCP_NATIVE;
    }
    return m;
}
int nr_comp_native(void) { return comp_mode() == NRCP_NATIVE; }
#define NR_CL_IDS 1024
/* The range starts known and empty (as after DrawListResetClipRangeMaybe_148040's upload of
 * (2^24, -2^24)): a run that begins mid-frame (a state load) needs no VU program for its first
 * composite either (docs/NATIVE-RENDER.md "VU1 off the default path"). */
static struct {
    int known;               /* lo / hi = VU qw98/99 at this point of the build */
    nr_qw lo, hi;
    uint32_t ids[NR_CL_IDS]; /* native Z-scale records since the reset */
    int nids;
} g_cl = { 1, { { 0x4B800000u, 0x4B800000u, 0x4B800000u, 0x4B800000u } },
           { { 0xCB800000u, 0xCB800000u, 0xCB800000u, 0xCB800000u } }, { 0 }, 0 };
static struct {
    uint64_t resets, sprites_native, sprites_vu, strips, unknown_emu, unknown_ovf, vu_merges, empty;
    uint64_t chk_runs, chk_strips, chk_bad, chk_extra, chk_missing, chk_wdiff;
    int printed;
} g_cs;
/* the range becomes unknown: the VU program will run, VU memory needs the
 * native meshes recorded since the reset (their markers have not reached the
 * VIF yet: the frame's DMA starts after the build) */
static void clip_unknown(void)
{
    int i;
    if (!g_cl.known) return;
    g_cl.known = 0;
    for (i = 0; i < g_cl.nids; i++) {
        nr_rec *q = rec_of(g_cl.ids[i]);
        if (q->id == g_cl.ids[i]) q->vu_bbox = 1;
    }
    g_cl.nids = 0;
}
void nr_clip_reset(uint32_t ctx)
{
    int k;
    (void)ctx;
    if (!active()) return;
    g_cs.resets++;
    g_cl.known = 1;
    for (k = 0; k < 4; k++) { g_cl.lo.u[k] = 0x4B800000u; g_cl.hi.u[k] = 0xCB800000u; }
    g_cl.nids = 0;
}
/* record time: a mesh about to be drawn (r: its native record, or NULL when
 * it stays emulated) by draw context ctx */
static void clip_note(nr_rec *r, uint32_t ctx)
{
    int k;
    /* a native mesh whose program has no Z-scale output piece leaves qw98/99 alone: only
     * 0x43CA90 / 0x43CD40 / 0x43D110 store there (none of the shadow / line / other pieces
     * does; out/nrender/dis listings), so it does not make the range unknown (it did before
     * 2026-10-18 (7): 6,995 ranges to field 23,260, each a composite drawn by the VU program) */
    if (r && !(r->variant & NRV_ZSCALE)) return;
    if (r) {
        bbox_compute(r);
        /* the VU program needs it in VU memory unless the sprite is built here */
        r->vu_bbox = comp_mode() != NRCP_NATIVE || nr_mode() != NR_NATIVE || !g_cl.known;
        if (!g_cl.known) return;
        if (g_cl.nids == NR_CL_IDS) { g_cs.unknown_ovf++; r->vu_bbox = 1; clip_unknown(); return; }
        g_cl.ids[g_cl.nids++] = r->id;
        if (r->has_bb)
            for (k = 0; k < 4; k++) {
                if (r->bb_lo.f[k] < g_cl.lo.f[k]) g_cl.lo.f[k] = r->bb_lo.f[k];
                if (r->bb_hi.f[k] > g_cl.hi.f[k]) g_cl.hi.f[k] = r->bb_hi.f[k];
            }
        return;
    }
    /* an emulated mesh while the clip range is on: its output piece merges
     * into VU memory, which only the VU program then knows */
    if (ctx && *(const int32_t *)(uintptr_t)(ctx + 0x3CCCu) != 0 && g_cl.known) {
        g_cs.unknown_emu++;
        clip_unknown();
    }
}

/* check mode: the sprites the VU program must kick, in DMA order */
#define NR_CHK_Q 64
static struct { nr_comp_strip s[32]; int n; } g_chkq[NR_CHK_Q];
static int g_chkq_h, g_chkq_t;     /* the EE pushes at h, the VU side pops at t */
static struct { int in_run, k; } g_chkr;

int nr_comp_sprite(uint32_t ctx, const float *r, uint32_t *dst, int cap_qw)
{
    nr_comp_in in;
    nr_comp_strip st[32];
    int n, k, j, q;
    (void)ctx;
    if (!active() || nr_mode() != NR_NATIVE || comp_mode() == NRCP_OFF || !g_cl.known) { g_cs.sprites_vu++; return -1; }
    memcpy(in.rmin, r, 16);
    memcpy(in.rmax, r + 4, 16);
    memcpy(in.dy, r + 8, 16);
    in.ofs[0] = r[12];
    in.ofs[1] = r[13];
    in.i_reg = 0.0f;   /* only the W word of the second XYZ2 depends on I (docs) */
    memcpy(in.lo, g_cl.lo.f, 12);
    memcpy(in.hi, g_cl.hi.f, 12);
    n = nr_comp_strips(&in, st, 32);
    if (comp_mode() == NRCP_CHECK) {
        /* the VU program runs (original packet) on the bbox the tap merges */
        if (n > 0 && ((g_chkq_h + 1) % NR_CHK_Q) != g_chkq_t) {
            memcpy(g_chkq[g_chkq_h].s, st, (size_t)n * sizeof st[0]);
            g_chkq[g_chkq_h].n = n;
            g_chkq_h = (g_chkq_h + 1) % NR_CHK_Q;
        }
        g_cs.sprites_vu++;
        return -1;
    }
    if (n < 0 || 2 + 4 * n > cap_qw) { g_cs.sprites_vu++; return -1; }
    g_cs.sprites_native++;
    if (n == 0) { g_cs.empty++; return 0; }
    g_cs.strips += (uint64_t)n;
    /* DMA CNT (1 + 4n qwords) + VIF NOP, DIRECT; GIF tag: qw144's (PACKED, NREG 4:
     * UV XYZ2 UV XYZ2) with NLOOP n, EOP; then the strips' register qwords */
    q = 1 + 4 * n;
    dst[0] = 0x10000000u | (uint32_t)q; dst[1] = 0; dst[2] = 0; dst[3] = 0x50000000u | (uint32_t)q;
    dst[4] = 0x8000u | (uint32_t)n; dst[5] = 0x40000000u; dst[6] = 0x4343u; dst[7] = 0;
    for (k = 0; k < n; k++)
        for (j = 0; j < 4; j++) memcpy(dst + 8 + (k * 4 + j) * 4, st[k].q[j], 16);
    return 1 + q;
}

/* check mode, VU1 PATH1 output: the composite program's kicks (tag NLOOP 1,
 * EOP, NREG 4, regs UV XYZ2 UV XYZ2 + 4 qwords per sprite; a run ends with
 * the same tag at NLOOP 0) against the queue */
static void comp_check_p1(const uint8_t *d, uint32_t bytes)
{
    uint32_t w0, w1, w2, w3;
    int j, k;
    if (bytes < 16) return;
    w0 = rd32(d); w1 = rd32(d + 4); w2 = rd32(d + 8); w3 = rd32(d + 12);
    if (w1 != 0x40000000u || w2 != 0x4343u || w3 != 0) return;
    if (w0 == 0x8000u) {             /* end of a run */
        if (g_chkr.in_run) {
            if (g_chkq_t != g_chkq_h) {
                if (g_chkr.k < g_chkq[g_chkq_t].n) g_cs.chk_missing += (uint64_t)(g_chkq[g_chkq_t].n - g_chkr.k);
                g_chkq_t = (g_chkq_t + 1) % NR_CHK_Q;
            }
            g_cs.chk_runs++;
        }
        g_chkr.in_run = 0;
        g_chkr.k = 0;
        return;
    }
    if (w0 != 0x8001u || bytes < 80) return;
    g_chkr.in_run = 1;
    if (g_chkq_t == g_chkq_h || g_chkr.k >= g_chkq[g_chkq_t].n) { g_cs.chk_extra++; return; }
    {
        const nr_comp_strip *e = &g_chkq[g_chkq_t].s[g_chkr.k++];
        int bad = 0, wd = 0;
        for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++) {
                uint32_t got = rd32(d + 16 + j * 16 + k * 4), want = (uint32_t)e->q[j][k];
                /* compared bits: UV 14 + 14 (x, y); XYZ2 X, Y 16, ADC (w bit 15) */
                /* (Z is compared apart: the composite draws with the Z test off
                 * and Z writes masked, and the second vertex's Z is max(Z, I)
                 * with the VU's I register, which the EE does not know) */
                uint32_t mask = (j & 1) ? (k < 2 ? 0xFFFFu : k == 2 ? 0u : 0x8000u) : (k < 2 ? 0x3FFFu : 0u);
                if ((got ^ want) & mask) bad = 1;
                else if (got != want && (j & 1)) wd = 1;
            }
        g_cs.chk_strips++;
        if (bad) {
            g_cs.chk_bad++;
            if (g_cs.printed < 10) {
                g_cs.printed++;
                fprintf(stderr, "nr comp check: sprite differs: VU");
                for (j = 0; j < 16; j++) fprintf(stderr, " %08X", rd32(d + 16 + j * 4));
                fprintf(stderr, " | native");
                for (j = 0; j < 16; j++) fprintf(stderr, " %08X", (uint32_t)e->q[j >> 2][j & 3]);
                fputc('\n', stderr);
            }
        }
        if (wd) g_cs.chk_wdiff++;
    }
}

/* ---- slice 1 check: game constants vs VU memory at the marker -------------
 * Every qword (lane) the native pipeline reads, compared with what the VU1
 * program would read when the marker passes the VIF (RG_NR_CONST=check, and
 * in verify mode).  Floats within 1e-5 relative (+1e-6 absolute: the VU's
 * FMAC rounding and the order of the program at 0 vs C float). */
enum { CG_VIEW, CG_CAM, CG_LIGHT, CG_OBJ, CG_DERIVED, CG_INFO, CG_MAT, CG_BONES, CG_N };
static const char *const cg_name[CG_N] = { "view 0-19", "camera 24-26", "lights 33-43", "object 60-63",
                                           "derived 64-111", "info 77-81", "material 82-88", "bones" };
static struct { uint64_t recs, bad_recs, inexact_recs, cmp[CG_N], bad[CG_N]; int printed; } g_chk;

static int fdiff(float a, float b)
{
    float d = a - b, m = fabsf(a) > fabsf(b) ? fabsf(a) : fabsf(b);
    if (a == b || !memcmp(&a, &b, 4)) return 0;
    if (d != d) return 1;
    return fabsf(d) > 1e-5f * m + 1e-6f;
}

static void const_check(const nr_rec *r, const uint8_t *vumem)
{
    /* qword, lane mask (bit 0 = x), group, 1 = integer compare */
    static const struct { uint16_t q; uint8_t lanes, grp, integer; } L[] = {
        { 1, 2, CG_VIEW, 0 }, { 24, 15, CG_CAM, 0 }, { 25, 15, CG_CAM, 0 }, { 26, 15, CG_CAM, 0 }, { 27, 15, CG_CAM, 0 },
        { 33, 15, CG_LIGHT, 0 }, { 34, 15, CG_LIGHT, 0 }, { 35, 15, CG_LIGHT, 0 }, { 36, 15, CG_LIGHT, 0 },
        { 37, 15, CG_LIGHT, 0 }, { 39, 15, CG_LIGHT, 0 }, { 40, 15, CG_LIGHT, 0 }, { 41, 7, CG_LIGHT, 1 },
        { 42, 15, CG_LIGHT, 0 }, { 43, 15, CG_LIGHT, 0 },
        { 60, 15, CG_OBJ, 0 }, { 61, 15, CG_OBJ, 0 }, { 62, 15, CG_OBJ, 0 }, { 63, 15, CG_OBJ, 0 },
        { 64, 7, CG_DERIVED, 0 }, { 65, 7, CG_DERIVED, 0 }, { 66, 7, CG_DERIVED, 0 },
        { 68, 15, CG_DERIVED, 0 }, { 69, 15, CG_DERIVED, 0 }, { 70, 15, CG_DERIVED, 0 }, { 71, 15, CG_DERIVED, 0 },
        { 100, 15, CG_DERIVED, 0 }, { 101, 15, CG_DERIVED, 0 }, { 102, 15, CG_DERIVED, 0 }, { 111, 4, CG_DERIVED, 0 },
        { 77, 7, CG_INFO, 0 }, { 78, 7, CG_INFO, 0 }, { 79, 3, CG_INFO, 0 }, { 81, 1, CG_INFO, 1 }, { 81, 8, CG_INFO, 0 },
        { 82, 15, CG_MAT, 0 }, { 83, 7, CG_MAT, 0 }, { 87, 3, CG_MAT, 1 }, { 87, 4, CG_MAT, 0 }, { 88, 3, CG_MAT, 0 },
    };
    /* the shadow program's reads (nr_vu1sh.c) */
    static const struct { uint16_t q; uint8_t lanes, grp, integer; } LS[] = {
        { 0, 15, CG_VIEW, 1 }, { 8, 15, CG_VIEW, 0 }, { 9, 15, CG_VIEW, 0 }, { 10, 15, CG_VIEW, 0 }, { 11, 15, CG_VIEW, 0 },
        { 12, 15, CG_VIEW, 0 }, { 13, 15, CG_VIEW, 0 }, { 14, 15, CG_VIEW, 0 }, { 15, 15, CG_VIEW, 0 }, { 16, 15, CG_VIEW, 0 },
        { 24, 15, CG_CAM, 0 }, { 25, 15, CG_CAM, 0 }, { 26, 15, CG_CAM, 0 }, { 27, 15, CG_CAM, 0 },
        { 30, 15, CG_LIGHT, 0 }, { 31, 15, CG_LIGHT, 0 }, { 32, 15, CG_LIGHT, 0 }, { 33, 15, CG_LIGHT, 0 }, { 34, 7, CG_LIGHT, 0 },
        { 35, 15, CG_LIGHT, 1 }, { 36, 7, CG_LIGHT, 1 }, { 37, 15, CG_LIGHT, 1 }, { 38, 15, CG_LIGHT, 1 }, { 39, 7, CG_LIGHT, 1 },
        { 40, 15, CG_LIGHT, 1 },
        { 60, 15, CG_OBJ, 0 }, { 61, 15, CG_OBJ, 0 }, { 62, 15, CG_OBJ, 0 }, { 63, 15, CG_OBJ, 0 },
        { 76, 1, CG_INFO, 1 }, { 77, 7, CG_INFO, 0 }, { 87, 1, CG_MAT, 1 },
    };
    unsigned i, k, nl = (r->variant & NRV_SHADOW) ? sizeof LS / sizeof LS[0] : sizeof L / sizeof L[0];
    int bad = 0, grpbad[CG_N] = { 0 }, inexact = 0;
    g_chk.recs++;
    for (i = 0; i < nl; i++) {
        nr_qw v;
        int qb = 0;
        unsigned q = (r->variant & NRV_SHADOW) ? LS[i].q : L[i].q;
        unsigned lanes = (r->variant & NRV_SHADOW) ? LS[i].lanes : L[i].lanes;
        unsigned grp = (r->variant & NRV_SHADOW) ? LS[i].grp : L[i].grp;
        unsigned integer = (r->variant & NRV_SHADOW) ? LS[i].integer : L[i].integer;
        memcpy(&v, vumem + q * 16, 16);
        for (k = 0; k < 4; k++) {
            if (!(lanes & (1 << k))) continue;
            if (integer ? v.u[k] != r->c[q].u[k] : fdiff(v.f[k], r->c[q].f[k])) qb = 1;
            if (v.u[k] != r->c[q].u[k]) inexact = 1;
        }
        if (qb) {
            grpbad[grp] = 1;
            if (g_chk.printed < 30) {
                g_chk.printed++;
                fprintf(stderr, "nr const check: rec %u mesh %08X var %02X qw%u: VU %g %g %g %g (%08X %08X %08X %08X) | game %g %g %g %g (%08X %08X %08X %08X)\n",
                        r->id, r->mesh->pkt, r->variant, q, v.f[0], v.f[1], v.f[2], v.f[3], v.u[0], v.u[1], v.u[2], v.u[3],
                        r->c[q].f[0], r->c[q].f[1], r->c[q].f[2], r->c[q].f[3], r->c[q].u[0],
                        r->c[q].u[1], r->c[q].u[2], r->c[q].u[3]);
                fprintf(stderr, "    src: ctx %08X view %08X light %08X obj %08X info %08X skin %08X mat %08X cam %08X (now %08X)\n",
                        r->src[0], r->src[1], r->src[2], r->src[3], r->src[4], r->src[5], r->src[6], r->cam,
                        cam_of(r->src[0]));
                if (q == 71 && g_chk.printed < 8) {
                    static const int dq[] = { 4, 5, 6, 7, 24, 25, 26, 27, 60, 61, 62, 63, 68, 71 };
                    unsigned z;
                    for (z = 0; z < sizeof dq / sizeof dq[0]; z++) {
                        nr_qw w;
                        memcpy(&w, vumem + dq[z] * 16, 16);
                        fprintf(stderr, "    qw%d VU %g %g %g %g | game %g %g %g %g\n", dq[z], w.f[0], w.f[1], w.f[2], w.f[3],
                                r->c[dq[z]].f[0], r->c[dq[z]].f[1], r->c[dq[z]].f[2], r->c[dq[z]].f[3]);
                    }
                }
            }
        }
    }
    if (r->variant & NRV_SKIN) {
        /* the bone rows the mesh's vertices use */
        const nr_mesh *m = r->mesh;
        uint8_t used[NR_BONE_ROWS] = { 0 };
        for (i = 0; i < m->nvtx; i++)
            for (k = 0; k < 4; k++)
                if (m->vtx[i].wgt[k]) used[m->vtx[i].bone[k]] = 1;
        for (i = 0; i + 3 < NR_BONE_ROWS; i++) {
            if (!used[i]) continue;
            for (k = 0; k < 16; k++) {
                float a, b;
                memcpy(&a, vumem + (768 + i + k / 4) * 16 + (k & 3) * 4, 4);
                b = r->bones[i + k / 4].f[k & 3];
                if (fdiff(a, b)) {
                    grpbad[CG_BONES] = 1;
                    if (g_chk.printed < 30) {
                        g_chk.printed++;
                        fprintf(stderr, "nr const check: rec %u mesh %08X bone row %u lane %u: VU %g game %g (game rows %u)\n",
                                r->id, r->mesh->pkt, 768 + i + k / 4, k & 3, a, b, r->bones_hi);
                    }
                    break;
                }
            }
        }
        g_chk.cmp[CG_BONES]++;
    }
    for (k = 0; k < CG_N; k++) {
        if (k != CG_BONES) g_chk.cmp[k]++;
        if (grpbad[k]) { g_chk.bad[k]++; bad = 1; }
    }
    if (bad) g_chk.bad_recs++;
    if (inexact) g_chk.inexact_recs++;
}

/* ---- VIF1 tap: constants at the marker ------------------------------------ */
static struct {
    vif_gif_sink_fn sink;
    void *user;
    vu_state *vu;
} g_tap;

static void tap_sink(void *user, const uint8_t *d, uint32_t bytes)
{
    (void)user;
    if (bytes == 32 && rd32(d) == 0x00008001u && rd32(d + 4) == 0x10000000u && rd32(d + 8) == 0x0Eu &&
        rd32(d + 24) == GS_NATIVE_MARK && g_rec && !(rd32(d + 20) & 0x80000000u)) {   /* (bit 63: an immediate record, nr_im.h) */
        uint32_t id = rd32(d + 16);
        nr_rec *r = rec_of(id);
        if (r->id == id && g_tap.vu) {
            if (cmode() == NRC_TAP || !r->filled) {
                memcpy(r->c, g_tap.vu->mem, sizeof r->c);
                memcpy(r->bones, g_tap.vu->mem + 768 * 16, sizeof r->bones);
                r->filled = 1;
            } else if (cmode() == NRC_CHECK || nr_mode() == NR_VERIFY) {
                const_check(r, g_tap.vu->mem);
            }
            r->tapped = 1;
            g_st.tapped++;
            if (nr_mode() == NR_VERIFY) {
                if (g_ver.rec && (g_ver.rec->variant & NRV_SHADOW) && g_vs.next < g_vs.nf) g_vs.missing += (uint64_t)(g_vs.nf - g_vs.next);
                g_ver.rec = r; g_ver.batch = 0; g_ver.meshes++;
                if (r->variant & NRV_LINES) { g_vl.batch = 0; g_vl.meshes++; }
                if (r->variant & NRV_SHADOW) {
                    g_vs.nf = shadow_faces(r, &g_vsh);
                    g_vs.next = 0;
                    g_vs.pending_reg = -1;
                    g_vs.meshes++;
                }
            }
            else if ((r->variant & NRV_ZSCALE) && bbox_on() && r->vu_bbox) {
                if (!r->has_bb) bbox_compute(r);
                bbox_merge_vu(r, g_tap.vu);
                g_cs.vu_merges++;
            }
        } else {
            g_st.tap_stale++;
        }
    }
    g_tap.sink(g_tap.user, d, bytes);
}

void nr_runtime_attach_vif(struct vif_state *vif1, struct vu_state *vu1)
{
    if (!active() || !need_tap() || !vif1 || vif1->gif_sink == tap_sink) return;
    g_tap.sink = vif1->gif_sink;
    g_tap.user = vif1->gif_user;
    g_tap.vu = vu1;
    if (vu1) g_vu1mem = vu1->mem;
    vif1->gif_sink = tap_sink;
    if (nr_mode() == NR_VERIFY && vu1 && vu1->gif_sink) {
        g_p1_sink = vu1->gif_sink;
        g_p1_user = vu1->gif_user;
        vu1->gif_sink = p1_tap;
    } else if (nr_mode() == NR_NATIVE && comp_mode() == NRCP_CHECK && vu1 && vu1->gif_sink) {
        g_p1_sink = vu1->gif_sink;
        g_p1_user = vu1->gif_user;
        vu1->gif_sink = p1_comp;
    }
}

#ifdef RG_HAVE_GPU
/* ---- GS thread: the draw ---------------------------------------------------- */
static gpu_nr_draw g_draw;      /* GS thread only */
static int g_fault;             /* RG_NR_FAULT (test controls only) */
static int g_dbg, g_dbgn;         /* RG_NR_DEBUG */
static int g_cullmode = 1;      /* RG_NR_CULL: 1 as the program, 0 off, -1 inverted (checks) */
static int g_nobox;             /* RG_NR_NOBOX=1: coherence rectangle = scissor (check) */
static int g_noswap;            /* RG_NR_NOSWAP=1: shadow faces change ALPHA (one batch per run of faces) */

static void build_cb_cv(const nr_qw *c, int v, gpu_nr_draw *g)
{
    int k;
    float m82[4], add[3];
    memset(g->cb, 0, sizeof g->cb);
    for (k = 0; k < 4; k++) memcpy(g->cb[k], c[NRQ_SCREEN + k].f, 16);
    memcpy(g->cb[4], c[NRQ_POSSCALE].f, 16);
    memcpy(g->cb[5], c[NRQ_NRMSCALE].f, 16);
    g->cb[6][0] = c[NRQ_UVSCALE].f[0];
    g->cb[6][1] = c[NRQ_UVSCALE].f[1];
    g->cb[6][2] = c[NRQ_UVOFS].f[0];
    g->cb[6][3] = c[NRQ_UVOFS].f[1];
    /* colour stage constants (0x43A620 / 0x43AEC0) */
    memcpy(m82, c[NRQ_COLMUL].f, 16);
    m82[3] *= c[NRQ_FLAGS].f[3];
    add[0] = c[NRQ_COLADD].f[0]; add[1] = c[NRQ_COLADD].f[1]; add[2] = c[NRQ_COLADD].f[2];
    for (k = 0; k < 4; k++) {
        if (c[NRQ_MAT].u[1] & 0x200) g->cb[7][k] = m82[k] * c[NRQ_MATCOL2].f[k];
        else g->cb[7][k] = m82[k] * c[NRQ_MATCOL].f[k] + (k < 3 ? add[k] : 0.0f) * 128.0f;
    }
    memcpy(g->cb[8], c[NRQ_COLCLAMP].f, 16);
    memcpy(g->cb[9], c[NRQ_FOG].f, 16);
    g->cb[10][0] = c[NRQ_MAT].f[2];
    g->cb[10][1] = c[NRQ_ZMAX].f[1];
    /* environment map: view(24..26).xy x object rotation (64..66) */
    if (v & NRV_ENVMAP) {
        float e[3][2];
        for (k = 0; k < 3; k++) {
            const float *rr = c[NRQ_NRMMTX + k].f;
            e[k][0] = c[NRQ_VIEW].f[0] * rr[0] + c[NRQ_VIEW + 1].f[0] * rr[1] + c[NRQ_VIEW + 2].f[0] * rr[2];
            e[k][1] = c[NRQ_VIEW].f[1] * rr[0] + c[NRQ_VIEW + 1].f[1] * rr[1] + c[NRQ_VIEW + 2].f[1] * rr[2];
        }
        g->cb[12][0] = e[0][0]; g->cb[12][1] = e[0][1]; g->cb[12][2] = e[1][0]; g->cb[12][3] = e[1][1];
        g->cb[13][0] = e[2][0]; g->cb[13][1] = e[2][1];
    }
    if (v & NRV_REFLECT) {
        /* kind 0x43F100: object matrix rows qw60-63 (R[12..15]), camera position qw28
         * (R[16]), object rotation qw64-66 (R[17..19]); never with the lights (R[14..21]) */
        for (k = 0; k < 4; k++) memcpy(g->cb[12 + k], c[60 + k].f, 16);
        memcpy(g->cb[16], c[NRQ_CAMPOS].f, 16);
        for (k = 0; k < 3; k++) memcpy(g->cb[17 + k], c[NRQ_NRMMTX + k].f, 16);
    }
    if (v & NRV_REFRACT) {
        /* kind 0x43ECD0: the clip matrix qw72-75, the material's offset / scale (qw82) */
        for (k = 0; k < 4; k++) memcpy(g->cb[12 + k], c[NRQ_CLIP + k].f, 16);
        g->cb[16][0] = (c[NRQ_COLMUL].f[0] - 1.0f) * 0.05f;
        g->cb[16][1] = (c[NRQ_COLMUL].f[1] - 1.0f) * 0.05f;
        g->cb[16][2] = c[NRQ_COLMUL].f[2];
        g->cb[16][3] = 0.0f;
    }
    if (v & NRV_LIGHT) {
        int j;
        for (k = 0; k < 3; k++) memcpy(g->cb[14 + k], c[NRQ_LIGHTDIR + k].f, 16);
        for (k = 0; k < 5; k++)
            for (j = 0; j < 4; j++) g->cb[17 + k][j] = c[NRQ_LIGHTCOL + k].f[j] * c[NRQ_COLMUL].f[j];
        g->cb[21][3] *= c[NRQ_FLAGS].f[3];
    }
    {
        uint32_t vv = (uint32_t)v;
        memcpy(&g->cb[22][0], &vv, 4);
        memcpy(&g->cb[22][2], &c[NRQ_MAT].u[1], 4);   /* 87.y flags (0x43B120's 0x100 path) */
    }
    /* deliberate faults for the verification controls (RG_NR_FAULT, docs
     * "Verification"): 1 UV scale halved, 2 colour x 0.6, 3 everything 2 pixels
     * to the right */
    if (g_fault == 1) { g->cb[6][0] *= 0.5f; g->cb[6][1] *= 0.5f; }
    else if (g_fault == 2) { for (k = 0; k < 3; k++) g->cb[7][k] *= 0.6f; }
    else if (g_fault == 3) { for (k = 0; k < 4; k++) g->cb[k][0] += 2.0f * g->cb[k][3]; }   /* screen x + 2 */
}
static void build_cb(const nr_rec *r, gpu_nr_draw *g) { build_cb_cv(r->c, r->variant, g); }

/* the shadow program's GS output, generated natively: per face the register
 * packet (A+D writes and a PACKED RGBAQ, parsed from VU qw35 / qw38 as the
 * program kicks them), PRIM 5 + PRMODE qw87.x, and the fan's vertices with
 * the GS's XYZF2 rules (ADC: no drawing kick) */
static shbuf g_dsh;
static uint64_t g_sh_faces, g_sh_tris, g_sh_bad;
/* one register packet of the shadow program (VU qw35 / qw38) as GS writes */
typedef struct shregs { int n; uint32_t reg[8]; uint64_t val[8]; } shregs;
static int shadow_regs(const nr_qw *c, uint32_t q, uint64_t rgbaq_q, shregs *o)
{
    uint32_t nloop = c[q].u[0] & 0x7FFF, nreg = c[q].u[1] >> 28, i, j;
    uint64_t regs = (uint64_t)c[q].u[2] | ((uint64_t)c[q].u[3] << 32);
    uint32_t a = q + 1;
    o->n = 0;
    if (nreg == 0) nreg = 16;
    if ((c[q].u[1] >> 26 & 3) != 0) return -1;      /* PACKED only */
    for (i = 0; i < nloop; i++)
        for (j = 0; j < nreg; j++, a++) {
            uint32_t desc = (uint32_t)(regs >> (4 * j)) & 15;
            if (a >= NRQ_CONST_N || o->n == 8) return -1;
            if (desc == 0xE) {
                uint32_t reg = c[a].u[2] & 0x7F;
                if (reg != GS_ALPHA_1 && reg != GS_ALPHA_2 && reg != GS_RGBAQ && reg != GS_TEST_1 && reg != GS_TEST_2)
                    return -1;
                o->reg[o->n] = reg;
                o->val[o->n++] = (uint64_t)c[a].u[0] | ((uint64_t)c[a].u[1] << 32);
            } else if (desc == 0x1) {
                o->reg[o->n] = GS_RGBAQ;
                o->val[o->n++] = (uint64_t)(c[a].u[0] & 0xFF) | ((uint64_t)(c[a].u[1] & 0xFF) << 8) |
                                 ((uint64_t)(c[a].u[2] & 0xFF) << 16) | ((uint64_t)(c[a].u[3] & 0xFF) << 24) |
                                 (rgbaq_q << 32);
            } else {
                return -1;
            }
        }
    return 0;
}
static uint64_t alpha_swap_ab(uint64_t a) { return (a & ~0xFull) | ((a & 3) << 2) | ((a >> 2) & 3); }

/* generated primitives through the native immediate pipeline (gpu_nr_im_submit,
 * docs/NATIVE-RENDER.md "Generated primitives natively", checkpoint 9): a run of primitives
 * with one GS register state is one native draw; a state the native pipeline does not
 * cover goes to the GS draw path as before.  RG_NR_GENIM=0: the GS draw path for all. */
#define GEN_MAXP 2048
static gs_vertex g_gen_v[GEN_MAXP * 3];
static uint8_t g_gen_sw[GEN_MAXP];   /* per primitive: ALPHA with A / B swapped */
static int g_gen_n, g_gen_type, g_gen_anysw;
static uint64_t g_gen_nat, g_gen_emu, g_gen_runs;
static int genim_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_GENIM"); on = !(e && e[0] == '0') || NR_ONLY; }
    return on;
}
static void gen_flush(gpu_renderer *gr, gpu_gs *gs)
{
    int i, nv;
    if (!g_gen_n) return;
    g_gen_runs++;
    if (gpu_nr_im_submit_swap(gr, g_gen_v, g_gen_n, g_gen_type, g_gen_anysw ? g_gen_sw : NULL) >= 0) {
        g_gen_nat += (uint64_t)g_gen_n;
    } else {
        nv = g_gen_type == GS_PRIM_LINE ? 2 : 3;
        gpu_nr_prims_begin(gr);
        for (i = 0; i < g_gen_n; i++) {
            gpu_nr_prims_alpha_swap(gr, g_gen_sw[i]);
            gs_draw_kick(gs, &g_gen_v[i * 3], nv, g_gen_type);
        }
        gpu_nr_prims_alpha_swap(gr, 0);
        gpu_nr_prims_end(gr);
        g_gen_emu += (uint64_t)g_gen_n;
    }
    g_gen_n = 0;
    g_gen_anysw = 0;
}
static void gen_prim_sw(gpu_renderer *gr, gpu_gs *gs, const gs_vertex *v, int type, int sw)
{
    if (g_gen_n && (type != g_gen_type || g_gen_n >= GEN_MAXP)) gen_flush(gr, gs);
    g_gen_type = type;
    memcpy(&g_gen_v[g_gen_n * 3], v, (size_t)(type == GS_PRIM_LINE ? 2 : 3) * sizeof(gs_vertex));
    g_gen_sw[g_gen_n] = (uint8_t)sw;
    g_gen_anysw |= sw;
    g_gen_n++;
}
static void gen_prim(gpu_renderer *gr, gpu_gs *gs, const gs_vertex *v, int type) { gen_prim_sw(gr, gs, v, type, 0); }
/* a register write between generated primitives: the run so far is drawn with the old value */
static void gen_reg(gpu_renderer *gr, gpu_gs *gs, uint32_t reg, uint64_t val)
{
    if (gs->reg[reg] == val) return;
    gen_flush(gr, gs);
    gs->reg[reg] = val;
}

static void draw_shadow_im(const nr_rec *r, gpu_renderer *gr, gpu_gs *gs, int nf)
{
    int i, k, sw = 0;
    gs_vertex v[4];
    uint64_t batch_alpha = gs->reg[GS_ALPHA_1];
    g_gen_n = 0;
    g_gen_anysw = 0;
    gs->reg[GS_PRIM] = 5;
    gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
    for (i = 0; i < nf; i++) {
        const nr_shface *f = &g_dsh.f[i];
        shregs rg;
        uint64_t rgbaq;
        int j;
        if (shadow_regs(r->c, f->regq, gs->reg[GS_RGBAQ] >> 32, &rg) != 0) { g_sh_bad++; break; }
        /* the faces' ALPHA / TEST writes: a new draw when they change (RGBAQ is per vertex),
         * except an ALPHA that is the draw's with A and B swapped (the faces alternate between
         * the two: flagged primitives of the same draw) */
        for (j = 0; j < rg.n; j++) {
            if (rg.reg[j] == GS_RGBAQ) { gs->reg[GS_RGBAQ] = rg.val[j]; continue; }
            if (rg.reg[j] == GS_ALPHA_1 && !g_noswap) {
                if (rg.val[j] == batch_alpha) { sw = 0; continue; }
                if (rg.val[j] == alpha_swap_ab(batch_alpha) && (rg.val[j] & 0xF) != (batch_alpha & 0xF)) { sw = 1; continue; }
                gen_flush(gr, gs);
                gs->reg[GS_ALPHA_1] = batch_alpha = rg.val[j];
                sw = 0;
                continue;
            }
            gen_reg(gr, gs, rg.reg[j], rg.val[j]);
        }
        rgbaq = gs->reg[GS_RGBAQ];
        for (k = 0; k < 4; k++) {
            memset(&v[k], 0, sizeof v[k]);
            v[k].x = (uint16_t)f->x[k];
            v[k].y = (uint16_t)f->y[k];
            v[k].z = ((uint32_t)f->z[k] >> 4) & 0xFFFFFFu;
            v[k].f = (uint8_t)((uint32_t)f->w[k] >> 4);
            v[k].r = (uint8_t)rgbaq; v[k].g = (uint8_t)(rgbaq >> 8); v[k].b = (uint8_t)(rgbaq >> 16);
            v[k].a = (uint8_t)(rgbaq >> 24);
            { uint32_t qb = (uint32_t)(rgbaq >> 32); memcpy(&v[k].q, &qb, 4); }
        }
        if (!((uint32_t)f->w[2] & 0x8000)) { gs_vertex t[3] = { v[0], v[1], v[2] }; gen_prim_sw(gr, gs, t, GS_PRIM_TRIANGLE, sw); g_sh_tris++; }
        if (!((uint32_t)f->w[3] & 0x8000)) { gs_vertex t[3] = { v[0], v[2], v[3] }; gen_prim_sw(gr, gs, t, GS_PRIM_TRIANGLE, sw); g_sh_tris++; }
        g_sh_faces++;
        gs->reg[GS_FOG] = (uint64_t)v[3].f << 56;
    }
    gen_flush(gr, gs);
    /* the register as the program leaves it: the last face's ALPHA */
    if (sw) gs->reg[GS_ALPHA_1] = alpha_swap_ab(batch_alpha);
    g_st.drawn++;
}

static void draw_shadow(const nr_rec *r, gpu_renderer *gr, gpu_gs *gs)
{
    int nf = shadow_faces(r, &g_dsh), i, k, swapped = 0;
    gs_vertex v[4];
    uint64_t batch_alpha = 0;
    int have_alpha = 0;
    if (nf <= 0) { g_st.drawn++; return; }
    if (genim_on()) { draw_shadow_im(r, gr, gs, nf); return; }
    gpu_nr_prims_begin(gr);
    gs->reg[GS_PRIM] = 5;
    gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
    for (i = 0; i < nf; i++) {
        const nr_shface *f = &g_dsh.f[i];
        shregs rg;
        uint64_t rgbaq;
        int j, sw = 0;
        if (shadow_regs(r->c, f->regq, gs->reg[GS_RGBAQ] >> 32, &rg) != 0) { g_sh_bad++; break; }
        /* faces alternate between the two ALPHA writes: when this one is the
         * batch's with A and B swapped, keep the register and flag the
         * primitives (one batch, primitive order kept) */
        for (j = 0; j < rg.n; j++) {
            if (rg.reg[j] == GS_ALPHA_1 && have_alpha && rg.val[j] != batch_alpha && rg.val[j] == alpha_swap_ab(batch_alpha) &&
                !g_noswap) {
                sw = 1;
                continue;
            }
            if (rg.reg[j] == GS_ALPHA_1) { batch_alpha = rg.val[j]; have_alpha = 1; }
            gs->reg[rg.reg[j]] = rg.val[j];
        }
        gpu_nr_prims_alpha_swap(gr, sw);
        swapped = sw;
        rgbaq = gs->reg[GS_RGBAQ];
        for (k = 0; k < 4; k++) {
            memset(&v[k], 0, sizeof v[k]);
            v[k].x = (uint16_t)f->x[k];
            v[k].y = (uint16_t)f->y[k];
            v[k].z = ((uint32_t)f->z[k] >> 4) & 0xFFFFFFu;
            v[k].f = (uint8_t)((uint32_t)f->w[k] >> 4);
            v[k].r = (uint8_t)rgbaq; v[k].g = (uint8_t)(rgbaq >> 8); v[k].b = (uint8_t)(rgbaq >> 16);
            v[k].a = (uint8_t)(rgbaq >> 24);
            { uint32_t qb = (uint32_t)(rgbaq >> 32); memcpy(&v[k].q, &qb, 4); }
        }
        /* fan: v2 kicks (v0 v1 v2), v3 kicks (v0 v2 v3); ADC = no kick */
        if (!((uint32_t)f->w[2] & 0x8000)) { gs_vertex t[3] = { v[0], v[1], v[2] }; gs_draw_kick(gs, t, 3, GS_PRIM_TRIFAN); g_sh_tris++; }
        if (!((uint32_t)f->w[3] & 0x8000)) { gs_vertex t[3] = { v[0], v[2], v[3] }; gs_draw_kick(gs, t, 3, GS_PRIM_TRIFAN); g_sh_tris++; }
        gs->reg[GS_FOG] = (uint64_t)v[3].f << 56;
        g_sh_faces++;
    }
    gpu_nr_prims_end(gr);
    /* the registers as the program leaves them: the last face's ALPHA */
    if (swapped) gs->reg[GS_ALPHA_1] = alpha_swap_ab(batch_alpha);
    g_st.drawn++;
}

/* ---- frame list (nr.h) -------------------------------------------------- */
typedef struct frame_buf { nr_frame f; nr_frame_item *it; uint32_t cap; } frame_buf;
static frame_buf g_fb[2];
static int g_fb_cur;
static int g_fdump = -2;
static void frame_dump(const nr_frame *f)
{
    /* RG_NR_FRAMEDUMP=N: the frame list of frame N, as text, on stderr */
    uint32_t i;
    fprintf(stderr, "nr frame %u: %u native draws\n", f->number, f->count);
    for (i = 0; i < f->count; i++) {
        const nr_frame_item *t = &f->items[i];
        const nr_qw *c = (const nr_qw *)t->c;
        fprintf(stderr, "  %4u rec %u mesh %u (%u vtx) var %03X obj T %.2f %.2f %.2f FRAME %llX ZBUF %llX TEX0 %llX ALPHA %llX box %s %.0f %.0f %.0f %.0f\n",
                i, t->id, t->mesh ? ((const nr_mesh *)t->mesh)->id : 0, t->mesh ? ((const nr_mesh *)t->mesh)->nvtx : 0,
                t->variant, c[63].f[0], c[63].f[1], c[63].f[2], (unsigned long long)t->gs[NRF_FRAME],
                (unsigned long long)t->gs[NRF_ZBUF], (unsigned long long)t->gs[NRF_TEX0],
                (unsigned long long)t->gs[NRF_ALPHA], t->has_box ? "yes" : "no", t->box[0], t->box[1], t->box[2], t->box[3]);
    }
}
static void frame_replay(gpu_renderer *gr, const nr_frame *f);
static void frame_add(const nr_rec *r, gpu_renderer *gr, const gpu_gs *gs, int textured_mesh)
{
    frame_buf *b = &g_fb[g_fb_cur];
    nr_frame_item *t;
    int ctx;
    if (b->f.count && r->frame != b->f.number) {
        /* a new frame: publish this one */
        if (g_fdump == -2) { const char *e = getenv("RG_NR_FRAMEDUMP"); g_fdump = e ? atoi(e) : -1; }
        if (g_fdump >= 0 && b->f.number == (uint32_t)g_fdump) frame_dump(&b->f);
        frame_replay(gr, &b->f);
        g_fb_cur ^= 1;
        b = &g_fb[g_fb_cur];
        b->f.count = 0;
    }
    b->f.number = r->frame;
    if (b->f.count == b->cap) {
        b->cap = b->cap ? b->cap * 2 : 1024;
        b->it = (nr_frame_item *)realloc(b->it, b->cap * sizeof *b->it);
        if (!b->it) { b->cap = 0; b->f.count = 0; return; }
    }
    b->f.items = b->it;
    t = &b->it[b->f.count++];
    ctx = (int)((gs->reg[GS_PRMODE] >> 9) & 1);
    t->id = r->id;
    t->mesh = r->mesh;
    t->variant = r->variant;
    t->c = r->c;
    t->bones = r->bones;
    memcpy(t->src, r->src, sizeof t->src);
    t->gs[NRF_FRAME] = gs->reg[GS_FRAME_1 + ctx];
    t->gs[NRF_ZBUF] = gs->reg[GS_ZBUF_1 + ctx];
    t->gs[NRF_TEST] = gs->reg[GS_TEST_1 + ctx];
    t->gs[NRF_ALPHA] = gs->reg[GS_ALPHA_1 + ctx];
    t->gs[NRF_TEX0] = gs->reg[GS_TEX0_1 + ctx];
    t->gs[NRF_TEX1] = gs->reg[GS_TEX1_1 + ctx];
    t->gs[NRF_CLAMP] = gs->reg[GS_CLAMP_1 + ctx];
    t->gs[NRF_PRMODE] = gs->reg[GS_PRMODE];
    t->gs[NRF_XYOFFSET] = gs->reg[GS_XYOFFSET_1 + ctx];
    t->gs[NRF_SCISSOR] = gs->reg[GS_SCISSOR_1 + ctx];
    t->gs[NRF_FBA] = gs->reg[GS_FBA_1 + ctx];
    t->gs[NRF_FOGCOL] = gs->reg[GS_FOGCOL];
    t->gs[NRF_TEXA] = gs->reg[GS_TEXA];
    t->gs[NRF_PRIM] = gs->reg[GS_PRIM];
    t->gs[NRF_PRMODECONT] = gs->reg[GS_PRMODECONT];
    t->gs[NRF_PABE] = gs->reg[GS_PABE];
    t->gs[NRF_COLCLAMP] = gs->reg[GS_COLCLAMP];
    t->gs[NRF_DTHE] = gs->reg[GS_DTHE];
    t->gs[NRF_DIMX] = gs->reg[GS_DIMX];
    t->gs[NRF_SCANMSK] = gs->reg[GS_SCANMSK];
    t->gs[NRF_MIPTBP1] = gs->reg[GS_MIPTBP1_1 + ctx];
    t->gs[NRF_MIPTBP2] = gs->reg[GS_MIPTBP2_1 + ctx];
    t->has_box = r->has_box;
    memcpy(t->box, r->box, sizeof t->box);
    if (textured_mesh) gpu_nr_last_texkey(gr, t->texkey);
    else memset(t->texkey, 0, sizeof t->texkey);
}

/* ---- replay (docs/NATIVE-RENDER.md "Replay") --------------------------------
 * RG_NR_REPLAY=N: every completed frame list is drawn again N times, without
 * the game, into an offscreen target (gpu_nr_replay_*): each item from its own
 * data only (decoded mesh, constant block, bone rows, GS registers, texture
 * key), nothing read from VU memory, the GS model or local memory.  The N
 * images must be identical; the run (its hash, every game-visible output) must
 * not change.  Shadow volumes and line strands (drawn through the GS draw
 * path) are counted, not replayed. */
static struct {
    int n;                   /* RG_NR_REPLAY, -1 unknown */
    uint64_t frames, same, differ, items, drawn, skipped, notex, other, stale, offtarget;
    uint64_t last_hash;
    int printed;
} g_rp = { -1 };
static gpu_nr_draw g_rpd;
static void frame_replay(gpu_renderer *gr, const nr_frame *f)
{
    uint32_t i;
    int k, w = 0, h = 512;
    uint64_t hash0 = 0;
    if (g_rp.n < 0) { const char *e = getenv("RG_NR_REPLAY"); g_rp.n = e ? atoi(e) : 0; }
    if (g_rp.n <= 0 || !f->count) return;
    /* the target: the frame buffer most items draw into (the others, e.g. the
     * composite's work textures, are counted, not replayed) */
    uint32_t fb = 0;
    {
        uint32_t cand[8] = { 0 }, cnt[8] = { 0 };
        int nc = 0, best = -1, j;
        for (i = 0; i < f->count; i++) {
            uint32_t v;
            if (f->items[i].variant & (NRV_SHADOW | NRV_LINES)) continue;
            v = (uint32_t)f->items[i].gs[NRF_FRAME];
            for (j = 0; j < nc && cand[j] != v; j++) {}
            if (j == nc) { if (nc == 8) continue; cand[nc++] = v; }
            cnt[j]++;
        }
        for (j = 0; j < nc; j++) if (best < 0 || cnt[j] > cnt[best]) best = j;
        if (best < 0) return;
        fb = cand[best];
        w = (int)((fb >> 16) & 0x3F) * 64;
    }
    if (w <= 0) return;
    for (k = 0; k < g_rp.n; k++) {
        uint64_t hh;
        if (gpu_nr_replay_begin(gr, w, h) != 0) return;
        for (i = 0; i < f->count; i++) {
            const nr_frame_item *t = &f->items[i];
            const nr_rec *rr = rec_of(t->id);
            const nr_mesh *m = t->mesh;
            const nr_qw *c = (const nr_qw *)t->c;
            uint64_t regs[128];
            int ctx, rc;
            if (k == 0) g_rp.items++;
            if (t->variant & (NRV_SHADOW | NRV_LINES)) { if (k == 0) g_rp.other++; continue; }
            if ((uint32_t)t->gs[NRF_FRAME] != fb) { if (k == 0) g_rp.offtarget++; continue; }
            if (rr->id != t->id) { if (k == 0) g_rp.stale++; continue; }   /* the record ring wrapped */
            memset(regs, 0, sizeof regs);
            ctx = (int)((t->gs[NRF_PRMODE] >> 9) & 1);
            regs[GS_FRAME_1 + ctx] = t->gs[NRF_FRAME];
            regs[GS_ZBUF_1 + ctx] = t->gs[NRF_ZBUF];
            regs[GS_TEST_1 + ctx] = t->gs[NRF_TEST];
            regs[GS_ALPHA_1 + ctx] = t->gs[NRF_ALPHA];
            regs[GS_TEX0_1 + ctx] = t->gs[NRF_TEX0];
            regs[GS_TEX1_1 + ctx] = t->gs[NRF_TEX1];
            regs[GS_CLAMP_1 + ctx] = t->gs[NRF_CLAMP];
            regs[GS_XYOFFSET_1 + ctx] = t->gs[NRF_XYOFFSET];
            regs[GS_SCISSOR_1 + ctx] = t->gs[NRF_SCISSOR];
            regs[GS_FBA_1 + ctx] = t->gs[NRF_FBA];
            regs[GS_MIPTBP1_1 + ctx] = t->gs[NRF_MIPTBP1];
            regs[GS_MIPTBP2_1 + ctx] = t->gs[NRF_MIPTBP2];
            regs[GS_PRMODE] = t->gs[NRF_PRMODE];
            regs[GS_PRIM] = t->gs[NRF_PRIM];
            regs[GS_PRMODECONT] = t->gs[NRF_PRMODECONT];
            regs[GS_FOGCOL] = t->gs[NRF_FOGCOL];
            regs[GS_TEXA] = t->gs[NRF_TEXA];
            regs[GS_PABE] = t->gs[NRF_PABE];
            regs[GS_COLCLAMP] = t->gs[NRF_COLCLAMP];
            regs[GS_DTHE] = t->gs[NRF_DTHE];
            regs[GS_DIMX] = t->gs[NRF_DIMX];
            regs[GS_SCANMSK] = t->gs[NRF_SCANMSK];
            g_rpd.mesh.id = m->id;
            g_rpd.mesh.vtx = m->vtx;
            g_rpd.mesh.nvtx = m->nvtx;
            g_rpd.mesh.stride = sizeof(nr_vtx);
            g_rpd.mesh.idx = m->idx;
            g_rpd.mesh.nidx = m->nidx;
            build_cb_cv(c, t->variant, &g_rpd);
            if (t->variant & NRV_SKIN) {
                memcpy(g_rpd.bones, t->bones, sizeof g_rpd.bones);
                g_rpd.nbones_rows = NR_BONE_ROWS;
            } else {
                g_rpd.nbones_rows = 0;
            }
            g_rpd.cull = (t->variant & NRV_CULL) != 0 && g_cullmode != 0;
            g_rpd.cull_sign = c[NRQ_HAND].f[2] * ((c[NRQ_MAT].u[1] & 0x1000) ? -1.0f : 1.0f) * (g_cullmode < 0 ? -1.0f : 1.0f);
            g_rpd.has_box = 0;
            rc = gpu_nr_replay_draw(gr, &g_rpd, regs, t->texkey);
            if (k == 0) {
                if (rc == 0) g_rp.drawn++;
                else if (rc == 1) g_rp.skipped++;
                else g_rp.notex++;
            }
        }
        if (gpu_nr_replay_end(gr, &hh) != 0) return;
        if (k == 0) hash0 = hh;
        else if (hh != hash0) {
            g_rp.differ++;
            if (g_rp.printed < 10) {
                g_rp.printed++;
                fprintf(stderr, "nr replay: frame %u pass %d hash %016llX != pass 0 %016llX\n", f->number, k,
                        (unsigned long long)hh, (unsigned long long)hash0);
            }
            hash0 = 0;
            break;
        }
    }
    g_rp.frames++;
    if (hash0) g_rp.same++;
    g_rp.last_hash = hash0;
}

/* the line program's GS output, generated natively: PRIM 1 + PRMODE qw87.x,
 * per record PACKED RGBAQ (16, 16, 16, alpha; Q kept) and four lines
 * (v0 v1, v2 v3, v4 v5, v6 v7); ADC records kick nothing */
static lnbuf g_dlb;
static uint64_t g_ln_recs, g_ln_lines;
static void draw_lines(const nr_rec *r, gpu_renderer *gr, gpu_gs *gs)
{
    uint32_t b;
    int any = 0;
    for (b = 0; b < r->mesh->nbatch; b++) {
        int four, nr = line_records(r, b, &g_dlb, &four), i, k;
        if (nr <= 0) continue;
        if (genim_on()) {
            /* native: a run per batch (RGBAQ is per vertex) */
            any = 2;
            gs->reg[GS_PRIM] = 1;
            gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
            g_gen_n = 0;
            for (i = 0; i < nr; i++) {
                const nr_lnrec *e = &g_dlb.rec[i];
                uint64_t rgbaq = 16u | (16u << 8) | (16u << 16) | ((uint64_t)e->alpha << 24) | (gs->reg[GS_RGBAQ] & 0xFFFFFFFF00000000ull);
                gs_vertex v[8];
                gs->reg[GS_RGBAQ] = rgbaq;
                g_ln_recs++;
                if (e->adc) continue;
                for (k = 0; k < 8; k++) {
                    memset(&v[k], 0, sizeof v[k]);
                    v[k].x = (uint16_t)e->x[k];
                    v[k].y = (uint16_t)e->y[k];
                    v[k].z = ((uint32_t)e->z[k] >> 4) & 0xFFFFFFu;
                    v[k].f = (uint8_t)((uint32_t)e->adc >> 4);
                    v[k].r = 16; v[k].g = 16; v[k].b = 16; v[k].a = (uint8_t)e->alpha;
                    { uint32_t qb = (uint32_t)(rgbaq >> 32); memcpy(&v[k].q, &qb, 4); }
                }
                for (k = 0; k < 8; k += 2) { gen_prim(gr, gs, &v[k], GS_PRIM_LINE); g_ln_lines++; }
            }
            gen_flush(gr, gs);
            gs->reg[GS_FOG] = (uint64_t)(uint8_t)((uint32_t)g_dlb.rec[nr - 1].adc >> 4) << 56;
            continue;
        }
        if (!any) { gpu_nr_prims_begin(gr); any = 1; }
        gs->reg[GS_PRIM] = 1;
        gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
        for (i = 0; i < nr; i++) {
            const nr_lnrec *e = &g_dlb.rec[i];
            uint64_t rgbaq = 16u | (16u << 8) | (16u << 16) | ((uint64_t)e->alpha << 24) | (gs->reg[GS_RGBAQ] & 0xFFFFFFFF00000000ull);
            gs_vertex v[8];
            gs->reg[GS_RGBAQ] = rgbaq;
            for (k = 0; k < 8; k++) {
                memset(&v[k], 0, sizeof v[k]);
                v[k].x = (uint16_t)e->x[k];
                v[k].y = (uint16_t)e->y[k];
                v[k].z = ((uint32_t)e->z[k] >> 4) & 0xFFFFFFu;
                v[k].f = (uint8_t)((uint32_t)e->adc >> 4);
                v[k].r = 16; v[k].g = 16; v[k].b = 16; v[k].a = (uint8_t)e->alpha;
                { uint32_t qb = (uint32_t)(rgbaq >> 32); memcpy(&v[k].q, &qb, 4); }
            }
            g_ln_recs++;
            if (e->adc) continue;
            for (k = 0; k < 8; k += 2) { gs_draw_kick(gs, &v[k], 2, GS_PRIM_LINE); g_ln_lines++; }
        }
        gs->reg[GS_FOG] = (uint64_t)(uint8_t)((uint32_t)g_dlb.rec[nr - 1].adc >> 4) << 56;
    }
    if (any == 1) gpu_nr_prims_end(gr);
    /* every batch's kick writes PRIM and PRMODE, records or not */
    if (r->mesh->nbatch) {
        gs->reg[GS_PRIM] = 1;
        gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
    }
    g_st.drawn++;
}

/* ---- interpolated presentation (nr_interp.h, docs/NATIVE-RENDER.md) ----------------
 * ip_note: a native mesh draw goes into the frame's log (copies of its constants);
 * nr_ip_mesh_cb: a replay of the frame's device commands (nr_iprec.cpp) asks for the mesh
 * draw's constant rows and bones, interpolated (nr_interp.c). */
static void ip_note(const nr_rec *r, const gpu_gs *gs)
{
    int ctx = (int)((gs->reg[GS_PRMODE] >> 9) & 1);
    if (!nr_ip_on()) return;
    nr_ip_note(r->id, r->mesh, r->variant, r->src[0], gs->reg[GS_FRAME_1 + ctx], r->has_box, r->box, r->c, r->bones,
               r->bones_hi);
}
int nr_ip_mesh_cb(uint32_t id, struct gpu_nr_draw *d)
{
    const nr_ip_draw *x = nr_ip_draw_for(id);
    if (!x || !x->interp) return 0;
    build_cb_cv((const nr_qw *)x->c, x->variant, d);
    if (x->variant & NRV_SKIN) memcpy(d->bones, x->bones, sizeof d->bones);
    return 1;
}

static void gs_marker(void *user, gpu_renderer *gr, gpu_gs *gs, uint64_t value)
{
    uint32_t id = (uint32_t)value;
    nr_rec *r;
    const nr_mesh *m;
    (void)user;
    if (nr_mode() != NR_NATIVE) return;
    if (value & NRIM_MARK_BIT) { nr_im_marker(gr, gs, id); return; }   /* immediate packets (nr_im.h) */
    if (!g_rec) return;
    r = rec_of(id);
    if (r->id != id) { g_st.stale_gs++; return; }
    if (!r->filled) { g_st.not_filled++; return; }
    if (r->variant & NRV_SHADOW) { frame_add(r, gr, gs, 0); draw_shadow(r, gr, gs); ip_note(r, gs); return; }
    if (r->variant & NRV_LINES) { frame_add(r, gr, gs, 0); draw_lines(r, gr, gs); ip_note(r, gs); return; }
    m = r->mesh;
    /* the GS register writes the skipped program would have made: PRIM and
     * PRMODE (header .x of the last batch, 87.x) and the one-register packet
     * (qw41 at register qw41.z: FOGCOL; 87.y bit 0x10 clears its data) */
    {
        gs->reg[GS_PRIM] = m->last_prim;
        gs->reg[GS_PRMODE] = r->c[NRQ_MAT].u[0];
        {
            uint32_t addr = r->c[NRQ_REGDATA].u[2] & 0x7F;
            uint64_t dat = (uint64_t)r->c[NRQ_REGDATA].u[0] | ((uint64_t)r->c[NRQ_REGDATA].u[1] << 32);
            if (r->c[NRQ_MAT].u[1] & 0x10) dat &= 0xFFFFFFFF00000000ull;
            if (addr == GS_FOGCOL) gs->reg[GS_FOGCOL] = dat;
        }
    }
    g_draw.mesh.id = m->id;
    g_draw.mesh.vtx = m->vtx;
    g_draw.mesh.nvtx = m->nvtx;
    g_draw.mesh.stride = sizeof(nr_vtx);
    g_draw.mesh.idx = m->idx;
    g_draw.mesh.nidx = m->nidx;
    build_cb(r, &g_draw);
    if (r->variant & NRV_SKIN) {
        memcpy(g_draw.bones, r->bones, sizeof g_draw.bones);
        g_draw.nbones_rows = NR_BONE_ROWS;
    } else {
        g_draw.nbones_rows = 0;
    }
    g_draw.cull = (r->variant & NRV_CULL) != 0 && g_cullmode != 0;
    g_draw.has_box = r->has_box && !g_nobox;
    memcpy(g_draw.box, r->box, sizeof g_draw.box);
    g_draw.cull_sign = r->c[NRQ_HAND].f[2] * ((r->c[NRQ_MAT].u[1] & 0x1000) ? -1.0f : 1.0f) * (g_cullmode < 0 ? -1.0f : 1.0f);
    if (g_dbg && (m->skipwrite || g_dbg > 1) && g_dbgn < 400) {
        /* RG_NR_DEBUG=1: the screen extent of skipping-write meshes (2: all
         * meshes) from the native math on the CPU, and the GS state */
        float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f, z0 = 1e30f, z1 = -1e30f;
        uint32_t i, wneg = 0;
        for (i = 0; i < m->nvtx; i++) {
            const nr_vtx *x = &m->vtx[i];
            nr_vout e;
            int16_t pos[3] = { x->px, x->py, x->pz };
            int8_t nrm[3] = { x->nx, x->ny, x->nz };
            int16_t uv[2] = { x->u, x->v };
        uint8_t col[4] = { x->r, x->g, x->b, x->a };
            nr_vu1_vertex(r->c, r->bones, r->variant, pos, nrm, uv, col, x->bone, x->wgt, &e);
            if (e.clip[3] <= 0) { wneg++; continue; }
            if (e.sx < x0) x0 = e.sx; if (e.sx > x1) x1 = e.sx;
            if (e.sy < y0) y0 = e.sy; if (e.sy > y1) y1 = e.sy;
            if (e.sz < z0) z0 = e.sz; if (e.sz > z1) z1 = e.sz;
        }
        g_dbgn++;
        fprintf(stderr, "nr draw %u: mesh %u pkt %08X var %02X nv %u skip %d | screen %.0f..%.0f x %.0f..%.0f z %.0f..%.0f w<=0 %u | "
                        "FRAME %016llX ZBUF %016llX TEST %016llX ALPHA %016llX PRMODE %llX XYOFF %016llX\n",
                id, m->id, m->pkt, r->variant, m->nvtx, m->skipwrite, x0, x1, y0, y1, z0, z1, wneg,
                (unsigned long long)gs->reg[GS_FRAME_1], (unsigned long long)gs->reg[GS_ZBUF_1],
                (unsigned long long)gs->reg[GS_TEST_1], (unsigned long long)gs->reg[GS_ALPHA_1],
                (unsigned long long)gs->reg[GS_PRMODE], (unsigned long long)gs->reg[GS_XYOFFSET_1]);
    }
    gpu_ip_set_mesh(id);   /* (interpolated presentation: the recorder tags the draw) */
    if (gpu_nr_submit(gr, &g_draw) < 0) g_st.gpu_fail++;
    else g_st.drawn++;
    gpu_ip_set_mesh(0);
    frame_add(r, gr, gs, 1);
    ip_note(r, gs);
}
const nr_frame *nr_frame_last(void) { return &g_fb[g_fb_cur ^ 1].f; }
#else
const nr_frame *nr_frame_last(void) { static nr_frame none; return &none; }
#endif

void nr_runtime_gpu_config(struct gpu_config *gc)
{
#ifdef RG_HAVE_GPU
    (void)gc;   /* native draws work with either depth mode (nr_draw.hlsl NR_ZROV) */
#else
    (void)gc;
#endif
}

/* The lens-flare depth probe and other local->host reads (libgraph
 * rg_gs_store_hook, docs/NATIVE-RENDER.md "Lens-flare depth probe"): the GS
 * worker finishes what is queued (the frame the probe reads), then the
 * transfer is made on the model directly: the renderer serves the read from
 * its early copy of the depth target (deterministic: exactly the bytes the
 * VIF1 FIFO path delivers), no DMA, no VIF1, no FIFO. */
static uint64_t g_store_n;
#ifdef RG_HAVE_GPU
static int native_store(uint64_t bitblt, uint64_t trxpos, uint64_t trxreg, void *dst, int bytes, int fifo_bytes)
{
    static uint8_t *buf;
    static int cap;
    gpu_gs *gs = g_store_gr ? gpu_attached_state(g_store_gr) : NULL;
    if (!gs || bytes <= 0 || fifo_bytes < bytes) return -1;
    if (fifo_bytes > cap) {
        free(buf);
        buf = (uint8_t *)malloc((size_t)fifo_bytes);
        cap = buf ? fifo_bytes : 0;
        if (!buf) return -1;
    }
#if NR_ONLY
    {
        /* the device reads the rectangle from the GPU (early copy of its pages) once the worker
         * has run what is queued */
        gs_mem_rect rc;
        rc.bp = (uint32_t)(bitblt & 0x3FFF);
        rc.bw = (uint32_t)((bitblt >> 16) & 0x3F);
        rc.psm = (int)((bitblt >> 24) & 0x3F);
        rc.x = (uint32_t)(trxpos & 0x7FF);
        rc.y = (uint32_t)((trxpos >> 16) & 0x7FF);
        rc.w = (uint32_t)(trxreg & 0xFFF);
        rc.h = (uint32_t)((trxreg >> 32) & 0xFFF);
        nr_ip_settle();   /* (an interpolated image in the device: the exact frame first) */
        nr_q_drain();
        if (gpu_mem_read(g_store_gr, &rc, buf, (uint32_t)fifo_bytes) != 0) return -1;
    }
#else
    gs_async_drain(gs);
    gs_write_reg(gs, GS_BITBLTBUF, bitblt);
    gs_write_reg(gs, GS_TRXPOS, trxpos);
    gs_write_reg(gs, GS_TRXREG, trxreg);
    gs_write_reg(gs, GS_TRXDIR, 1);
    if ((int)gs_read_fifo(gs, buf, (uint32_t)fifo_bytes) < fifo_bytes) return -1;
#endif
    memcpy(dst, buf, (size_t)bytes);
    g_store_n++;
    return 0;
}
#endif
int (*nr_native_store_fn(void))(uint64_t, uint64_t, uint64_t, void *, int, int)
{
#ifdef RG_HAVE_GPU
    const char *e = getenv("RG_NR_STORE");
    if (nr_mode() != NR_NATIVE || (e && e[0] == '0')) return NULL;
    return native_store;
#else
    return NULL;   /* no renderer to serve the read: the DMA path */
#endif
}

void nr_im_path3_raw(const uint8_t *qw, uint32_t nqw)
{
#if defined(RG_HAVE_GPU) && NR_ONLY
    nr_gs_gif(GS_PATH3, qw, nqw);
#elif defined(RG_HAVE_GPU)
    gpu_gs *gs = g_store_gr ? gpu_attached_state(g_store_gr) : NULL;
    if (gs && nqw) gs_gif_write(gs, GS_PATH3, qw, nqw);
#else
    (void)qw; (void)nqw;
#endif
}

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
/* the native libdma's GIF channel (src/sce/graphics/libdma_native.c) */
extern void (*rg_gif3_hook)(const void *qw, uint32_t nqw);
#endif

void nr_runtime_attach_gpu(struct gpu_renderer *r)
{
#ifdef RG_HAVE_GPU
    if (!active() || !r) return;
    {
        const char *f = getenv("RG_NR_FAULT");
        g_fault = f ? atoi(f) : 0;
        f = getenv("RG_NR_DEBUG");
        g_dbg = f ? atoi(f) : 0;
        f = getenv("RG_NR_CULL");
        if (f) g_cullmode = atoi(f);
        f = getenv("RG_NR_NOBOX");
        g_nobox = f && atoi(f) != 0;
        f = getenv("RG_NR_NOSWAP");
        g_noswap = f && atoi(f) != 0;
    }
    gpu_set_native_handler(r, gs_marker, NULL);
    g_store_gr = r;
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
    /* every GIF channel send to the native GIF input (records, IMAGE data to the device) and the
     * state block's marker writes to the mesh handler (docs/NATIVE-RENDER.md "Checkpoint 10") */
    rg_gif3_hook = nr_gs_gif_path3;
    nr_gs_set_marker(gs_marker, NULL);
#endif
    g_attached = 1;
#else
    (void)r;
#endif
}

static int cen_cmp(const void *a, const void *b)
{
    uint64_t x = ((const uint64_t *)a)[0], y = ((const uint64_t *)b)[0];
    return x < y ? 1 : x > y ? -1 : 0;
}

void nr_runtime_stats(FILE *f)
{
    nr_ip_stats(f);   /* interpolated presentation (when on) */
    if (g_cen_n && f) {
        /* sort by draws (n), descending */
        static uint64_t ord[NR_CEN][2];
        int i;
        uint64_t tot = 0, nat = 0;
        for (i = 0; i < g_cen_n; i++) { ord[i][0] = g_cen[i].n; ord[i][1] = (uint64_t)i; tot += g_cen[i].n; nat += g_cen[i].native; }
        qsort(ord, (size_t)g_cen_n, sizeof ord[0], cen_cmp);
        fprintf(f, "native render census: %llu mesh draws, %llu native (%.1f %%); microcode tuples (head kind tail decode colour output: draws native variant):\n",
                (unsigned long long)tot, (unsigned long long)nat, tot ? 100.0 * (double)nat / (double)tot : 0.0);
        for (i = 0; i < g_cen_n && i < 40; i++) {
            int k = (int)ord[i][1];
            fprintf(f, "  %08X %08X %08X %08X %08X %08X: %llu %llu %d  (last qw900 %g %g %g %g, qw84 %g %g %g %g)\n",
                    g_cen[k].in[0], g_cen[k].in[1], g_cen[k].in[2], g_cen[k].in[3], g_cen[k].in[4], g_cen[k].in[5],
                    (unsigned long long)g_cen[k].n, (unsigned long long)g_cen[k].native, g_cen[k].variant,
                    g_cen[k].q900[0], g_cen[k].q900[1], g_cen[k].q900[2], g_cen[k].q900[3],
                    g_cen[k].q84[0], g_cen[k].q84[1], g_cen[k].q84[2], g_cen[k].q84[3]);
        }
    }
    const nr_mesh_stats *ms = nr_mesh_get_stats();
    if (!active() || !f) return;
    nr_im_stats(f);
    nr_fx_stats(f);
    nr_mem_stats(f);
    nr_vux_stats(f);
#ifdef RG_HAVE_GPU
    if (g_store_n) fprintf(f, "native render: local->host reads served natively (no VIF1/FIFO) %llu\n",(unsigned long long)g_store_n);
#endif
    fprintf(f, "native render: meshes %llu recorded %llu (fallback: variant %llu mesh %llu off %llu); "
               "tapped %llu (stale %llu); drawn %llu (not filled %llu, stale %llu, gpu fail %llu); "
               "mesh cache: lookups %llu decodes %llu rehash %llu bad %llu, %.1f MB hashed\n",
            (unsigned long long)g_st.meshes, (unsigned long long)g_st.recorded,
            (unsigned long long)g_st.fallback_variant, (unsigned long long)g_st.fallback_mesh,
            (unsigned long long)g_st.fallback_off, (unsigned long long)g_st.tapped,
            (unsigned long long)g_st.tap_stale, (unsigned long long)g_st.drawn,
            (unsigned long long)g_st.not_filled, (unsigned long long)g_st.stale_gs,
            (unsigned long long)g_st.gpu_fail, (unsigned long long)ms->lookups,
            (unsigned long long)ms->decodes, (unsigned long long)ms->rehash, (unsigned long long)ms->bad,
            (double)ms->bytes_hashed / 1e6);
    {
        int k;
        fprintf(f, "native render constants (%s): model items %llu (no camera %llu, no view %llu, no light %llu); scan failures model",
                cmode() == NRC_TAP ? "tap" : cmode() == NRC_CHECK ? "game, checked" : "game",
                (unsigned long long)g_cst.models, (unsigned long long)g_cst.no_cam, (unsigned long long)g_cst.no_view,
                (unsigned long long)g_cst.no_light);
        for (k = 1; k < 12; k++) if (g_cst.model_fail[k]) fprintf(f, " [%s] %llu", nr_const_err(-k), (unsigned long long)g_cst.model_fail[k]);
        fprintf(f, ", material");
        for (k = 1; k < 12; k++) if (g_cst.mat_fail[k]) fprintf(f, " [%s] %llu", nr_const_err(-k), (unsigned long long)g_cst.mat_fail[k]);
        fprintf(f, "; meshes left emulated %llu\n", (unsigned long long)g_st.fallback_const);
        if (stale_check_on() || g_nst.view_bad || g_nst.chain_sub[0] + g_nst.chain_sub[1] + g_nst.chain_empty[0] + g_nst.chain_empty[1])
            fprintf(f, "native render constants notes: request view packets %llu (not noted %llu: read in place %llu, "
                    "neither %llu), applied view %llu (stale %llu); sorted-chain packets view %llu (copies %llu, empty %llu) "
                    "light %llu (copies %llu, empty %llu)\n",
                    (unsigned long long)g_nst.req_view, (unsigned long long)g_nst.view_unknown, (unsigned long long)g_nst.view_inplace,
                    (unsigned long long)g_nst.view_bad, (unsigned long long)g_nst.used_view, (unsigned long long)g_nst.stale_view,
                    (unsigned long long)g_nst.chain[0], (unsigned long long)g_nst.chain_sub[0], (unsigned long long)g_nst.chain_empty[0],
                    (unsigned long long)g_nst.chain[1], (unsigned long long)g_nst.chain_sub[1], (unsigned long long)g_nst.chain_empty[1]);
        if (stale_check_on() || g_nst.uncopyable || g_nst.req_unknown)
            fprintf(f, "native render constants notes: %llu copied (%llu not a builder layout), applied camera %llu (stale %llu) "
                    "light %llu (stale %llu); request light packets %llu (not noted %llu: read in place %llu)%s\n",
                    (unsigned long long)g_nst.notes, (unsigned long long)g_nst.uncopyable,
                    (unsigned long long)g_nst.used_cam, (unsigned long long)g_nst.stale_cam,
                    (unsigned long long)g_nst.used_light, (unsigned long long)g_nst.stale_light,
                    (unsigned long long)g_nst.req_light, (unsigned long long)g_nst.req_unknown, (unsigned long long)g_nst.req_inplace,
                    stale_check_on() ? "" : " (RG_NR_STALE=1 counts stale)");
        if (g_chk.recs) {
            fprintf(f, "native render constants check: records %llu (not bit-identical %llu), with a difference %llu:",
                    (unsigned long long)g_chk.recs, (unsigned long long)g_chk.inexact_recs, (unsigned long long)g_chk.bad_recs);
            for (k = 0; k < CG_N; k++)
                fprintf(f, " %s %llu/%llu", cg_name[k], (unsigned long long)g_chk.bad[k], (unsigned long long)g_chk.cmp[k]);
            fprintf(f, ": %s\n", g_chk.bad_recs == 0 ? "PASS" : "FAIL");
        }
    }
    if (g_cs.resets || g_cs.sprites_native || g_cs.sprites_vu)
        fprintf(f, "native render composite (%s): clip ranges %llu, sprites native %llu (%llu strips, %llu empty) / VU program %llu; "
                   "ranges made unknown by an emulated mesh %llu (overflow %llu); bbox merges in the VIF tap %llu\n",
                comp_mode() == NRCP_NATIVE ? "native" : comp_mode() == NRCP_CHECK ? "check" : "off",
                (unsigned long long)g_cs.resets, (unsigned long long)g_cs.sprites_native, (unsigned long long)g_cs.strips,
                (unsigned long long)g_cs.empty, (unsigned long long)g_cs.sprites_vu, (unsigned long long)g_cs.unknown_emu,
                (unsigned long long)g_cs.unknown_ovf, (unsigned long long)g_cs.vu_merges);
    if (comp_mode() == NRCP_CHECK && nr_mode() == NR_NATIVE)
        fprintf(f, "native render composite check: VU program runs %llu, sprites %llu compared (X/Y/UV/ADC bits different %llu, "
                   "Z or W words different %llu), unexpected %llu, missing %llu: %s\n",
                (unsigned long long)g_cs.chk_runs, (unsigned long long)g_cs.chk_strips, (unsigned long long)g_cs.chk_bad,
                (unsigned long long)g_cs.chk_wdiff, (unsigned long long)g_cs.chk_extra, (unsigned long long)g_cs.chk_missing,
                g_cs.chk_strips && !g_cs.chk_bad && !g_cs.chk_extra && !g_cs.chk_missing ? "PASS" : "FAIL");
#ifdef RG_HAVE_GPU
    if (g_rp.n > 0)
        fprintf(f, "native render replay x%d: frames %llu (all passes identical %llu, different %llu); items %llu: drawn %llu, "
                   "nothing to draw %llu, texture no longer cached %llu, shadow/line items %llu, other targets %llu, stale %llu; last frame hash %016llX: %s\n",
                g_rp.n, (unsigned long long)g_rp.frames, (unsigned long long)g_rp.same, (unsigned long long)g_rp.differ,
                (unsigned long long)g_rp.items, (unsigned long long)g_rp.drawn, (unsigned long long)g_rp.skipped,
                (unsigned long long)g_rp.notex, (unsigned long long)g_rp.other, (unsigned long long)g_rp.offtarget,
                (unsigned long long)g_rp.stale,
                (unsigned long long)g_rp.last_hash, g_rp.frames && !g_rp.differ ? "PASS" : "FAIL");
    if (g_gen_runs)
        fprintf(f, "native render generated primitives (shadow faces, line strands): %llu native, %llu GS draw path, %llu runs\n",
                (unsigned long long)g_gen_nat, (unsigned long long)g_gen_emu, (unsigned long long)g_gen_runs);
    if (g_ln_recs)
        fprintf(f, "native render line strands: records %llu, lines %llu\n", (unsigned long long)g_ln_recs,
                (unsigned long long)g_ln_lines);
    if (g_sh_faces || g_sh_bad)
        fprintf(f, "native render shadow volumes: faces %llu, triangles %llu, register packets not covered %llu\n",
                (unsigned long long)g_sh_faces, (unsigned long long)g_sh_tris, (unsigned long long)g_sh_bad);
#endif
    if (nr_mode() == NR_VERIFY && g_vl.meshes)
        fprintf(f, "native render verify lines: meshes %llu, batches %llu, records %llu (exact %llu, different %llu), unmatched packets %llu: %s\n",
                (unsigned long long)g_vl.meshes, (unsigned long long)g_vl.batches, (unsigned long long)g_vl.recs,
                (unsigned long long)g_vl.exact, (unsigned long long)g_vl.bad, (unsigned long long)g_vl.unmatched,
                g_vl.bad + g_vl.unmatched == 0 && g_vl.recs ? "PASS" : "FAIL");
    if (nr_mode() == NR_VERIFY && g_vs.meshes)
        fprintf(f, "native render verify shadows: meshes %llu, faces %llu (exact %llu, within tolerance %llu, different %llu), "
                   "faces missing %llu, extra %llu, register packet wrong %llu: %s\n",
                (unsigned long long)g_vs.meshes, (unsigned long long)g_vs.faces, (unsigned long long)g_vs.exact,
                (unsigned long long)g_vs.close, (unsigned long long)g_vs.bad, (unsigned long long)g_vs.missing,
                (unsigned long long)g_vs.extra, (unsigned long long)g_vs.reg_bad,
                g_vs.bad + g_vs.missing + g_vs.extra + g_vs.reg_bad == 0 && g_vs.faces ? "PASS" : "FAIL");
    if (nr_mode() == NR_VERIFY)
        fprintf(f, "native render verify: PATH1 packets %llu, meshes %llu (with a mismatch %llu), batches %llu (unmatched packets %llu), "
                   "vertices %llu (ADC %llu); mismatching vertices: xy %llu z %llu fog %llu rgba %llu stq %llu: %s\n",
                (unsigned long long)g_p1_calls, (unsigned long long)g_ver.meshes, (unsigned long long)g_ver.bad_meshes,
                (unsigned long long)g_ver.batches, (unsigned long long)g_ver.unmatched,
                (unsigned long long)g_ver.vertices, (unsigned long long)g_ver.adc,
                (unsigned long long)g_ver.mism[0], (unsigned long long)g_ver.mism[1], (unsigned long long)g_ver.mism[2],
                (unsigned long long)g_ver.mism[3], (unsigned long long)g_ver.mism[4],
                g_ver.bad_meshes == 0 && g_ver.batches > 0 ? "PASS" : "FAIL");
}
