/* rgp:protos */
#define RGP_SELF_ClsnInfoChain_23bba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
/*rgp*/
/*rgp*/
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ClsnInfoChain_23bba0(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if ((D_00481EB0 == 0) || (D_00481EB4 <= 0)) {
        return 1;
    }
    temp_17 = (D_00481EB0 + (D_00481EB4 << 5)) - 0x20;
    temp_16 = ScriptArgGetInt_23fc00(arg0);
    ((void)(ScriptArgGetInt_23fc00(arg0 + 8)), ClsnInfoSetChain_228170());
    return 1;
}
