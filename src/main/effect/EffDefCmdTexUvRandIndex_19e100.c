#include "types.h"

typedef struct Obj0019e100 {
    void *unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} Obj0019e100;

typedef struct Own0019e100 {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x50 - 0x24];
    Obj0019e100 *unk50;
} Own0019e100;

extern Obj0019e100 *MemStackNew_14e230(s32, s32);
extern f32 VariantGetFloat_15f740(s32);
extern s32 VariantGetInt_15f780(s32);
extern void EffTexUvParamSetCellSize_198a50(Obj0019e100 *, f32, f32);
extern u8 D_00470820[];
extern u8 D_004709E0[];
extern u8 D_00470E30[];

s32 EffDefCmdTexUvRandIndex_19e100(s32 arg0, s32 arg1, Own0019e100 **arg2)
{
    Own0019e100 *own;
    Obj0019e100 *o;
    f32 f;

    own = *arg2;
    o = own->unk50;
    switch ((s32)o) {
    case 0:
    {
        Obj0019e100 *t = MemStackNew_14e230(0x20, own->unk20);
        if (t) {
            t->unk0 = D_00470E30;
            t->unk4 = -1;
            t->unk0 = D_004709E0;
            t->unk8 = 1.0f;
            t->unkC = 1.0f;
            t->unk10 = 1;
            t->unk14 = 1;
            t->unk0 = D_00470820;
            t->unk18 = 0;
            t->unk1C = 0;
        }
        own->unk50 = t;
        o = t;
    }
    }
    if (!o) {
        return 0;
    }

    f = VariantGetFloat_15f740(arg0);
    EffTexUvParamSetCellSize_198a50(o, f, VariantGetFloat_15f740(arg0 + 8));
    o->unk18 = VariantGetInt_15f780(arg0 + 0x10);
    o->unk1C = VariantGetInt_15f780(arg0 + 0x18);
    return 1;
}
