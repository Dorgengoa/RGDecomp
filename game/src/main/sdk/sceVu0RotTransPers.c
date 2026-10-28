#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c. Transforms v1 by m0,
   perspective-divides by the resulting w, then converts to fixed-point:
   vftoi4 (screen xy, 12-bit fraction) unconditionally, and vftoi0 (plain
   round) additionally overwrites z/w when mode is set -- retail's own
   fall-through, transcribed as the label the reference disassembly has. */

void sceVu0RotTransPers(s32 *v0, const Mtx4 *m0, const Vec4 *v1, s32 mode)
{
    asm volatile {
        .set noreorder
        lqc2         vf4, 0x0($5)
        lqc2         vf5, 0x10($5)
        lqc2         vf6, 0x20($5)
        lqc2         vf7, 0x30($5)
        lqc2         vf8, 0x0($6)
        vmulax.xyzw  ACC, vf4, vf8x
        vmadday.xyzw ACC, vf5, vf8y
        vmaddaz.xyzw ACC, vf6, vf8z
        vmaddw.xyzw  vf9, vf7, vf8w
        vdiv         Q, vf0w, vf9w
        vwaitq
        vmulq.xyz    vf9, vf9, Q
        beqz         $7, rottp_done
        vftoi4.xyzw  vf10, vf9
        vftoi0.zw    vf10, vf9
      rottp_done:
        sqc2         vf10, 0x0($4)
    }
}
