#include "vec.h"

asm void sceVu0InterVector(Vec4 *dst, const Vec4 *v0, const Vec4 *v1, f32 t)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($6);
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf6;
    vaddw.x    $vf7, $vf0, $vf0w;
    vsub.x     $vf8, $vf7, $vf6;
    vmulax.xyzw $ACC, $vf4, $vf6x;
    vmaddx.xyzw $vf9, $vf5, $vf8x;
    jr         $31;
    sqc2      $vf9, 0x0($4);
}
