/* rgp:protos */
#define RGP_SELF_ActInfoAtkPrm_23d090 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044C850[0x400];
extern u8 D_004BCE20[0x400];
extern u8 *D_004BCE70[4];
extern s16 D_004BCE94[8];

s32 ActInfoAtkPrm_23d090(s32 arg0, s32 arg1) {
    u8 *p;
    s32 i;
    u8 *e;
    s32 temp_16;
    s32 temp_17;

    if (arg1 != 3) {
        return 0;
    }
    p = D_004BCE70[0];
    if (p == NULL || (i = D_004BCE94[0]) >= 0x20) {
        return 1;
    }
    e = p + i * 8;
    temp_17 = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0), D_0044C850, 0);
    temp_16 = ScriptArgGetInt_23fc00(arg0 + 8);
    ActInfoAtkPrmInit_22eb50(e, temp_17, temp_16, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x10))));
    ActCfgTableSetAtkPrmCount_223be0(D_004BCE20, D_004BCE94[0] + 1);
    return 1;
}
