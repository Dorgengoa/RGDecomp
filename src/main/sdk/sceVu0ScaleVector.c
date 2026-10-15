#include "vec.h"

asm void sceVu0ScaleVector(Vec4 *dst, const Vec4 *src, f32 t)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf5;
    vmulx.xyzw $vf6, $vf4, $vf5x;
    jr         $31;
    sqc2      $vf6, 0x0($4);
}
