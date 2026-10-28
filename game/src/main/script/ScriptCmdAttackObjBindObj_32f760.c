/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjBindObj_32f760 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
typedef struct Item0032f760 {
    u8 pad0[0x86];
    s16 unk86;
    u8 pad88[2];
    s16 unk8A;
} Item0032f760;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAttackObjBindObj_32f760(s64 *arg0, s32 arg1) {
    Item0032f760 *temp_2;
    u8 *p;
    s16 temp_16_2;

    if (arg1 != 2) {
        return 0;
    }
    if (((unsigned char)IsInBattle_288420()) == 0) {
        return 1;
    }
    temp_2 = ((Item0032f760 *)HandleRegistryLookup_314aa0(((s32)GetObjRefTable_313de0()), ScriptSlotGetInt_3348b0((s32)arg0)));
    if (temp_2 == NULL) {
        return 1;
    }
    switch (temp_2->unk8A) {
    default:
        return 1;
    case 1:
        temp_16_2 = temp_2->unk86;
        p = (u8 *)temp_2 + 0x10;
        ExecInfoInitFromObj_3a7790(p, temp_16_2, ScriptSlotGetCodeAddr_334870((s32)(arg0 + 1)));
        JudgeObjectSyncOwner_314440(temp_2);
        break;
    }
    return 1;
}
