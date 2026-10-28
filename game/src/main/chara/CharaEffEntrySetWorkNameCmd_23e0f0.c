/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetWorkNameCmd_23e0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
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
    CharaEffEntrySetWorkName_2301e0(e, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(pd0))));
    return 1;
}
