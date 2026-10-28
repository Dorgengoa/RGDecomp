/* SPDX-License-Identifier: CC0-1.0 */
/* Native renderer, immediate packets (docs/NATIVE-RENDER.md "Immediate
 * packets (slice 3)").
 *
 * The game's 2D / effect drawing (UI, HUD, fonts, menus, message windows,
 * sprites, screen-effect passes) goes through one API: DrawListBeginPrim_141b00
 * hands out a GsPkt builder, the GsPkt* functions write a DMA sub-chain of
 * VIF DIRECT + GIF packets, and DrawListEndPrim_141a20 puts a DMA CALL to it
 * into the frame's chain.  The EndPrim override calls nr_im_end_prim on the
 * finished sub-chain: it is decoded ONCE on the EE into a record (the exact
 * sequence of GS register writes the GIF would make, PACKED conversions
 * applied, IMAGE data copied) and its head is rewritten into a marker
 * (CNT + DIRECT A+D write of the record id to GS_NATIVE_MARK, bit 63 set) +
 * RET, so neither the VIF nor the GIF parser sees the packet.  On the GS
 * thread the marker runs the record:
 *
 *   native  state registers go to the GS register file (CLUT loads and
 *           transfers included), primitives are batched by state and drawn by
 *           the native pipeline (gpu_nr_im_submit: hardware raster, decoded
 *           textures, hardware blending); states it does not cover go through
 *           the GS draw path (gs_draw_kick, the emulated exact path)
 *   replay  every write through gs_write_reg: what the GIF parser would do
 *           (check of the decoder: frames bit-identical to off)
 *
 * RG_NR_IM = native (default) | replay | off (the packets go to the VIF as
 * before).  Only with RG_RENDER=native. */
#ifndef RG_NR_IM_H
#define RG_NR_IM_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

enum { NRIM_OFF = 0, NRIM_NATIVE = 1, NRIM_REPLAY = 2 };
int nr_im_mode(void);

/* EE (DrawListEndPrim_141a20 override): the sub-chain at host address pkt is
 * finished; decode it and replace it by a marker.  1 replaced, 0 left as is. */
int nr_im_end_prim(uint32_t pkt);
/* the packet being closed was squeezed in X by the widescreen layout (GsPktClose override,
 * rg_layout_packet): the next nr_im_end_prim record draws its upscaled point sprites without
 * snapping X to native pixels (gpu_set_im_xfree), so no texel column is dropped */
void nr_im_note_xscaled(void);

/* EE: a bare GIF stream (PACKED / REGLIST / IMAGE tags; the native VU1 programs' XGKICK
 * packets, nr_vux.c) decoded into a record like a sub-chain's GIF data.  Returns 1 and the
 * 32-byte GIF packet (A+D, the marker write) that replaces it in the GS input in out; 0 when
 * the stream is not taken (send it as it is). */
int nr_im_gif(const void *qw, uint32_t nqw, uint8_t out[32]);

/* EE: a GIF stream for one path (the frame walker's DIRECT payloads, the GIF channel's data)
 * split into packets: a packet without IMAGE data becomes a record (nr_im_gif) and its marker
 * goes to sink in its place; a packet with IMAGE tags is split (its runs of other tags as
 * records with EOP set, the IMAGE tags as they are); packets nr_im_gif refuses (SIGNAL /
 * FINISH / LABEL, markers, local->host) and a packet still open at the end of the data (its
 * rest is recognised at the start of the next call) go to sink as they are, in order. */
typedef void (*nr_gif_sink)(void *user, const uint8_t *data, uint32_t bytes);
typedef struct nr_gif_split {
    int open;                          /* a packet passed as it is continues in the next call */
    uint32_t nloop, nreg, flg, eop, in_tag;
    uint64_t pkts, recs, raw, raw_open, split;
    uint8_t *tmp;
    uint32_t tcap;
} nr_gif_split;
void nr_im_gif_stream(nr_gif_split *st, const uint8_t *qw, uint32_t nqw, nr_gif_sink sink, void *user);
/* the GIF channel (PATH3) through nr_im_gif_stream: installed into the native libdma by
 * nr_runtime_attach_gpu (native-only builds) */
void nr_im_path3(const void *qw, uint32_t nqw);
/* (nr_scene.c) the data as it is to the attached GS's PATH3 */
void nr_im_path3_raw(const uint8_t *qw, uint32_t nqw);
void nr_im_path3_stats(FILE *f);

/* the value bit that marks an immediate record in a GS_NATIVE_MARK write */
#define NRIM_MARK_BIT (1ull << 63)

struct gpu_renderer;
#ifndef RG_GPU_GS_T
#define RG_GPU_GS_T
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
typedef struct nr_gs gpu_gs;      /* (as gpu.h) the native state block */
#else
typedef struct gs_state gpu_gs;   /* the GS model */
#endif
#endif
/* GS thread (the marker handler): run record id */
void nr_im_marker(struct gpu_renderer *gr, gpu_gs *gs, uint32_t id);

/* RG_NATIVE_ONLY (nr_gs.c "GIF input"): complete GIF packets (nqw qwords, every packet
 * closed by EOP) as one record; SIGNAL / FINISH / LABEL are raised on the calling (EE)
 * thread, markers and every register write stay in the record in order.  Returns the
 * record id (run it with nr_im_marker), 0 when refused (open packet, too large). */
uint32_t nr_im_gif_rec(const void *qw, uint32_t nqw);

/* (nr_interp.c: interpolated presentation) the record is still in the ring (a pass may run it
 * again); a census signature: FNV of its state writes and IMAGE sizes, its vertex writes
 * counted and hashed apart */
int nr_im_rec_valid(uint32_t id);
void nr_im_rec_info(uint32_t id, uint64_t *sig, uint32_t *nvtx, uint64_t *vhash);

void nr_im_stats(FILE *f);

#ifdef __cplusplus
}
#endif
#endif
