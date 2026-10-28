/* rgp:protos */
#define RGP_SELF_ActTimeAccl_23ba60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

/*rgp*/
/*rgp*/

extern s32 D_00481EB8;
extern s32 D_00481EBC;

s32 ActTimeAccl_23ba60(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    s32 temp_17;

    if (arg1 != 4) {
        return 0;
    }
    if ((D_00481EB8 == 0) || (D_00481EBC >= 0x40)) return 1;
    temp_17 = D_00481EB8 + (D_00481EBC * 0x10);
    temp_f22 = ScriptArgGetFloat_23fbc0(arg0);
    temp_f21 = ScriptArgGetFloat_23fbc0(arg0 + 8);
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
    ActTimeAcclInit_227aa0(temp_17, temp_f22, temp_f21, temp_f20, ScriptArgGetFloat_23fbc0(arg0 + 0x18));
    D_00481EBC += 1;
    return 1;
    return 1;
}
