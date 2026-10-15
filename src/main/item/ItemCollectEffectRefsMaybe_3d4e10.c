#include "types.h"

typedef struct Obj4e10 {
    u8 pad0[0x40];
    s32 unk40;
} Obj4e10;

typedef struct Arg4e10 {
    u8 pad0[0x10];
    s32 unk10;
} Arg4e10;

extern Obj4e10 *D_004838EC;
extern s32 ItemDefCollectEffectRefsMaybe_40c460(s32, s32, s32, s32, s32);

s32 ItemCollectEffectRefsMaybe_3d4e10(Arg4e10 *a0, s32 a1, s32 a2, s32 a3)
{
    s32 result;
    s32 t3;
    s32 t5;

    result = a3;
    if (D_004838EC == 0) {
        return result;
    }
    t3 = D_004838EC->unk40;
    if (t3 == 0) {
        return result;
    }
    t5 = a0->unk10;
    if (t5 == 0) {
        return result;
    }
    result = ItemDefCollectEffectRefsMaybe_40c460(t3, t5, a1, a2, a3);
    return result;
}
