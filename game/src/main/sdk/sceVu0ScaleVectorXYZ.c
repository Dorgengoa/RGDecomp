#include "vec.h"

asm void sceVu0ScaleVectorXYZ(Vec4 *dst, const Vec4 *src, f32 t)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf5;
    vmulx.xyz  $vf4, $vf4, $vf5x;
    jr         $31;
    sqc2      $vf4, 0x0($4);
}
