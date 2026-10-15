#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x2C];
    f32 a[3];
    f32 b[3];
    f32 r;
} Tgt;

extern f32 VariantGetFloat_15f740(s32);
extern void VariantReadVec3_2fd830(void *, s32);
extern f32 NpcCfgLocalToWorldYaw_2fd890(void *, Tgt *, Tgt *, Tgt *, Tgt *, f32);
extern void NpcCfgLocalToWorldPos_2fd8d0(void *, void *, void *);
extern f32 D_0047F090;
extern f32 D_0047F094;
extern f32 D_0047F098;
extern f32 D_0047F09C;
extern u8 D_004E6620[];
extern u8 D_004E6628[0x400];
#define PT (*(Tgt **)D_004E6628)
s32 NpcCfgCmdSetPosYaw_2fd5c0(s32 arg0, s32 arg1)
{
    f32 sp40[4];
    f32 v[4];
    f32 f20;
    f32 *pv;
    Tgt *p1;
    Tgt *p2;
    Tgt *p3;
    Tgt *p4;

    if (arg1 != 4) {
        return 0;
    }
    if (PT == NULL) {
        return 0;
    }
    VariantReadVec3_2fd830(sp40, arg0);
    f20 = VariantGetFloat_15f740(arg0 + 0x18);
    sp40[3] = 1.0f;
    v[0] = D_0047F090;
    v[1] = D_0047F094;
    v[2] = D_0047F098;
    v[3] = D_0047F09C;
    pv = v;
    NpcCfgLocalToWorldPos_2fd8d0(D_004E6620, pv, sp40);
    p1 = PT;
    p1->a[0] = v[0];
    p2 = PT;
    p2->a[1] = v[1];
    p3 = PT;
    p3->a[2] = v[2];
    p4 = PT;
    p4->b[0] = v[0];
    PT->b[1] = v[1];
    PT->b[2] = v[2];
    PT->r = NpcCfgLocalToWorldYaw_2fd890(D_004E6620, p4, p3, p2, p1, f20);
    return 1;
}
