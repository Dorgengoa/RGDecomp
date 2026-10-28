/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetWorkFltCmd_23df60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004BCE60[];
extern s16 D_004BCE8C[];

s32 CharaEffEntrySetWorkFltCmd_23df60(s32 arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if (D_004BCE60[0] == 0 || D_004BCE8C[0] >= 0x80) {
        return 1;
    }
    temp_18 = D_004BCE60[0] + (D_004BCE8C[0] * 0x7C);
    temp_17 = ScriptArgGetInt_23fc00(arg0);
    CharaEffEntrySetWorkFlt_230160(temp_18, temp_17, ScriptArgGetFloat_23fbc0(arg0 + 8));
    return 1;
}
