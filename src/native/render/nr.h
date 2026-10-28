/* SPDX-License-Identifier: CC0-1.0 */
/* Native renderer, scene side (docs/NATIVE-RENDER.md).
 *
 * Three callers:
 *   - the game (overrides of ModelEmitDrawPacketsMaybe_14ec20 and
 *     ModelQueueSortedPackets_14f0d0): nr_model_record() per mesh;
 *   - the runtime: nr_runtime_* wiring (mode, VIF1 tap, renderer);
 *   - the GS worker (through gpu_core's marker hook): the native draw.
 */
#ifndef RG_NR_H
#define RG_NR_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RG_RENDER = native (default since 2026-10-18) | emu | verify.  verify: meshes are recorded
 * and marked as for native, but the original MSCAL + CALL stays too and the
 * GS draws nothing for the marker; the VU1 program's output is compared
 * with the native math (nr_vu1_vertex) on the decoded mesh and the
 * snapshotted constants (docs/NATIVE-RENDER.md "Verification") */
enum { NR_EMU = 0, NR_NATIVE = 1, NR_VERIFY = 2 };
int nr_mode(void);
/* 1: the game keeps the original MSCAL + CALL after a marker (verify mode) */
int nr_keep_original(void);
/* 1: the draw list may skip a native mesh's item packets and microcode
 * uploads (native mode, game constants; nr_scene.c) */
int nr_lazy_item_packets(void);

/* ---- game side -------------------------------------------------------- */
/* A mesh about to be drawn by the dominant VU1 program: mesh_pkt is the
 * mesh's static DMA packet (the CALL target after MSCAL 0x320); variant the
 * NRV_* features (nr_vu1.h) of the microcode pieces ModelEmitDrawPackets
 * uploads for it (D_00491280 row: head, kind, tail, decode, colour, output),
 * or -1 when one of them is not covered.  Returns a record id (nonzero) when
 * the mesh is drawn natively: the caller then emits the marker
 * (nr_marker_qwords) instead of the MSCAL + CALL; 0: emit the original. */
uint32_t nr_model_record(uint32_t mesh_pkt, int variant);
/* nr_model_record with the record's constant block filled from the game's
 * packet builders (nr_const.h; RG_NR_CONST): src[0] draw context, [1] camera
 * view packet, [2] light packet, [3] object matrix packet, [4] model info
 * packet, [5] skin packet, [6] the mesh's texture/material packet.  0 also
 * when the builders' packets are not in the covered layout. */
uint32_t nr_model_record2(uint32_t mesh_pkt, int variant, const uint32_t *src);
/* DrawPktBuildCameraMatrix_1486c0 (override): the camera matrix packet the
 * draw context ctx most recently built */
void nr_note_cammtx(uint32_t ctx, uint32_t pkt);
/* LightStateWritePacket_1484a0 (override): the light packet ctx wrote last */
void nr_note_light(uint32_t ctx, uint32_t pkt);
/* DrawPktBuildPlaneShadowMtx_147eb0 (override): the plane-shadow packet ctx built last */
void nr_note_plane(uint32_t ctx, uint32_t pkt);
/* CameraWriteViewPacket_148740 (override): a camera view packet (qw 0-19) ctx wrote at pkt */
void nr_note_view(uint32_t ctx, uint32_t pkt);
/* ModelQueueSortedPackets_14f0d0 (override): the view (kind 0) / light (kind 1) packet a sorted
 * node header names, resolved at build time (docs/NATIVE-RENDER.md "Remembered packets"):
 * returns pkt when its memory is live (what the builder wrote; normal play), else the address
 * of a copy written at dst (the frame's packet stack; *qw = qwords written, the caller advances
 * its cursor) */
uint32_t nr_chain_packet(uint32_t ctx, int kind, uint32_t pkt, uint32_t dst, uint32_t *qw);
/* DrawListFrameBegin_1425d0 (override), RG_NR_POISON: poison a frame packet stack's dead
 * contents before the game resets it (nr_mem.h) */
void nr_poison_stack(uint32_t base, uint32_t qwords);
/* Offscreen composite (nr_comp.h, docs/NATIVE-RENDER.md "Offscreen composite"):
 * DrawListResetClipRangeMaybe_148040 (override) resets the screen bbox the
 * Z-scale meshes accumulate (VU qw98/99); ScreenTexOverlayWriteSpriteMaybe_16a890
 * (override) asks for the sprite's native packet: r = the floats it would
 * upload to VU qw140-143 (16, z/w lanes as left in its packet buffer); writes a
 * DMA CNT + VIF DIRECT + GIF packet of at most cap_qw qwords into dst and
 * returns its size, 0 = nothing to draw (no packet), -1 = emit the original
 * MSCAL packet (the bbox is only known to VU1, or check/off modes). */
void nr_clip_reset(uint32_t ctx);
int nr_comp_sprite(uint32_t ctx, const float *r, uint32_t *dst, int cap_qw);
/* the three DMA qwords of a marker for record id: CNT + VIF DIRECT 2 +
 * GIF tag (A+D, NLOOP 1, EOP) + A+D write of id to GS register 0x7E */
void nr_marker_qwords(uint32_t id, uint32_t q[12]);

/* ---- frame list: the retained boundary (docs/NATIVE-RENDER.md "Frame list") --
 * Per game frame, the native draws in the order the GS executed them (= the
 * game's DMA order), each with everything needed to draw it again without the
 * game: the mesh (immutable decoded arrays), the program variant, the record's
 * constant block (the builders' source matrices and what nr_const_prog0
 * derived from them), the bone rows, the builders' packets it came from, the
 * GS register state the draw used and its screen box.  Built on the GS thread;
 * nr_frame_last() is the last completed frame (valid until the record ring
 * wraps: NR_RECS records, about ten frames). */
