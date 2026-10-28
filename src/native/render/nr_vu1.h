/* SPDX-License-Identifier: CC0-1.0 */
/* The dominant VU1 model program as plain C (docs/NATIVE-RENDER.md "The model
 * program").  Retail packet 0x436CB0 (head at VU 0x320/0x330) plus the pieces
 * it calls: decode (0x960: rigid 0x4392C0, skinned 0x4393B0), kind (0x39D0:
 * UV scroll 0x43E980), colour (0x10E0: constant 0x43A620, vertex colour
 * 0x43AEC0), output (0x1900: 0x43BC90 / 0x43BF60 / 0x43C2B0 / 0x43CA90 /
 * 0x43CD40 / 0x43D110) and the clipper (0x2620, 0x4371D0); also the kind piece
 * 0x43EA30 (environment map) and the colour piece 0x43A700 (directional lights).
 *
 * This file is the reference semantics: what the microprogram computes per
 * vertex, from the VU1 constant block (the game's camera / object / material
 * packets) and one vertex batch (the mesh's static VIF packet).  The native
 * renderer's vertex shader (src/gpu/shaders/nr_draw.hlsl) is a transcription;
 * render_nmcheck compares this code with the VU1 interpreter on captured
 * frames.  Not used for GPU-exact output: no VU rounding, no ftoi4 snapping
 * beyond what the comparison needs.
 */
#ifndef RG_NR_VU1_H
#define RG_NR_VU1_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* one VU1 data-memory quadword as the VIF leaves it (UNPACK sign/zero
 * extends to 32-bit lanes) */
typedef union nr_qw {
    uint32_t u[4];
    int32_t i[4];
    float f[4];
} nr_qw;

/* VU1 constant-block slots the program reads (quadword addresses) */
enum {
    NRQ_GIFTAG0 = 0,
    NRQ_VIEW = 24,       /* view matrix rows (24..27; camera packet) */
    NRQ_CAMPOS = 28,     /* .xyz camera position in world space (kind 0x43F100) */
    NRQ_LIGHTCOL = 33,   /* light colours 33..36 (lanes of 100..102), 37 ambient */     /* A+D GIF tag template of the batch header (PRIM, PRMODE) */
    NRQ_ZMAX = 1,        /* .y: largest Z (CA90 family) */
    NRQ_REGTAG = 19,     /* .yzw: GIF tag of the one-register packet (FOGCOL) */
    NRQ_COLCLAMP = 39,   /* colour clamp (min) */
    NRQ_FOG = 40,        /* fog = max(min(x + w * clip.w, y), z) */
    NRQ_REGDATA = 41,    /* A+D data of the one-register packet (FOGCOL) */
    NRQ_MATCOL = 42,     /* material colour (87.y bit 0x200 clear) */
    NRQ_MATCOL2 = 43,    /* material colour (87.y bit 0x200 set) */
    NRQ_OBJMTX = 60,     /* object matrix rows (60..63) */
    NRQ_NRMMTX = 64,     /* object rotation, rows normalised (64..66; VU program 0) */
    NRQ_SCREEN = 68,     /* object -> GS screen matrix rows (68..71; VU program 0) */
    NRQ_CLIP = 72,       /* object -> clip matrix rows (72..75; the clipper) */
    NRQ_BATCH = 76,      /* .x output offset, .z skinned */
    NRQ_POSSCALE = 77, NRQ_NRMSCALE = 78, NRQ_UVSCALE = 79,
    NRQ_FLAGS = 81,      /* .x bit 1: clipper on; .w alpha multiplier */
    NRQ_COLMUL = 82, NRQ_COLADD = 83,
    NRQ_TAGTPL = 86,     /* .yzw: vertex GIF tag template (STQ RGBAQ XYZF2) */
    NRQ_MAT = 87,        /* .x PRMODE, .y flags, .z Z scale */
    NRQ_UVOFS = 88,      /* .xy UV scroll */
    NRQ_LIGHTDIR = 100,  /* light directions in object space, one light per lane (100..102) */
    NRQ_GUARD = 109,     /* guard band scale / offset (109, 110) */
    NRQ_HAND = 111,      /* .z +-1: object matrix handedness (culling sign) */
    NRQ_BONES = 900,     /* bone matrices: rows at 900 + idx .. 903 + idx (idx even) */
    NRQ_CONST_N = 112
};

