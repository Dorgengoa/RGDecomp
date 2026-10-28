/* rgp:protos */
#define RGP_SELF_CameraBaseSetRotation_15fc20 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"

/* s88m de-asm: d[1..3].xyz = s[0..2].xyz (w of d kept), via vaddx.xyz with vf0.
 * Volatile loads keep retail's d-then-s lqc2 order in the third group. */
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz15fc20_t; /* rg:vu0bind vf0 */
#define vz15fc20 RG_VU0_BIND_VF(0, rgvb_vz15fc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_va15fc20_t; /* rg:vu0bind vf1 */
#define va15fc20 RG_VU0_BIND_VF(1, rgvb_va15fc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb15fc20_t; /* rg:vu0bind vf2 */
#define vb15fc20 RG_VU0_BIND_VF(2, rgvb_vb15fc20_t)


void CameraBaseSetRotation_15fc20(u128 *d, u128 *s)
{ RG_VU0_FRAME;
    va15fc20 = *(volatile u128 *)&d[1];
    vb15fc20 = *(volatile u128 *)&s[0];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[1] = va15fc20;
    va15fc20 = *(volatile u128 *)&d[2];
    vb15fc20 = *(volatile u128 *)&s[1];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[2] = va15fc20;
    va15fc20 = *(volatile u128 *)&d[3];
    vb15fc20 = *(volatile u128 *)&s[2];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[3] = va15fc20;
}
