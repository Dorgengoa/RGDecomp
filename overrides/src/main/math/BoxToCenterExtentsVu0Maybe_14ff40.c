/* rg-override: replaces game/src/main/math/BoxToCenterExtentsVu0Maybe_14ff40.c sha256 50b96e1f8b30b324750008e2bb6d228b4c09ebc6137f71efb838e50df94f3dd1
 * why: cross-file VU0 register protocol (loads the box extents/center (vf7) and the matrix (vf10-12) that BoxTransformExtentsVu0Maybe_14fed0 reads); with RG_VU0_LOCAL the file
 * shares the named context `xfbox` (port/vu0_ctx.h, docs/NATIVE-CPU.md); otherwise verbatim */
#define RG_VU0_CTX_NAME xfbox
#include "port/vu0_ctx.h"
/* rgp:protos */
#define RGP_SELF_BoxToCenterExtentsVu0Maybe_14ff40 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
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

typedef rg_u128 u128_14ff40;

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_vz_14ff40_t; /* rg:vu0bind vf0 */
#define vz_14ff40 RG_VU0_BIND_VF(0, rgvb_vz_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v1_14ff40_t; /* rg:vu0bind vf1 */
#define v1_14ff40 RG_VU0_BIND_VF(1, rgvb_v1_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v2_14ff40_t; /* rg:vu0bind vf2 */
#define v2_14ff40 RG_VU0_BIND_VF(2, rgvb_v2_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v3_14ff40_t; /* rg:vu0bind vf3 */
#define v3_14ff40 RG_VU0_BIND_VF(3, rgvb_v3_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v5_14ff40_t; /* rg:vu0bind vf5 */
#define v5_14ff40 RG_VU0_BIND_VF(5, rgvb_v5_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v6_14ff40_t; /* rg:vu0bind vf6 */
#define v6_14ff40 RG_VU0_BIND_VF(6, rgvb_v6_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v7_14ff40_t; /* rg:vu0bind vf7 */
#define v7_14ff40 RG_VU0_BIND_VF(7, rgvb_v7_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v10_14ff40_t; /* rg:vu0bind vf10 */
#define v10_14ff40 RG_VU0_BIND_VF(10, rgvb_v10_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v11_14ff40_t; /* rg:vu0bind vf11 */
#define v11_14ff40 RG_VU0_BIND_VF(11, rgvb_v11_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v12_14ff40_t; /* rg:vu0bind vf12 */
#define v12_14ff40 RG_VU0_BIND_VF(12, rgvb_v12_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_v13_14ff40_t; /* rg:vu0bind vf13 */
#define v13_14ff40 RG_VU0_BIND_VF(13, rgvb_v13_14ff40_t)

typedef u128_14ff40 __attribute__((aligned(4))) rgvb_acc_14ff40_t; /* rg:vu0bind ACC */
#define acc_14ff40 RG_VU0_BIND_ACC(rgvb_acc_14ff40_t)


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
