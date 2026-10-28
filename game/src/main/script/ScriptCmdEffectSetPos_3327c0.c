/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetPos_3327c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_004826E0;

s32 ScriptCmdEffectSetPos_3327c0(s32 arg0, s32 arg1) {
    u8 sp20[0x10] __attribute__((aligned(16)));
    s32 var_16;

    if (arg1 != 4 && arg1 != 3) {
        return 0;
    }
    var_16 = 0;
    switch (arg1) {
    case 3:
    case 4:
        var_16 = D_004826E0;
        break;
    }
    if (var_16 == 0) {
        return 0;
    }
    ScriptSlotsToVec4_334810(sp20, arg0);
    EffectInstanceSetPos_2dd570(var_16, sp20);
    return 1;
}
