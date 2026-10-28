/* rgp:protos */
#define RGP_SELF_CameraBaseGetMatrix_15fc60 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"

/* s88m de-asm: d[0..2] = s[1..3]; d[3] = vf0 (0,0,0,1). */
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz15fc60_t; /* rg:vu0bind vf0 */
#define vz15fc60 RG_VU0_BIND_VF(0, rgvb_vz15fc60_t)


void CameraBaseGetMatrix_15fc60(u128 *s, u128 *d)
{ RG_VU0_FRAME;
    d[0] = s[1];
    d[1] = s[2];
    d[2] = s[3];
    d[3] = vz15fc60;
}
