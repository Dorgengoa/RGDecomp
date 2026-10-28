/* SPDX-License-Identifier: CC0-1.0 */
/* Native renderer: the offscreen-composite VU1 program (retail MPG packet
 * 0x445C60, 59 instructions at VU address 0x960) as C, VU-exact
 * (docs/NATIVE-RENDER.md "Offscreen composite").
 *
 * ModelDrawOffscreenCompositeMaybe_16aac0 draws a character into a work
 * texture and composites it back with screen-space sprites
 * (ScreenTexOverlayWriteSpriteMaybe_16a890).  Each sprite is one MSCAL 0x960
 * with qw140-144 = rectangle min, max (pixels), UV offset, XYZ offset, GIF
 * tag; the program clips the rectangle to the screen bbox the Z-scale output
 * pieces of the model program left in qw98/99 (expanded by one pixel in x/y)
 * and kicks it as sprites 32 pixels wide:
 *
 *   a = max(rmin, lo - (1,1,0)), b = min(rmax, hi + (1,1,0))
 *   nothing when b.x - a.x < 0 or b.y - a.y < 0
 *   for x0 = a.x, a.x + 32, ... while (b.x - a.x - 1) - 32 k >= 0:
 *       x1 = min(x0 + 32, b.x)
 *       UV = ftoi4((x0, a.y, a.z, 0) + dy), XYZ2 = ftoi4((x0, a.y, a.z, 0) + ofs)
 *       UV = ftoi4((x1, b'.y, b'.z, b'.w) + dy), XYZ2 = ftoi4(same + ofs)
 *   with b' = max(b.yzw, I) (MAXi with the I register as the program finds
 *   it: the LOI in the same pair takes effect after the upper instruction)
 *
 * All arithmetic is the VU's (chopped toward zero). */
#ifndef RG_NR_COMP_H
#define RG_NR_COMP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nr_comp_in {
    float rmin[4];    /* qw140 (only xyz are loaded) */
    float rmax[4];    /* qw141 (xyz) */
    float dy[4];      /* qw142: UV offset (all four lanes are added) */
    float ofs[2];     /* qw143.xy: XYZ offset (z, w 0) */
    float lo[3];      /* qw98.xyz */
    float hi[3];      /* qw99.xyz */
    float i_reg;      /* the VU's I register at MSCAL */
} nr_comp_in;

/* one kicked sprite: the four PACKED register qwords (UV, XYZ2, UV, XYZ2) as
 * the program stores them (ftoi4 words; the GIF tag is qw144's) */
typedef struct nr_comp_strip {
    int32_t q[4][4];
} nr_comp_strip;

/* the strips of one program run; returns their count (0: the program kicks
 * nothing), or -1 when there are more than cap */
int nr_comp_strips(const nr_comp_in *in, nr_comp_strip *out, int cap);

#ifdef __cplusplus
}
#endif
#endif
