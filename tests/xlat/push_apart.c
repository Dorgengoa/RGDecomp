/* vu0asm stage input (mwcc asm-block form), verbatim body of
   game src/main/anim/DynClothSolveSpring_16a480.c.  CMake runs
   `tools/portxform.py vu0asm` on it; tests/test_vu0.c calls the result. */
#include "types.h"
#include "vec.h"

void xlat_push_apart(Vec4 *p0, Vec4 *p1, f32 a, f32 b)
{
    asm volatile {
        lqc2       vf10, 0(p0)
        lqc2       vf11, 0(p1)
        vsub.xyzw  vf31, vf31, vf31
        vaddw.xyzw vf31, vf31, vf0w
        vsub.xyzw  vf1, vf10, vf11
        vmul.xyz   vf2, vf1, vf1
        mfc1       $7, a
        mfc1       $8, b
        qmtc2.ni   $7, vf12
        qmtc2.ni   $8, vf13
        vadday.x   ACC, vf2, vf2y
        vmaddz.x   vf6, vf31, vf2z
        vrsqrt     Q, vf12x, vf6x
        vsub.x     vf14, vf31, vf13
        vwaitq
        vsubq.x    vf20, vf31, Q
        vmul.x     vf13, vf13, vf20
        vmul.x     vf14, vf14, vf20
        vmulx.xyzw vf21, vf1, vf13x
        vmulx.xyzw vf22, vf1, vf14x
        vsub.xyzw  vf10, vf10, vf21
        vadd.xyzw  vf11, vf11, vf22
        sqc2       vf10, 0(p0)
        sqc2       vf11, 0(p1)
    }
}

/* EE-only block: must stay asm (the stage leaves it; asmexclude cuts it) */
void *xlat_ee_only(void *list, s32 n)
{
    asm volatile {
        .set noreorder
        b      test
        sltu   $2, $0, $4
      loop:
        addiu  $5, $5, -1
      test:
        daddu  $2, $4, $0
    }
}
