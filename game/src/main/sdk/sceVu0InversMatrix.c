#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c. The rotation part is
   transposed via the same pextlw/pextuw/pcpyld/pcpyud shuffle sceVu0TransposeMatrix
   uses, then re-projected against the translation row to invert it. */

void sceVu0InversMatrix(Mtx4 *m0, const Mtx4 *m1)
{
    asm volatile {
        lq          $8, 0x0($5)
        lq          $9, 0x10($5)
        lq          $10, 0x20($5)
        lqc2        vf4, 0x30($5)
        vmove.xyzw  vf5, vf4
        vsub.xyz    vf4, vf4, vf4
        vmove.xyzw  vf9, vf4
        qmfc2.ni    $11, vf4
        pextlw      $12, $9, $8
        pextuw      $13, $9, $8
        pextlw      $14, $11, $10
        pextuw      $15, $11, $10
        pcpyld      $8, $14, $12
        pcpyud      $9, $12, $14
        pcpyld      $10, $15, $13
        qmtc2.ni    $8, vf6
        qmtc2.ni    $9, vf7
        qmtc2.ni    $10, vf8
        vmulax.xyz  ACC, vf6, vf5x
        vmadday.xyz ACC, vf7, vf5y
        vmaddz.xyz  vf4, vf8, vf5z
        vsub.xyz    vf4, vf9, vf4
        sq          $8, 0x0($4)
        sq          $9, 0x10($4)
        sq          $10, 0x20($4)
        sqc2        vf4, 0x30($4)
    }
}
