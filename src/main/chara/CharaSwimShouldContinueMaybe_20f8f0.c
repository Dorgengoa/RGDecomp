#include "types.h"

extern s32 CharaIsHeadUnderwaterMaybe_238250(void *arg0);
extern s32 CharaIsCurMotion_238540(void *arg0, void *arg1);
extern u8 D_0045C8C8[];
extern u8 D_0045C8D8[];

s32 CharaSwimShouldContinueMaybe_20f8f0(void *arg0)
{
    s16 sel;
    s32 flags;

    if (*(f32 *) ((u8 *) arg0 + 0xACC) < 15.0f) {
        return 1;
    }
    sel = *(s16 *) ((u8 *) arg0 + 0xA34);
    switch (sel) {
    case 0:
        if (CharaIsCurMotion_238540(arg0, D_0045C8C8) == 0) {
            return 1;
        }
        goto block_14;
    case 1:
        if (CharaIsCurMotion_238540(arg0, D_0045C8D8) == 0) {
            return 1;
        }
        goto block_14;
    default:
        return 0;
    }
block_14:
    if (CharaIsHeadUnderwaterMaybe_238250(arg0) != 0) {
        return 1;
    }
    flags = *(s32 *) ((u8 *) arg0 + 0x3D8);
    if ((flags & 0x10) == 0) {
        return 0;
    }
    return ((flags & 1) != 0) ^ 1;
}
