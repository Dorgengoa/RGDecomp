#include "types.h"
extern s32 ParseFlagNames_1ca940(s32, void *, s32);
extern void CharaEffEntrySetStyle_230230(s32, s32);
extern s32 ScriptArgGetStr_23fba0();
extern s32 ScriptArgGetInt_23fc00();
extern u8 D_0044C8A0[0x400];
extern s32 D_004BCE60[4];
extern s16 D_004BCE8C[8];

s32 CharaEffEntrySetStyleCmd_23e220(void *arg0, s32 arg1)
{
    s32 base;
    s16 idx;
    s32 p;

    if (arg1 != 1) return 0;
    base = D_004BCE60[0];
    if (base != 0) {
    idx = D_004BCE8C[0];
    if (idx < 0x80) goto body;
    }
    return 1;
body:
    p = base + idx * 0x7C;
    if (*(s32 *)((u8 *)arg0 + 8) == 0) {
        CharaEffEntrySetStyle_230230(p, ParseFlagNames_1ca940(ScriptArgGetStr_23fba0(), D_0044C8A0, 0));
    } else {
        CharaEffEntrySetStyle_230230(p, ScriptArgGetInt_23fc00());
    }
    return 1;
}
