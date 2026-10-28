/* rgp:protos */
#define RGP_SELF_CollTriTransform_16c1a0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

/* VU0 leaf: transform three points m[0..2] by the matrix the caller left in
 * vf10..vf13, store them to m[0], b, c, and store the cross product
 * (p1-p0) x (p2-p0) of the transformed points to n (triangle normal).
 * mwcc intrinsics on file-scope register bindings; only the ACC-destination
 * ops are SDK macros (Vu0MulMatrixAccR, Vu0OuterProductAcc in libvu0.h).
 * The empty `if (m)` launder is a zero-word block split that keeps the sqc2s
 * after the vsubs, as the original asm block did. */

#pragma vu0_mmi_reg_binding on

typedef rg_u128 u128_16c1a0;

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v13_16c1a0_t; /* rg:vu0bind vf13 */
#define v13_16c1a0 RG_VU0_BIND_VF(13, rgvb_v13_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v16_16c1a0_t; /* rg:vu0bind vf16 */
#define v16_16c1a0 RG_VU0_BIND_VF(16, rgvb_v16_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v17_16c1a0_t; /* rg:vu0bind vf17 */
#define v17_16c1a0 RG_VU0_BIND_VF(17, rgvb_v17_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v18_16c1a0_t; /* rg:vu0bind vf18 */
#define v18_16c1a0 RG_VU0_BIND_VF(18, rgvb_v18_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v20_16c1a0_t; /* rg:vu0bind vf20 */
#define v20_16c1a0 RG_VU0_BIND_VF(20, rgvb_v20_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v21_16c1a0_t; /* rg:vu0bind vf21 */
#define v21_16c1a0 RG_VU0_BIND_VF(21, rgvb_v21_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_v22_16c1a0_t; /* rg:vu0bind vf22 */
#define v22_16c1a0 RG_VU0_BIND_VF(22, rgvb_v22_16c1a0_t)

typedef u128_16c1a0 __attribute__((aligned(4))) rgvb_acc_16c1a0_t; /* rg:vu0bind ACC */
#define acc_16c1a0 RG_VU0_BIND_ACC(rgvb_acc_16c1a0_t)


void CollTriTransform_16c1a0(u128_16c1a0 *m, u128_16c1a0 *b, u128_16c1a0 *c, u128_16c1a0 *n)
{ RG_VU0_FRAME;
    v16_16c1a0 = m[0];
    v17_16c1a0 = m[1];
    v18_16c1a0 = m[2];
    Vu0MulMatrixAcc(xyzw, vf10, vf11, vf12, vf16);
    v16_16c1a0 = _vmaddbc(v16_16c1a0, 0xF, acc_16c1a0, v13_16c1a0, v16_16c1a0, 1);
    Vu0MulMatrixAcc(xyzw, vf10, vf11, vf12, vf17);
    v17_16c1a0 = _vmaddbc(v17_16c1a0, 0xF, acc_16c1a0, v13_16c1a0, v17_16c1a0, 1);
    Vu0MulMatrixAcc(xyzw, vf10, vf11, vf12, vf18);
    v18_16c1a0 = _vmaddbc(v18_16c1a0, 0xF, acc_16c1a0, v13_16c1a0, v18_16c1a0, 1);
    v20_16c1a0 = _vsub(v20_16c1a0, 0xF, v17_16c1a0, v16_16c1a0);
    v21_16c1a0 = _vsub(v21_16c1a0, 0xF, v18_16c1a0, v16_16c1a0);
    if (m) {
        m = (u128_16c1a0 *)(s32)(u32)m;
    }
    m[0] = v16_16c1a0;
    *b = v17_16c1a0;
    *c = v18_16c1a0;
    _vnop();
    Vu0OuterProductAcc(vf20, vf21);
    v22_16c1a0 = _vopmsub(v22_16c1a0, acc_16c1a0, v21_16c1a0, v20_16c1a0);
    *n = v22_16c1a0;
}
