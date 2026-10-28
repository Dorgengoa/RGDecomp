/* rgp:protos */
#define RGP_SELF_CharaCmdLocus_22bfc0 1
#include "port/game_protos.h"
#line 1
/* PARKED: 1 round trip: mechanical conversion; length 0x14C vs retail 0x15C. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdLocus_22bfc0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_17;
    f32 var_f20;
    f32 temp_f23;
    f32 var_f0;
    f32 var_f0_2;

    if (arg2 <= 2) {
        return 0;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = CharaGetActionTable_214cd0(temp_2);
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_f23 = ScriptArgGetFloat_302cf0(arg1 + 0xA);
    if (arg2 > 3) {
        var_f0 = ScriptArgGetFloat_302cf0(arg1 + 0xF);
    } else {
        var_f0 = 1.0f;
    }
    if (arg2 > 4) {
        var_f0_2 = ScriptArgGetFloat_302cf0(arg1 + 0x14);
    } else {
        var_f0_2 = temp_f23;
    }
    if (arg2 > 5) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 0x19);
    } else {
        var_f20 = 5.0f;
    }
    temp_17 = ScriptArgGetStr_302cb0(arg1 + 5);
    CharaWeaponTrailSetupByName_21f770(temp_2_2, *arg0, temp_17, ScriptArgGetInt_302d70(arg1), var_f0, temp_f23, var_f0_2, var_f20);
    return 1;
}
