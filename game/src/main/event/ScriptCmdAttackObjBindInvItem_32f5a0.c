/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjBindInvItem_32f5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAttackObjBindInvItem_32f5a0(s32 arg0, s32 arg1) {
    u8 *temp_2;
    s32 temp_16;
    u8 *p;
    s32 temp_16_2;

    switch (arg1) {
    case 2:
        if (((unsigned char)IsInBattle_288420()) == 0) {
            return 1;
        }
        temp_16 = ((s32)GetObjRefTable_313de0());
        temp_2 = (u8 *)HandleRegistryLookup_314aa0(temp_16, ScriptSlotGetInt_3348b0(arg0));
        if (temp_2 == NULL) {
            return 1;
        }
        temp_16_2 = *(s16 *)(temp_2 + 0x86);
        p = temp_2 + 0x10;
        ExecInfoInitFromInvItem_3a7430(p, temp_16_2, ScriptSlotGetInt_3348b0(arg0 + 8), 0);
        JudgeObjectSyncOwner_314440(temp_2);
        return 1;
    }
    return 0;
}
