/* rgp:protos */
#define RGP_SELF_XformPairInit_19a240 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz19a240_t; /* rg:vu0bind vf0 */
#define vz19a240 RG_VU0_BIND_VF(0, rgvb_vz19a240_t)


typedef struct Obj19a240 {
    s32 x0;
    u8 pad4[0xC];
    rg_s128 v10;
    rg_s128 v20;
    u8 m30[0x10];
    u8 m40[0x10];
    rg_s128 v50;
    rg_s128 v60;
    rg_s128 v70;
    u8 m80[0x10];
    u8 m90[0x10];
    rg_s128 vA0;
} Obj19a240;

/*rgp*/
/*rgp*/

void XformPairInit_19a240(Obj19a240 *p)
{ RG_VU0_FRAME;
    p->x0 = 0;
    p->v10 = vz19a240;
    p->v20 = 0;
    VecSetOnes_13e180(p->m30);
    VecSetOnes4_13e170(p->m40);
    p->v50 = 0;
    p->v60 = 0;
    p->v70 = 0;
    VecSetOnes_13e180(p->m80);
    VecSetOnes4_13e170(p->m90);
    p->vA0 = 0;
}
