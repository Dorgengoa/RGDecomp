/* MATCH: needed THREE things at once, per [[mwcc-daddiu-unsigned-narrow]]:
   var_19 as u16 (not s32/s64) for the `daddiu` opcode, its consumer spelled
   as a bare truth test (`if (var_19)`, not `!= 0`) to dodge the andi
   re-narrow, AND temp_20 declared TEXTUALLY BEFORE var_19 (both earlier
   orderings -- var_19 first, or the two separated by temp_2 -- left
   var_19/temp_20 coloured into the wrong of $19/$20, a pure register swap
   on top of an otherwise-correct opcode). Moving the var_19=0 STATEMENT
   earlier (as opposed to just the declaration) broke scheduling elsewhere
   and made it worse (10 bad) -- decl order and statement order are
   independent axes here. */
#include "types.h"

typedef struct Obj18 {
    u8 pad18[0x18];
    s32 unk18;
} Obj18;

typedef struct Obj2420 {
    u8 padC[0xC];
    s32 unkC;
} Obj2420;

s32 GetActionMgr_1fdb50(void);
Obj18 *GetGameData_1fede0(void);
s16 *FieldHudGetSuggestMemberPtr_203c60(void);
void FieldHudAllySuggestCancel_203c80(void);
s32 CharaGetAi_214a10(s32);
s32 ActionMgrFindById_233b50(s32, s32);
void AiAllySuggestClear_2bb9a0(s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Obj2420 *PartyGetMemberChara_3c2420(s32, s32);

s32 PartyAllySuggestCancel_2eea00(s32 arg0) {
    s32 temp_20;
    u16 var_19;
    s16 *temp_2;
    s32 temp_22;
    s32 temp_2_3;
    s32 temp_2_4;
    s32 temp_5;
    s32 var_18;
    Obj18 *temp_16;
    Obj2420 *temp_2_2;

    temp_2 = FieldHudGetSuggestMemberPtr_203c60();
    if (temp_2 == NULL) {
        return 0;
    }
    temp_16 = GetGameData_1fede0();
    temp_20 = GetActionMgr_1fdb50();
    var_19 = 0;
    temp_22 = PartyCountMembers_3c2010(temp_16->unk18, 1, 1);
    var_18 = 0;
    while (var_18 < temp_22) {
        temp_2_2 = PartyGetMemberChara_3c2420(temp_16->unk18, var_18);
        if ((temp_2_2 != NULL) && ((temp_5 = temp_2_2->unkC, (arg0 < 0)) || (arg0 == temp_5)) && (*temp_2 == temp_5)) {
            temp_2_3 = ActionMgrFindById_233b50(temp_20, temp_5);
            if (temp_2_3 != 0) {
                temp_2_4 = CharaGetAi_214a10(temp_2_3);
                if (temp_2_4 != 0) {
                    AiAllySuggestClear_2bb9a0(temp_2_4);
                    var_19 = 1;
                }
            }
        }
        var_18 += 1;
    }
    if (var_19) {
        FieldHudAllySuggestCancel_203c80();
    }
    return 1;
}
