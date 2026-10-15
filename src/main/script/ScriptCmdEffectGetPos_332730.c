#include "types.h"

extern void EffectInstanceGetPos_2dd540(s32 arg0, void *arg1);
extern void ScriptSlotStoreVec3_334790(s32 arg0, void *arg1);
extern s32 D_004826E0;

s32 ScriptCmdEffectGetPos_332730(s32 arg0, s32 arg1) {
    u8 sp20[16];
    s32 flag;

    if (arg1 != 4 && arg1 != 3) {
        return 0;
    }
    flag = 0;
    switch (arg1) {
    case 3:
    case 4:
        flag = D_004826E0;
    }
    if (flag == 0) {
        return 0;
    }
    EffectInstanceGetPos_2dd540(flag, sp20);
    ScriptSlotStoreVec3_334790(arg0, sp20);
    return 1;
    return 0;
}
