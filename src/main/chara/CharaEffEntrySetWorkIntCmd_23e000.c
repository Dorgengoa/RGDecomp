#include "types.h"

extern s32 ParseFlagNames_1ca940(s32, void *, s32);
extern void CharaEffEntrySetWorkInt_2301a0(s32, s32, s32);
extern s32 ScriptArgGetStr_23fba0(void *);
extern s32 ScriptArgGetInt_23fc00(u8 *);
extern u8 D_0044C8A0[];
extern u8 D_004BCE60[0x400];
extern u8 D_004BCE8C[0x400];

s32 CharaEffEntrySetWorkIntCmd_23e000(u8 *arg0, s32 arg1) {
    s32 base;
    s32 t;
    if (arg1 != 2) {
        return 0;
    }
    if (*(s32 *)D_004BCE60 == 0 || *(s16 *)D_004BCE8C >= 0x80) return 1;
    base = *(s32 *)D_004BCE60 + *(s16 *)D_004BCE8C * 0x7C;
    if (*(s32 *)(arg0 + 8) == 0) {
        t = ScriptArgGetInt_23fc00(arg0);
        CharaEffEntrySetWorkInt_2301a0(base, t, ParseFlagNames_1ca940(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C8A0, 0));
    } else {
        t = ScriptArgGetInt_23fc00(arg0);
        CharaEffEntrySetWorkInt_2301a0(base, t, ScriptArgGetInt_23fc00(arg0 + 8));
    }
    return 1;
}
