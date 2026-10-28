/* rgp:protos */
#define RGP_SELF_ClsnInfoPstr_23bc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ClsnInfoPstr_23bc30(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    s32 temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if (D_00481EB0 == 0 || D_00481EB4 <= 0) {
        return 1;
    }
    temp_17 = (D_00481EB0 + (D_00481EB4 << 5)) - 0x20;
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0);
    ClsnInfoSetPstr_228180(temp_17 + 4, temp_f20, ScriptArgGetFloat_23fbc0(arg0 + 8));
    return 1;
}