/* the program variant: which pieces are resident (VuMicrocodeTableInit
 * slot + D_00491280 tables), as features */
enum {
    NRV_SKIN = 1 << 0,      /* 0x4393B0 (else rigid 0x4392C0) */
    NRV_UVSCROLL = 1 << 1,  /* 0x43E980 */
    NRV_VCOL = 1 << 2,      /* 0x43AEC0 (else constant colour 0x43A620) */
    NRV_ZSCALE = 1 << 3,    /* output CA90 family: Z * 87.z, min qw1.y, bbox */
    NRV_GUARD = 1 << 4,     /* output marks guard-band vertices (ADC) for the clipper */
    NRV_CULL = 1 << 5,      /* output marks back faces (ADC) */
    NRV_ENVMAP = 1 << 6,    /* kind 0x43EA30: UV = view-space normal.xy * 0.5 + 0.5 */
    NRV_LIGHT = 1 << 7,     /* colour 0x43A700: ambient + 4 directional lights */
    NRV_SHADOW = 1 << 8,    /* another program: the shadow volumes, head 0x4425F0 (nr_vu1sh.h);
                               with NRV_SKIN: decode 0x43A020 */
    NRV_LINES = 1 << 9,     /* another program: the line strands, head 0x441660 (nr_vu1ln.h) */
    NRV_REFLECT = 1 << 12,  /* kind 0x43F100 (the INSECT overlay's floors): reflection map, UV =
                               (R.xz + 1) / 2, R = V - 2 (V.N) N, V = the eye -> vertex direction in
                               world space (object matrix qw60-63, camera position qw28, normalised),
                               N = the normal through qw64-66 (not normalised); 1 << 11 is the
                               shader's NRV_IM */
    NRV_REFRACT = 1 << 10   /* the refraction material (VuMicrocodeTableInit row 6): head 0x436FB0,
                               kind 0x43ECD0 (UV = the vertex's screen position through the clip
                               matrix qw72-75, around the object origin, scaled by 82.z, offset by
                               (82.xy - 1) * 0.05), output 0x43E380 (STQ = (u, v, 1): linear in
                               screen space; RGB 128; Z scale and clamp as the CA90 family, no
                               bbox) */
};

/* piece signatures: lower words of the first two pairs (render_vutrace
 * corpus header order: 0x320, 0x960, 0x10E0, 0x1900, 0x39D0); returns the
 * NRV_* features, or -1 when a resident piece is not one this code covers */
int nr_vu1_variant_from_sig(const uint32_t sig[10]);

/* One vertex as the program writes it into the GIF packet. */
typedef struct nr_vout {
    float sx, sy, sz;     /* GS window coordinates (x, y in pixels incl. the
                             2048 offset; z before ftoi4) */
    float fog;            /* 0..255 */
    float clip[4];        /* object -> screen matrix result (x, y, z, w) */
    float r, g, b, a;     /* 0..255 (after the clamp, before ftoi0) */
    float s, t, q;
    int adc;              /* the program would not draw it (ADC) */
} nr_vout;

/* Run the program's per-vertex math on one batch.
 *   mem: VU1 data memory (constants at their slots, the batch at top)
 *   top: the batch's quadword address (XTOP)
 *   variant: NRV_* features
 * Writes up to max vertices; returns the vertex count (header .y), or -1
 * when the batch uses a path this code does not cover (87.y bit 0x100). */
int nr_vu1_batch(const nr_qw *mem, uint32_t top, int variant, nr_vout *out, int max);

/* The native pipeline's math (= nr_draw.hlsl VS_nr) for one decoded vertex:
 * c = VU qwords 0..111, bones768 = VU qwords 768..899, bone[] = row - 768. */
int nr_vu1_vertex(const nr_qw *c, const nr_qw *bones768, int variant, const int16_t pos[3], const int8_t nrm[3],
                  const int16_t uv[2], const uint8_t col[4], const uint8_t bone[4], const uint8_t wgt[4],
                  nr_vout *o);

/* header fields of a batch at `top` */
static inline uint32_t nr_vu1_prim(const nr_qw *mem, uint32_t top) { return mem[top].u[0]; }
static inline uint32_t nr_vu1_count(const nr_qw *mem, uint32_t top) { return mem[top].u[1] & 0x7FFF; }

#ifdef __cplusplus
}
#endif
#endif