struct nr_mesh;
enum { NRF_FRAME, NRF_ZBUF, NRF_TEST, NRF_ALPHA, NRF_TEX0, NRF_TEX1, NRF_CLAMP, NRF_PRMODE, NRF_XYOFFSET,
       NRF_SCISSOR, NRF_FBA, NRF_FOGCOL, NRF_TEXA, NRF_PRIM,
       /* the rest of what a draw's pipeline reads (replay) */
       NRF_PRMODECONT, NRF_PABE, NRF_COLCLAMP, NRF_DTHE, NRF_DIMX, NRF_SCANMSK, NRF_MIPTBP1, NRF_MIPTBP2, NRF_N };
typedef struct nr_frame_item {
    uint32_t id;                 /* record id */
    const struct nr_mesh *mesh;
    int variant;                 /* NRV_* (nr_vu1.h) */
    const void *c;               /* nr_qw[112]: VU qwords 0..111 */
    const void *bones;           /* nr_qw[132]: VU qwords 768..899 */
    uint32_t src[8];             /* nr_model_record2 src: ctx, view, light, object, info, skin, material */
    uint64_t gs[NRF_N];          /* GS registers of the draw's context (NRF_*) */
    int has_box;
    float box[4];                /* GS window rectangle (pixels) */
    uint32_t texkey[8];          /* the decoded texture the draw sampled (renderer cache key, content-based) */
} nr_frame_item;
typedef struct nr_frame {
    uint32_t number;             /* nr_frame_begin count */
    uint32_t count;
    const nr_frame_item *items;
} nr_frame;
/* GS thread: the last completed frame (count 0 before the first) */
const nr_frame *nr_frame_last(void);
/* DrawListFrameBegin_1425d0 (override): a draw context starts a frame */
void nr_frame_begin(uint32_t ctx);

/* ---- runtime wiring --------------------------------------------------- */
struct vif_state;
struct vu_state;
struct gpu_renderer;
struct gpu_config;
/* before gpu_create: native mode needs hardware depth buffers */
void nr_runtime_gpu_config(struct gpu_config *gc);
/* after gpu_attach (and after every re-attach): the marker handler */
void nr_runtime_attach_gpu(struct gpu_renderer *r);
/* after vif_init of VIF1: the constant-snapshot tap on its PATH2 sink */
void nr_runtime_attach_vif(struct vif_state *vif1, struct vu_state *vu1);
/* the native local->host read for libgraph's rg_gs_store_hook (NULL: keep
 * the DMA path: emu / verify modes, RG_NR_STORE=0) */
int (*nr_native_store_fn(void))(uint64_t, uint64_t, uint64_t, void *, int, int);
/* counters (meshes recorded / drawn / fallbacks) */
void nr_runtime_stats(FILE *f);
/* the frame chain walker (nr_fx.c, docs/NATIVE-RENDER.md "Frame chain walker"): walks the
 * VIF1 chain at tadr like the DMAC + VIF would (tte: the tags' VIF words are part of the
 * stream), hands every DIRECT payload to sink in order and every other VIF command (VU data,
 * microcode, VIF registers; i bit cleared) to fwd, or drops them when fwd is NULL; DIRECT data
 * before a VU program start reaches sink first.  0 walked, -1 left to the DMAC (a bad address,
 * an invalid code, an open payload).
 * out->cl / wl: the VIF's STCYCL registers in (from the VIF) and out. */
typedef struct nr_fx_out {
    uint32_t tags, qwords;      /* the DMAC's cost units: tags + data qwords */
    uint32_t last_tag;          /* the last tag's low word (CHCR TAG bits) */
    uint32_t tadr, madr;        /* channel registers at the end */
    uint32_t cl, wl;
    int irq;                    /* a VIF code with the i bit */
} nr_fx_out;
typedef void (*nr_fx_sink)(void *user, const uint8_t *data, uint32_t bytes);
int nr_fx_on(void);
int nr_fx_walk(uint32_t tadr, int tte, nr_fx_sink sink, void *user, nr_fx_sink fwd, void *fwd_user, nr_fx_out *out);
void nr_fx_stats(FILE *f);
/* the native VU1 consumer of walked chains (nr_vux.c, docs/NATIVE-RENDER.md "VU1 programs at the
 * walker"): VU data memory, resident microcode and the translated programs; bind the GS input
 * first, then pass nr_vux_fwd as the walker's forward sink */
void nr_vux_bind(nr_fx_sink gs_sink, void *user);
uint32_t nr_frame_no(void);   /* frames begun (DrawListFrameBegin) */
void nr_vux_cmd(const uint8_t *data, uint32_t bytes);
void nr_vux_fwd(void *user, const uint8_t *data, uint32_t bytes);
void nr_vux_stats(FILE *f);
/* check mode (oracle builds, RG_NR_VU=check): the VU1 model's PATH1 sink is wrapped by nr_vux_p1_tap,
 * which compares every packet with ours, then calls orig */
typedef void (*nr_vux_p1_fn)(void *user, const uint8_t *data, uint32_t bytes, uint32_t vu_addr);
void nr_vux_check_bind(nr_vux_p1_fn orig, void *orig_user);
void nr_vux_p1_tap(void *user, const uint8_t *data, uint32_t bytes, uint32_t vu_addr);
/* 1: the offscreen composite's sprites are built natively (RG_NR_COMP=native, default) */
int nr_comp_native(void);
/* the state behind port/hwaccess.h's GS privileged / VIF1_FBRST routing (nr_hw.c) */
struct gs_state;
void nr_hw_bind(struct gs_state *gs, struct vif_state *vif1);

#ifdef __cplusplus
}
#endif
#endif
