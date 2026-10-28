#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c. Copies the rotation
   part of m1 through GPRs (plain qword loads/stores, no VU op needed) and
   adds the translation vector to m1's own translation row. */

void sceVu0TransMatrix(Mtx4 *m0, const Mtx4 *m1, const Vec4 *tv)
{
    asm volatile {
        lqc2      vf4, 0x0($6)
        lqc2      vf5, 0x30($5)
        lq        $7, 0x0($5)
        lq        $8, 0x10($5)
        lq        $9, 0x20($5)
        vadd.xyz  vf5, vf5, vf4
        sq        $7, 0x0($4)
        sq        $8, 0x10($4)
        sq        $9, 0x20($4)
        sqc2      vf5, 0x30($4)
    }
}
