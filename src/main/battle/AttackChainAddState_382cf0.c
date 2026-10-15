#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    s16 unk8;
    s16 unkA;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x224 - 0x18];
} Ent00382CF0;

typedef struct {
    Ent00382CF0 *unk0;
    s16 unk4;
    s16 unk6;
    u8 pad8[0x30 - 0x8];
    f32 unk30;
} Obj00382CF0;

extern f32 Atan2f_1291a8(f32, f32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(Ent00382CF0 *);

s32 AttackChainAddState_382cf0(Obj00382CF0 *arg0, s16 arg1, f32 x, f32 y, f32 a, f32 b)
{
    Ent00382CF0 *e;
    Ent00382CF0 *p;
    s32 h;
    f32 hw;
    f32 hh;

    p = arg0->unk0;
    if (p == NULL) {
        return -1;
    }
    if (arg0->unk4 >= arg0->unk6) {
        return -1;
    }
    e = &p[arg0->unk4];
    e->x = x;
    e->y = y;
    e->unkA = 0;
    e->unk8 = arg1;
    h = GetDrawCtx_15de80(p);
    hw = 0.5f * (f32)DrawEnvGetWidth_1451e0(h);
    hh = 0.5f * (f32)DrawEnvGetHeight_1451d0(h);
    if (a < 0.0f || b < 0.0f) {
        e->unkC = -1.0f;
        e->unk10 = -1.0f;
        e->unk14 = 0.0f;
    } else {
        e->unkC = a;
        a -= hw;
        e->unk10 = b;
        b -= hh;
        e->unk14 = (a == 0.0f && b == 0.0f) ? 0.0f : Atan2f_1291a8(b, a);
    }
    arg0->unk30 = x;
    return ++arg0->unk4 - 1;
}
