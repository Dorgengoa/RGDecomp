/* rgp:protos */
#define RGP_SELF_ActInfoEfctStart_23e340 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct { s32 p; u8 pad[0x28]; s16 idx; } S4BCE60;
extern S4BCE60 D_004BCE60;

s32 ActInfoEfctStart_23e340(s32 arg0, s32 arg1) {
    s32 t;

    if (arg1 != 2) {
        return 0;
    }
    if (D_004BCE60.p == 0) {
        return 1;
    }
    if (D_004BCE60.idx >= 0x80) {
        return 1;
    }
    t = D_004BCE60.p + D_004BCE60.idx * 0x7C;
    CharaEffEntryInitNamed_230710(t, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0))), ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 8))));
    return 1;
}
