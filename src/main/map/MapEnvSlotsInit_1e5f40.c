#include "types.h"

typedef struct Elem001e5f40 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    u8 padC[0x10 - 0xC];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    f32 unk1C;
} Elem001e5f40;

typedef struct Obj001e5f40 {
    Elem001e5f40 elems[3];
    f32 unk60;
} Obj001e5f40;

void MapEnvSlotsInit_1e5f40(Obj001e5f40 *arg0)
{
    s32 i;
    Elem001e5f40 *cur;
    f32 zero;

    i = 0;
    zero = 0.0f;
    do {
        cur = &arg0->elems[i];
        i += 1;
        cur->unk0 = -1;
        cur->unk4 = 0x3F800000;
        cur->unk8 = (f32) 0x2710;
        cur->unk10 = 0;
        cur->unk14 = 0;
        cur->unk18 = 0;
        cur->unk1C = 0.0f;
    } while (i < 3);
    arg0->unk60 = zero;
}
