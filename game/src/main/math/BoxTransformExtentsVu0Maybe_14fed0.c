/* rgp:protos */
#define RGP_SELF_BoxTransformExtentsVu0Maybe_14fed0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

/* VU0 leaf: rotate the three axis vectors the caller left in vf10..vf12 by
 * the 3x3 part of m (lqc2 vf1..vf4), sum their absolute values (box extent)
 * into *e, and transform the point in vf7 by m into *d.
 * mwcc intrinsics on file-scope register bindings; only the ACC-destination
 * ops and the vf26 result are SDK macros (Vu0ApplyMatrix3Acc, Vu0AddAcc,
 * Vu0MulMatrixAcc, Vu0StoreAccW26 in libvu0.h). */

#pragma vu0_mmi_reg_binding on

typedef rg_u128 u128_14fed0;

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_vz_14fed0_t; /* rg:vu0bind vf0 */
#define vz_14fed0 RG_VU0_BIND_VF(0, rgvb_vz_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v1_14fed0_t; /* rg:vu0bind vf1 */
#define v1_14fed0 RG_VU0_BIND_VF(1, rgvb_v1_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v2_14fed0_t; /* rg:vu0bind vf2 */
#define v2_14fed0 RG_VU0_BIND_VF(2, rgvb_v2_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v3_14fed0_t; /* rg:vu0bind vf3 */
#define v3_14fed0 RG_VU0_BIND_VF(3, rgvb_v3_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v4_14fed0_t; /* rg:vu0bind vf4 */
#define v4_14fed0 RG_VU0_BIND_VF(4, rgvb_v4_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v10_14fed0_t; /* rg:vu0bind vf10 */
#define v10_14fed0 RG_VU0_BIND_VF(10, rgvb_v10_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v11_14fed0_t; /* rg:vu0bind vf11 */
#define v11_14fed0 RG_VU0_BIND_VF(11, rgvb_v11_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v12_14fed0_t; /* rg:vu0bind vf12 */
#define v12_14fed0 RG_VU0_BIND_VF(12, rgvb_v12_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v20_14fed0_t; /* rg:vu0bind vf20 */
#define v20_14fed0 RG_VU0_BIND_VF(20, rgvb_v20_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v21_14fed0_t; /* rg:vu0bind vf21 */
#define v21_14fed0 RG_VU0_BIND_VF(21, rgvb_v21_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v22_14fed0_t; /* rg:vu0bind vf22 */
#define v22_14fed0 RG_VU0_BIND_VF(22, rgvb_v22_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_v25_14fed0_t; /* rg:vu0bind vf25 */
#define v25_14fed0 RG_VU0_BIND_VF(25, rgvb_v25_14fed0_t)

typedef u128_14fed0 __attribute__((aligned(4))) rgvb_acc_14fed0_t; /* rg:vu0bind ACC */
#define acc_14fed0 RG_VU0_BIND_ACC(rgvb_acc_14fed0_t)


void BoxTransformExtentsVu0Maybe_14fed0(u128_14fed0 *e, u128_14fed0 *d, u128_14fed0 *m)
{ RG_VU0_FRAME;
    v1_14fed0 = m[0];
    v2_14fed0 = m[1];
    v3_14fed0 = m[2];
    v4_14fed0 = m[3];
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf10);
    v20_14fed0 = _vmaddbc(v20_14fed0, 0xF, acc_14fed0, v3_14fed0, v10_14fed0, 2);
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf11);
    v21_14fed0 = _vmaddbc(v21_14fed0, 0xF, acc_14fed0, v3_14fed0, v11_14fed0, 2);
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf12);
    v22_14fed0 = _vmaddbc(v22_14fed0, 0xF, acc_14fed0, v3_14fed0, v12_14fed0, 2);
    v20_14fed0 = _vabs(v20_14fed0, 0xF, v20_14fed0);
    v21_14fed0 = _vabs(v21_14fed0, 0xF, v21_14fed0);
    v22_14fed0 = _vabs(v22_14fed0, 0xF, v22_14fed0);
    Vu0AddAcc(vf20, vf21);
    v25_14fed0 = _vmaddbc(v25_14fed0, 0xF, acc_14fed0, v22_14fed0, vz_14fed0, 1);
    Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf7);
    Vu0StoreAccW26(d);
    *e = v25_14fed0;
}
