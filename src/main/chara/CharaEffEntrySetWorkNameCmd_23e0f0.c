#include "types.h"
#pragma opt_propagation off

s32 CharaEffEntrySetWorkName_2301e0(u8 *, s32);
s32 ScriptArgGetStr_23fba0(s32);
s32 StrDupArena_23fc40(s32);
extern u8 *D_004BCE60[4];
extern s16 D_004BCE8C[8];

s32 CharaEffEntrySetWorkNameCmd_23e0f0(s32 pd0, s32 arg1) {
    u8 *p;
    s32 i;
    u8 *e;

    if (arg1 != 1) {
        return 0;
    }
    p = D_004BCE60[0];
    if (p == NULL || (i = D_004BCE8C[0]) >= 0x80) {
        return 1;
    }
    e = p + i * 0x7C;
    CharaEffEntrySetWorkName_2301e0(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(pd0)));
    return 1;
}
