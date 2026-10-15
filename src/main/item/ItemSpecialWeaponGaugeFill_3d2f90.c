#include "types.h"


typedef struct Src {
    u8 pad[0x2C];
    s8 unk2C;
} Src;

typedef struct Obj {
    u8 pad[0x10];
    s32 unk10;
    u8 pad14[0xC];
    f32 unk20;
    s16 unk24;
    s16 unk26;
} Obj;

extern Src *ItemDefGetSpecialWeaponData_40e0e0(s32);

s32 ItemSpecialWeaponGaugeFill_3d2f90(Obj *arg0, s32 arg1) {
    Src *o;

    o = ItemDefGetSpecialWeaponData_40e0e0(arg0->unk10);
    if (o == NULL) {
        return 0;
    }
    if (arg1 == 0) {
        return 1;
    }
    {
    f32 mx;
    arg0->unk20 = (f32)o->unk2C;
    arg0->unk26 = 0;
    mx = (f32)o->unk2C;
    if (arg0->unk20 <= 0.0f) {
        arg0->unk20 = 0.0f;
        arg0->unk24 = 0x14;
    } else if (arg0->unk20 >= mx) {
        arg0->unk20 = mx;
        arg0->unk24 = 0x21;
    } else {
        arg0->unk24 = 1;
    }
    }
    return 1;
}
