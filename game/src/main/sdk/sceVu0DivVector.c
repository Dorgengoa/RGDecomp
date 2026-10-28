#include "vec.h"

asm void sceVu0DivVector(Vec4 *dst, const Vec4 *src, f32 t)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf5;
    vdiv       $Q, $vf0w, $vf5x;
    vwaitq;
    vmulq.xyzw $vf4, $vf4, $Q;
    jr         $31;
    sqc2      $vf4, 0x0($4);
}
