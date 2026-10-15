#include "types.h"
#pragma vu0_mmi_reg_binding on
extern __int128 vz19a240 asm("vf0");

typedef struct Obj19a240 {
    s32 x0;
    u8 pad4[0xC];
    __int128 v10;
    __int128 v20;
    u8 m30[0x10];
    u8 m40[0x10];
    __int128 v50;
    __int128 v60;
    __int128 v70;
    u8 m80[0x10];
    u8 m90[0x10];
    __int128 vA0;
} Obj19a240;

extern void VecSetOnes_13e180(void *p);
extern void VecSetOnes4_13e170(void *p);

void XformPairInit_19a240(Obj19a240 *p)
{
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
