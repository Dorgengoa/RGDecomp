/* vu0asm stage input (GNU asm form, raw newlines inside the string
   literals), verbatim from src/main/anim/AnimKeyBlendMaterial_1559e0.c at
   naming 2efa6b43 (before the int128 stage).  d = d + (b - d) * t. */
#include "types.h"

typedef unsigned __int128 u128;

void xlat_lerp_gnu(u128 *d, u128 *b, f32 t)
{
    __asm__ __volatile__(
        "lqc2 $vf4, %0
"
        "lqc2 $vf5, 0(%1)
"
        "mfc1 $8, %2
"
        "nop
"
        "qmtc2.ni $8, $vf6
"
        "vsub.xyzw $vf7, $vf5, $vf4
"
        "vmulaw.xyzw $ACC, $vf4, $vf0w
"
        "vmaddx.xyzw $vf8, $vf7, $vf6x
"
        "sqc2 $vf8, %0
"
        : "+m"(*d) : "r"(b), "f"(t) : "$8");
}

