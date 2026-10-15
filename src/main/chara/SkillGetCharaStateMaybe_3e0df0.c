#include "types.h"

extern f32 D_00465D38[4];
extern u8 D_004E9770[0x400];
extern u8 D_004E9800[0x400];

s32 SkillGetCharaStateMaybe_3e0df0(s32 arg0)
{
    u8 *p;
    s32 i;

    if (arg0 < 0) {
        return 0;
    }
    p = D_004E9770;
    for (i = 0; i < 2; p += 0x48) {
        if (*(s16 *)(p + 0x3C) == arg0) {
            return 1;
        }
        i++;
    }
    p = D_004E9800;
    for (i = 0; i < 0x40; p += 0x18) {
        if (*(s16 *)(p + 2) == arg0) {
            if (*(f32 *)(p + 8) < D_00465D38[0]) {
                return 3;
            }
            return 2;
        }
        i++;
    }
    return 0;
}
