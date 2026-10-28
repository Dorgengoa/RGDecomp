/* rgp:protos */
#define RGP_SELF_ClsnInfoForce_23bcc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ClsnInfoForce_23bcc0(s32 pad0, s32 arg1)
{
    s32 temp_16;
    s32 t;
    s32 n;

    if (arg1 != 1) {
        return 0;
    }
    if (D_00481EB0 == 0 || D_00481EB4 <= 0) {
        return 1;
    }
    temp_16 = (D_00481EB0 + (D_00481EB4 << 5)) - 0x20;
    ClsnInfoSetForce_228190(temp_16 + 4, ScriptArgGetFloat_23fbc0((void *)pad0));
    return 1;
}
