#include "types.h"
#include "libvu0.h"

/* Pure VU0 macro-mode leaf: computes into vf7/vf10/vf11/vf12 and returns
   without storing them -- the caller picks the results up from the VU
   register file (file-scope register bindings here). mwcc intrinsics; only
   the ACC-destination ops are SDK macros (Vu0MulAccX, Vu0MulMatrixAccR in
   libvu0.h). D_0047DEE0 = {0.5f, 0, 0, 0} in .sdata (built with
   -sdatathreshold 16, config/toolchain.txt); the empty launder keeps its
   gp address in a register (`addiu v1,gp,..; lqc2 vf3,0(v1)`). */

#pragma vu0_mmi_reg_binding on

typedef unsigned __int128 u128_14ff40;

extern u128_14ff40 vz_14ff40 asm("vf0");
extern u128_14ff40 v1_14ff40 asm("vf1");
extern u128_14ff40 v2_14ff40 asm("vf2");
extern u128_14ff40 v3_14ff40 asm("vf3");
extern u128_14ff40 v5_14ff40 asm("vf5");
extern u128_14ff40 v6_14ff40 asm("vf6");
extern u128_14ff40 v7_14ff40 asm("vf7");
extern u128_14ff40 v10_14ff40 asm("vf10");
extern u128_14ff40 v11_14ff40 asm("vf11");
extern u128_14ff40 v12_14ff40 asm("vf12");
extern u128_14ff40 v13_14ff40 asm("vf13");
extern u128_14ff40 acc_14ff40 asm("ACC");

extern f32 D_0047DEE0[4];

void BoxToCenterExtentsVu0Maybe_14ff40(u128_14ff40 *a, u128_14ff40 *m)
{
    u128_14ff40 *h = (u128_14ff40 *)D_0047DEE0;

    if (h) {
        h = (u128_14ff40 *)(s32)(u32)h;
    }
    v3_14ff40 = *h;
    v1_14ff40 = a[0];
    v2_14ff40 = a[1];
    Vu0MulAccX(xyzw, vf1, vf3);
    v5_14ff40 = _vmsubbc(v5_14ff40, 0xF, acc_14ff40, v2_14ff40, v3_14ff40, 8);
    v6_14ff40 = _vadd(v6_14ff40, 0xF, v5_14ff40, v2_14ff40);
    v10_14ff40 = m[0];
    v11_14ff40 = m[1];
    v12_14ff40 = m[2];
    v13_14ff40 = m[3];
    Vu0MulMatrixAcc(xyzw, vf10, vf11, vf12, vf6);
    v7_14ff40 = _vmaddbc(v7_14ff40, 0xF, acc_14ff40, v13_14ff40, vz_14ff40, 1);
    v10_14ff40 = _vmulbc(v10_14ff40, 0xF, v10_14ff40, v5_14ff40, 8);
    v11_14ff40 = _vmulbc(v11_14ff40, 0xF, v11_14ff40, v5_14ff40, 4);
    v12_14ff40 = _vmulbc(v12_14ff40, 0xF, v12_14ff40, v5_14ff40, 2);
}
