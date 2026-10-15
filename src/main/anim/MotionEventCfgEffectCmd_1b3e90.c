#include "types.h"

typedef struct Sub {
    u8 pad0[0x28];
    s32 x28;
    s32 x2C;
    u8 pad30[4];
    u8 x34;
    u8 x35;
} Sub;

typedef struct Obj {
    u8 pad0[0x30];
    s32 x30;
    u8 pad34[0x1C];
    Sub *x50;
} Obj;

extern s32 SlotGetInt_15f720(void *);
extern s32 VariantGetInt_15f780(void *);
extern s32 MemStackStrDup_14cf10(s32, s32);

s32 MotionEventCfgEffectCmd_1b3e90(u8 *arg0, s32 arg1, Obj **arg2)
{
    Obj *o;
    s32 t;
    s32 a;
    s32 c;

    o = *arg2;
    if (o->x50 == NULL) {
        return 0;
    }
    t = o->x30;
    a = SlotGetInt_15f720(arg0);
    c = 0;
    if (arg1 >= 2) {
        c = SlotGetInt_15f720(arg0 + 8);
    }
    o->x50->x28 = MemStackStrDup_14cf10(a, t);
    o->x50->x2C = MemStackStrDup_14cf10(c, t);
    if (arg1 >= 3) {
        o->x50->x34 = VariantGetInt_15f780(arg0 + 0x10) != 0;
    }
    if (arg1 >= 4) {
        o->x50->x35 = VariantGetInt_15f780(arg0 + 0x18) != 0;
    }
    return 1;
}
