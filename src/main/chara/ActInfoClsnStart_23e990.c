#include "types.h"

extern void *ScriptArgGetStr_23fba0(void *);
extern s32 StrDupArena_23fc40(void *);
extern s32 ParseFlagNames_1ca700(void *, void *, s32);
extern void ActInfoClsnInit_230bf0(void *, s32, s32, s32, s32, s32, s32);
extern u8 D_0044C7B0[];
extern s32 D_00481E90;
extern s32 D_00481E94;
extern s32 D_00481E98;
extern s32 D_00481E9C;
extern s32 D_004BCE58[4];
extern s16 D_004BCE88[8];
#define D58 D_004BCE58[0]
#define D88 D_004BCE88[0]

s32 ActInfoClsnStart_23e990(u8 *arg0, s32 arg1)
{
    s32 v;
    u8 *p;


    if (arg1 <= 0) {
        return 0;
    }
    if (D58 == 0) {
        return 1;
    }
    if (D88 >= 0x40) {
        return 1;
    }
    p = (u8 *)D58 + D88 * 0x14;
    v = 0;
    if (arg1 > 1) {
        v = ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C7B0, 0);
    }
    ActInfoClsnInit_230bf0(p, StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)), v, D_00481E90 + D_00481E94 * 0x10, 0, D_00481E98 + D_00481E9C * 0x18, 0);
    return 1;
}
