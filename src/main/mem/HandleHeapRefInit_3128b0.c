#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    s32 unk0;
    s32 unk4;
    u32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} S003128b0;

void HandleHeapRefInit_3128b0(S003128b0 **arg0, s32 arg1, u32 arg2, u32 arg3) {
    S003128b0 *obj;
    u32 t;

    obj = *arg0;
    if (obj->unk0 != 0) {
        obj->unk0 = 0;
    }
    obj->unk0 = arg3 * ((arg1 + arg3 - 1) / arg3);
    obj->unk4 = arg3 * (arg2 / arg3);
    obj->unk8 = arg3;
    obj->unkC = obj->unk0;
    obj->unk10 = obj->unk0 + obj->unk4;
    obj->unk14 = 0;
    obj->unk18 = 0;
    obj->unk1C = 0;
    t = obj->unk8;
    obj->unk20 = t * ((t + 0xB) / t);
}
