/* rgp:protos */
#define RGP_SELF_CharaCmdFlameThrower_228ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdFlameThrower_228ea0(s32 *arg0, s32 arg1, s32 arg2) {
    u8 sp50[0x20] __attribute__((aligned(16)));
    s32 temp_2;
    s32 a;
    s32 id;

    if (arg2 != 3) {
        return 0;
    }
    a = ScriptArgGetInt_302d70(arg1);
    temp_2 = GetObjNodeByName_1ce3a0(*arg0, a, ScriptArgGetStr_302cb0(arg1 + 5));
    if (temp_2 == 0) {
        return 1;
    }
    id = ((s32)GetEffectMgr_2d9040());
    EffectCreateByName_2e1020(sp50, id, ScriptArgGetStr_302cb0(arg1 + 0xA), -1);
    EffectSetAutoRelease_2e1170(id, sp50, 1);
    EffectSetId_2e0100(id, sp50, *arg0);
    EffectAttachToNode_2e0790(id, sp50, temp_2);
    return 1;
}
