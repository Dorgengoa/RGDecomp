/* rgp:protos */
#define RGP_SELF_ActInfoWepActStart_23d4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044C850[0x10];
extern s32 D_00481E80;
extern s32 D_00481E84;
extern s32 D_004BCE68[4];
extern s16 D_004BCE90[8];

s32 ActInfoWepActStart_23d4a0(s32 arg0, s32 arg1)
{
    s32 temp_17;
    s32 temp_16;

    if (arg1 != 2) {
        return 0;
    }
    if (D_004BCE68[0] == 0 || D_004BCE90[0] >= 0x20) {
        return 1;
    }
    temp_17 = D_004BCE68[0] + (D_004BCE90[0] * 0xC);
    temp_16 = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0), D_0044C850, 0);
    ActInfoWepActInit_22f0b0(temp_17, temp_16, ScriptArgGetInt_23fc00(arg0 + 8), D_00481E80 + (D_00481E84 * 8), 0);
    return 1;
}
