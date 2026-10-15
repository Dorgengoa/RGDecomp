#include "types.h"


typedef struct Obj1ce800 {
    u8 pad0[0x2C];
    f32 unk2C;
} Obj1ce800;

typedef struct Ent1ce800 {
    u8 pad0[0x32];
    s16 unk32;
    u8 pad34[0x30];
    f32 unk64;
} Ent1ce800;

extern s32 MapPartsGroupGetParts_188dc0(s32, void *, void *, s32);

void DoorGlareParamsApply_1ce800(Obj1ce800 *arg0, s32 arg1) {
    Ent1ce800 *arr[2];
    s32 flag;
    s32 t;
    s32 count;
    s32 i;
    Ent1ce800 *p;

    if (arg1 == 0) {
        return;
    }
    flag = (u8)((arg0->unk2C > 0.0f) ? 1 : 0);
    count = MapPartsGroupGetParts_188dc0(arg1, arg0, arr, 2);
    for (i = 0; i < count; i++) {
        p = arr[i];
        if (p != 0) {
            p->unk32 = (flag != 0);
            p->unk64 = arg0->unk2C;
        }
    }
}
