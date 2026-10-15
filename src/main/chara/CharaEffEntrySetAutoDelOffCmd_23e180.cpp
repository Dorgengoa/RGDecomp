#include "types.h"
extern "C" {
extern void CharaEffEntrySetAutoDelOff_230200(s32, bool);
extern s32 ScriptArgGetInt_23fc00(s32, s32);
extern s32 D_004BCE60[0x10];
extern s16 D_004BCE8C[0x10];

s32 CharaEffEntrySetAutoDelOffCmd_23e180(s32 arg0, s32 arg1)
{
    s32 base;
    s32 p;
    bool flag;

    if (arg1 != 0 && arg1 != 1) {
        return 0;
    }
    base = D_004BCE60[0];
    if (base == 0 || D_004BCE8C[0] >= 0x80) {
        return 1;
    }
    p = base + D_004BCE8C[0] * 0x7C;
    flag = 1;
    if (arg1 > 0) {
        flag = ScriptArgGetInt_23fc00(arg0, arg1) != 0;
    }
    CharaEffEntrySetAutoDelOff_230200(p, flag);
    return 1;
}
}
