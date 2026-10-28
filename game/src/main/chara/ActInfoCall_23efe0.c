/* rgp:protos */
#define RGP_SELF_ActInfoCall_23efe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044BB40[0x400];
extern u8 D_0044BDA0[0x400];
extern u8 D_0044C8A0[0x400];
extern u8 D_004BCE20[0x30];
extern u8 *D_004BCE50[4];
extern s16 D_004BCE84[0x20];

s32 ActInfoCall_23efe0(s32 arg0, s32 arg1)
{
    u8 *p;
    s32 a;
    s32 b;
    u64 hi;

    if (arg1 != 3) {
        return 0;
    }
    if (D_004BCE50[0] == 0) {
        return 1;
    }
    if (D_004BCE84[0] >= 0x40) {
        return 1;
    }

    p = D_004BCE50[0] + D_004BCE84[0] * 0x10;
    a = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
    b = ParseFlagNames_1ca940(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C8A0, 0);
    hi = (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x10), D_0044BB40, 0)) << 32;
    ActInfoCallInit_231170(p, a, b, hi | ((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x10), D_0044BDA0, 0)));
    if (ActInfoCallGetMask_2310a0(p) == 0) {
        return 1;
    }
    ActCfgTableSetCallCount_223c60(D_004BCE20, D_004BCE84[0] + 1);
    return 1;
}
