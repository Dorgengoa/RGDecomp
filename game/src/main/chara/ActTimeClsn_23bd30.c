/* rgp:protos */
#define RGP_SELF_ActTimeClsn_23bd30 1
#include "port/game_protos.h"
#line 1
/* PARK (round 1): length 0x104 vs retail 0x108 (4 short), close. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ActTimeClsn_23bd30(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_19;
    s32 temp_18;

    if (arg1 < 4) {
        return 0;
    }
    if ((D_00481EB0 == 0) || (D_00481EB4 >= 0x40)) return 1;
    temp_19 = D_00481EB0 + (D_00481EB4 << 5);
    temp_f21 = ScriptArgGetFloat_23fbc0(arg0);
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0 + 8);
    temp_18 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x10)));
    ActTimeClsnInit_227c30(temp_19, temp_18, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x18))), temp_f21, temp_f20);
    if (arg1 > 4) {
        ClsnInfoSetForce_228190(temp_19 + 4, ScriptArgGetFloat_23fbc0(arg0 + 0x20));
    }
    D_00481EB4 += 1;
    return 1;
    return 1;
}
