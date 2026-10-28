/* SPDX-License-Identifier: CC0-1.0 */
/* The shadow-volume VU1 program as plain C (docs/NATIVE-RENDER.md "Shadow
 * volumes", slice 2).  Retail packet 0x4425F0 (head at VU 0x320, table row 4
 * of VuMicrocodeTableInit) with its main piece 0x4427E0 at 0x10E0 and the
 * model program's decode pieces at 0x960 (rigid 0x4392C0 / skinned 0x4393B0).
 *
 * For every source triangle (vertices taken three at a time) whose world
 * normal faces the shadow light (dot(qw34, n) > 0.0001), the program takes
 * the triangle A (object matrix qw60-63, then camera) and its projection B on
 * the shadow plane (plane-projection matrix qw30-33 x object matrix), skips
 * the triangle when any of the six clip vectors leaves the (guard-scaled)
 * frustum, and draws the closed prism as five 4-vertex fans: the three sides
 * (A0 B0 B1 A1, A1 B1 B2 A2, A2 B2 B0 A0) and both caps (A0 A1 A2 A2,
 * B2 B1 B0 B0).  Each fan is preceded by one of two register packets in VU
 * memory, chosen by the fan's screen-space winding: qw38 (z of the screen
 * cross product > 0) or qw35, each an A+D ALPHA_1 write plus a PACKED RGBAQ
 * (DrawPktBuildPlaneShadowMtx_147eb0: (Cs-0)*As+Cd at qw35, (0-Cs)*As+Cd at
 * qw38, colour 1,1,1,0x80).  The fans' PRIM is 5 (fan), attributes from
 * PRMODE (qw87.x), vertices XYZF2 only.
 *
 * The arithmetic follows the VU (single precision chopped toward zero, the
 * program's operation order) so the generated fixed-point vertices match the
 * VU1 interpreter exactly (rg-nr-nmcheck --shadow). */
#ifndef RG_NR_VU1SH_H
#define RG_NR_VU1SH_H

#include <stdint.h>

#include "nr_vu1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* one fan as the program kicks it */
typedef struct nr_shface {
    uint32_t regq;            /* register packet: 35 or 38 (VU qword) */
    int32_t x[4], y[4], z[4]; /* ftoi4 of the screen vector (GS takes x, y bits 0-15, z >> 4) */
    int32_t w[4];             /* ftoi4 of w (XYZF2 word 3: fog bits 4-11, ADC bit 15) */
} nr_shface;

/* positions: decoded object-space vertices (the decode piece's output);
 * n: vertex count (triangles = n / 3); c: VU qwords 0..111.  Returns the
 * number of faces written (at most max; 5 per drawn triangle). */
int nr_vu1sh_faces(const nr_qw *c, const float (*pos)[3], uint32_t n, nr_shface *out, int max);

/* decode one batch's positions from VU memory as the decode pieces do
 * (rigid: itof15 * qw77; skinned: bone matrices 900 + 2 i, weights / 255);
 * returns the vertex count (header .y) */
int nr_vu1_decode_positions(const nr_qw *mem, uint32_t top, int skinned, float (*out)[3], int max);

/* the decode pieces' arithmetic (VU-exact): position lane = itof15(raw) * scale,
 * weight = itof0(byte) * 0.00392157, skinning over nb bones (rows[b][0..3]
 * = the bone matrix rows) */
float nr_vu1sh_pos(int32_t raw, float scale);
float nr_vu1sh_weight(uint32_t byte);
void nr_vu1sh_skin(const float p[3], const float *const rows[4][4], const float w[4], int nb, float out[3]);

/* piece signature of the shadow main piece at 0x10E0 (corpus header) */
int nr_vu1sh_is_shadow_sig(const uint32_t sig[10]);

#ifdef __cplusplus
}
#endif
#endif
