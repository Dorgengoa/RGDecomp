/* rgp:protos */
#define RGP_SELF_EvCmdVecLength_25db40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVecLength_25db40(u8 *arg0, s32 arg1)
{
    u8 sp30[0x10] __attribute__((aligned(16)));
    u8 sp20[0x10] __attribute__((aligned(16)));
    f32 var_f0;

    switch (arg1) {
    case 4:
        ScriptArgsToVec4_26a220(sp30, arg0);
        arg0 += 0x18;
        var_f0 = VecLength_13d4a0(sp30);
        break;
    case 7:
        ScriptArgsToVec4_26a220(sp30, arg0);
        ScriptArgsToVec4_26a220(sp20, arg0 + 0x18);
        arg0 += 0x30;
        var_f0 = VecDistance_13d3d0(sp30, sp20);
        break;
    default:
        return 0;
    }
    ScriptSetRefFloat_26a1c0(arg0, var_f0);
    return 1;
}
