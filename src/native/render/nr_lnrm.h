/* SPDX-License-Identifier: CC0-1.0 */
/* Leftover normals natively (RG_NR_MISSNRM=3, the default since lane missnrm3, docs/NATIVE-RENDER.md "Leftover normals
 * natively", lane missnrm3).
 *
 * A lit / environment-mapped model mesh whose batches unpack no normals (Blue Thunder,
 * chara/mob/e129; Cactugus e147; two JR05 field meshes) has the VU program read its normal
 * slots as they were left by the batches before it.  Those values are the data flow of the
 * model program itself: every batch's decode piece stores its positions, normals and UVs back
 * in place as floats (0x4392C0 / 0x4393B0), the environment-map kind stores its UVs (0x43EA30),
 * the loops store one element past the batch, the output pieces build the GIF packet after
 * the arrays.  A frame's draws therefore leave, at fixed VU addresses (TOP = 140 or
 * 140 + 2 x qw76.x, alternating per batch), values that are a deterministic function of the
 * meshes drawn before (their unpacked data, constants and bone matrices).
 *
 * This module keeps the frame's model batches in draw order (from the walker's markers) as a
 * log of what each writes where, and computes, only for a mesh that reads leftovers, the value
 * of each normal slot: the last writer's in-place store, from that writer's own inputs
 * (recursively: its input is the slot's earlier value), in VU arithmetic.  No VU program, no
 * VU memory image: what is not a model batch (output packets, clipper fans, particle and
 * composite programs, shadow volumes) makes the slots it may write unknown, and an unknown
 * slot falls back to RG_NR_MISSNRM=2's sign vector (counted). */
#ifndef RG_NR_LNRM_H
#define RG_NR_LNRM_H

#include <stdint.h>

#include "nr_mesh.h"
#include "nr_vu1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* one native model draw as the VU program sees it */
typedef struct nr_lnrm_draw {
    const nr_mesh *mesh;
    int skinned;              /* the skinned decode piece (0x4393B0) is resident */
    int env;                  /* the environment-map kind (0x43EA30) */
    int shadow;               /* the shadow-volume program (head 0x4425F0; decode 0x439F90 / 0x43A020) */
    const nr_qw *c;           /* constants qw 0..111 (copied: rows 24-26, 64-66, 76-81) */
    const nr_qw *bones;       /* qw 768..1023 (kept by pointer: valid while *live == live_id) */
    const uint32_t *live;
    uint32_t live_id;
    const uint32_t *items;    /* item packets (EE addresses) the PS2 chain CALLs before this draw */
    int nitems;
} nr_lnrm_draw;

int nr_lnrm_on(void);         /* RG_NR_MISSNRM=3 (the default; 0 / 1 / 2: off) */
/* a model draw passes (walker order); when out != NULL, first the leftover of each of its
 * vertices' normal slots (raw qword lanes x, y, z as the program reads them, per vertex in
 * vtx[] order) into out and a known flag into known; returns the vertices left unknown */
uint32_t nr_lnrm_draw_pass(const nr_lnrm_draw *d, int32_t (*out)[3], uint8_t *known);
/* something that is not a model batch may write qwords [lo, lo + n) (mod 1024) */
void nr_lnrm_unknown(uint32_t lo, uint32_t n);
/* the walker's VIF codes in chain order (STCYCL CL / WL in effect): OFFSET / BASE / program
 * starts drive the double buffer, UNPACKs make their qwords unknown */
void nr_lnrm_vif(uint32_t code, uint32_t cl, uint32_t wl);
void nr_lnrm_vux_present(void);   /* nr_vux.c consumes the walker's VU work (reports program writes) */
void nr_lnrm_sprite(void);
void nr_lnrm_opaque_draw(void);   /* a draw whose VU work is not modelled (shadow volumes, lines, ...) */        /* the composite's sprite (MSCAL 0x960, writes qw140-169) */
/* VU ITOF15 (the double result chopped to 24 bits) */
float nr_lnrm_itof15(int32_t v);
/* nr_scene.c: a DIRECT payload of qw qwords the frame chain walker passes (DMA order) */
void nr_lnrm_walk_direct(const uint8_t *p, uint32_t qw);
/* stats line (nr_runtime_stats) */
void nr_lnrm_stats(void *file);

#ifdef __cplusplus
}
#endif
#endif
