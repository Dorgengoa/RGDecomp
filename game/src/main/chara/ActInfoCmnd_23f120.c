/* rgp:protos */
#define RGP_SELF_ActInfoCmnd_23f120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044BB40[0x400];
extern u8 D_0044BDA0[0x400];
extern u8 D_004BCE20[0x400];
extern s32 D_004BCE4C[4];
extern s16 D_004BCE82[8];
#define D4C D_004BCE4C[0]
#define D82 D_004BCE82[0]

s32 ActInfoCmnd_23f120(u8 *arg0, s32 arg1)
{
    u8 *p;
    s32 c;
    u64 h;

    if (arg1 != 2) {
        return 0;
    }
    if (D4C == 0) {
        return 1;
    }
    if (D82 >= 0x40) {
        return 1;
    }
    p = (u8 *)D4C + D82 * 0xC;
    c = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
    h = (u64)(u32)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BB40, 0)) << 32;
    ActInfoCmndInit_2312b0(p, c, h | (u32)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BDA0, 0)));
    if (ActInfoCmndGetMask_2311f0(p) == 0) {
        return 1;
    }
    ActCfgTableSetCmndCount_223c70(D_004BCE20, D82 + 1);
    return 1;
}
